#pragma once

#include <iostream>
#include <unistd.h>
#include "IBaseARPSpoofing.cpp"

class BroadcastARPSpoofing: public IBaseARPSpoofing {
private:
    int sendFeq = 0;

    u_char* buildBroadcastARPAttackPacket() {
        return nullptr;
    }
public:
    explicit BroadcastARPSpoofing(char *networkInterface, int sendFeq):
            IBaseARPSpoofing(networkInterface), sendFeq(sendFeq) {}

    void startARPSpoofing(int sessionTime) override {
        this->setUpTimer(sessionTime);

        auto packet = buildBroadcastARPAttackPacket();

        uint seq = 0;
        while (this->isAlive()) {
            seq++;
            pcap_sendpacket(this->pcapHandle, packet, 0);
            std::cout << "INFO: send broadcast ARP-Spoofing; seq: " << seq << std::endl;
            sleep(this->sendFeq);
        }
    }
};
