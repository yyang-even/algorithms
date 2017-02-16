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


const InputType LOWER = 0;
const InputType UPPER = UINT_MAX;

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
