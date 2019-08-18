#include <optional>
#include <netinet/in.h>
#include <iostream>
#include <ctime>
#include <pcap.h>
#include "ARPSessionAdaptor.cpp"
#include "ARPSpoofingInterface.cpp"
#include "../NetFuncs.cpp"

class SessionARPSpoofing: ARPSpoofingInterface {
private:
    NetFuncs* netFuncs;
    std::pair<uint8_t*, uint8_t*>* sessionList;

    ARPSessionAdaptor* arpSessionAdaptor;
public:
    explicit SessionARPSpoofing(char* netInterface, std::pair<uint8_t*, uint8_t*>* sessionList):
    netFuncs(new NetFuncs(netInterface)), sessionList(sessionList), arpSessionAdaptor(new ARPSessionAdaptor(netInterface)) {}

    void buildSessions() override {
        std::cout << "INFO: Start scanning sender clients..." << std::endl;

        char errBuf[PCAP_ERRBUF_SIZE];
        pcap_t* handle = pcap_open_live(this->netFuncs->getNetworkInterface(), BUFSIZ, 1, 1000, errBuf);
        auto go = true;
        while (go) {
            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(handle, &header, &packet);

            auto arpHeader = this->processARPPacket(packet);

            if (arpHeader) {
                if (this->arpSessionAdaptor->addSession(*arpHeader.value(), true)) {
                    std::cout << "INFO: Collected ARP sender: " << arpHeader.value()->sender_ip << std::endl;
                    go = false;
                }
            }
        }

        std::cout << "INFO: Success scanning sender clients" << std::endl;
    }

    void startARPSpoofing(int sessionTime) override {
        std::cout << "INFO: Start ARP-Spoofing ..." << std::endl;

        auto startTime = std::time(nullptr);

        bool go = true;
        while (go) {
            if (startTime < std::time(nullptr)) go = false;
            auto session = this->arpSessionAdaptor->getSession({});
            if (session) session.value()->recivePacket(nullptr);
        }

        std::cout << "INFO: End ARP-Spoofing::TimeOut" << std::endl;
    }
private:
    std::optional<ARPHeader*> processARPPacket(const uint8_t *packet) {
        auto *etherHeader = (EtherHeader *) packet;
        if (ntohs(etherHeader->type) == ETHER_TYPE_ARP) {
            auto *arpHeader = (ARPHeader *) (packet + sizeof(EtherHeader));
            if (arpHeader->op_code == ARP_OPCODE_REPLY) {
                return (const std::optional<ARPHeader *> &) packet;
            }
        }
        return {};
    }

    void replyARP(pcap_t *pPacket) {
    }

    void relayIPPacket(pcap_t *pPacket) {

    }
};