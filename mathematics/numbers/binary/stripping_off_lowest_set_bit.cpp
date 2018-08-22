#include "common_header.h"

using InputType = unsigned;

/** Stripping off the lowest set bit
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 */
auto StripLastSetBit(const InputType num) {
    return num & (num - 1);
}


SIMPLE_BENCHMARK(StripLastSetBit, 0);

SIMPLE_TEST(StripLastSetBit, TestSample1, 0b1000, 0b1100);
