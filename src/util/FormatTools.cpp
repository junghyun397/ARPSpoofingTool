#pragma once

#include <optional>
#include <arpa/inet.h>

class FormatTools {
public:
    static std::optional<uint8_t*> strToIP(char* strIP) {
        uint8_t ip[4];
        try {
            inet_pton(AF_INET, strIP, ip);
            return ip;
        } catch (error_t error) {
            return {};
        }
    }

    static std::optional<char*> ipToStr(uint8_t* ip) {
        char rsStr[15];
        try {
            inet_ntop(AF_INET, &(ip), rsStr, INET_ADDRSTRLEN);
            return rsStr;
        } catch (error_t error) {
            return {};
        }
    }

    static std::optional<int> strToInt(char* strNum) {
        try {
            return std::stoi(strNum);
        } catch (error_t error) {
            return {};
        }
    }

    static bool equalIPAddress(const uint8_t* ip1, const uint8_t* ip2) {
        return (ip1[3] == ip2[3] and ip1[2] == ip2[2]
            and ip1[1] == ip2[1] and ip1[0] == ip2[0]);
    }

    static bool equalMACAddress(const uint8_t* mac1, const uint8_t* mac2) {
        return (mac1[5] == mac2[5] and mac1[4] == mac2[4]
            and mac1[3] == mac2[3] and mac1[2] == mac2[2]
            and mac1[1] == mac2[1] and mac1[0] == mac2[0]);
    }

    static void fillVirtualMac(uint8_t* virtualMac) {
        for(int i = 0; i < 6; i++) virtualMac[i] = random();
    }

};