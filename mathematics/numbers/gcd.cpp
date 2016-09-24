#include "common_header.h"

/** GCD - Greatest Common Divisor
 * @reference Ronald Graham, Oren Patashnik, Donald Knuth.
 *            Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.1.
 *
 * The greatest common divisor of two integers m and n is the largest integer that divides them both.
 */

/**
 * Euclid's algorithm
 *
 * gcd(0,n) = n;
 * gcd(m,n) = gcd(n mod m, m),  for n > m > 0.
 */
unsigned gcd(unsigned m, unsigned n) {
    if (m > n) {
        std::swap(m, n);
    }
    if (m == 0) {
        return n;
    } else {
        return gcd(n % m, m);
    }
}

SIMPLE_BENCHMARK(gcd, 12, 18);
SIMPLE_BENCHMARK(gcd, 18, 12);
SIMPLE_TEST(gcd, Test1, 6, 12, 18);
SIMPLE_TEST(gcd, Test2, 6, 18, 12);
