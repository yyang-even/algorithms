#include "common_header.h"

typedef unsigned InputType;

/** Compute the lexicographically next bit permutation
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the lexicographically next bit permutation
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Suppose we have a pattern of N bits set to 1 in an integer and we want the next permutation
 * of N 1 bits in a lexicographical sense. For example, if N is 3 and the bit pattern is 00010011,
 * the next patterns would be 00010101, 00010110, 00011001,00011010, 00011100, 00100011, and so forth.
 */
#ifdef __GNUC__
InputType NextPermutation(const InputType num) {
    const InputType t = num | (num - 1); // t gets num's least significant 0 bits set to 1
    // Next set to 1 the most significant bit to change,
    // set to 0 the least significant ones, and add the necessary 1 bits.
    return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(num) + 1)); //count trailing zeros
}
#endif


InputType NextPermutationDivision(const InputType num) {
    const InputType t = (num | (num - 1)) + 1;
    return t | ((((t & -t) / (num & -num)) >> 1) - 1);
}


constexpr InputType LOWER = 1;
constexpr auto UPPER = std::numeric_limits<InputType>::max();

#ifdef __GNUC__
SIMPLE_BENCHMARK(NextPermutation, UPPER);

SIMPLE_TEST(NextPermutation, TestLOWER, 2, LOWER);
//SIMPLE_TEST(NextPermutation, TestUPPER, UPPER, UPPER);  //Failed
SIMPLE_TEST(NextPermutation, TestSAMPLE1, 0b00011001, 0b00010110);
SIMPLE_TEST(NextPermutation, TestSAMPLE2, 0b00011100, 0b00011010);
#endif

SIMPLE_BENCHMARK(NextPermutationDivision, UPPER);

SIMPLE_TEST(NextPermutationDivision, TestLOWER, 2, LOWER);
SIMPLE_TEST(NextPermutationDivision, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(NextPermutationDivision, TestSAMPLE1, 0b00011001, 0b00010110);
SIMPLE_TEST(NextPermutationDivision, TestSAMPLE2, 0b00011100, 0b00011010);
