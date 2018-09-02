#include "common_header.h"

using InputType = int;

/** Check if two numbers are equal without using comparison operators
 *
 * @reference   https://www.geeksforgeeks.org/check-two-numbers-equal-without-using-comparison-operators/
 *
 * Following are not allowed to use
 * 1) Comparison Operators
 * 2) String functions
 */
INT_BOOL EqualXor(const InputType lhs, const InputType rhs) {
    return not(lhs ^ rhs);
}

INT_BOOL EqualSubtract(const InputType lhs, const InputType rhs) {
    return not(lhs - rhs);
}


SIMPLE_BENCHMARK(EqualXor, 0, 4);

SIMPLE_TEST(EqualXor, TestSample1, TRUE, 1233, 1233);
SIMPLE_TEST(EqualXor, TestSample2, FALSE, 123, 321);


SIMPLE_BENCHMARK(EqualSubtract, 0, 4);

SIMPLE_TEST(EqualSubtract, TestSample1, TRUE, 1233, 1233);
SIMPLE_TEST(EqualSubtract, TestSample2, FALSE, 123, 321);
