#pragma once

#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <cstdio>

class NetFuncs {
private:
    char* networkInterface;

    uint8_t* myIP;
    uint8_t* myMAC;

    uint8_t* gatewayIP;
    uint8_t* gatewayMAC;
public:
    NetFuncs(char* networkInterface): networkInterface(networkInterface) {
    }

    char* getNetworkInterface() {
        return this->networkInterface;
    }

    uint8_t* getGatewayIP() {
        if (this->gatewayIP) return this->gatewayIP;
        return this->gatewayMAC;
    }

    uint8_t* getGatewayMAC() {
        if (this->gatewayMAC) return this->gatewayMAC;
        return this->gatewayMAC;
    }

    uint8_t* getMyIP() {
        if (this->myIP) return this->myIP;
        return this->myIP;
    }

    uint8_t* getMyMac() {
        if (this->myMAC) return this->myMAC;

        char tMAC[18]="";
        char ifPath[256]="/sys/class/net/";
        strcat(ifPath, this->networkInterface);
        strcat(ifPath, "/address");
        FILE *if_f =fopen(ifPath, "r");
        fread(tMAC, 1, 17, if_f);
        fclose(if_f);

        return this->myMAC;
    }

    void fillVirtualMac(uint8_t* virtualMac) {
        for(int i = 0; i < 6; i++) virtualMac[i] = random();
    }

};
