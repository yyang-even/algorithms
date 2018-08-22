#include "common_header.h"

using InputType = unsigned;

/** Getting lowest set bit of a number
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 */
auto ClearAllBitsExceptTheLastSetBit(const InputType num) {
    return num & (-num);
}


SIMPLE_BENCHMARK(ClearAllBitsExceptTheLastSetBit, 1);

SIMPLE_TEST(ClearAllBitsExceptTheLastSetBit, TestSample1, 0b00000100, 0b00101100);
