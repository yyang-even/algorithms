#include "common_header.h"


namespace {

/** Sum of squares of first n natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-squares-of-first-n-natural-numbers/
 *
 * Given n, find sum of squares of first n natural numbers.
 */
auto SumOfSquares(const unsigned N) {
    return (N * (N + 1) * (2 * N + 1)) / 6;
}


/** Sum of square-sums of first n natural numbers
 *
 * reference    https://www.geeksforgeeks.org/sum-square-sums-first-n-natural-numbers/
 *
 * Given a positive integer n. The task is to find the sum of the sum of square of first n natural number.
 */
auto SumOfSquareSums(const unsigned N) {
    return (N * (N + 1) * (N + 1) * (N + 2)) / 12;
}

}//namespace


SIMPLE_BENCHMARK(SumOfSquares, 7);

SIMPLE_TEST(SumOfSquares, TestSAMPLE1, 5u, 2);
SIMPLE_TEST(SumOfSquares, TestSAMPLE2, 204u, 8);
SIMPLE_TEST(SumOfSquares, TestSAMPLE3, 385u, 10);


SIMPLE_BENCHMARK(SumOfSquareSums, 7);

SIMPLE_TEST(SumOfSquareSums, TestSAMPLE1, 6u, 2);
SIMPLE_TEST(SumOfSquareSums, TestSAMPLE2, 20u, 3);
