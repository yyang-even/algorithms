#include "common_header.h"


namespace {

/** Merge bits from two values according to a mask
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Merge bits from two values according to a mask
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * @param mask  1 where bits from b should be selected; 0 where from a.
 */
inline constexpr unsigned
MaskedBitsMerge(const unsigned a, const unsigned b, const unsigned mask) {
    return a ^ ((a ^ b) & mask);
}

}//namespace


SIMPLE_BENCHMARK(MaskedBitsMerge, Sample1, 0b0110, 0b1101, 0b1010);
SIMPLE_BENCHMARK(MaskedBitsMerge, Sample2, 0b0110, 0b1101, 0b1010);

SIMPLE_TEST(MaskedBitsMerge, TestSample1, 0b1100, 0b0110, 0b1101, 0b1010);
SIMPLE_TEST(MaskedBitsMerge, TestSample2, 0b0100, 0b1110, 0b0001, 0b1010);
