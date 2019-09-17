#include "common_header.h"


namespace {

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
 * @reference   Check whether the bit at given position is set or unset
 *              https://www.geeksforgeeks.org/check-whether-bit-given-position-set-unset/
 *
 * A number N is given. We need to print its ‘K’th Least Significant Bit.
 */
bool IsBitSet(const unsigned num, const unsigned position) {
    return num & (1 << position);
}

}//namespace


SIMPLE_BENCHMARK(IsBitSet, 0, 4);

SIMPLE_TEST(IsBitSet, TestSample1, true, 0b101, 0);
SIMPLE_TEST(IsBitSet, TestSample2, false, 0, 0);
SIMPLE_TEST(IsBitSet, TestSample3, false, 0, 1);
SIMPLE_TEST(IsBitSet, TestSample4, false, 13, 1);
SIMPLE_TEST(IsBitSet, TestSample5, true, 14, 2);
SIMPLE_TEST(IsBitSet, TestSample6, true, 10, 1);
SIMPLE_TEST(IsBitSet, TestSample7, false, 21, 3);
