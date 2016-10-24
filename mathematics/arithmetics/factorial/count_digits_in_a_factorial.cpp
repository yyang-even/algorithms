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
    for (unsigned long long i = 2; i <= n; ++i) {
        digits += std::log10(i);
    }

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
