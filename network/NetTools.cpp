#pragma once

#include <stdint-gcc.h>
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
        return {};
    }

    static uint8_t* findMyIP() {
        return {};
    }

    static uint8_t* findMyMac() {
        return {};
    }
};

