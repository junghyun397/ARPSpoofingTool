#pragma once

#ifndef ARPSpoofingTool_NETWORKHEADER_H
#define ARPSpoofingTool_NETWORKHEADER_H

#include <cstdint>

const uint16_t ETHER_TYPE_ARP           = 0x0806;
const uint16_t ETHER_TYPE_IPV4          = 0x0800;

const uint16_t ARP_PROTOCOL_TYPE_IPV4   = 0x0800;
const uint16_t ARP_OPCODE_REPLY         = 0x0020;

struct EtherHeader {
    uint8_t d_host[6];
    uint8_t s_host[6];
    uint16_t type;
};

struct IPHeader{
    uint8_t ver4_hlen4;
    uint8_t DSF;
    uint16_t total_len;
    uint16_t id;
    uint16_t frag_offset;
    uint8_t ttl;
    uint8_t protocol_type;
    uint16_t h_checksum;
    uint32_t src_ip;
    uint32_t dst_ip;
};

struct ARPHeader {
    uint16_t hardware_type;
    uint16_t protocol_type;
    uint8_t hardware_size;
    uint8_t protocol_size;
    uint16_t op_code;
    uint8_t sender_mac[6];
    uint8_t sender_ip[4];
    uint8_t target_mac[6];
    uint8_t target_ip[4];
};

union ProcessAblePacket {
    ARPHeader* arpHeader;
    u_char* packet;
};

#endif
