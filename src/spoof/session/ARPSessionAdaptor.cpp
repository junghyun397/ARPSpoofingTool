#pragma once

#include <vector>
#include <map>
#include "ARPSession.cpp"
#include "../../util/NetworkHeader.h"
#include "../../util/FormatTools.cpp"

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

    bool addSession(ARPHeader* arpHeader, bool relayPacket=true) {
        if (this->maxSessions <= this->sessionCount or
        this->sessionList.find(arpHeader->sender_mac) == this->sessionList.end()) return false;

        auto session = new ARPSession(arpHeader->sender_ip, arpHeader->target_ip,
                arpHeader->sender_mac, arpHeader->target_mac, FormatTools::buildVirtualMac(), relayPacket);

        this->sessionCount++;
        this->sessionList.insert(std::make_pair(arpHeader->sender_mac, session));
        return true;
    }

    std::optional<ARPSession*> getSession(uint8_t* destMac) {
        if (this->sessionList.count(destMac)) return this->sessionList[destMac];
        return {};
    }
};
