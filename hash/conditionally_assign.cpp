#include "common_header.h"


namespace {

/** Conditionally assign a value without using conditional and arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/conditionally-assign-value-without-using-conditional-arithmetic-operators/
 * @reference   Set a variable without using Arithmetic, Relational or Conditional Operator
 *              https://www.geeksforgeeks.org/set-variable-without-using-arithmetic-relational-conditional-operator/
 * @reference   Programming puzzle (Assign value without any control statement)
 *              https://www.geeksforgeeks.org/programming-puzzle-assign-value-without-control-statement/
 * @reference   Print “Even” or “Odd” without using conditional statement
 *              https://www.geeksforgeeks.org/even-or-odd-without-using-condtional-statement/
 * @reference   Implementing ternary operator without any conditional statement
 *              https://www.geeksforgeeks.org/implementing-ternary-operator-without-conditional-statement/
 *
 * Given 4 integers a, b, y, and x, where x can only either 0 and 1 only. The ask is as
 * follows:
 *  If 'x' is 0,
 *      Assign value 'a' to variable 'y'
 *  Else (If 'x' is 1)
 *      Assign value 'b' to variable 'y'.
 * Note: You are not allowed to use any conditional operator (including ternary operator)
 * or any arithmetic operator ( +, -, *, /).
 */
constexpr inline auto
ConditionallyAssign(const int a, const int b, const bool x) {
    const int table[] = {a, b};
    return table[x];
}


/** Conditionally assign a value using arithmetic operators
 */
constexpr inline auto
ConditionallyAssign_Arithmetic(const int a, const int b, const bool x) {
    return (1 - x) * a + x * b;
}


constexpr inline auto
ConditionallyAssign_Not(const int a, const int b, const bool x) {
    return (!x) * a + (!!x) * b;
}

}//namespace


THE_BENCHMARK(ConditionallyAssign, 5, 10, 1);

SIMPLE_TEST(ConditionallyAssign, TestSample1, 10, 5, 10, 1);
SIMPLE_TEST(ConditionallyAssign, TestSample2, 5, 5, 10, 0);


THE_BENCHMARK(ConditionallyAssign_Arithmetic, 5, 10, 1);

SIMPLE_TEST(ConditionallyAssign_Arithmetic, TestSample1, 10, 5, 10, 1);
SIMPLE_TEST(ConditionallyAssign_Arithmetic, TestSample2, 5, 5, 10, 0);


THE_BENCHMARK(ConditionallyAssign_Not, 5, 10, 1);

SIMPLE_TEST(ConditionallyAssign_Not, TestSample1, 10, 5, 10, 1);
SIMPLE_TEST(ConditionallyAssign_Not, TestSample2, 5, 5, 10, 0);
