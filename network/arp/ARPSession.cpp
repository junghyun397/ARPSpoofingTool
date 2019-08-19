#pragma once

#include <cstdint>
#include <pcap.h>
#include "../NetworkHeader.h"

class ARPSession {
private:
    uint8_t* senderIP;
    uint8_t* targetIP;

    uint8_t* senderMAC;
    uint8_t* targetMAC;

    uint8_t* virtualMAC;

    bool setRelayPacket;

    pcap_t* packet = nullptr;
    uint8_t* targetPacket = nullptr;

    void buildPacket() {
        this->packet = nullptr;
        this->targetPacket = nullptr;
    }

    void relayPacket(u_char* tPacket) {

    }
public:
    ARPSession(uint8_t* senderIP, uint8_t* targetIP, uint8_t* senderMAC, uint8_t* targetMAC,
            uint8_t* virtualMAC, bool setRelayPacket):
            senderIP(senderIP), targetIP(targetIP), senderMAC(senderMAC), targetMAC(targetMAC),
            virtualMAC(virtualMAC), setRelayPacket(setRelayPacket){
        this->buildPacket();
    }

    void reciveARPPacket(ARPHeader *arpHeader) {
    }

    void recivePacket(u_char* rPacket) {
        if (this->setRelayPacket) relayPacket(rPacket);
    }

    uint8_t* getSenderMacAddress() {
        return this->senderMAC;
    }
};