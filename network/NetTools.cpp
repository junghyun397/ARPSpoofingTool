#pragma once

#include <optional>

class NetTools {
private:
    static uint8_t myIP;

public:
    static std::optional<uint8_t*> strToIP(char *string) {
        uint8_t ip[4];
        return {};
    }

    static std::optional<char*> ipToStr(uint8_t *ip) {
        char strIP[15];
        return {};
    }

    static uint8_t* findGateway() {
        uint8_t gatewayIP[4];
        return gatewayIP;
    }

    static uint8_t* findMyIP() {
        return {};
    }

    static uint8_t* findMyMac() {
        return {};
    }

    static bool equalIPAddress(uint8_t* ip1, uint8_t* ip2) {
        return false;
    }

    static bool equalMacAddress(uint8_t* mac1, uint8_t mac2) {
        return false;
    }
};

