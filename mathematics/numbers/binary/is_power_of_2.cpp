#include "common_header.h"

/** Compute the sign of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determining if an integer is a power of 2
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
INT_BOOL IsPowerOf2(const unsigned num) {
    return num && !(num & (num - 1));
}


SIMPLE_BENCHMARK(IsPowerOf2, 1);
SIMPLE_BENCHMARK(IsPowerOf2, 0);
SIMPLE_BENCHMARK(IsPowerOf2, INT_MIN);
SIMPLE_BENCHMARK(IsPowerOf2, UINT_MAX);

SIMPLE_TEST(IsPowerOf2, TestSample1, TRUE, 1);
SIMPLE_TEST(IsPowerOf2, TestSample2, FALSE, 0);
SIMPLE_TEST(IsPowerOf2, TestSample3, TRUE, INT_MIN);
SIMPLE_TEST(IsPowerOf2, TestSample4, FALSE, INT_MAX);
SIMPLE_TEST(IsPowerOf2, TestSample5, FALSE, UINT_MAX);
SIMPLE_TEST(IsPowerOf2, TestSample6, TRUE, 1 << 8);
SIMPLE_TEST(IsPowerOf2, TestSample7, FALSE, 118);
