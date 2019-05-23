#include "common_header.h"

namespace {

/** To find sum of two numbers without using any operator
 *
 * @reference   https://www.geeksforgeeks.org/to-find-sum-of-two-numbers-without-using-any-operator/
 *
 * Write a C program to find sum of positive integers without using any operator.
 * Only use of printf() is allowed. No other library function can be used.
 */
auto Sum_Printf(const unsigned a, const unsigned b) {
    return printf("%*c%*c", a, ' ', b, ' ');
}


/** Add two numbers without using arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/add-two-numbers-without-using-arithmetic-operators/
 *
 * Write a function Add() that returns sum of two integers. The function should
 * not use any of the arithmetic operators (+, ++, --, -, .. etc).
 */
auto Sum_HalfAdder_Iterative(int a, int b) {
    while (b) {
        const auto carry = a & b;
        a ^= b;
        b = carry << 1;
    }
    return a;
}

auto Sum_HalfAdder_Recursive(const int a, const int b) {
    if (b == 0) {
        return a;
    } else {
        return Sum_HalfAdder_Recursive(a ^ b, (a & b) << 1);
    }
}


/** How to sum two integers without using arithmetic operators in C/C++?
 *
 * @reference   https://www.geeksforgeeks.org/how-to-sum-two-integers-without-using-arithmetic-operators-in-cc/
 *
 * Given two integers a and b, how can we evaluate the sum a + b without using
 * operators such as +, -, ++, --, …?
 */
auto Sum_Pointer(const int a, const int b) {
    const char *p = reinterpret_cast<char *>(a);
    return reinterpret_cast<long>(&p[b]);
}

}//namespace


SIMPLE_BENCHMARK(Sum_Printf, 3, 4);

SIMPLE_TEST(Sum_Printf, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(Sum_Printf, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(Sum_Printf, TestSAMPLE3, 47, 15, 32);


SIMPLE_BENCHMARK(Sum_HalfAdder_Iterative, 3, 4);

SIMPLE_TEST(Sum_HalfAdder_Iterative, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(Sum_HalfAdder_Iterative, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(Sum_HalfAdder_Iterative, TestSAMPLE3, 47, 15, 32);


SIMPLE_BENCHMARK(Sum_HalfAdder_Recursive, 3, 4);

SIMPLE_TEST(Sum_HalfAdder_Recursive, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(Sum_HalfAdder_Recursive, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(Sum_HalfAdder_Recursive, TestSAMPLE3, 47, 15, 32);


SIMPLE_BENCHMARK(Sum_Pointer, 3, 4);

SIMPLE_TEST(Sum_Pointer, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(Sum_Pointer, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(Sum_Pointer, TestSAMPLE3, 47, 15, 32);
