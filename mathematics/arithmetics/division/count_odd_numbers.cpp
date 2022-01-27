#include "common_header.h"


namespace {

inline constexpr auto CountOddNumbersNoGreaterThan(const int n) {
    return (n + 1) / 2;
}


/** Count Odd Numbers in an Interval Range
 *
 * @reference   https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/
 *
 * Given two non-negative integers low and high. Return the count of odd numbers between
 * low and high (inclusive).
 */
inline constexpr auto CountOddNumbers(const int low, const int high) {
    return (high + 1) / 2 - low / 2;
}

}//namespace


THE_BENCHMARK(CountOddNumbers, 3, 7);

SIMPLE_TEST(CountOddNumbers, TestSAMPLE1, 3, 3, 7);
SIMPLE_TEST(CountOddNumbers, TestSAMPLE2, 2, 3, 6);
SIMPLE_TEST(CountOddNumbers, TestSAMPLE3, 2, 4, 7);
SIMPLE_TEST(CountOddNumbers, TestSAMPLE4, 1, 8, 10);


THE_BENCHMARK(CountOddNumbersNoGreaterThan, 7);

SIMPLE_TEST(CountOddNumbersNoGreaterThan, TestSAMPLE1, 4, 7);
SIMPLE_TEST(CountOddNumbersNoGreaterThan, TestSAMPLE2, 4, 8);
