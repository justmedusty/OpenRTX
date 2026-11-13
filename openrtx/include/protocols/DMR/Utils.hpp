#ifndef DMR_UTILS_H
#define DMR_UTILS_H

#include <cstdint>
#include <cstddef>
#include <array>

namespace DMR {

    /**
     * DMR 4FSK Symbol mapping.
     * DMR symbols are typically mapped to frequency deviations:
     * +3: +1.875kHz, +1: +0.625kHz, -1: -0.625kHz, -3: -1.875kHz
     */
    inline std::array<int8_t, 4> byteToSymbols(uint8_t value) {
        static constexpr int8_t LUT[] = { +1, +3, -1, -3 };
        std::array<int8_t, 4> symbols;
        for(int i = 0; i < 4; ++i) {
            symbols[i] = LUT[(value >> (i * 2)) & 0x03];
        }
        return symbols;
    }

    /**
     * Utility function allowing to retrieve the value of a single bit from an array
     * of bytes. Bits are counted scanning from left to right, thus bit number zero
     * is the leftmost bit of array[0].
     *
     * @param array: byte array.
     * @param pos: bit position inside the array.
     * @return value of the indexed bit, as boolean variable.
     */
    template < size_t N >
    inline bool getBit(const std::array< uint8_t, N >& array, const size_t pos)
    {
        size_t i = pos / 8;
        size_t j = pos % 8;
        return (array[i] >> (7 - j)) & 0x01;
    }


    /**
     * Utility function allowing to set the value of a single bit from an array
     * of bytes. Bits are counted scanning from left to right, thus bit number zero
     * is the leftmost bit of array[0].
     *
     * @param array: byte array.
     * @param pos: bit position inside the array.
     * @param bit: bit value to be set.
     */
    template < size_t N >
    inline void setBit(std::array< uint8_t, N >& array, const size_t pos,
                       const bool bit)
    {
        size_t i     = pos / 8;
        size_t j     = pos % 8;
        uint8_t mask = 1 << (7 - j);
        array[i] = (array[i] & ~mask) |
        (bit ? mask : 0x00);
    }


} // namespace DMR
#endif
