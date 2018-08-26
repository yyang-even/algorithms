#include "common_header.h"

#include "set_all_bits_after_most_significant_bit.h"

typedef unsigned InputType;

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
InputType RoundUpToPowerOf2Float(const InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    if (num) {
        const float f_num = (float)num;
        const auto temp = 1U << ((*(unsigned int *)&f_num >> 23) - 0x7f);
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
 * @reference   Smallest power of 2 greater than or equal to n
 *              https://www.geeksforgeeks.org/smallest-power-of-2-greater-than-or-equal-to-n/
 */
InputType RoundUpToPowerOf2(const InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    if (num) {
        return SetAllBitsAfterMSB(num - 1) + 1;
    } else {
        return 1;
    }
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr InputType UPPER = 1u << (Bits_Number<InputType>() - 1u);

SIMPLE_BENCHMARK(RoundUpToPowerOf2Float, UPPER);

SIMPLE_TEST(RoundUpToPowerOf2Float, TestLOWER, 1, LOWER);
SIMPLE_TEST(RoundUpToPowerOf2Float, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(RoundUpToPowerOf2Float, TestSAMPLE1, 4, 3);
SIMPLE_TEST(RoundUpToPowerOf2Float, TestSAMPLE2, 8, 8);
SIMPLE_TEST(RoundUpToPowerOf2Float, TestSAMPLE3, UPPER, UPPER - 1);

SIMPLE_BENCHMARK(RoundUpToPowerOf2, UPPER);

SIMPLE_TEST(RoundUpToPowerOf2, TestLOWER, 1, LOWER);
SIMPLE_TEST(RoundUpToPowerOf2, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(RoundUpToPowerOf2, TestSAMPLE1, 4, 3);
SIMPLE_TEST(RoundUpToPowerOf2, TestSAMPLE2, 8, 8);
SIMPLE_TEST(RoundUpToPowerOf2, TestSAMPLE3, UPPER, UPPER - 1);

MUTUAL_RANDOM_TEST(RoundUpToPowerOf2Float, RoundUpToPowerOf2, LOWER, UPPER);
