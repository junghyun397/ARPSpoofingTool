#pragma once

#include <vector>
#include <map>
#include "ARPSession.cpp"
#include "../NetworkHeader.h"

class ARPSessionAdaptor {
private:
    char* netInterface;

    std::map<uint8_t*, ARPSession*> sessionList;
    int sessionCount;

    int maxSessions;
public:
    explicit ARPSessionAdaptor(char* netInterface, uint maxSessions=128):
            netInterface(netInterface), maxSessions(maxSessions) {
        this->sessionCount = 0;
    }

    bool addSession(ARPHeader arpHeader, bool relayPacket=true) {
        if (this->maxSessions <= this->sessionCount or
        this->sessionList.find(arpHeader.sender_ip) == this->sessionList.end()) return false;

        uint8_t virtualMac[6];

        auto session = new ARPSession(arpHeader.sender_ip, arpHeader.target_ip,
                                  arpHeader.sender_mac, arpHeader.target_mac, virtualMac, relayPacket);

        this->sessionCount++;
        this->sessionList.insert(std::make_pair(arpHeader.sender_ip, session));
        return true;
    }

    std::optional<ARPSession*> getSession(uint8_t* tempIP) {
        if (this->sessionList.find(tempIP) == this->sessionList.end()) return {};
        return this->sessionList[tempIP];
    }
};
