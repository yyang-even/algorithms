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


/** Check if all bits of a number are set
 *
 * @reference   https://www.geeksforgeeks.org/check-bits-number-set/
 *
 * Given a number n. The problem is to check whether every bit in the binary
 * representation of the given number is set or not. Here 0 <= n.
 */
INT_BOOL AreAllBitsSet(const InputType num) {
    if (num == 0) {
        return FALSE;
    }
    return not(num & (num + 1));
}


SIMPLE_BENCHMARK(IsBitSet, 0, 4);

SIMPLE_TEST(IsBitSet, TestSample1, TRUE, 0b101, 0);
SIMPLE_TEST(IsBitSet, TestSample2, FALSE, 0, 0);
SIMPLE_TEST(IsBitSet, TestSample3, FALSE, 0, 1);


SIMPLE_BENCHMARK(AreAllBitsSet, 7);

SIMPLE_TEST(AreAllBitsSet, TestSample1, TRUE, 0b111);
SIMPLE_TEST(AreAllBitsSet, TestSample2, FALSE, 0);
SIMPLE_TEST(AreAllBitsSet, TestSample3, FALSE, 0b101);
