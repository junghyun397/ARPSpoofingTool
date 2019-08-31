#pragma once

#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stropts.h>
#include <optional>

#include "../util/NetworkHeader.h"

class NetFuncs {
private:
    char* networkInterface;

    uint8_t* myIP[4];
    uint8_t* myMAC[6];
public:
    explicit NetFuncs(char* networkInterface): networkInterface(networkInterface) {}

    char* getNetworkInterface() {
        return this->networkInterface;
    }

    uint8_t* getMyIP() {
        if (this->myIP[0]) return reinterpret_cast<uint8_t *>(this->myIP);

        struct ifreq ifr{};
        int fd = socket(AF_INET, SOCK_DGRAM, 0);
        ifr.ifr_addr.sa_family = AF_INET;
        strncpy(ifr.ifr_name, this->networkInterface, IFNAMSIZ-1);
        ioctl(fd, SIOCGIFADDR, &ifr);

        memcpy(this->myIP, &(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr), 4);
        close(fd);

        return reinterpret_cast<uint8_t *>(this->myIP);
    }

    uint8_t* getMyMac() {
        if (this->myMAC[0]) return reinterpret_cast<uint8_t *>(this->myMAC);

        struct ifreq ifr{};
        int s = socket(AF_INET, SOCK_STREAM, 0);
        strcpy(ifr.ifr_name, this->networkInterface);
        ioctl(s, SIOCGIFHWADDR, &ifr);

        memcpy(this->myMAC, ifr.ifr_hwaddr.sa_data, 6);
        close(s);

        return reinterpret_cast<uint8_t *>(this->myMAC);
    }

    std::optional<ARPHeader*> findTargetByIP(uint8_t* ip) {
        struct ARPHeader* arpHeader{};


        return arpHeader;
    }
};
