#include "common_header.h"

#include "clear_bit.h"


namespace {

/** How to unset/clear a bit at n’th position in the number ‘num’
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 * @reference   How to turn off a particular bit in a number?
 *              https://www.geeksforgeeks.org/how-to-turn-off-a-particular-bit-in-a-number/
 * @reference   Program to clear K-th bit of a number N
 *              https://www.geeksforgeeks.org/program-to-clear-k-th-bit-of-a-number-n/
 */
inline constexpr auto ClearBit(const unsigned num, const unsigned position) {
    return num & (~(1 << position));
}


/** Clear all bits from LSB to ith bit
 *
 * @reference   Bit Tricks for Competitive Programming
 *              https://www.geeksforgeeks.org/bit-tricks-competitive-programming/
 * @reference   Unset the last m bits
 *              https://www.geeksforgeeks.org/unset-last-m-bits/
 */
inline constexpr auto ClearBitsFromLSB(const unsigned num, const unsigned i) {
    const auto mask = ~((1 << (i + 1)) - 1);
    return num & mask;
}


/** Clearing all bits from MSB to i-th bit
 *
 * @reference   Bit Tricks for Competitive Programming
 *              https://www.geeksforgeeks.org/bit-tricks-competitive-programming/
 */
inline constexpr auto ClearBitsFromMSB(const unsigned num, const unsigned i) {
    const auto mask = (1 << i) - 1;
    return num & mask;
}

}//namespace


THE_BENCHMARK(ClearBit, 0, 4);

SIMPLE_TEST(ClearBit, TestSample1, 0b101, 0b111, 1);
SIMPLE_TEST(ClearBit, TestSample2, 0, 0, 0);
SIMPLE_TEST(ClearBit, TestSample3, 0, 0, 1);


THE_BENCHMARK(ClearBitsFromLSB, 0, 4);

SIMPLE_TEST(ClearBitsFromLSB, TestSample1, 0b00010000, 0b00011101, 3);
SIMPLE_TEST(ClearBitsFromLSB, TestSample2, 8, 10, 1);
SIMPLE_TEST(ClearBitsFromLSB, TestSample3, 144, 150, 3);


THE_BENCHMARK(ClearBitsFromMSB, 0, 4);

SIMPLE_TEST(ClearBitsFromMSB, TestSample1, 0b00000111, 0b11010111, 4);


THE_BENCHMARK(ClearRightmostBit, 7);

SIMPLE_TEST(ClearRightmostBit, TestSample1, 8, 12);
SIMPLE_TEST(ClearRightmostBit, TestSample2, 6, 7);
