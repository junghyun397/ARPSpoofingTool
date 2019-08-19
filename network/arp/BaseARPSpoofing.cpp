#pragma once

#include <optional>
#include <ctime>
#include <netinet/in.h>
#include <pcap/pcap.h>
#include "../NetFuncs.cpp"
#include "../NetworkHeader.h"

class BaseARPSpoofing {
private:
    int endTime = 0;
protected:
    NetFuncs* netFuncs;
    pcap_t* pcapHandle;

    std::optional<std::pair<uint16_t, ProcessAblePacket>> processPacket(const u_char* packet) {
        auto *etherHeader = (EtherHeader*) packet;
        switch (ntohs(etherHeader->type)) {
            union ProcessAblePacket processAblePacket;
            case ETHER_TYPE_ARP:
                processAblePacket.arpHeader = (ARPHeader*) (packet + sizeof(EtherHeader));
                return std::make_pair(ETHER_TYPE_ARP, processAblePacket);
                break;
            case ETHER_TYPE_IPV4:
                processAblePacket.packet = const_cast<u_char *>(packet);
                return std::make_pair(ETHER_TYPE_IPV4, processAblePacket);
                break;
        }
        return {};
    }

    void setUpTimer(int sessionTime) {
        if (sessionTime != SESSION_TIME_UNLIMITED) this->endTime = std::time(nullptr) + sessionTime;
    }

    bool isAlive() {
        return !(this->endTime < std::time(nullptr)
                 and this->endTime != BaseARPSpoofing::SESSION_TIME_UNLIMITED);
    }
public:
    explicit BaseARPSpoofing(char* networkInterface): netFuncs(new NetFuncs(networkInterface)) {}

    static const int SESSION_TIME_UNLIMITED = 0;
    static const int SESSION_TIME_1M        = 60;
    static const int SESSION_TIME_10M       = 600;
    static const int SESSION_TIME_1H        = 3600;

    void buildPCAPHandle() {
        char errBuf[PCAP_ERRBUF_SIZE];
        this->pcapHandle = pcap_open_live(this->netFuncs->getNetworkInterface(), BUFSIZ, 1, 1000, errBuf);
    }

    virtual void startARPSpoofing(int sessionTime) = 0;
};