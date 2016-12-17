#include "common_header.h"

typedef int InputType;

/** Compute the minimum (min) or maximum (max) of two integers without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the minimum (min) or maximum (max) of two integers without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Compute the minimum or maximum of two integers without branching
 *              http://www.geeksforgeeks.org/compute-the-minimum-or-maximum-max-of-two-integers-without-branching/
 */
InputType MinXor(const InputType x, const InputType y) {
    return y ^ ((x ^ y) & -(x < y));
}

InputType MaxXor(const InputType x, const InputType y) {
    return x ^ ((x ^ y) & -(x < y));
}

//If and only if INT_MIN <= x - y <= INT_MAX
InputType MinQuickDirty(const InputType x, const InputType y) {
    auto diff = x - y;
    return y + ((diff) & ((diff) >> (sizeof(int) * CHAR_BIT - 1)));
}

//If and only if INT_MIN <= x - y <= INT_MAX
InputType MaxQuickDirty(const InputType x, const InputType y) {
    auto diff = x - y;
    return x - ((diff) & ((diff) >> (sizeof(int) * CHAR_BIT - 1)));
}


SIMPLE_BENCHMARK(MinXor, -1, 0);
SIMPLE_BENCHMARK(MinXor, -1, 1);
SIMPLE_BENCHMARK(MinXor, INT_MIN, INT_MAX);

SIMPLE_TEST(MinXor, TestSample1, -1, -1, 0);
SIMPLE_TEST(MinXor, TestSample2, -1, -1, -1);
SIMPLE_TEST(MinXor, TestSample3, 0, 0, 1);
SIMPLE_TEST(MinXor, TestSample4, 1, 1, 1);
SIMPLE_TEST(MinXor, TestSample5, -1, -1, 1);
SIMPLE_TEST(MinXor, TestSample6, 0, 0, 0);
SIMPLE_TEST(MinXor, TestSample7, INT_MIN, INT_MIN, INT_MAX);
SIMPLE_TEST(MinXor, TestSample8, INT_MIN, INT_MIN, INT_MIN);

SIMPLE_BENCHMARK(MaxXor, -1, 0);
SIMPLE_BENCHMARK(MaxXor, -1, 1);
SIMPLE_BENCHMARK(MaxXor, INT_MIN, INT_MAX);

SIMPLE_TEST(MaxXor, TestSample1, 0, -1, 0);
SIMPLE_TEST(MaxXor, TestSample2, -1, -1, -1);
SIMPLE_TEST(MaxXor, TestSample3, 1, 0, 1);
SIMPLE_TEST(MaxXor, TestSample4, 1, 1, 1);
SIMPLE_TEST(MaxXor, TestSample5, 1, -1, 1);
SIMPLE_TEST(MaxXor, TestSample6, 0, 0, 0);
SIMPLE_TEST(MaxXor, TestSample7, INT_MAX, INT_MIN, INT_MAX);
SIMPLE_TEST(MaxXor, TestSample8, INT_MIN, INT_MIN, INT_MIN);

SIMPLE_BENCHMARK(MinQuickDirty, -1, 0);
SIMPLE_BENCHMARK(MinQuickDirty, -1, 1);
SIMPLE_BENCHMARK(MinQuickDirty, INT_MIN, INT_MAX);

SIMPLE_TEST(MinQuickDirty, TestSample1, -1, -1, 0);
SIMPLE_TEST(MinQuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(MinQuickDirty, TestSample3, 0, 0, 1);
SIMPLE_TEST(MinQuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(MinQuickDirty, TestSample5, -1, -1, 1);
SIMPLE_TEST(MinQuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(MinQuickDirty, TestSample7, INT_MIN, INT_MIN, INT_MIN);

SIMPLE_BENCHMARK(MaxQuickDirty, -1, 0);
SIMPLE_BENCHMARK(MaxQuickDirty, -1, 1);
SIMPLE_BENCHMARK(MaxQuickDirty, INT_MIN, INT_MAX);

SIMPLE_TEST(MaxQuickDirty, TestSample1, 0, -1, 0);
SIMPLE_TEST(MaxQuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(MaxQuickDirty, TestSample3, 1, 0, 1);
SIMPLE_TEST(MaxQuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(MaxQuickDirty, TestSample5, 1, -1, 1);
SIMPLE_TEST(MaxQuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(MaxQuickDirty, TestSample7, INT_MIN, INT_MIN, INT_MIN);
