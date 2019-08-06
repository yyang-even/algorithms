#include "common_header.h"


namespace {

typedef int InputType;

/** Compute the sign of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the sign of an integer
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
bool IsNegative_Portable(const InputType num) {
    return 1 & ((unsigned InputType)num >> (Bits_Number<decltype(num)>() - 1));
}


inline auto IsNegative(const InputType num) {
    return num < 0;
}


/** Check if a number is positive, negative or zero using bit operators
 *
 * @reference   https://www.geeksforgeeks.org/check-number-positive-negative-zero-using-bit-operators/
 */
int IsNegativeOrZeroOrPositive(const InputType num) {
    constexpr auto BITS_NUM = Bits_Number<decltype(num)>() - 1;
    return 1 + (num >> BITS_NUM) - (-num >> BITS_NUM);
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(IsNegative_Portable, -1);
SIMPLE_BENCHMARK(IsNegative_Portable, 0);
SIMPLE_BENCHMARK(IsNegative_Portable, LOWER);
SIMPLE_BENCHMARK(IsNegative_Portable, UPPER);

SIMPLE_TEST(IsNegative_Portable, TestSample1, true, -1);
SIMPLE_TEST(IsNegative_Portable, TestSample2, false, 0);
SIMPLE_TEST(IsNegative_Portable, TestSample3, true, LOWER);
SIMPLE_TEST(IsNegative_Portable, TestSample4, false, UPPER);

MUTUAL_RANDOM_TEST(IsNegative_Portable, IsNegative, LOWER, UPPER);


SIMPLE_BENCHMARK(IsNegativeOrZeroOrPositive, UPPER);

SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample1, 0, -1);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample2, 0, -20);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample3, 0, -UPPER);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample4, 1, 0);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample5, 2, 1);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample6, 2, 30);
SIMPLE_TEST(IsNegativeOrZeroOrPositive, TestSample7, 2, UPPER);
