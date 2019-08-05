#include <iostream>
#include <pcap/pcap.h>
#include <netinet/in.h>
#include "NetworkHeader.h"
#include "SendARPManager.cpp"

auto sendArpManager = SendARPManager();

char* netInterface;
uint8_t* senderIp;
uint8_t* targetIp;

uint8_t* strToIP(char *string) {
    return nullptr;
}

bool getIsBroadcast(char *string) {
    return false;
}

int main(int argc, char* argv[]) {
    netInterface = argv[0];
    senderIp = strToIP(argv[1]);
    targetIp = strToIP(argv[2]);
}

ARPHeader * findARPPacket(const uint8_t *packet) {
    auto *etherHeader = (EtherHeader *) packet;
    if (ntohs(etherHeader->type) == ETHER_TYPE_ARP) {
        auto *arpHeader = (ARPHeader *) (packet + sizeof(EtherHeader));
        if (arpHeader->opcode == ARP_OPCODE_REPLY) {

        }
    }
    return nullptr;
}

void collectTargets() {
    char errBuf[PCAP_ERRBUF_SIZE];

    pcap_t* handle = pcap_open_live(netInterface, BUFSIZ, 1, 1000, errBuf);
    auto go = true;
    while (go) {
        struct pcap_pkthdr* header;
        const u_char* packet;
        pcap_next_ex(handle, &header, &packet);

        auto arp_header = findARPPacket(packet);
        std::cout << "Collected ARP Target: " << "some..." << std::endl;
        sendArpManager.addARPTarget(arp_header);
    }
}

void startSendARPPacket() {
    auto run = true;
    while (run) {
        sendArpManager.sendARPPacket();
    }
}
