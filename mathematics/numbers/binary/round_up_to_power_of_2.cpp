#include "common_header.h"

#include "binary.h"
#include "set_all_bits_after_most_significant_bit.h"


namespace {

/** Round up to the next highest power of 2 by float casting
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Round up to the next highest power of 2 by float casting
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Smallest power of 2 greater than or equal to n
 *              https://www.geeksforgeeks.org/smallest-power-of-2-greater-than-or-equal-to-n/
 *
 * So num=3 -> r=4; num=8 -> r=8
 */
constexpr inline unsigned RoundUpToPowerOf2_Float(const uint32_t num) {
    if (num) {
        FloatUnsignedUnion float_unsigned_union{};
        float_unsigned_union.f = static_cast<float>(num);
        const auto temp = 1U << ((float_unsigned_union.u >> 23) - 0x7f);
        return temp << (temp < num);
    } else {
        return 1;
    }
}


/** Round up to the next highest power of 2
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Round up to the next highest power of 2
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
constexpr inline unsigned RoundUpToPowerOf2(const uint32_t num) {
    if (num) {
        return SetAllBitsAfterMSB(num - 1) + 1;
    } else {
        return 1;
    }
}

}//namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = 1u << (BitsNumber<uint32_t> - 1);


THE_BENCHMARK(RoundUpToPowerOf2_Float, UPPER);

SIMPLE_TEST(RoundUpToPowerOf2_Float, TestLOWER, 1, LOWER);
SIMPLE_TEST(RoundUpToPowerOf2_Float, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(RoundUpToPowerOf2_Float, TestSAMPLE1, 4, 3);
SIMPLE_TEST(RoundUpToPowerOf2_Float, TestSAMPLE2, 8, 8);
SIMPLE_TEST(RoundUpToPowerOf2_Float, TestSAMPLE3, UPPER, UPPER - 1);


THE_BENCHMARK(RoundUpToPowerOf2, UPPER);

SIMPLE_TEST(RoundUpToPowerOf2, TestLOWER, 1, LOWER);
SIMPLE_TEST(RoundUpToPowerOf2, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(RoundUpToPowerOf2, TestSAMPLE1, 4, 3);
SIMPLE_TEST(RoundUpToPowerOf2, TestSAMPLE2, 8, 8);
SIMPLE_TEST(RoundUpToPowerOf2, TestSAMPLE3, UPPER, UPPER - 1);

MUTUAL_RANDOM_TEST(RoundUpToPowerOf2_Float, RoundUpToPowerOf2, LOWER, UPPER);
