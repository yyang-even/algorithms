#include "common_header.h"

#include "are_all_bits_set.h"


namespace {

/** How to set a bit in the number ‘num’
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 * @reference   Set the K-th bit of a given number
 *              https://www.geeksforgeeks.org/set-k-th-bit-given-number/
 * @reference   How to turn on a particular bit in a number?
 *              https://www.geeksforgeeks.org/turn-particular-bit-number-2/
 *
 * @reference   Set, Clear and Toggle a given bit of a number in C
 *              https://www.geeksforgeeks.org/set-clear-and-toggle-a-given-bit-of-a-number-in-c/
 */
inline constexpr auto SetBit(const unsigned num, const unsigned position) {
    return num | (1 << position);
}


/** Set the rightmost off bit
 *
 * @reference   https://www.geeksforgeeks.org/set-the-rightmost-off-bit/
 * @reference   Set the rightmost unset bit
 *              https://www.geeksforgeeks.org/set-rightmost-unset-bit/
 * @reference   Set the rightmost unset bit
 *              https://www.geeksforgeeks.org/set-rightmost-unset-bit-2/
 */
inline constexpr auto SetRightmostOffBit(const unsigned num) {
    if (AreAllBitsSet(num)) {
        return num;
    }
    return num | (num + 1);
}

}//namespace


THE_BENCHMARK(SetBit, 0, 4);

SIMPLE_TEST(SetBit, TestSample1, 0b110, 0b100, 1);
SIMPLE_TEST(SetBit, TestSample2, 1, 0, 0);
SIMPLE_TEST(SetBit, TestSample3, 0b10, 0, 1);


THE_BENCHMARK(SetRightmostOffBit, 7);

SIMPLE_TEST(SetRightmostOffBit, TestSample1, 13, 12);
SIMPLE_TEST(SetRightmostOffBit, TestSample2, 7, 7);
