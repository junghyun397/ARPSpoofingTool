#pragma once

#include <vector>
#include "ARPSession.cpp"
#include "../NetworkHeader.h"

class ARPSessionManager {
private:
    char* netInetrface;

    std::vector<ARPSession> sessionList;
    int sessionCount;

    int maxSessions;
public:
    ARPSessionManager(char* netInetrface, uint maxSessions=128):
            netInetrface(netInetrface), maxSessions(maxSessions) {
        this->sessionCount = 0;
    }

    bool addSession(ARPHeader arpHeader) {
        if (this->maxSessions <= this->sessionCount) return false;

        uint8_t* virtualMac;
        virtualMac = {};

        auto agent = ARPSession(arpHeader.sender_ip, arpHeader.target_ip,
                                arpHeader.sender_mac, arpHeader.target_mac, virtualMac);
        this->sessionCount++;
        this->sessionList.resize(this->sessionCount);
        this->sessionList[this->sessionCount] = agent;
        return true;
    }

    int sendARPPacket() {
        int success = 0;
        for (ARPSession agent: this->sessionList) success += agent.sendARPPacket();
        return success;
    }
};
