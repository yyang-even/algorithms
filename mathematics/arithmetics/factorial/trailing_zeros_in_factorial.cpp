#include "common_header.h"

#include "mathematics/numbers/prime/prime.h"

typedef unsigned InputType;

/**
 * @reference   Count trailing zeros in factorial of a number
 *              http://www.geeksforgeeks.org/count-trailing-zeroes-factorial-number/
 *
 * Given an integer n, write a function that returns count of trailing zeros in n!.
 */
InputType CountTrailing0sInFactorialOf(const InputType num) {
    return LargestPowerOfPDividesFactorialN(5, num);
}


const InputType LOWER = 0;
const InputType UPPER = UINT_MAX;
const InputType SAMPLE1 = 5;
const InputType SAMPLE2 = 20;
const InputType SAMPLE3 = 21;
const InputType SAMPLE4 = 100;

SIMPLE_BENCHMARK(CountTrailing0sInFactorialOf, LOWER);
SIMPLE_BENCHMARK(CountTrailing0sInFactorialOf, UPPER);
RANDOM_BENCHMARK(CountTrailing0sInFactorialOf, LOWER, UPPER);

SIMPLE_TEST(CountTrailing0sInFactorialOf, TestLOWER, 0, LOWER);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE3, 4, SAMPLE3);
SIMPLE_TEST(CountTrailing0sInFactorialOf, TestSAMPLE4, 24, SAMPLE4);
