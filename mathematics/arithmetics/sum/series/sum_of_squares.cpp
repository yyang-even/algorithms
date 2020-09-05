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
auto SumOfSquares(const unsigned N) {
    return (N * (N + 1) * (2 * N + 1)) / 6;
}


auto SumOfSquares_2(const unsigned N) {
    return ((N * (N + 1) / 2) * (2 * N + 1)) / 3;
}


/** Average of Squares of Natural Numbers
 *
 * @reference   https://www.geeksforgeeks.org/average-squares-natural-numbers/
 */
auto AverageOfSquaresOfNaturalNumbers(const unsigned N) {
    return static_cast<double>((N + 1) * (2 * N + 1)) / 6.0;
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


SIMPLE_BENCHMARK(SumOfSquares, Sample1, 7);

SIMPLE_TEST(SumOfSquares, TestSAMPLE1, 5u, 2);
SIMPLE_TEST(SumOfSquares, TestSAMPLE2, 204u, 8);
SIMPLE_TEST(SumOfSquares, TestSAMPLE3, 385u, 10);
SIMPLE_TEST(SumOfSquares, TestSAMPLE4, 55u, 5);


SIMPLE_BENCHMARK(SumOfSquareSums, Sample1, 7);

SIMPLE_TEST(SumOfSquareSums, TestSAMPLE1, 6u, 2);
SIMPLE_TEST(SumOfSquareSums, TestSAMPLE2, 20u, 3);


SIMPLE_BENCHMARK(SumOfSquares_2, Sample1, 7);

SIMPLE_TEST(SumOfSquares_2, TestSAMPLE1, 5u, 2);
SIMPLE_TEST(SumOfSquares_2, TestSAMPLE2, 204u, 8);
SIMPLE_TEST(SumOfSquares_2, TestSAMPLE3, 385u, 10);


SIMPLE_BENCHMARK(AverageOfSquaresOfNaturalNumbers, Sample1, 7);

SIMPLE_TEST(AverageOfSquaresOfNaturalNumbers, TestSAMPLE1, 2.5, 2);
