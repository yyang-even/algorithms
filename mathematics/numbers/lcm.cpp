#include "common_header.h"

#include "numbers.h"

/** LCM - Least Common Multiple
 * @reference Ronald Graham, Oren Patashnik, Donald Knuth.
 *            Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Exercise 4.2.
 *
 * The best way known to compute lcm(m, n) is to compute gcd(m, n) first and then to divide mn by the gcd.
 */
unsigned lcm(unsigned m, unsigned n) {
    return m * n / gcd(m, n);
}


SIMPLE_BENCHMARK(lcm, 12, 18);
SIMPLE_BENCHMARK(lcm, 18, 12);
SIMPLE_TEST(lcm, Test1, 36, 12, 18);
SIMPLE_TEST(lcm, Test2, 36, 18, 12);
