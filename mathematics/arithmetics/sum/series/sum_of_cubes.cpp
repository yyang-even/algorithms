#include "common_header.h"


namespace {

/** Program for cube sum of first n natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/program-cube-sum-first-n-natural-numbers/
 * @reference   C++ Program for cube sum of first n natural numbers
 *              https://www.geeksforgeeks.org/cpp-program-for-program-for-cube-sum-of-first-n-natural-numbers/
 * @reference   C Program for cube sum of first n natural numbers
 *              https://www.geeksforgeeks.org/c-program-for-program-for-cube-sum-of-first-n-natural-numbers/
 *
 * Print the sum of series 1^3 + 2^3 + 3^3 + 4^3 + ... + n^3 till n-th term.
 */
constexpr inline auto SumOfCubes(const unsigned N) {
    const unsigned long long x = (N * (N + 1) / 2);
    return x * x;
}


/** Sum of cubes of first n odd natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-cubes-of-first-n-odd-natural-numbers/
 *
 * Given a number n, find sum of first n odd natural numbers.
 */
constexpr inline auto SumOfOddCubes(const unsigned N) {
    return N * N * (2 * N * N - 1);
}


/** Sum of cubes of first n even numbers
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-cubes-of-first-n-even-numbers/
 *
 * Given a number n, find sum of first n even natural numbers.
 */
constexpr inline auto SumOfEvenCubes(const unsigned N) {
    return 2 * N * N * (N + 1) * (N + 1);
}

}//namespace


THE_BENCHMARK(SumOfCubes, 7);

SIMPLE_TEST(SumOfCubes, TestSAMPLE1, 225, 5);
SIMPLE_TEST(SumOfCubes, TestSAMPLE2, 784, 7);


THE_BENCHMARK(SumOfOddCubes, 7);

SIMPLE_TEST(SumOfOddCubes, TestSAMPLE1, 28, 2);
SIMPLE_TEST(SumOfOddCubes, TestSAMPLE2, 496, 4);


THE_BENCHMARK(SumOfEvenCubes, 7);

SIMPLE_TEST(SumOfEvenCubes, TestSAMPLE1, 72, 2);
SIMPLE_TEST(SumOfEvenCubes, TestSAMPLE2, 800, 4);
SIMPLE_TEST(SumOfEvenCubes, TestSAMPLE3, 10368, 8);
