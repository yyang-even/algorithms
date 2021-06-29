#include "common_header.h"

#include "mathematics/numbers/perfect_square.h"


namespace {

/** Square root of an integer
 *
 * @reference   https://www.geeksforgeeks.org/square-root-of-an-integer/
 * @reference   Square root of a number without using sqrt() function
 *              https://www.geeksforgeeks.org/square-root-of-a-number-without-using-sqrt-function/
 *
 * Given an integer x, find square root of it. If x is not a perfect square, then return
 * floor(√x).
 *
 * @reference   Sqrt(x)
 *              https://leetcode.com/problems/sqrtx/
 *
 * Given a non-negative integer x, compute and return the square root of x. Since the
 * return type is an integer, the decimal digits are truncated, and only the integer
 * part of the result is returned. Note: You are not allowed to use any built-in
 * exponent function or operator, such as pow(x, 0.5) or x ** 0.5.
 */
constexpr auto SquareRoot_BinarySearch(const unsigned N) {
    if (N < 2) {
        return N;
    }

    unsigned left = 1, result = 0;
    auto right = N / 2;
    while (left <= right) {
        const auto mid = (left + right) / 2;
        const auto squre_of_mid = mid * mid;

        if (squre_of_mid == N) {
            return mid;
        }
        if (squre_of_mid < N) {
            left = mid + 1;
            result = mid;
        } else {
            right = mid - 1;
        }
    }

    return result;
}


/**
 * @reference   Find square root of number upto given precision using binary search
 *              https://www.geeksforgeeks.org/find-square-root-number-upto-given-precision-using-binary-search/
 */
constexpr auto
SquareRoot_Double_BinarySearch(const unsigned N, const unsigned precision) {
    double result = SquareRoot_BinarySearch(N);

    auto increment = 0.1;
    for (unsigned i = 0; i < precision; ++i) {
        while (result * result <= N) {
            result += increment;
        }

        result -= increment;
        increment /= 10;
    }

    return result;
}


/**
 * @reference   Babylonian method for square root
 *              https://www.geeksforgeeks.org/square-root-of-a-perfect-square/
 */
constexpr auto PerfectSquareRoot_Babylonian(const unsigned N) {
    assert(IsPerfectSquare(N));

    auto x = N;
    unsigned y = 1;
    while (x > y) {
        x = (x + y) / 2;
        y = N / x;
    }
    return x;
}


/**
 * @reference   Square root of a number using log
 *              https://www.geeksforgeeks.org/square-root-number-using-log/
 */
inline constexpr auto
SquareRoot_Log(const double N) {
    return std::pow(2.0, 0.5 * std::log2(N));
}

}//namespace


THE_BENCHMARK(SquareRoot_BinarySearch, 49);

SIMPLE_TEST(SquareRoot_BinarySearch, TestSAMPLE1, 7, 50);
SIMPLE_TEST(SquareRoot_BinarySearch, TestSAMPLE2, 7, 49);
SIMPLE_TEST(SquareRoot_BinarySearch, TestSAMPLE3, 3, 11);


THE_BENCHMARK(SquareRoot_Double_BinarySearch, 50, 3);

SIMPLE_DOUBLE_TEST(SquareRoot_Double_BinarySearch, TestSAMPLE1, 7.071, 50, 3);
SIMPLE_DOUBLE_TEST(SquareRoot_Double_BinarySearch, TestSAMPLE2, 3.1622, 10, 4);


THE_BENCHMARK(PerfectSquareRoot_Babylonian, 49);

SIMPLE_TEST(PerfectSquareRoot_Babylonian, TestSAMPLE2, 7, 49);


THE_BENCHMARK(SquareRoot_Log, 49);

SIMPLE_DOUBLE_TEST(SquareRoot_Log, TestSAMPLE1, 3.464101615137755, 12);
SIMPLE_DOUBLE_TEST(SquareRoot_Log, TestSAMPLE2, 7, 49);
