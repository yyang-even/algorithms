#include "common_header.h"

using InputType = unsigned;

/** How to unset/clear a bit at n’th position in the number ‘num’
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 */
auto ClearBit(const InputType num, const InputType position) {
    return num & (~(1 << position));
}


SIMPLE_BENCHMARK(ClearBit, 0, 4);

SIMPLE_TEST(ClearBit, TestSample1, 0b101, 0b111, 1);
SIMPLE_TEST(ClearBit, TestSample2, 0, 0, 0);
SIMPLE_TEST(ClearBit, TestSample3, 0, 0, 1);
