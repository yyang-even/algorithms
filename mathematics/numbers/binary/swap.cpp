#include "common_header.h"

typedef unsigned InputType;

/** Swapping values with subtraction and addition
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Swapping values with subtraction and addition
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Swap two values without using a temporary variable.
 */
void SwapSubAdd(InputType &a, InputType &b) {
    if (a != b) {
        a -= b;
        b += a;
        a = b - a;
    }
}

/** Swapping values with XOR
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Swapping values with XOR
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
void SwapXor(InputType &a, InputType &b) {
    if (a != b) {
        a ^= b;
        b ^= a;
        a ^= b;
    }
}

INT_BOOL TestSwap(std::function<void(InputType &, InputType &)> swap,
                  const InputType a, const InputType b) {
    InputType swapped_a = b;
    InputType swapped_b = a;
    swap(swapped_a, swapped_b);
    return swapped_a == a and swapped_b == b;
}


/** Swapping individual bits with XOR
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Swapping individual bits with XOR
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * As an example of swapping ranges of bits suppose we have have number=00101111 (expressed in binary)
 * and we want to swap the bit_length=3 consecutive bits starting at i = 1 (the second bit from the right)
 * with the 3 consecutive bits starting at j = 5; the result would be r=11100011 (binary).
 */
InputType SwapBitRange(const InputType number, const unsigned i, const unsigned j,
                       const unsigned bit_length) {
    constexpr unsigned NUM_BITS = sizeof(number) * CHAR_BIT;
    if (i + bit_length >= NUM_BITS or
        j + bit_length >= NUM_BITS or
        i == j or
        (i > j and j + bit_length > i) or
        (i < j and i + bit_length > j)) {
        return 0;
    }
    unsigned int xor_mask = ((number >> i) ^ (number >> j)) & ((1U << bit_length) - 1U);
    return number ^ ((xor_mask << i) | (xor_mask << j));
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(TestSwap, SwapSubAdd, LOWER, UPPER);

SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE1, TRUE, SwapSubAdd, 6, 13);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE2, TRUE, SwapSubAdd, 13, 6);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE3, TRUE, SwapSubAdd, LOWER, UPPER);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE4, TRUE, SwapSubAdd, UPPER, LOWER);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE5, TRUE, SwapSubAdd, 6, 6);
SIMPLE_TEST(TestSwap, TestSwapSubAddSAMPLE6, TRUE, SwapSubAdd, UPPER, UPPER);

SIMPLE_BENCHMARK(TestSwap, SwapXor, LOWER, UPPER);

SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE1, TRUE, SwapXor, 6, 13);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE2, TRUE, SwapXor, 13, 6);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE3, TRUE, SwapXor, LOWER, UPPER);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE4, TRUE, SwapXor, UPPER, LOWER);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE5, TRUE, SwapXor, 13, 13);
SIMPLE_TEST(TestSwap, TestSwapXorSAMPLE6, TRUE, SwapXor, UPPER, UPPER);

SIMPLE_BENCHMARK(SwapBitRange, 0b00101111, 1, 5, 3);

SIMPLE_TEST(SwapBitRange, TestSAMPLE1, 0b11100011, 0b00101111, 1, 5, 3);
SIMPLE_TEST(SwapBitRange, TestSAMPLE2, 0, 0b00101111, 0, 4, 5);
