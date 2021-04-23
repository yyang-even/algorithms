#include "common_header.h"


namespace {

#include "swap.h"

/** Swapping values with subtraction and addition
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Swapping values with subtraction and addition
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   How to swap two numbers without using a temporary variable?
 *              https://www.geeksforgeeks.org/swap-two-numbers-without-using-temporary-variable/
 * @reference   TCS Coding Practice Question | Swap two Numbers
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-swap-2-numbers/
 * @reference   Command line arguments in C/C++
 *              https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
 *
 * Swap two values without using a temporary variable.
 */
constexpr inline void Swap_SubAdd(unsigned &a, unsigned &b) {
    if (a != b) {
        a -= b;
        b += a;
        a = b - a;
    }
}


template <typename SwapFunc>
constexpr inline auto TestSwap(const SwapFunc swap,
                               const unsigned a, const unsigned b) {
    unsigned swapped_a = b;
    unsigned swapped_b = a;
    swap(swapped_a, swapped_b);
    return swapped_a == a and swapped_b == b;
}


/** Swapping individual bits with XOR
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Swapping individual bits with XOR
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Swap bits in a given number
 *              https://www.geeksforgeeks.org/swap-bits-in-a-given-number/
 *
 * As an example of swapping ranges of bits suppose we have have number=00101111
 * (expressed in binary) and we want to swap the bit_length=3 consecutive bits starting
 * at i = 1 (the second bit from the right) with the 3 consecutive bits starting at
 * j = 5; the result would be r=11100011 (binary).
 *
 * @reference   How to swap two bits in a given integer?
 *              https://www.geeksforgeeks.org/how-to-swap-two-bits-in-a-given-integer/
 *
 * Given an integer n and two bit positions p1 and p2 inside it, swap bits at the given
 * positions. The given positions are from least significant bit (lsb). For example, the
 * position for lsb is 0.
 */
constexpr unsigned SwapBitRange(const unsigned number,
                                const unsigned i,
                                const unsigned j,
                                const unsigned bit_length) {
    constexpr auto NUM_BITS = BitsNumber<decltype(number)>;
    if (i + bit_length >= NUM_BITS or
        j + bit_length >= NUM_BITS or
        i == j or
        (i > j and j + bit_length > i) or
        (i < j and i + bit_length > j)) {
        return 0;
    }
    const unsigned xor_mask = ((number >> i) ^ (number >> j)) & ((1U << bit_length) - 1);
    return number ^ ((xor_mask << i) | (xor_mask << j));
}


/**
 * @reference   C Program to Swap two Numbers
 *              https://www.geeksforgeeks.org/c-program-swap-two-numbers/
 */

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


SIMPLE_BENCHMARK(TestSwap, Sample1, Swap_SubAdd, LOWER, UPPER);

SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE1, true, Swap_SubAdd, 6, 13);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE2, true, Swap_SubAdd, 13, 6);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE3, true, Swap_SubAdd, LOWER, UPPER);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE4, true, Swap_SubAdd, UPPER, LOWER);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE5, true, Swap_SubAdd, 6, 6);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE6, true, Swap_SubAdd, UPPER, UPPER);


SIMPLE_BENCHMARK(TestSwap, Sample2, Swap_Xor<unsigned>, LOWER, UPPER);

SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE1, true, Swap_Xor<unsigned>, 6, 13);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE2, true, Swap_Xor<unsigned>, 13, 6);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE3, true, Swap_Xor<unsigned>, LOWER, UPPER);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE4, true, Swap_Xor<unsigned>, UPPER, LOWER);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE5, true, Swap_Xor<unsigned>, 13, 13);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE6, true, Swap_Xor<unsigned>, UPPER, UPPER);


THE_BENCHMARK(SwapBitRange, 0b00101111, 1, 5, 3);

SIMPLE_TEST(SwapBitRange, TestSAMPLE1, 0b11100011u, 0b00101111, 1, 5, 3);
SIMPLE_TEST(SwapBitRange, TestSAMPLE2, 0u, 0b00101111, 0, 4, 5);
SIMPLE_TEST(SwapBitRange, TestSAMPLE3, 21u, 28, 0, 3, 1);
SIMPLE_TEST(SwapBitRange, TestSAMPLE4, 24u, 20, 2, 3, 1);
