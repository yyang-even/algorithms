#include "common_header.h"

/** Check if n is divisible by power of 2 without using arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/check-n-divisible-power-2-without-using-arithmetic-operators/
 *
 * Given two positive integers n and m. The problem is to check whether n
 * is divisible by 2^m or not without using arithmetic operators.
 */
INT_BOOL IsDivisibleByPowerOf2(const unsigned n, const unsigned m) {
    return (n & ((1 << m) - 1)) == 0;
}


SIMPLE_BENCHMARK(IsDivisibleByPowerOf2, 8, 2);

SIMPLE_TEST(IsDivisibleByPowerOf2, TestSample1, TRUE, 8, 2);
SIMPLE_TEST(IsDivisibleByPowerOf2, TestSample2, FALSE, 14, 3);
