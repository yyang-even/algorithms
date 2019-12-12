#include "common_header.h"

#include "mathematics/numbers/prime/largest_power_of_p_divides_factorial_n.h"


namespace {

/**
 * @reference   Count trailing zeros in factorial of a number
 *              https://www.geeksforgeeks.org/count-trailing-zeroes-factorial-number/
 *
 * Given an integer n, write a function that returns count of trailing zeros in n!.
 */
unsigned CountTrailing0sInFactorialOf(const unsigned num) {
    return LargestPowerOfPDividesFactorialN(5, num);
}


/** Numbers whose factorials end with n zeros
 *
 * @reference   https://www.geeksforgeeks.org/numbers-whose-factorials-end-with-n-zeros/
 *
 * Given an integer n, we need to find the number of positive integers whose factorial ends with n zeros.
 */
auto FindNumbersWhoseFactorialsEndWithNZeros_BinarySearch(const unsigned N) {
    unsigned low = 0;
    unsigned high = LARGE_PRIME;

    while (low < high) {
        const auto mid = (low + high) / 2;
        const auto trailing_zeros = CountTrailing0sInFactorialOf(mid);
        if (trailing_zeros < N) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    std::vector<unsigned> outputs;
    while (CountTrailing0sInFactorialOf(low) == N) {
        outputs.push_back(low++);
    }

    return outputs;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();
constexpr unsigned SAMPLE1 = 5;
constexpr unsigned SAMPLE2 = 20;
constexpr unsigned SAMPLE3 = 21;
constexpr unsigned SAMPLE4 = 100;


SIMPLE_BENCHMARK(CountTrailing0sInFactorialOf, LOWER);
SIMPLE_BENCHMARK(CountTrailing0sInFactorialOf, UPPER);
RANDOM_BENCHMARK(CountTrailing0sInFactorialOf, LOWER, UPPER);

SIMPLE_TEST(CountTrailing0sInFactorialOf, TestLOWER, 0u, LOWER);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE1, 1u, SAMPLE1);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE2, 4u, SAMPLE2);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE3, 4u, SAMPLE3);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE4, 24u, SAMPLE4);


const std::vector<unsigned> EXPECTED1 = {5, 6, 7, 8, 9};
const std::vector<unsigned> EXPECTED2 = {10, 11, 12, 13, 14};


SIMPLE_BENCHMARK(FindNumbersWhoseFactorialsEndWithNZeros_BinarySearch, 2);

SIMPLE_TEST(FindNumbersWhoseFactorialsEndWithNZeros_BinarySearch, TestSAMPLE1, EXPECTED1, 1);
SIMPLE_TEST(FindNumbersWhoseFactorialsEndWithNZeros_BinarySearch, TestSAMPLE2, EXPECTED2, 2);
