
#include <iostream>
#include "SendARPAgent.cpp"
#include "NetworkHeader.h"

class SendARPManager {
private:
    SendARPAgent *agentList[128];
    int agentCount = 0;
public:
    void addARPTarget(ARPHeader *arpHeader) {
        auto agent = SendARPAgent(arpHeader->sender_ip, arpHeader->target_ip,
                                  arpHeader->sender_mac, arpHeader->target_mac);
        this->agentList[agentCount] = &agent;
        this->agentCount++;
    }

    void sendARPPacket() {
        int success = 0;
        for (SendARPAgent *agent: this->agentList) success += agent->sendARPPacket();
        std::cout << "Success send ARP Packet: " << success << " victims" << std::endl;
    }
};
