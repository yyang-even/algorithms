#include "common_header.h"

#include "mathematics/numbers/prime/largest_power_of_p_divides_factorial_n.h"


namespace {

/**
 * @reference   Count trailing zeros in factorial of a number
 *              https://www.geeksforgeeks.org/count-trailing-zeroes-factorial-number/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.3.
 *
 * Given an integer n, write a function that returns count of trailing zeros in n!.
 */
inline constexpr unsigned CountTrailing0sInFactorialOf(const unsigned num) {
    return LargestPowerOfPDividesFactorialN(5, num);
}


/**
 * @reference   Trailing number of 0s in product of two factorials
 *              https://www.geeksforgeeks.org/trailing-number-0s-product-two-factorials/
 */


/** Find the smallest number X such that X! contains at least Y trailing zeros.
 *
 * @reference   https://www.geeksforgeeks.org/find-the-smallest-number-x-such-that-x-contains-at-least-y-trailing-zeros/
 * @reference   Smallest number with at least n trailing zeroes in factorial
 *              https://www.geeksforgeeks.org/smallest-number-least-n-trailing-zeroes-factorial/
 */
constexpr auto
SmallestNumberWhoseFactorialContainsYTrailingZeros(const unsigned Y) {
    unsigned low = 0;
    unsigned high = Y * 5;

    while (low < high) {
        const auto mid = (low + high) / 2;
        const auto trailing_zeros = CountTrailing0sInFactorialOf(mid);
        if (trailing_zeros < Y) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}


/** Numbers whose factorials end with n zeros
 *
 * @reference   https://www.geeksforgeeks.org/numbers-whose-factorials-end-with-n-zeros/
 *
 * Given an integer n, we need to find the number of positive integers whose factorial
 * ends with n zeros.
 */
inline auto
FindNumbersWhoseFactorialsEndWithNZeros_BinarySearch(const unsigned N) {
    auto lower_bound = SmallestNumberWhoseFactorialContainsYTrailingZeros(N);

    std::vector<unsigned> outputs(5, lower_bound);
    std::generate_n(outputs.begin(), 5, [&lower_bound]() {
        return lower_bound++;
    });

    return outputs;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();
constexpr unsigned SAMPLE1 = 5;
constexpr unsigned SAMPLE2 = 20;
constexpr unsigned SAMPLE3 = 21;
constexpr unsigned SAMPLE4 = 100;


SIMPLE_BENCHMARK(CountTrailing0sInFactorialOf, Sample1, LOWER);
SIMPLE_BENCHMARK(CountTrailing0sInFactorialOf, Sample2, UPPER);

SIMPLE_TEST(CountTrailing0sInFactorialOf, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE3, 4, SAMPLE3);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE4, 24, SAMPLE4);


THE_BENCHMARK(SmallestNumberWhoseFactorialContainsYTrailingZeros, 10);

SIMPLE_TEST(SmallestNumberWhoseFactorialContainsYTrailingZeros, TestSAMPLE1, 10, 2);
SIMPLE_TEST(SmallestNumberWhoseFactorialContainsYTrailingZeros, TestSAMPLE2, 25, 6);
SIMPLE_TEST(SmallestNumberWhoseFactorialContainsYTrailingZeros, TestSAMPLE3, 45, 10);


const std::vector<unsigned> EXPECTED1 = {5, 6, 7, 8, 9};
const std::vector<unsigned> EXPECTED2 = {10, 11, 12, 13, 14};


THE_BENCHMARK(FindNumbersWhoseFactorialsEndWithNZeros_BinarySearch, 2);

SIMPLE_TEST(FindNumbersWhoseFactorialsEndWithNZeros_BinarySearch, TestSAMPLE1,
            EXPECTED1, 1);
SIMPLE_TEST(FindNumbersWhoseFactorialsEndWithNZeros_BinarySearch, TestSAMPLE2,
            EXPECTED2, 2);
