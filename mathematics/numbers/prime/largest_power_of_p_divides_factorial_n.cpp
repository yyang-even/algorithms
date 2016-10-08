#include "common_header.h"

typedef unsigned InputType;

/**The largest power of p that divides n!
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.4.
 *
 * We'd like to determine, for any given prime p, the largest power of p that divides n!; that is,
 * we want the exponent of p in n!'s unique factorization.
 */
InputType LargestPowerOfPDividesFactorialN(const InputType p, const InputType n) {
    InputType power = 0;
    for (InputType i = p; i <= n; i *= p) {
        power += (n / i);
    }
    return power;
}

SIMPLE_BENCHMARK(LargestPowerOfPDividesFactorialN, 2, 10);

SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE1, 0, 3, 2);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE2, 8, 2, 10);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE3, 4, 3, 9);
SIMPLE_TEST(LargestPowerOfPDividesFactorialN, TestSAMPLE4, 97, 2, 100);
