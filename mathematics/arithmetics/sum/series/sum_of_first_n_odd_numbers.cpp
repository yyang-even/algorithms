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

}//namespace


SIMPLE_BENCHMARK(SumOfFirstNOddNumbers, 10);

SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE1, 100u, 10);
SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE2, 25u, 5);
SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE3, 4u, 2);
