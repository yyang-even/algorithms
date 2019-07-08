#include "common_header.h"


namespace {

typedef int InputType;

/** Compute the minimum (min) or maximum (max) of two integers without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the minimum (min) or maximum (max) of two integers without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Compute the minimum or maximum of two integers without branching
 *              https://www.geeksforgeeks.org/compute-the-minimum-or-maximum-max-of-two-integers-without-branching/
 */
InputType Min_Xor(const InputType x, const InputType y) {
    return y ^ ((x ^ y) & -(x < y));
}


InputType Max_Xor(const InputType x, const InputType y) {
    return x ^ ((x ^ y) & -(x < y));
}


//If and only if INT_MIN <= x - y <= INT_MAX
InputType Min_QuickDirty(const InputType x, const InputType y) {
    auto diff = x - y;
    return y + ((diff) & ((diff) >> (Bits_Number<decltype(diff)>() - 1)));
}


//If and only if INT_MIN <= x - y <= INT_MAX
InputType Max_QuickDirty(const InputType x, const InputType y) {
    auto diff = x - y;
    return x - ((diff) & ((diff) >> (Bits_Number<decltype(diff)>() - 1)));
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(Min_Xor, -1, 0);
SIMPLE_BENCHMARK(Min_Xor, -1, 1);
SIMPLE_BENCHMARK(Min_Xor, LOWER, UPPER);

SIMPLE_TEST(Min_Xor, TestSample1, -1, -1, 0);
SIMPLE_TEST(Min_Xor, TestSample2, -1, -1, -1);
SIMPLE_TEST(Min_Xor, TestSample3, 0, 0, 1);
SIMPLE_TEST(Min_Xor, TestSample4, 1, 1, 1);
SIMPLE_TEST(Min_Xor, TestSample5, -1, -1, 1);
SIMPLE_TEST(Min_Xor, TestSample6, 0, 0, 0);
SIMPLE_TEST(Min_Xor, TestSample7, LOWER, LOWER, UPPER);
SIMPLE_TEST(Min_Xor, TestSample8, LOWER, LOWER, LOWER);


SIMPLE_BENCHMARK(Max_Xor, -1, 0);
SIMPLE_BENCHMARK(Max_Xor, -1, 1);
SIMPLE_BENCHMARK(Max_Xor, LOWER, UPPER);

SIMPLE_TEST(Max_Xor, TestSample1, 0, -1, 0);
SIMPLE_TEST(Max_Xor, TestSample2, -1, -1, -1);
SIMPLE_TEST(Max_Xor, TestSample3, 1, 0, 1);
SIMPLE_TEST(Max_Xor, TestSample4, 1, 1, 1);
SIMPLE_TEST(Max_Xor, TestSample5, 1, -1, 1);
SIMPLE_TEST(Max_Xor, TestSample6, 0, 0, 0);
SIMPLE_TEST(Max_Xor, TestSample7, UPPER, LOWER, UPPER);
SIMPLE_TEST(Max_Xor, TestSample8, LOWER, LOWER, LOWER);


SIMPLE_BENCHMARK(Min_QuickDirty, -1, 0);
SIMPLE_BENCHMARK(Min_QuickDirty, -1, 1);
SIMPLE_BENCHMARK(Min_QuickDirty, LOWER, UPPER);

SIMPLE_TEST(Min_QuickDirty, TestSample1, -1, -1, 0);
SIMPLE_TEST(Min_QuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(Min_QuickDirty, TestSample3, 0, 0, 1);
SIMPLE_TEST(Min_QuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(Min_QuickDirty, TestSample5, -1, -1, 1);
SIMPLE_TEST(Min_QuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(Min_QuickDirty, TestSample7, LOWER, LOWER, LOWER);


SIMPLE_BENCHMARK(Max_QuickDirty, -1, 0);
SIMPLE_BENCHMARK(Max_QuickDirty, -1, 1);
SIMPLE_BENCHMARK(Max_QuickDirty, LOWER, UPPER);

SIMPLE_TEST(Max_QuickDirty, TestSample1, 0, -1, 0);
SIMPLE_TEST(Max_QuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(Max_QuickDirty, TestSample3, 1, 0, 1);
SIMPLE_TEST(Max_QuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(Max_QuickDirty, TestSample5, 1, -1, 1);
SIMPLE_TEST(Max_QuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(Max_QuickDirty, TestSample7, LOWER, LOWER, LOWER);
