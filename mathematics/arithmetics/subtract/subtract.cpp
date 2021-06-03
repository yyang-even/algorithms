#include "common_header.h"

#include "subtract.h"
#include "negate.h"


namespace {

/** Subtract two numbers without using arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/subtract-two-numbers-without-using-arithmetic-operators/
 *
 * Write a function subtract(x, y) that returns x-y where x and y are integers. The
 * function should not use any of the arithmetic operators (+, ++, --, -, .. etc).
 */
constexpr inline auto Subtract_Iterative(int x, int y) {
    while (y) {
        auto borrow = ~x & y;
        x ^= y;
        y = borrow << 1;
    }

    return x;
}


constexpr inline auto Subtract_Recursive(const int x, const int y) {
    if (not y) {
        return x;
    }
    return Subtract_Recursive(x ^ y, (~x & y) << 1);
}


constexpr inline auto Subtract_Plus(const int x, const int y) {
    return x + Negate(y);
}

}//namespace


THE_BENCHMARK(Subtract_Iterative, 29, 13);

SIMPLE_TEST(Subtract_Iterative, TestSAMPLE1, 16, 29, 13);
SIMPLE_TEST(Subtract_Iterative, TestSAMPLE2, 6, 4, -2);


THE_BENCHMARK(Subtract_Recursive, 29, 13);

SIMPLE_TEST(Subtract_Recursive, TestSAMPLE1, 16, 29, 13);
SIMPLE_TEST(Subtract_Recursive, TestSAMPLE2, 6, 4, -2);


THE_BENCHMARK(Subtract_Bits, 29, 13);

SIMPLE_TEST(Subtract_Bits, TestSAMPLE1, 16, 29, 13);
SIMPLE_TEST(Subtract_Bits, TestSAMPLE2, 6, 4, -2);


THE_BENCHMARK(Subtract_Plus, 29, 13);

SIMPLE_TEST(Subtract_Plus, TestSAMPLE1, 16, 29, 13);
SIMPLE_TEST(Subtract_Plus, TestSAMPLE2, 6, 4, -2);
