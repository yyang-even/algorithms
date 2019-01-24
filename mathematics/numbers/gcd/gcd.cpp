#include "common_header.h"

#include "gcd.h"
#include "mathematics/numbers/binary/count_trailing_zeros.h"

/** Stein’s Algorithm for finding GCD
 *
 * @reference   https://www.geeksforgeeks.org/steins-algorithm-for-finding-gcd/
 *
 * Stein’s algorithm or binary GCD algorithm is an algorithm that computes the
 * greatest common divisor of two non-negative integers. Stein’s algorithm
 * replaces division with arithmetic shifts, comparisons, and subtraction.
 */
auto GcdSteinIterative(unsigned a, unsigned b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }

    const auto k = CountTrailingZerosLinear(a | b);
    a >>= k;
    b >>= k;

    while (not(a & 1)) {
        a >>= 1;
    }

    do {
        while (not(b & 1)) {
            b >>= 1;
        }
        if (a > b) {
            std::swap(a, b);
        }

        b -= a;

    } while (b != 0);

    return a << k;
}

auto GcdSteinRecursive(const unsigned a, const unsigned b) {
    if (a == b) {
        return a;
    }

    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }

    if (not(a & 1)) {
        if (b & 1) {
            return GcdSteinRecursive(a >> 1, b);
        } else {
            return GcdSteinRecursive(a >> 1, b >> 1) << 1;
        }
    } else if (not(b & 1)) {
        return GcdSteinRecursive(a, b >> 1);
    }

    return a > b ? GcdSteinRecursive((a - b) >> 1, b) : GcdSteinRecursive((b - a) >> 1, a);
}


SIMPLE_BENCHMARK(gcd, 12, 18);
SIMPLE_BENCHMARK(gcd, 18, 12);

SIMPLE_TEST(gcd, Test1, 6, 12, 18);
SIMPLE_TEST(gcd, Test2, 6, 18, 12);
SIMPLE_TEST(gcd, Test3, 5, 10, 15);
SIMPLE_TEST(gcd, Test4, 5, 35, 10);
SIMPLE_TEST(gcd, Test5, 1, 31, 2);


const auto EXPECTED1 = std::make_tuple(10, 1, -1);
const auto EXPECTED2 = std::make_tuple(5, 1, -2);

SIMPLE_BENCHMARK(gcdExtended, 18, 12);

SIMPLE_TEST(gcdExtended, TestSample1, EXPECTED1, 30, 20);
SIMPLE_TEST(gcdExtended, TestSample2, EXPECTED2, 35, 15);


SIMPLE_BENCHMARK(GcdSteinIterative, 18, 12);

SIMPLE_TEST(GcdSteinIterative, Test1, 6, 12, 18);
SIMPLE_TEST(GcdSteinIterative, Test2, 6, 18, 12);
SIMPLE_TEST(GcdSteinIterative, Test3, 5, 10, 15);
SIMPLE_TEST(GcdSteinIterative, Test4, 5, 35, 10);
SIMPLE_TEST(GcdSteinIterative, Test5, 1, 31, 2);
SIMPLE_TEST(GcdSteinIterative, Test6, 17, 17, 34);
SIMPLE_TEST(GcdSteinIterative, Test7, 1, 50, 49);


SIMPLE_BENCHMARK(GcdSteinRecursive, 18, 12);

SIMPLE_TEST(GcdSteinRecursive, Test1, 6, 12, 18);
SIMPLE_TEST(GcdSteinRecursive, Test2, 6, 18, 12);
SIMPLE_TEST(GcdSteinRecursive, Test3, 5, 10, 15);
SIMPLE_TEST(GcdSteinRecursive, Test4, 5, 35, 10);
SIMPLE_TEST(GcdSteinRecursive, Test5, 1, 31, 2);
SIMPLE_TEST(GcdSteinRecursive, Test6, 17, 17, 34);
SIMPLE_TEST(GcdSteinRecursive, Test7, 1, 50, 49);
