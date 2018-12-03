#include "common_header.h"

/** To find sum of two numbers without using any operator
 *
 * @reference   https://www.geeksforgeeks.org/to-find-sum-of-two-numbers-without-using-any-operator/
 *
 * Write a C program to find sum of positive integers without using any operator.
 * Only use of printf() is allowed. No other library function can be used.
 */
auto SumPrintf(const unsigned a, const unsigned b) {
    return printf("%*c%*c", a, ' ', b, ' ');
}


/** Add two numbers without using arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/add-two-numbers-without-using-arithmetic-operators/
 *
 * Write a function Add() that returns sum of two integers. The function should
 * not use any of the arithmetic operators (+, ++, –, -, .. etc).
 */
auto SumHalfAdderIterative(unsigned a, unsigned b) {
    while (b) {
        const auto carry = a & b;
        a ^= b;
        b = carry << 1;
    }
    return a;
}

auto SumHalfAdderRecursive(const unsigned a, const unsigned b) {
    if (b == 0) {
        return a;
    } else {
        return SumHalfAdderRecursive(a ^ b, (a & b) << 1);
    }
}


SIMPLE_BENCHMARK(SumPrintf, 3, 4);

SIMPLE_TEST(SumPrintf, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(SumPrintf, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(SumPrintf, TestSAMPLE3, 47, 15, 32);


SIMPLE_BENCHMARK(SumHalfAdderIterative, 3, 4);

SIMPLE_TEST(SumHalfAdderIterative, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(SumHalfAdderIterative, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(SumHalfAdderIterative, TestSAMPLE3, 47, 15, 32);


SIMPLE_BENCHMARK(SumHalfAdderRecursive, 3, 4);

SIMPLE_TEST(SumHalfAdderRecursive, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(SumHalfAdderRecursive, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(SumHalfAdderRecursive, TestSAMPLE3, 47, 15, 32);
