#pragma once

#include <vector>
#include "ARPSession.cpp"
#include "../NetworkHeader.h"

class ARPSessionAdaptor {
private:
    char* netInetrface;

    std::vector<ARPSession> sessionList;
    int sessionCount;

    int maxSessions;
public:
    ARPSessionAdaptor(char* netInetrface, uint maxSessions=128):
            netInetrface(netInetrface), maxSessions(maxSessions) {
        this->sessionCount = 0;
    }

    bool addSession(ARPHeader arpHeader) {
        if (this->maxSessions <= this->sessionCount) return false;

        uint8_t virtualMac[6];

        auto session = ARPSession(arpHeader.sender_ip, arpHeader.target_ip,
                                  arpHeader.sender_mac, arpHeader.target_mac, virtualMac);

        this->sessionCount++;
        this->sessionList.reserve(this->sessionCount);
        this->sessionList[this->sessionCount] = session;
        return true;
    }

    int sendARPPacket() {
        int success = 0;
        for (ARPSession agent: this->sessionList) success += agent.sendARPPacket();
        return success;
    }
};
