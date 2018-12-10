#include "common_header.h"

/** Conditionally assign a value without using conditional and arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/conditionally-assign-value-without-using-conditional-arithmetic-operators/
 *
 * Given 4 integers a, b, y, and x, where x can only either 0 and 1 only.
 * The ask is as follows:
 * If 'x' is 0,
 *    Assign value 'a' to variable 'y'
 * Else (If 'x' is 1)
 *    Assign value 'b' to variable 'y'.
 * Note: – You are not allowed to use any conditional operator (including
 * ternary operator) or any arithmetic operator ( +, -, *, /).
 */
auto ConditionallyAssign(const int a, const int b, const bool x) {
    const int table[] = {a, b};
    return table[x];
}


SIMPLE_BENCHMARK(ConditionallyAssign, 5, 10, 1);

SIMPLE_TEST(ConditionallyAssign, TestSample1, 10, 5, 10, 1);
SIMPLE_TEST(ConditionallyAssign, TestSample2, 5, 5, 10, 0);
