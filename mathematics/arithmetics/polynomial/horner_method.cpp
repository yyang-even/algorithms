#include "common_header.h"


namespace {

template <std::size_t N>
using ArrayType = std::array<int, N>;


/** Horner’s Method for Polynomial Evaluation
 *
 * Given a polynomial of the form c(n)x^n + c(n-1)x^(n-1) + c(n-2)x^(n-2) + ... + c1x + c0
 * and a value of x, find the value of polynomial for a given value of x. Here cn, cn-1,
 * ... are integers (may be negative) and n is a positive integer. Input is in the form
 * of an array say poly[] where poly[0] represents coefficient for x^n and poly[1]
 * represents coefficient for x^(n-1) and so on.
 *
 * @reference   https://www.geeksforgeeks.org/horners-method-polynomial-evaluation/
 *
 * @complexity: O(n)
 */
template <std::size_t N>
constexpr auto HornerMethod(ArrayType<N> coefficients, const int x) {
    int result = 0;

    for (const auto coefficient : coefficients) {
        result = coefficient + result * x;
    }

    return result;
}

}//namespace


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<1> VALUES2 = {1};
constexpr ArrayType<2> VALUES3 = {1, 0};
constexpr ArrayType<4> VALUES4 = {2, -6, 2, -1};
constexpr ArrayType<4> VALUES5 = {2, 0, 3, 1};


SIMPLE_TEST(HornerMethod, TestSAMPLE1, 0, VALUES1, 3);
SIMPLE_TEST(HornerMethod, TestSAMPLE2, 1, VALUES2, 3);
SIMPLE_TEST(HornerMethod, TestSAMPLE3, 3, VALUES3, 3);
SIMPLE_TEST(HornerMethod, TestSAMPLE4, 5, VALUES4, 3);
SIMPLE_TEST(HornerMethod, TestSAMPLE5, 23, VALUES5, 2);
