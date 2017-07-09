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


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(MinXor, -1, 0);
SIMPLE_BENCHMARK(MinXor, -1, 1);
SIMPLE_BENCHMARK(MinXor, LOWER, UPPER);

SIMPLE_TEST(MinXor, TestSample1, -1, -1, 0);
SIMPLE_TEST(MinXor, TestSample2, -1, -1, -1);
SIMPLE_TEST(MinXor, TestSample3, 0, 0, 1);
SIMPLE_TEST(MinXor, TestSample4, 1, 1, 1);
SIMPLE_TEST(MinXor, TestSample5, -1, -1, 1);
SIMPLE_TEST(MinXor, TestSample6, 0, 0, 0);
SIMPLE_TEST(MinXor, TestSample7, LOWER, LOWER, UPPER);
SIMPLE_TEST(MinXor, TestSample8, LOWER, LOWER, LOWER);

SIMPLE_BENCHMARK(MaxXor, -1, 0);
SIMPLE_BENCHMARK(MaxXor, -1, 1);
SIMPLE_BENCHMARK(MaxXor, LOWER, UPPER);

SIMPLE_TEST(MaxXor, TestSample1, 0, -1, 0);
SIMPLE_TEST(MaxXor, TestSample2, -1, -1, -1);
SIMPLE_TEST(MaxXor, TestSample3, 1, 0, 1);
SIMPLE_TEST(MaxXor, TestSample4, 1, 1, 1);
SIMPLE_TEST(MaxXor, TestSample5, 1, -1, 1);
SIMPLE_TEST(MaxXor, TestSample6, 0, 0, 0);
SIMPLE_TEST(MaxXor, TestSample7, UPPER, LOWER, UPPER);
SIMPLE_TEST(MaxXor, TestSample8, LOWER, LOWER, LOWER);

SIMPLE_BENCHMARK(MinQuickDirty, -1, 0);
SIMPLE_BENCHMARK(MinQuickDirty, -1, 1);
SIMPLE_BENCHMARK(MinQuickDirty, LOWER, UPPER);

SIMPLE_TEST(MinQuickDirty, TestSample1, -1, -1, 0);
SIMPLE_TEST(MinQuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(MinQuickDirty, TestSample3, 0, 0, 1);
SIMPLE_TEST(MinQuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(MinQuickDirty, TestSample5, -1, -1, 1);
SIMPLE_TEST(MinQuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(MinQuickDirty, TestSample7, LOWER, LOWER, LOWER);

SIMPLE_BENCHMARK(MaxQuickDirty, -1, 0);
SIMPLE_BENCHMARK(MaxQuickDirty, -1, 1);
SIMPLE_BENCHMARK(MaxQuickDirty, LOWER, UPPER);

SIMPLE_TEST(MaxQuickDirty, TestSample1, 0, -1, 0);
SIMPLE_TEST(MaxQuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(MaxQuickDirty, TestSample3, 1, 0, 1);
SIMPLE_TEST(MaxQuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(MaxQuickDirty, TestSample5, 1, -1, 1);
SIMPLE_TEST(MaxQuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(MaxQuickDirty, TestSample7, LOWER, LOWER, LOWER);
