#include "common_header.h"

/** Compute the sign of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determining if an integer is a power of 2
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 *              Program to find whether a no is power of two
 *              https://www.geeksforgeeks.org/program-to-find-whether-a-no-is-power-of-two/
 */
INT_BOOL IsPowerOf2(const unsigned num) {
    return num && !(num & (num - 1));
}


SIMPLE_BENCHMARK(IsPowerOf2, 1);
SIMPLE_BENCHMARK(IsPowerOf2, 0);
SIMPLE_BENCHMARK(IsPowerOf2, std::numeric_limits<int>::min());
SIMPLE_BENCHMARK(IsPowerOf2, std::numeric_limits<unsigned>::max());

SIMPLE_TEST(IsPowerOf2, TestSample1, TRUE, 1);
SIMPLE_TEST(IsPowerOf2, TestSample2, FALSE, 0);
SIMPLE_TEST(IsPowerOf2, TestSample3, TRUE, std::numeric_limits<int>::min());
SIMPLE_TEST(IsPowerOf2, TestSample4, FALSE, std::numeric_limits<int>::max());
SIMPLE_TEST(IsPowerOf2, TestSample5, FALSE, std::numeric_limits<unsigned>::max());
SIMPLE_TEST(IsPowerOf2, TestSample6, TRUE, 1 << 8);
SIMPLE_TEST(IsPowerOf2, TestSample7, FALSE, 118);
