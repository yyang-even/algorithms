#include "common_header.h"

#include "set_all_bits_after_most_significant_bit.h"


namespace {

/** Find most significant set bit of a number
 *
 * @reference   https://www.geeksforgeeks.org/find-significant-set-bit-number/
 * @reference   Highest power of 2 less than or equal to given number
 *              https://www.geeksforgeeks.org/highest-power-2-less-equal-given-number/
 *
 * Some people are standing in a queue. A selection process follows a rule where people
 * standing on even positions are selected. Of the selected people a queue is formed and
 * again out of these only people on even position are selected. This continues until we
 * are left with one person. Find out the position of that person in the original queue.
 * Print the position(original queue) of that person who is left.
 *
 * @reference   Highest power of 2 less than or equal to given Integer
 *              https://www.geeksforgeeks.org/highest-power-of-2-less-than-or-equal-to-given-integer/
 *
 * Given a number, find the most significant bit number which is set bit and which is in
 * power of two.
 */
inline constexpr unsigned FindMSB(const unsigned num) {
    return (SetAllBitsAfterMSB(num) + 1ull) >> 1;
}


inline constexpr unsigned FindMSB_Float(const unsigned num) {
    return std::pow(2, static_cast<unsigned>(std::log2(num)));
}

}//namespace


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


THE_BENCHMARK(FindMSB, 4);

SIMPLE_TEST(FindMSB, TestLOWER, 1, LOWER);
SIMPLE_TEST(FindMSB, TestUPPER, 1 << (BitsNumber<decltype(UPPER)> - 1), UPPER);
SIMPLE_TEST(FindMSB, TestSample1, 0b100, 0b101);
SIMPLE_TEST(FindMSB, TestSample2, 256, 273);
SIMPLE_TEST(FindMSB, TestSample3, 8, 10);


THE_BENCHMARK(FindMSB_Float, 4);

SIMPLE_TEST(FindMSB_Float, TestLOWER, 1, LOWER);
SIMPLE_TEST(FindMSB_Float, TestUPPER, 1 << (BitsNumber<decltype(UPPER)> - 1), UPPER);
SIMPLE_TEST(FindMSB_Float, TestSample1, 0b100, 0b101);
SIMPLE_TEST(FindMSB_Float, TestSample2, 256, 273);

MUTUAL_RANDOM_TEST(FindMSB, FindMSB_Float, LOWER, UPPER);
