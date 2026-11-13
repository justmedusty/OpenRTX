#ifndef _SMS_H_
#define _SMS_H_



#include <stdint.h>


struct IP_Header {
    uint8_t protocol; //0x45 const
    uint8_t type; // 0x00 const
    uint16_t packet_length; //big endian packet packet_length
    uint16_t sequence_number; // big endian sequence, increment for each new packet
    uint16_t flags; // unused 0x00 const
    uint8_t ttl; // 0x01 const
    uint8_t udp_protocol_identifier; //0x11 const
    uint16_t ip_header_checksum; //BE from RFC 791
    uint32_t source; // Source IP contains the DMR Id of the sender of the message. The first byte is 0x0C for user DMR Id, and the remaining 3 bytes are the DMR Idin big endian order. Ex. 12.0.1.1 for DMR Id 257.
    uint32_t dest; //Dest IP Contains either a user or a group id. The first byte of a group address is 0xE1 and the remaining 3 are Group Id in big endian order. Ex. 225.0.0.1 is group Id 1. User Ids are prefixed with 0x0C
};




struct DMR_Standard_IP_Datagram {
    struct IP_Header header;
    uint16_t udp_source_port; // 0x1398 const for DMR Standard
    uint16_t udp_dest_port;  // 0x1398 const for DMR Standard
    uint16_t udp_data_length; //double byte message length + 12. Ex. “HELLO” would be 5*2+12=22.
    uint16_t udp_checksum; //big endian RFC 768 CRC
    uint8_t start; // 0x00 const
    uint8_t const_1; //0x0D
    uint16_t const_2; //0x00
    uint8_t const_3; //0x0A
    uint8_t const_4; //0x00
    //Text , text len * 2
};































#endif
