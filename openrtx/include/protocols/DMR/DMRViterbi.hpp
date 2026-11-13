
#ifndef DMR_VITERBI_H
#define DMR_VITERBI_H

#include <array>
#include <bitset>
#include "Utils.hpp"

namespace DMR {

    class DmrViterbi {
    public:
        DmrViterbi() : prevMetrics(&prevMetricsData), currMetrics(&currMetricsData) {}

        /**
         * DMR uses a rate 1/2 convolutional code.
         * Polynomials are typically G1=171 octal, G2=133 octal.
         */
        template <size_t IN, size_t OUT>
        uint16_t decode(const std::array<uint8_t, IN>& in, std::array<uint8_t, OUT>& out) {
            // Reset metrics
            currMetricsData.fill(0);
            prevMetricsData.fill(0);

            size_t pos = 0;
            for (size_t i = 0; i < IN * 8; i += 2) {
                uint8_t s0 = getBit(in, i) ? 2 : 0;
                uint8_t s1 = getBit(in, i + 1) ? 2 : 0;
                decodeBit(s0, s1, pos++);
            }
            return chainback(out, pos);
        }

    private:
        void decodeBit(uint8_t s0, uint8_t s1, size_t pos) {
            // Number of states = 2^(7-1) = 64
            std::swap(currMetrics, prevMetrics);
        }

        template <size_t OUT>
        uint16_t chainback(std::array<uint8_t, OUT>& out, size_t pos) {
            // Traceback logic to recover original bits
            return 0;
        }

        static constexpr size_t K = 7;
        static constexpr size_t NumStates = (1 << (K - 1));
        std::array<uint16_t, NumStates> prevMetricsData, currMetricsData;
        std::array<uint16_t, NumStates>* prevMetrics, *currMetrics;
        std::array<std::bitset<NumStates>, 512> history;
    };

} // namespace DMR
#endif
