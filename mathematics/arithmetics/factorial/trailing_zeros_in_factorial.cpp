#include "common_header.h"

#include "mathematics/numbers/prime/largest_power_of_p_divides_factorial_n.h"

namespace {

typedef unsigned InputType;

/**
 * @reference   Count trailing zeros in factorial of a number
 *              http://www.geeksforgeeks.org/count-trailing-zeroes-factorial-number/
 *
 * Given an integer n, write a function that returns count of trailing zeros in n!.
 */
InputType CountTrailing0sInFactorialOf(const InputType num) {
    return LargestPowerOfPDividesFactorialN(5, num);
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();
constexpr InputType SAMPLE1 = 5;
constexpr InputType SAMPLE2 = 20;
constexpr InputType SAMPLE3 = 21;
constexpr InputType SAMPLE4 = 100;

SIMPLE_BENCHMARK(CountTrailing0sInFactorialOf, LOWER);
SIMPLE_BENCHMARK(CountTrailing0sInFactorialOf, UPPER);
RANDOM_BENCHMARK(CountTrailing0sInFactorialOf, LOWER, UPPER);

SIMPLE_TEST(CountTrailing0sInFactorialOf, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE3, 4, SAMPLE3);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE4, 24, SAMPLE4);
