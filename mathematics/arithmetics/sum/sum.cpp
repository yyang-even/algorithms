#include "common_header.h"


namespace {

/** C Program to Add two Integers
 *
 * @reference   https://www.geeksforgeeks.org/c-program-to-add-two-integers/
 */


/** To find sum of two numbers without using any operator
 *
 * @reference   https://www.geeksforgeeks.org/to-find-sum-of-two-numbers-without-using-any-operator/
 *
 * Write a C program to find sum of positive integers without using any operator. Only
 * use of printf() is allowed. No other library function can be used.
 */
inline constexpr auto Sum_Printf(const unsigned a, const unsigned b) {
    return printf("%*c%*c", a, ' ', b, ' ');
}


/** Add two numbers without using arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/add-two-numbers-without-using-arithmetic-operators/
 *
 * Write a function Add() that returns sum of two integers. The function should not use
 * any of the arithmetic operators (+, ++, --, -, .. etc).
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.1.
 */
constexpr auto Sum_HalfAdder_Iterative(int a, int b) {
    while (b) {
        const auto carry = a & b;
        a ^= b;
        b = carry << 1;
    }
    return a;
}

inline constexpr auto
Sum_HalfAdder_Recursive(const int a, const int b) {
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
 * Given two integers a and b, how can we evaluate the sum a + b without using operators
 * such as +, -, ++, --, ...?
 */
inline constexpr auto Sum_Pointer(const int a, const int b) {
    const char *p = reinterpret_cast<char *>(a);
    return reinterpret_cast<long>(&p[b]);
}


/** Add two numbers using ++ and/or --
 *
 * @reference   https://www.geeksforgeeks.org/add-two-numbers-using-andor/
 */
constexpr auto Sum_Loop(int a, int b) {
    if (b > 0) {
        for (; b--; ++a);
    } else if (b < 0) {
        for (; b++; --a);
    }

    return a;
}


/** Add 1 to a given number
 *
 * @reference   https://www.geeksforgeeks.org/add-1-to-a-given-number/
 *
 * Write a program to add one to a given number. The use of operators like '+', '-', '*',
 * '/', '++', '--' ...etc are not allowed.
 *
 * ~x = -(x+1)
 */
inline constexpr auto Add1_HalfAdder(const int x) {
    return Sum_HalfAdder_Iterative(x, 1);
}


inline constexpr auto Add1_2sComplement(const int x) {
    return -(~x);
}

}//namespace


THE_BENCHMARK(Sum_Printf, 3, 4);

SIMPLE_TEST(Sum_Printf, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(Sum_Printf, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(Sum_Printf, TestSAMPLE3, 47, 15, 32);


THE_BENCHMARK(Sum_HalfAdder_Iterative, 3, 4);

SIMPLE_TEST(Sum_HalfAdder_Iterative, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(Sum_HalfAdder_Iterative, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(Sum_HalfAdder_Iterative, TestSAMPLE3, 47, 15, 32);


THE_BENCHMARK(Sum_HalfAdder_Recursive, 3, 4);

SIMPLE_TEST(Sum_HalfAdder_Recursive, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(Sum_HalfAdder_Recursive, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(Sum_HalfAdder_Recursive, TestSAMPLE3, 47, 15, 32);


THE_BENCHMARK(Sum_Pointer, 3, 4);

SIMPLE_TEST(Sum_Pointer, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(Sum_Pointer, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(Sum_Pointer, TestSAMPLE3, 47, 15, 32);


THE_BENCHMARK(Sum_Loop, 3, 4);

SIMPLE_TEST(Sum_Loop, TestSAMPLE1, 7, 3, 4);
SIMPLE_TEST(Sum_Loop, TestSAMPLE2, 15, 5, 10);
SIMPLE_TEST(Sum_Loop, TestSAMPLE3, 47, 15, 32);


THE_BENCHMARK(Add1_HalfAdder, 4);

SIMPLE_TEST(Add1_HalfAdder, TestSAMPLE1, 7, 6);
SIMPLE_TEST(Add1_HalfAdder, TestSAMPLE2, 14, 13);


THE_BENCHMARK(Add1_2sComplement, 4);

SIMPLE_TEST(Add1_2sComplement, TestSAMPLE1, 7, 6);
SIMPLE_TEST(Add1_2sComplement, TestSAMPLE2, 14, 13);
