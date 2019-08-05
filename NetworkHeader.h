#ifndef BOB_ARP_SEND_NETWORKHEADER_H
#define BOB_ARP_SEND_NETWORKHEADER_H

#include <cstdint>

const uint16_t ETHER_TYPE_ARP = 0x0806;

const uint16_t ARP_PROTOCOL_TYPE_IPV4 = 0x0800;
const uint16_t ARP_OPCODE_REPLY = 0x0020;

struct EtherHeader {
    uint8_t d_host[6];
    uint8_t s_host[6];
    uint16_t type;
};

struct ARPHeader {
    uint16_t hardware_type;
    uint16_t protocol_type;
    uint8_t hardware_size;
    uint8_t protocol_size;
    uint16_t opcode;
    uint8_t sender_mac[6];
    uint8_t sender_ip[4];
    uint8_t target_mac[6];
    uint8_t target_ip[4];
};

#endif
