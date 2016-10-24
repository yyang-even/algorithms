#include "common_header.h"

typedef unsigned InputType;

/**
 * @reference   Count digits in a factorial | Set 1
 *              http://www.geeksforgeeks.org/count-digits-factorial-set-1/
 *
 * Given an integer n, find the number of digits that appear in its factorial,
 * where factorial is defined as, factorial(n) = 1*2*3*4……..*n and factorial(0) = 1
 */
InputType CountDigitsInAFactorial(const InputType n) {
    if (n <= 1) {
        return 1;
    }

    double digits = 0.0;
    for (InputType i = 2; i <= n; ++i) {
        digits += std::log10(i);
    }

    return std::floor(digits) + 1;
}

/**
 * @reference   Count digits in a factorial | Set 2
 *              http://www.geeksforgeeks.org/count-digits-factorial-set-2/
 */
unsigned long long CountDigitsInAFactorialKamenetsky(const InputType n) {
    if (n <= 1) {
        return 1ULL;
    }

    // Use Kamenetsky formula to calculate the
    // number of digits
    double digits = ((n * std::log10(n / M_E) + std::log10(2 * M_PI * n) / 2.0));

    return std::floor(digits) + 1;
}

const InputType LOWER = 0;

SIMPLE_BENCHMARK(CountDigitsInAFactorial, LOWER);
SIMPLE_BENCHMARK(CountDigitsInAFactorial, 120);

SIMPLE_TEST(CountDigitsInAFactorial, TestLOWER, 1, LOWER);
SIMPLE_TEST(CountDigitsInAFactorial, TestSAMPLE1, 1, 1);
SIMPLE_TEST(CountDigitsInAFactorial, TestSAMPLE2, 3, 5);
SIMPLE_TEST(CountDigitsInAFactorial, TestSAMPLE3, 7, 10);
SIMPLE_TEST(CountDigitsInAFactorial, TestSAMPLE4, 199, 120);

const InputType UPPER = UINT_MAX;

SIMPLE_BENCHMARK(CountDigitsInAFactorialKamenetsky, LOWER);
SIMPLE_BENCHMARK(CountDigitsInAFactorialKamenetsky, UPPER);
SIMPLE_BENCHMARK(CountDigitsInAFactorialKamenetsky, 120);
RANDOM_BENCHMARK(CountDigitsInAFactorialKamenetsky, LOWER, UPPER)

SIMPLE_TEST(CountDigitsInAFactorialKamenetsky, TestLOWER, 1, LOWER);
SIMPLE_TEST(CountDigitsInAFactorialKamenetsky, TestSAMPLE1, 1, 1);
SIMPLE_TEST(CountDigitsInAFactorialKamenetsky, TestSAMPLE2, 7, 10);
SIMPLE_TEST(CountDigitsInAFactorialKamenetsky, TestSAMPLE3, 199, 120);
SIMPLE_TEST(CountDigitsInAFactorialKamenetsky, TestSAMPLE4, 363233781, 50000000);
SIMPLE_TEST(CountDigitsInAFactorialKamenetsky, TestSAMPLE5, 8565705523, 1000000000);
