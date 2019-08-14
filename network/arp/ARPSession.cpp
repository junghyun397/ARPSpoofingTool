#pragma once

#include <cstdint>
#include <pcap.h>

class ARPSession {
private:
    uint8_t* senderIP;
    uint8_t* targetIP;

    uint8_t* senderMAC;
    uint8_t* targetMAC;

    uint8_t* virtualMAC;

    pcap_t* packet = nullptr;
    uint8_t* targetPacket = nullptr;

    void buildPacket() {
        this->packet = nullptr;
        this->targetPacket = nullptr;
    }

    void relayPacket(pcap_t* rPacket) {

    }
public:
    ARPSession(uint8_t* senderIP, uint8_t* targetIP, uint8_t* senderMAC, uint8_t* targetMAC, uint8_t* virtualMAC):
    senderIP(senderIP), targetIP(targetIP), senderMAC(senderMAC), targetMAC(targetMAC), virtualMAC(virtualMAC) {
        this->buildPacket();
    }

    void recivePacket() {
    }

    int sendARPRequestPacket() {
        return 0;
    }

    int sendARPPacket() {
        return pcap_sendpacket(this->packet, this->targetPacket, sizeof(this->packet));
    }

    uint8_t* getSenderMacAddress() {
        return this->senderMAC;
    }
};