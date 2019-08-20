#pragma once

#include <cstdint>
#include <pcap.h>
#include "../../NetworkHeader.h"

class ARPSession {
private:
    uint8_t* senderIP;
    uint8_t* targetIP;

    uint8_t* senderMAC;
    uint8_t* targetMAC;

    uint8_t* virtualMAC;

    bool setRelayPacket;

    uint8_t* targetPacket = nullptr;

    void buildPacket() {
        this->targetPacket = nullptr;
    }

    void relayPacket(pcap_t* pcapHandle, u_char* tPacket) {
    }
public:
    ARPSession(uint8_t* senderIP, uint8_t* targetIP, uint8_t* senderMAC, uint8_t* targetMAC,
            uint8_t* virtualMAC, bool setRelayPacket):
            senderIP(senderIP), targetIP(targetIP), senderMAC(senderMAC), targetMAC(targetMAC),
            virtualMAC(virtualMAC), setRelayPacket(setRelayPacket){
        this->buildPacket();
    }

    void receiveARPPacket(pcap_t* pcapHandle, ARPHeader *arpHeader) {
    }

    void receiveIPV4Packet(pcap_t* pcapHandle, u_char* rPacket) {
        if (this->setRelayPacket) relayPacket(pcapHandle, rPacket);
    }
};