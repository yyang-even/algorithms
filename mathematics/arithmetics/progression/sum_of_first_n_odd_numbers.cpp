#include "common_header.h"


namespace {

/** Sum of first n odd numbers in O(1) Complexity
 *
 * @reference   https://www.geeksforgeeks.org/sum-first-n-odd-numbers-o1-complexity/
 *
 * To find the sum of first n odd numbers we can apply odd number theorem, it states
 * that the sum of first n odd numbers is equal to the square of n.
 */
inline constexpr auto SumOfFirstNOddNumbers(const unsigned N) {
    return N * N;
}


/**
 * @reference   Average of first n odd naturals numbers
 *              https://www.geeksforgeeks.org/average-of-first-n-odd-naturals-numbers/
 */


/**
 * @reference   Sum of all odd natural numbers in range L and R
 *              https://www.geeksforgeeks.org/sum-of-all-odd-natural-numbers-in-range-l-and-r/
 */
inline constexpr auto SumOfOddNumbersTillN(const unsigned N) {
    return SumOfFirstNOddNumbers((N + 1) / 2);
}

inline constexpr auto
SumOfFirstNOddNumbersInRange(const unsigned L, const unsigned R) {
    assert(L);
    assert(L <= R);

    return SumOfOddNumbersTillN(R) - SumOfOddNumbersTillN(L - 1);
}

}//namespace


THE_BENCHMARK(SumOfFirstNOddNumbers, 10);

SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE1, 100, 10);
SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE2, 25, 5);
SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE3, 4, 2);


THE_BENCHMARK(SumOfFirstNOddNumbersInRange, 2, 5);

SIMPLE_TEST(SumOfFirstNOddNumbersInRange, TestSAMPLE1, 8, 2, 5);
SIMPLE_TEST(SumOfFirstNOddNumbersInRange, TestSAMPLE2, 40, 7, 13);
