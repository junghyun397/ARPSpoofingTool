
#include <cstdint>
#include <iostream>
#include <pcap.h>

class SendARPAgent {
private:
    uint8_t* sender_ip;
    uint8_t* target_ip;

    uint8_t* sender_mac;
    uint8_t* target_mac;

    pcap_t* packet = nullptr;
    uint8_t target_packet[42];

    void buildPacket() {
        std::cout << "Build...?" << std::endl;
    }
public:
    SendARPAgent(uint8_t* senderIP, uint8_t* targetIP, uint8_t* senderMac, uint8_t* targetMac) {
        this->sender_ip = senderIP;
        this->target_ip = targetIP;
        this->sender_mac = senderMac;
        this->target_mac = targetMac;
        this->buildPacket();
    }

    int sendARPPacket() {
        return pcap_sendpacket(this->packet, this->target_packet, sizeof(this->packet));
    }

    uint8_t* getSenderMacAddress() {
        return this->sender_mac;
    }
};
