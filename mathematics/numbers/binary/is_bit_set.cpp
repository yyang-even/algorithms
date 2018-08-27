#include "common_header.h"

using InputType = unsigned;

/** Checking if bit at nth position is set or unset
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 * @reference   Check whether K-th bit is set or not
 *              https://www.geeksforgeeks.org/check-whether-k-th-bit-set-not/
 */
INT_BOOL IsBitSet(const InputType num, const InputType position) {
    return static_cast<bool>(num & (1 << position));
}


SIMPLE_BENCHMARK(IsBitSet, 0, 4);

SIMPLE_TEST(IsBitSet, TestSample1, TRUE, 0b101, 0);
SIMPLE_TEST(IsBitSet, TestSample2, FALSE, 0, 0);
SIMPLE_TEST(IsBitSet, TestSample3, FALSE, 0, 1);
