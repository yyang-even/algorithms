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

}//namespace


SIMPLE_BENCHMARK(ClearBit, 0, 4);

SIMPLE_TEST(ClearBit, TestSample1, 0b101, 0b111, 1);
SIMPLE_TEST(ClearBit, TestSample2, 0, 0, 0);
SIMPLE_TEST(ClearBit, TestSample3, 0, 0, 1);


SIMPLE_BENCHMARK(ClearBitsFromLSB, 0, 4);

SIMPLE_TEST(ClearBitsFromLSB, TestSample1, 0b00010000, 0b00011101, 3);


SIMPLE_BENCHMARK(ClearBitsFromMSB, 0, 4);

SIMPLE_TEST(ClearBitsFromMSB, TestSample1, 0b00000111, 0b11010111, 4);
