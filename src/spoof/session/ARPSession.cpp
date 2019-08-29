#pragma once

#include <cstdint>
#include <pcap.h>
#include "../../util/NetworkHeader.h"

class ARPSession {
private:
    uint8_t* senderIP;
    uint8_t* targetIP;

    uint8_t* senderMAC;
    uint8_t* targetMAC;

    uint8_t* virtualMAC;

    bool setRelayPacket;

    u_char* arpRequestPacket = nullptr;

    void buildPacket() {
        struct EtherHeader etherHeader{};
        struct ARPHeader arpHeader{};
    }

    void sendARPRequestPacket(pcap_t* pcapHandle, uint8_t* ip) {

    }

    void sendARPReplyPacket(pcap_t* pcapHandle, ARPHeader *arpHeader) {

    }

    void relayPacket(pcap_t* pcapHandle, u_char* rPacket) {

    }
public:
    ARPSession(uint8_t* senderIP, uint8_t* targetIP, uint8_t* senderMAC, uint8_t* targetMAC,
            uint8_t* virtualMAC, bool setRelayPacket):
            senderIP(senderIP), targetIP(targetIP), senderMAC(senderMAC), targetMAC(targetMAC),
            virtualMAC(virtualMAC), setRelayPacket(setRelayPacket){
        this->buildPacket();
    }

    void receiveARPRequestPacket(pcap_t* pcapHandle, ARPHeader *arpHeader) {
        this->sendARPReplyPacket(pcapHandle, arpHeader);
    }

    void receiveIPV4Packet(pcap_t* pcapHandle, u_char* rPacket) {
        if (this->setRelayPacket) this->relayPacket(pcapHandle, rPacket);
    }

    uint8_t* getSenderMAC() {
        return this->senderMAC;
    }
};