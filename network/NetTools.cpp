#pragma once

#include <optional>
#include <cstring>

class NetTools {
public:
    static std::optional<uint8_t*> strToIP(char *strIP) {
        char* uintIP[1];
        return {};
    }

    static std::optional<char*> ipToStr(uint8_t *ip) {
        return {};
    }

    static bool equalIPAddress(uint8_t* ip1, uint8_t* ip2) {
        return memcmp(ip1, ip2, sizeof(&ip1));
    }

    static bool equalMacAddress(uint8_t* mac1, uint8_t* mac2) {
        return memcmp(mac1, mac2, sizeof(&mac1));
    }
};