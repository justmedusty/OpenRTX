#ifndef _DMR_PACKET_H
#define _DMR_PACKET_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

/*
     * DMR Data Types
     */
enum DMR_Data_Type {
    PRIVACY_INDICATOR =
        0,               // Privacy Indicator information in a standalone burst
    VOICE_LC,            // Indicates the beginning of voice transmission
    TERMINATOR_WITH_LC,  // Indicates the end of transmission
    CSBK,                // Carries a control block
    MULTI_BLOCK_CONTROL, // Header for multi-block control
    MULTI_BLOCK_CONT_CONT, // Follow-on blocks for multi-block control
    DATA,          // Carries addressing and numbering of packet data blocks
    RATE12_DATA,   // Payload for rate 1/2 packet data
    RATE34_DATA,   // Payload for rate 3/4 packet data
    IDLE,          // Fills channel when no info to transmit
    VOICE_BURST_A, // Burst A marks the start of a superframe
    VOICE_BURST_B, // Bursts B to F carry embedded signalling
    VOICE_BURST_C,
    VOICE_BURST_D,
    VOICE_BURST_E,
    VOICE_BURST_F,
    IPSC_SYNC,
    UNKNOWN_SLOT_TYPE,
    DATA_TYPE_MAX // Useful for array bounds checking
};

/*
         *  String Mappings for DMR_Data_Type
         */
static const char *const DataTypeName[] = {
    [PRIVACY_INDICATOR] = "privacy indicator",
    [VOICE_LC] = "voice LC",
    [TERMINATOR_WITH_LC] = "terminator with LC",
    [CSBK] = "control block",
    [MULTI_BLOCK_CONTROL] = "multi-block control",
    [MULTI_BLOCK_CONT_CONT] = "multi-block control follow-on",
    [DATA] = "data",
    [RATE12_DATA] = "rate ½ packet data",
    [RATE34_DATA] = "rate ¾ packet data",
    [IDLE] = "idle",
    [VOICE_BURST_A] = "voice (burst A)",
    [VOICE_BURST_B] = "voice (burst B)",
    [VOICE_BURST_C] = "voice (burst C)",
    [VOICE_BURST_D] = "voice (burst D)",
    [VOICE_BURST_E] = "voice (burst E)",
    [VOICE_BURST_F] = "voice (burst F)",
    [IPSC_SYNC] = "IPSC sync",
    [UNKNOWN_SLOT_TYPE] = "unknown"
};

/**
     * Call Type
     */
enum DMR_Call_Type { CALL_TYPE_PRIVATE = 0, CALL_TYPE_GROUP, CALL_TYPE_MAX };

// String mapping for DMR_Call_Type
static const char *const CallTypeName[] = { [CALL_TYPE_PRIVATE] = "private",
                                            [CALL_TYPE_GROUP] = "group" };

/**
     * Packet represents a frame transported by the Air Interface (TS 102 361-1 , TS 102 361-3)
     */
struct DMR_Packet {
    // 0 for slot 1, 1 for slot 2
    uint8_t timeslot;

    // Starts at zero for each incoming transmission, wraps at 256
    uint8_t sequence;

    // Source and destination DMR ID
    uint32_t src_id;
    uint32_t dst_id;

    // 3 bytes registered DMR-ID for public repeaters, 4 bytes for private repeaters
    uint32_t repeater_id;

    // Identifies a stream from PTT-press to PTT-release
    uint32_t stream_id;

    // Data Type or Slot type
    DMR_Data_Type data_type;

    // 0 for group call, 1 for unit to unit
    DMR_Call_Type call_type;

    // The on-air DMR data (34 bytes)
    uint8_t data[34];

    // The raw bits (264 bits / 8 = 33 bytes)
    uint8_t bits[33];
};

#ifdef __cplusplus
}
#endif

#endif
