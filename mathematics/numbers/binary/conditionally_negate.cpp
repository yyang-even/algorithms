#include "common_header.h"

/** Conditionally set or clear bits without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Conditionally set or clear bits without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
/**
 * b_negate ? -num : num
 */
int NegateIfTrue(const bool b_negate, const int num) {
    return (num ^ -b_negate) + b_negate;
}

int NegateIfFalse(const bool b_dont_negate, const int num) {
    return (b_dont_negate ^ (b_dont_negate - 1)) * num;
}


SIMPLE_BENCHMARK(NegateIfTrue, true, -1);
SIMPLE_BENCHMARK(NegateIfTrue, true, 0);
SIMPLE_BENCHMARK(NegateIfTrue, false, INT_MIN);
SIMPLE_BENCHMARK(NegateIfTrue, false, INT_MAX);

SIMPLE_TEST(NegateIfTrue, TestSample1, 1, true, -1);
SIMPLE_TEST(NegateIfTrue, TestSample2, 0, true, 0);
SIMPLE_TEST(NegateIfTrue, TestSample3, -1, true, 1);
SIMPLE_TEST(NegateIfTrue, TestSample4, INT_MIN, true, INT_MIN);
SIMPLE_TEST(NegateIfTrue, TestSample5, INT_MIN + 1, true, INT_MAX);
SIMPLE_TEST(NegateIfTrue, TestSample6, -1, false, -1);
SIMPLE_TEST(NegateIfTrue, TestSample7, 0, false, 0);
SIMPLE_TEST(NegateIfTrue, TestSample8, 1, false, 1);
SIMPLE_TEST(NegateIfTrue, TestSample9, INT_MIN, false, INT_MIN);
SIMPLE_TEST(NegateIfTrue, TestSample10, INT_MAX, false, INT_MAX);

SIMPLE_BENCHMARK(NegateIfFalse, true, -1);
SIMPLE_BENCHMARK(NegateIfFalse, true, 0);
SIMPLE_BENCHMARK(NegateIfFalse, false, INT_MIN);
SIMPLE_BENCHMARK(NegateIfFalse, false, INT_MAX);

SIMPLE_TEST(NegateIfFalse, TestSample1, 1, false, -1);
SIMPLE_TEST(NegateIfFalse, TestSample2, 0, false, 0);
SIMPLE_TEST(NegateIfFalse, TestSample3, -1, false, 1);
SIMPLE_TEST(NegateIfFalse, TestSample4, INT_MIN, false, INT_MIN);
SIMPLE_TEST(NegateIfFalse, TestSample5, INT_MIN + 1, false, INT_MAX);
SIMPLE_TEST(NegateIfFalse, TestSample6, -1, true, -1);
SIMPLE_TEST(NegateIfFalse, TestSample7, 0, true, 0);
SIMPLE_TEST(NegateIfFalse, TestSample8, 1, true, 1);
SIMPLE_TEST(NegateIfFalse, TestSample9, INT_MIN, true, INT_MIN);
SIMPLE_TEST(NegateIfFalse, TestSample10, INT_MAX, true, INT_MAX);
