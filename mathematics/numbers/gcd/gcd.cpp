#include "common_header.h"

#include "gcd.h"
#include "mathematics/numbers/binary/count_trailing_zeros.h"


namespace {

/** Stein’s Algorithm for finding GCD
 *
 * @reference   https://www.geeksforgeeks.org/steins-algorithm-for-finding-gcd/
 *
 * Stein’s algorithm or binary GCD algorithm is an algorithm that computes the
 * greatest common divisor of two non-negative integers. Stein’s algorithm
 * replaces division with arithmetic shifts, comparisons, and subtraction.
 *
 * @reference   Euclid’s Algorithm when % and / operations are costly
 *              https://www.geeksforgeeks.org/euclids-algorithm-when-and-operations-are-costly/
 */
auto Gcd_Stein_Iterative(unsigned a, unsigned b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }

    const auto k = CountTrailingZeros_Linear(a | b);
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


auto Gcd_Stein_Recursive(const unsigned a, const unsigned b) {
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
            return Gcd_Stein_Recursive(a >> 1, b);
        } else {
            return Gcd_Stein_Recursive(a >> 1, b >> 1) << 1;
        }
    } else if (not(b & 1)) {
        return Gcd_Stein_Recursive(a, b >> 1);
    }

    return a > b ? Gcd_Stein_Recursive((a - b) >> 1, b) : Gcd_Stein_Recursive((b - a) >> 1, a);
}

}//namespace


SIMPLE_BENCHMARK(gcd, 12, 18);
SIMPLE_BENCHMARK(gcd, 18, 12);

SIMPLE_TEST(gcd, Test1, 6u, 12, 18);
SIMPLE_TEST(gcd, Test2, 6u, 18, 12);
SIMPLE_TEST(gcd, Test3, 5u, 10, 15);
SIMPLE_TEST(gcd, Test4, 5u, 35, 10);
SIMPLE_TEST(gcd, Test5, 1u, 31, 2);


const auto EXPECTED1 = std::make_tuple(10u, 1, -1);
const auto EXPECTED2 = std::make_tuple(5u, 1, -2);


SIMPLE_BENCHMARK(gcd_Extended, 18, 12);

SIMPLE_TEST(gcd_Extended, TestSample1, EXPECTED1, 30, 20);
SIMPLE_TEST(gcd_Extended, TestSample2, EXPECTED2, 35, 15);


SIMPLE_BENCHMARK(Gcd_Stein_Iterative, 18, 12);

SIMPLE_TEST(Gcd_Stein_Iterative, Test1, 6u, 12, 18);
SIMPLE_TEST(Gcd_Stein_Iterative, Test2, 6u, 18, 12);
SIMPLE_TEST(Gcd_Stein_Iterative, Test3, 5u, 10, 15);
SIMPLE_TEST(Gcd_Stein_Iterative, Test4, 5u, 35, 10);
SIMPLE_TEST(Gcd_Stein_Iterative, Test5, 1u, 31, 2);
SIMPLE_TEST(Gcd_Stein_Iterative, Test6, 17u, 17, 34);
SIMPLE_TEST(Gcd_Stein_Iterative, Test7, 1u, 50, 49);


SIMPLE_BENCHMARK(Gcd_Stein_Recursive, 18, 12);

SIMPLE_TEST(Gcd_Stein_Recursive, Test1, 6u, 12, 18);
SIMPLE_TEST(Gcd_Stein_Recursive, Test2, 6u, 18, 12);
SIMPLE_TEST(Gcd_Stein_Recursive, Test3, 5u, 10, 15);
SIMPLE_TEST(Gcd_Stein_Recursive, Test4, 5u, 35, 10);
SIMPLE_TEST(Gcd_Stein_Recursive, Test5, 1u, 31, 2);
SIMPLE_TEST(Gcd_Stein_Recursive, Test6, 17u, 17, 34);
SIMPLE_TEST(Gcd_Stein_Recursive, Test7, 1u, 50, 49);
