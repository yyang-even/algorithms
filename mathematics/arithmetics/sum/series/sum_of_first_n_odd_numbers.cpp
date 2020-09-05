#include "common_header.h"


namespace {

/** Sum of first n odd numbers in O(1) Complexity
 *
 * @reference   https://www.geeksforgeeks.org/sum-first-n-odd-numbers-o1-complexity/
 *
 * To find the sum of first n odd numbers we can apply odd number theorem, it states
 * that the sum of first n odd numbers is equal to the square of n.
 */
auto SumOfFirstNOddNumbers(const unsigned N) {
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
auto SumOfOddNumbersTillN(const unsigned N) {
    return SumOfFirstNOddNumbers((N + 1) / 2);
}

auto SumOfFirstNOddNumbersInRange(const unsigned L, const unsigned R) {
    assert(L);
    assert(L <= R);

    return SumOfOddNumbersTillN(R) - SumOfOddNumbersTillN(L - 1);
}

}//namespace


SIMPLE_BENCHMARK(SumOfFirstNOddNumbers, Sample1, 10);

SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE1, 100u, 10);
SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE2, 25u, 5);
SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE3, 4u, 2);


SIMPLE_BENCHMARK(SumOfFirstNOddNumbersInRange, Sample1, 2, 5);

SIMPLE_TEST(SumOfFirstNOddNumbersInRange, TestSAMPLE1, 8, 2, 5);
SIMPLE_TEST(SumOfFirstNOddNumbersInRange, TestSAMPLE2, 40, 7, 13);
