#include "common_header.h"

#include "count_trailing_zeros.h"
#include "is_power_of_2.h"

/** Check if given number is a power of d where d is a power of 2
 *
 * @reference   https://www.geeksforgeeks.org/check-given-number-power-d-d-power-2/
 *
 * Given an integer n, find whether it is a power of d or not,
 * where d is itself a power of 2.
 */
INT_BOOL IsPowerOfPowerOf2(const unsigned n, const unsigned d) {
    return IsPowerOf2(n) and (CountTrailingZerosLinear(n) % static_cast<unsigned>(log2(d))) == 0;
}


/** Find whether a given number is a power of 4 or not
 *
 * @reference   https://www.geeksforgeeks.org/find-whether-a-given-number-is-a-power-of-4-or-not/
 *
 * Given an integer n, find whether it is a power of 4 or not.
 */
INT_BOOL IsPowerOf4(const unsigned num) {
    return IsPowerOfPowerOf2(num, 4);
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


SIMPLE_BENCHMARK(IsPowerOfPowerOf2, 8, 2);

SIMPLE_TEST(IsPowerOfPowerOf2, TestSample1, FALSE, 0, 2);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample2, TRUE, 8, 2);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample3, FALSE, 14, 8);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample4, FALSE, 32, 16);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample5, TRUE, 256, 16);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample6, TRUE, 64, 8);
