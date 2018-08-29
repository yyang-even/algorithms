#include "common_header.h"

#include "set_all_bits_after_most_significant_bit.h"

using InputType = unsigned;

/** Find most significant set bit of a number
 *
 * @reference   https://www.geeksforgeeks.org/find-significant-set-bit-number/
 *
 * Given a number, find the most significant bit number which is set bit and which is in power of two.
 */
auto FindMSB(const InputType num) {
    return (SetAllBitsAfterMSB(num) + 1ull) >> 1;
}


InputType FindMSBFloat(const InputType num) {
    return pow(2, static_cast<InputType>(log2(num)));
}


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(FindMSB, 4);

SIMPLE_TEST(FindMSB, TestLOWER, 1, LOWER);
SIMPLE_TEST(FindMSB, TestUPPER, 1u << (Bits_Number<InputType>() - 1), UPPER);
SIMPLE_TEST(FindMSB, TestSample1, 0b100, 0b101);
SIMPLE_TEST(FindMSB, TestSample2, 256, 273);


SIMPLE_BENCHMARK(FindMSBFloat, 4);

SIMPLE_TEST(FindMSBFloat, TestLOWER, 1, LOWER);
SIMPLE_TEST(FindMSBFloat, TestUPPER, 1u << (Bits_Number<InputType>() - 1), UPPER);
SIMPLE_TEST(FindMSBFloat, TestSample1, 0b100, 0b101);
SIMPLE_TEST(FindMSBFloat, TestSample2, 256, 273);

MUTUAL_RANDOM_TEST(FindMSB, FindMSBFloat, LOWER, UPPER);
