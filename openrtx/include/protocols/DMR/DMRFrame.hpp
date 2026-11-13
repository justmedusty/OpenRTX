
#ifndef DMR_FRAME_H
#define DMR_FRAME_H

#include <cstdint>
#include <cstddef>
#include <array>
#include <vector>
#include <string.h>

namespace DMR {

    struct DmrHeader {
        uint16_t colorCode;
        uint16_t destinationId;
        uint16_t sourceId;
        uint8_t  frameType; // Voice, Data, SMS, etc.
    };

    class DmrFrame {
    public:
        DmrFrame() { clear(); }

        void clear() {
            payload.fill(0);
            memset(&header, 0, sizeof(header));
        }

        // DMR frames are approx 48 bits of header + payload
        void setPayload(const uint8_t* data, size_t len) {
            for(size_t i = 0; i < len && i < payload.size(); ++i) {
                payload[i] = data[i];
            }
        }

        uint8_t* data() { return payload.data(); }

    private:
        DmrHeader header;
        std::array<uint8_t, 120> payload; // Adjusted for DMR data slot size
    };

} // namespace DMR
#endif
