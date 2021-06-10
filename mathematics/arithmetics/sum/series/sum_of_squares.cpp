#include "common_header.h"


namespace {

/** Sum of squares of first n natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-squares-of-first-n-natural-numbers/
 * @reference   Sum of squares of first n natural numbers
 *              https://www.geeksforgeeks.org/sum-squares-first-n-natural-numbers/
 * @reference   Program to find the sum of a Series (1*1) + (2*2) + (3*3) + (4*4) + (5*5) + … + (n*n)
 *              https://www.geeksforgeeks.org/program-find-sum-series-11-22-33-44-55-nn/
 * @reference   Sum of the series 1^1 + 2^2 + 3^3 + ….. + n^n using recursion
 *              https://www.geeksforgeeks.org/sum-of-the-series-11-22-33-nn-using-recursion/
 *
 * Given n, find sum of squares of first n natural numbers.
 */
inline constexpr auto SumOfSquares(const unsigned N) {
    return (N * (N + 1) * (2 * N + 1)) / 6;
}


inline constexpr auto SumOfSquares_2(const unsigned N) {
    return ((N * (N + 1) / 2) * (2 * N + 1)) / 3;
}


/** Average of Squares of Natural Numbers
 *
 * @reference   https://www.geeksforgeeks.org/average-squares-natural-numbers/
 */
inline constexpr auto
AverageOfSquaresOfNaturalNumbers(const unsigned N) {
    return static_cast<double>((N + 1) * (2 * N + 1)) / 6.0;
}


/** Sum of square-sums of first n natural numbers
 *
 * reference    https://www.geeksforgeeks.org/sum-square-sums-first-n-natural-numbers/
 *
 * Given a positive integer n. The task is to find the sum of the sum of square of first
 * n natural number.
 */
inline constexpr auto
SumOfSquareSums(const unsigned N) {
    return (N * (N + 1) * (N + 1) * (N + 2)) / 12;
}

}//namespace


THE_BENCHMARK(SumOfSquares, 7);

SIMPLE_TEST(SumOfSquares, TestSAMPLE1, 5, 2);
SIMPLE_TEST(SumOfSquares, TestSAMPLE2, 204, 8);
SIMPLE_TEST(SumOfSquares, TestSAMPLE3, 385, 10);
SIMPLE_TEST(SumOfSquares, TestSAMPLE4, 55, 5);


THE_BENCHMARK(SumOfSquareSums, 7);

SIMPLE_TEST(SumOfSquareSums, TestSAMPLE1, 6, 2);
SIMPLE_TEST(SumOfSquareSums, TestSAMPLE2, 20, 3);


THE_BENCHMARK(SumOfSquares_2, 7);

SIMPLE_TEST(SumOfSquares_2, TestSAMPLE1, 5, 2);
SIMPLE_TEST(SumOfSquares_2, TestSAMPLE2, 204, 8);
SIMPLE_TEST(SumOfSquares_2, TestSAMPLE3, 385, 10);


THE_BENCHMARK(AverageOfSquaresOfNaturalNumbers, 7);

SIMPLE_TEST(AverageOfSquaresOfNaturalNumbers, TestSAMPLE1, 2.5, 2);
