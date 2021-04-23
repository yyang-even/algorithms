#include "common_header.h"


namespace {

/** Compute the sign of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the sign of an integer
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
constexpr inline bool IsNegative_Portable(const int num) {
    return 1 & ((unsigned int)num >> (BitsNumber<decltype(num)> - 1));
}


constexpr inline auto IsNegative(const int num) {
    return num < 0;
}


/** Check if a number is positive, negative or zero using bit operators
 *
 * @reference   https://www.geeksforgeeks.org/check-number-positive-negative-zero-using-bit-operators/
 */
constexpr inline int IsNegativeOrZeroOrPositive(const int num) {
    constexpr auto BITS_NUM = BitsNumber<decltype(num)> - 1;
    return 1 + (num >> BITS_NUM) - (-num >> BITS_NUM);
}

}//namespace


constexpr auto LOWER = std::numeric_limits<int>::min();
constexpr auto UPPER = std::numeric_limits<int>::max();


SIMPLE_BENCHMARK(IsNegative_Portable, Sample1, -1);
SIMPLE_BENCHMARK(IsNegative_Portable, Sample2, 0);

SIMPLE_TEST(IsNegative_Portable, TestSample1, true, -1);
SIMPLE_TEST(IsNegative_Portable, TestSample2, false, 0);
SIMPLE_TEST(IsNegative_Portable, TestSample3, true, LOWER);
SIMPLE_TEST(IsNegative_Portable, TestSample4, false, UPPER);

MUTUAL_RANDOM_TEST(IsNegative_Portable, IsNegative, LOWER, UPPER);


THE_BENCHMARK(IsNegativeOrZeroOrPositive, UPPER);

SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample1, 0, -1);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample2, 0, -20);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample3, 0, -UPPER);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample4, 1, 0);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample5, 2, 1);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample6, 2, 30);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample7, 2, UPPER);
