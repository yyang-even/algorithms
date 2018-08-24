#include "common_header.h"

typedef unsigned InputType;

/** How to set a bit in the number ‘num’
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 * @reference   Set the K-th bit of a given number
 *              https://www.geeksforgeeks.org/set-k-th-bit-given-number/
 */
auto SetBit(const InputType num, const InputType position) {
    return num | (1 << position);
}


SIMPLE_BENCHMARK(SetBit, 0, 4);

SIMPLE_TEST(SetBit, TestSample1, 0b110, 0b100, 1);
SIMPLE_TEST(SetBit, TestSample2, 1, 0, 0);
SIMPLE_TEST(SetBit, TestSample3, 0b10, 0, 1);
