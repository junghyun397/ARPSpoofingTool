#pragma once

#include "SendARPAgent.cpp"
#include "../NetworkHeader.h"

class SendARPManager {
private:
    SendARPAgent* agentList[256]{};
    int agentCount;

    int maxAgents;
public:
    explicit SendARPManager(uint maxAgents=128): maxAgents(maxAgents) {
        this->agentCount = 0;
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

    int sendARPPacket() {
        int success = 0;
        for (SendARPAgent *agent: this->agentList) success += agent->sendARPPacket();
        return success;
    }
};
