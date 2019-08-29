#include "common_header.h"


namespace {

using InputType = unsigned;

/** How to unset/clear a bit at n’th position in the number ‘num’
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 *              How to turn off a particular bit in a number?
 *              https://www.geeksforgeeks.org/how-to-turn-off-a-particular-bit-in-a-number/
 */
auto ClearBit(const InputType num, const InputType position) {
    return num & (~(1 << position));
}


/** Clear all bits from LSB to ith bit
 *
 * @reference   Bit Tricks for Competitive Programming
 *              https://www.geeksforgeeks.org/bit-tricks-competitive-programming/
 */
auto ClearBitsFromLSB(const InputType num, const InputType i) {
    const auto mask = ~((1 << (i + 1)) - 1);
    return num & mask;
}


/** Clearing all bits from MSB to i-th bit
 *
 * @reference   Bit Tricks for Competitive Programming
 *              https://www.geeksforgeeks.org/bit-tricks-competitive-programming/
 */
auto ClearBitsFromMSB(const InputType num, const InputType i) {
    const auto mask = (1 << i) - 1;
    return num & mask;
}


/** Turn off the rightmost set bit
 *
 * @reference   https://www.geeksforgeeks.org/turn-off-the-rightmost-set-bit/
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 */
auto ClearRightmostBit(const InputType num) {
    return num & (num - 1);
}

}//namespace


SIMPLE_BENCHMARK(ClearBit, 0, 4);

SIMPLE_TEST(ClearBit, TestSample1, 0b101u, 0b111, 1);
SIMPLE_TEST(ClearBit, TestSample2, 0u, 0, 0);
SIMPLE_TEST(ClearBit, TestSample3, 0u, 0, 1);


SIMPLE_BENCHMARK(ClearBitsFromLSB, 0, 4);

SIMPLE_TEST(ClearBitsFromLSB, TestSample1, 0b00010000u, 0b00011101, 3);


SIMPLE_BENCHMARK(ClearBitsFromMSB, 0, 4);

SIMPLE_TEST(ClearBitsFromMSB, TestSample1, 0b00000111u, 0b11010111, 4);


SIMPLE_BENCHMARK(ClearRightmostBit, 7);

SIMPLE_TEST(ClearRightmostBit, TestSample1, 8u, 12);
SIMPLE_TEST(ClearRightmostBit, TestSample2, 6u, 7);
