#include "common_header.h"

namespace {


/** Subtract two numbers without using arithmetic operators
 *
 * @reference   https://www.geeksforgeeks.org/subtract-two-numbers-without-using-arithmetic-operators/
 *
 * Write a function subtract(x, y) that returns x-y where x and y are integers.
 * The function should not use any of the arithmetic operators (+, ++, –, -, .. etc).
 */
auto Subtract_Iterative(int x, int y) {
    while (y) {
        auto borrow = ~x & y;
        x ^= y;
        y = borrow << 1;
    }

    return x;
}

auto Subtract_Recursive(const int x, const int y) {
    if (not y) {
        return x;
    }
    return Subtract_Recursive(x ^ y, (~x & y) << 1);
}

}//namespace


SIMPLE_BENCHMARK(Subtract_Iterative, 29, 13);

SIMPLE_TEST(Subtract_Iterative, TestSAMPLE1, 16, 29, 13);


SIMPLE_BENCHMARK(Subtract_Recursive, 29, 13);

SIMPLE_TEST(Subtract_Recursive, TestSAMPLE1, 16, 29, 13);
