#include "common_header.h"

typedef unsigned InputType;

/**
 * @reference   Count factorial numbers in a given range
 *              http://www.geeksforgeeks.org/count-factorial-numbers-in-a-given-range/
 *
 * A number F is a factorial number if there exists some integer I >= 0 such that F = I!
 * (that is, F is factorial of I). Examples of factorial numbers are 1, 2, 6, 24, 120, ….
 * Write a program that takes as input two long integers ‘low’ and ‘high’ where
 * 0 < low < high and finds count of factorial numbers in the closed interval [low, high].
 */
InputType CountFactorialNumInRange(const InputType low, const InputType high) {
    if (low > high) {
        return 0;
    }

    unsigned long long F = 1ULL;
    InputType i = 2;
    //Find the first F >= low
    for (; F < low; ++i) {
        F *= i;
    }

    //Find the first F > high
    InputType count = 0;
    for (; F <= high; ++i) {
        ++count;
        F *= i;
    }

    return count;
}


const InputType LOWER = 0;
const InputType UPPER = UINT_MAX;

SIMPLE_BENCHMARK(CountFactorialNumInRange, LOWER, 1);
SIMPLE_BENCHMARK(CountFactorialNumInRange, LOWER, UPPER);
SIMPLE_BENCHMARK(CountFactorialNumInRange, 2, 10);

SIMPLE_TEST(CountFactorialNumInRange, TestSAMPLE1, 1, 0, 1);
SIMPLE_TEST(CountFactorialNumInRange, TestSAMPLE2, 2, 12, 122);
SIMPLE_TEST(CountFactorialNumInRange, TestSAMPLE3, 5, 2, 720);
SIMPLE_TEST(CountFactorialNumInRange, TestUPPER, 12, LOWER, UPPER);
