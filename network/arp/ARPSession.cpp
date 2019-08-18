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

    bool setRelayPacket;

    pcap_t* packet = nullptr;
    uint8_t* targetPacket = nullptr;

    void buildPacket() {
        this->packet = nullptr;
        this->targetPacket = nullptr;
    }

    void relayPacket(pcap_t *tPacket) {

    }
public:
    ARPSession(uint8_t* senderIP, uint8_t* targetIP, uint8_t* senderMAC, uint8_t* targetMAC,
            uint8_t* virtualMAC, bool setRelayPacket):
            senderIP(senderIP), targetIP(targetIP), senderMAC(senderMAC), targetMAC(targetMAC),
            virtualMAC(virtualMAC), setRelayPacket(setRelayPacket){
        this->buildPacket();
    }

    void recivePacket(pcap_t *rPacket) {
        if (this->setRelayPacket) relayPacket(rPacket);
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