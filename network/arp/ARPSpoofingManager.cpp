#pragma once

#include <optional>
#include "../NetFuncs.cpp"
#include "../NetworkHeader.h"

class ARPSpoofingManager {
protected:
    NetFuncs* netFuncs;

    std::optional<std::pair<int, ProcessAblePacket>> processPacket(const uint8_t *packet) {
        auto *etherHeader = (EtherHeader*) packet;
        switch (ntohs(etherHeader->type)) {
            union ProcessAblePacket processAblePacket;
            case ETHER_TYPE_ARP:
                processAblePacket.arpHeader = (ARPHeader*) (packet + sizeof(EtherHeader));
                return std::make_pair(ETHER_TYPE_ARP, processAblePacket);
                break;
            case ETHER_TYPE_IPV4:
                processAblePacket.packet = const_cast<uint8_t *>(packet);
                return std::make_pair(ETHER_TYPE_IPV4, processAblePacket);
                break;
        }
        return {};
    }
public:
    ARPSpoofingManager(char* networkInterface): netFuncs(new NetFuncs(networkInterface)) {}

    static const int UNLIMITED = 0;

    virtual void buildSessions() = 0;
    virtual void startARPSpoofing(int sessionTime) = 0;
};