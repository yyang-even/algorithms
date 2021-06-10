#include "common_header.h"


namespace {

/** Conditionally negate a value without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Conditionally negate a value without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
/**
 * @param b_negate  b_negate ? -num : num
 */
inline constexpr int NegateIfTrue(const bool b_negate, const int num) {
    return (num ^ -b_negate) + b_negate;
}

inline constexpr int NegateIfFalse(const bool b_dont_negate, const int num) {
    return (b_dont_negate ^ (b_dont_negate - 1)) * num;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<int>::min();
constexpr auto UPPER = std::numeric_limits<int>::max();


SIMPLE_BENCHMARK(NegateIfTrue, Sample1, true, -1);
SIMPLE_BENCHMARK(NegateIfTrue, Sample2, true, 0);

SIMPLE_TEST(NegateIfTrue, TestSample1, 1, true, -1);
SIMPLE_TEST(NegateIfTrue, TestSample2, 0, true, 0);
SIMPLE_TEST(NegateIfTrue, TestSample3, -1, true, 1);
SIMPLE_TEST(NegateIfTrue, TestSample4, LOWER, true, LOWER);
SIMPLE_TEST(NegateIfTrue, TestSample5, LOWER + 1, true, UPPER);
SIMPLE_TEST(NegateIfTrue, TestSample6, -1, false, -1);
SIMPLE_TEST(NegateIfTrue, TestSample7, 0, false, 0);
SIMPLE_TEST(NegateIfTrue, TestSample8, 1, false, 1);
SIMPLE_TEST(NegateIfTrue, TestSample9, LOWER, false, LOWER);
SIMPLE_TEST(NegateIfTrue, TestSample10, UPPER, false, UPPER);


SIMPLE_BENCHMARK(NegateIfFalse, Sample1, true, -1);
SIMPLE_BENCHMARK(NegateIfFalse, Sample2, true, 0);

SIMPLE_TEST(NegateIfFalse, TestSample1, 1, false, -1);
SIMPLE_TEST(NegateIfFalse, TestSample2, 0, false, 0);
SIMPLE_TEST(NegateIfFalse, TestSample3, -1, false, 1);
SIMPLE_TEST(NegateIfFalse, TestSample4, LOWER, false, LOWER);
SIMPLE_TEST(NegateIfFalse, TestSample5, LOWER + 1, false, UPPER);
SIMPLE_TEST(NegateIfFalse, TestSample6, -1, true, -1);
SIMPLE_TEST(NegateIfFalse, TestSample7, 0, true, 0);
SIMPLE_TEST(NegateIfFalse, TestSample8, 1, true, 1);
SIMPLE_TEST(NegateIfFalse, TestSample9, LOWER, true, LOWER);
SIMPLE_TEST(NegateIfFalse, TestSample10, UPPER, true, UPPER);
