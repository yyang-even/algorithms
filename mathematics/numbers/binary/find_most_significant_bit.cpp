#include "common_header.h"

#include "set_all_bits_after_most_significant_bit.h"


namespace {

using InputType = unsigned;

/** Find most significant set bit of a number
 *
 * @reference   https://www.geeksforgeeks.org/find-significant-set-bit-number/
 * @reference   Highest power of 2 less than or equal to given number
 *              https://www.geeksforgeeks.org/highest-power-2-less-equal-given-number/
 *
 * Given a number, find the most significant bit number which is set bit and which is in power of two.
 */
auto FindMSB(const InputType num) {
    return (SetAllBitsAfterMSB(num) + 1ull) >> 1;
}


InputType FindMSB_Float(const InputType num) {
    return pow(2, static_cast<InputType>(log2(num)));
}

}//namespace


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(FindMSB, 4);

SIMPLE_TEST(FindMSB, TestLOWER, 1u, LOWER);
SIMPLE_TEST(FindMSB, TestUPPER, 1u << (BitsNumber<decltype(UPPER)> - 1), UPPER);
SIMPLE_TEST(FindMSB, TestSample1, 0b100u, 0b101);
SIMPLE_TEST(FindMSB, TestSample2, 256u, 273);
SIMPLE_TEST(FindMSB, TestSample3, 8u, 10);


SIMPLE_BENCHMARK(FindMSB_Float, 4);

SIMPLE_TEST(FindMSB_Float, TestLOWER, 1u, LOWER);
SIMPLE_TEST(FindMSB_Float, TestUPPER, 1u << (BitsNumber<decltype(UPPER)> - 1), UPPER);
SIMPLE_TEST(FindMSB_Float, TestSample1, 0b100u, 0b101);
SIMPLE_TEST(FindMSB_Float, TestSample2, 256u, 273);

MUTUAL_RANDOM_TEST(FindMSB, FindMSB_Float, LOWER, UPPER);
