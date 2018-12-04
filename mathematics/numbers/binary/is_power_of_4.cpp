#include "common_header.h"

#include "is_power_of_2.h"
#include "count_trailing_zeros.h"

/** Find whether a given number is a power of 4 or not
 *
 * @reference   https://www.geeksforgeeks.org/find-whether-a-given-number-is-a-power-of-4-or-not/
 *
 * Given an integer n, find whether it is a power of 4 or not.
 */
INT_BOOL IsPowerOf4(const unsigned num) {
    return IsPowerOf2(num) and not(CountTrailingZerosLinear(num) % 2);
}


SIMPLE_BENCHMARK(IsPowerOf4, 1);
SIMPLE_BENCHMARK(IsPowerOf4, 0);
SIMPLE_BENCHMARK(IsPowerOf4, std::numeric_limits<unsigned>::max());

SIMPLE_TEST(IsPowerOf4, TestSample1, TRUE, 1);
SIMPLE_TEST(IsPowerOf4, TestSample2, FALSE, 0);
SIMPLE_TEST(IsPowerOf4, TestSample3, FALSE, std::numeric_limits<int>::max());
SIMPLE_TEST(IsPowerOf4, TestSample4, FALSE, 20);
SIMPLE_TEST(IsPowerOf4, TestSample5, TRUE, 16);
SIMPLE_TEST(IsPowerOf4, TestSample6, TRUE, 64);
