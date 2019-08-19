#pragma once

#include <optional>
#include <netinet/in.h>
#include <iostream>
#include <ctime>
#include <pcap.h>
#include "ARPSessionAdaptor.cpp"
#include "ARPSpoofingManager.cpp"
#include "../NetFuncs.cpp"

class SessionARPSpoofing: public ARPSpoofingManager {
private:
    std::pair<uint8_t*, uint8_t*>* sessionList;

    ARPSessionAdaptor* arpSessionAdaptor;
public:
    explicit SessionARPSpoofing(char *networkInterface,
                                std::pair<uint8_t *, uint8_t *> *sessionList):
            ARPSpoofingManager(networkInterface), sessionList(sessionList),
            arpSessionAdaptor(new ARPSessionAdaptor(networkInterface)) {}

    void buildSessions() override {
        std::cout << "INFO: Start scanning sender clients..." << std::endl;

        char errBuf[PCAP_ERRBUF_SIZE];
        pcap_t* handle = pcap_open_live(this->netFuncs->getNetworkInterface(), BUFSIZ, 1, 1000, errBuf);
        auto go = true;
        while (go) {
            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(handle, &header, &packet);
        }

        std::cout << "INFO: Success scanning sender clients" << std::endl;
    }

    void startARPSpoofing(int sessionTime) override {
        std::cout << "INFO: Start ARP-Spoofing ..." << std::endl;

        auto startTime = std::time(nullptr);

        bool go = true;
        while (go) {
            if (startTime < std::time(nullptr)) go = false;
            auto session = this->arpSessionAdaptor->getSession({});
            if (session) session.value()->recivePacket(nullptr);
        }

        std::cout << "INFO: End ARP-Spoofing::TimeOut" << std::endl;
    }
private:
    void replyARP(pcap_t *pPacket) {
    }

    void relayIPPacket(pcap_t *pPacket) {
    }
};
