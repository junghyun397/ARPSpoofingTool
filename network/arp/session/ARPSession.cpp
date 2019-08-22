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

    u_char* arpRequestPacket;

    void buildPacket() {
        struct EtherHeader etherHeader;
        struct ARPHeader arpHeader;
    }
public:
    ARPSession(uint8_t* senderIP, uint8_t* targetIP, uint8_t* senderMAC, uint8_t* targetMAC,
            uint8_t* virtualMAC, bool setRelayPacket):
            senderIP(senderIP), targetIP(targetIP), senderMAC(senderMAC), targetMAC(targetMAC),
            virtualMAC(virtualMAC), setRelayPacket(setRelayPacket){
        this->buildPacket();
    }

    uint8_t* getSenderMAC() {
        return this->senderMAC;
    }

    void receiveARPRequestPacket(pcap_t* pcapHandle, ARPHeader *arpHeader) {
        pcap_sendpacket(pcapHandle, this->arpRequestPacket, 0);
    }

    void receiveIPV4Packet(pcap_t* pcapHandle, u_char* rPacket) {
        if (!this->setRelayPacket) return;
        pcap_sendpacket(pcapHandle, rPacket, 0);
    }
};