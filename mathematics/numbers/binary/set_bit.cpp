#include "common_header.h"

#include "are_all_bits_set.h"


namespace {

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


/** Set the rightmost off bit
 *
 * @reference   https://www.geeksforgeeks.org/set-the-rightmost-off-bit/
 * @reference   Set the rightmost unset bit
 *              https://www.geeksforgeeks.org/set-rightmost-unset-bit/
 * @reference   Set the rightmost unset bit
 *              https://www.geeksforgeeks.org/set-rightmost-unset-bit-2/
 */
auto SetRightmostOffBit(const InputType num) {
    if (AreAllBitsSet(num)) {
        return num;
    }
    return num | (num + 1);
}

}//namespace


SIMPLE_BENCHMARK(SetBit, 0, 4);

SIMPLE_TEST(SetBit, TestSample1, 0b110u, 0b100, 1);
SIMPLE_TEST(SetBit, TestSample2, 1u, 0, 0);
SIMPLE_TEST(SetBit, TestSample3, 0b10u, 0, 1);


SIMPLE_BENCHMARK(SetRightmostOffBit, 7);

SIMPLE_TEST(SetRightmostOffBit, TestSample1, 13u, 12);
SIMPLE_TEST(SetRightmostOffBit, TestSample2, 7u, 7);
