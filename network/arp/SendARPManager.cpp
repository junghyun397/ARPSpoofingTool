#pragma once

#include <iostream>
#include "SendARPAgent.cpp"
#include "../NetworkHeader.h"

class SendARPManager {
private:
    SendARPAgent* agentList[256]{};
    int maxAgents;

    int agentCount = 0;
public:
    explicit SendARPManager(uint maxAgents=128) {
        this->maxAgents = maxAgents;
    }

    bool addARPTarget(ARPHeader *arpHeader) {
        if (this->maxAgents < this->agentCount)
            return false;
        auto agent = SendARPAgent(arpHeader->sender_ip, arpHeader->target_ip,
                                  arpHeader->sender_mac, arpHeader->target_mac);
        this->agentList[agentCount] = &agent;
        this->agentCount++;
        return true;
    }

    void sendARPPacket() {
        int success = 0;
        for (SendARPAgent *agent: this->agentList) success += agent->sendARPPacket();
        std::cout << "Success send ARP Packet: " << success << " victims" << std::endl;
    }
};
