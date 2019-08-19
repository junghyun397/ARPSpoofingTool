#pragma once

#include <optional>
#include <netinet/in.h>
#include <iostream>
#include <ctime>
#include <pcap.h>
#include "ARPSessionAdaptor.cpp"
#include "BaseARPSpoofing.cpp"
#include "../NetFuncs.cpp"

class SessionARPSpoofing: public BaseARPSpoofing {
private:
    std::pair<uint8_t*, uint8_t*>* sessionList;

    ARPSessionAdaptor* arpSessionAdaptor;
public:
    explicit SessionARPSpoofing(char *networkInterface,
                                std::pair<uint8_t *, uint8_t *> *sessionList):
            BaseARPSpoofing(networkInterface), sessionList(sessionList),
            arpSessionAdaptor(new ARPSessionAdaptor(networkInterface)) {}

    void buildSession() {
        std::cout << "INFO: Start scanning sender clients..." << std::endl;
        auto go = true;
        while (go) {
            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(this->pcapHandle, &header, &packet);
        }

        std::cout << "INFO: Success scanning sender clients" << std::endl;
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
                            session.value()->recivePacket(nPacket.value().second.packet);
                            break;
                    }
                }
            }
        }

        std::cout << "INFO: End ARP-Spoofing::TimeOut" << std::endl;
    }
};
