#include "common_header.h"

using InputType = unsigned;

/** Checking if bit at nth position is set or unset
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 * @reference   Check whether K-th bit is set or not
 *              https://www.geeksforgeeks.org/check-whether-k-th-bit-set-not/
 * @reference   Print ‘K’th least significant bit of a number
 *              https://www.geeksforgeeks.org/print-kth-least-significant-bit-number/
 * @reference   Find value of k-th bit in binary representation
 *              https://www.geeksforgeeks.org/find-value-k-th-bit-binary-representation/
 *
 * A number N is given. We need to print its ‘K’th Least Significant Bit.
 */
INT_BOOL IsBitSet(const InputType num, const InputType position) {
    return static_cast<bool>(num & (1 << position));
}


SIMPLE_BENCHMARK(IsBitSet, 0, 4);

SIMPLE_TEST(IsBitSet, TestSample1, TRUE, 0b101, 0);
SIMPLE_TEST(IsBitSet, TestSample2, FALSE, 0, 0);
SIMPLE_TEST(IsBitSet, TestSample3, FALSE, 0, 1);
SIMPLE_TEST(IsBitSet, TestSample4, FALSE, 13, 1);
SIMPLE_TEST(IsBitSet, TestSample5, TRUE, 14, 2);
