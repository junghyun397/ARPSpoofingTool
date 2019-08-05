#pragma once

#include <cstdint>
#include <iostream>
#include <pcap.h>

class SendARPAgent {
private:
    uint8_t* senderIP;
    uint8_t* targetIP;

    uint8_t* senderMAC;
    uint8_t* targetMAC;

    pcap_t* packet = nullptr;
    uint8_t* targetPacket{};

    void buildPacket() {
        this->targetPacket = nullptr;
        std::cout << "Build...?" << std::endl;
    }
public:
    SendARPAgent(uint8_t* senderIP, uint8_t* targetIP, uint8_t* senderMAC, uint8_t* targetMAC):
    senderIP(senderIP), targetIP(targetIP), senderMAC(senderMAC), targetMAC(targetMAC) {
        this->buildPacket();
    }

    int sendARPPacket() {
        return pcap_sendpacket(this->packet, this->targetPacket, sizeof(this->packet));
    }

    uint8_t* getSenderMacAddress() {
        return this->senderMAC;
    }
};