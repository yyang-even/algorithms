#include "common_header.h"

#include "count_trailing_zeros.h"
#include "is_power_of_2.h"


namespace {

/** Check if given number is a power of d where d is a power of 2
 *
 * @reference   https://www.geeksforgeeks.org/check-given-number-power-d-d-power-2/
 *
 * Given an integer n, find whether it is a power of d or not,
 * where d is itself a power of 2.
 */
INT_BOOL IsPowerOfPowerOf2(const unsigned n, const unsigned d) {
    return IsPowerOf2(n) and (CountTrailingZeros_Linear(n) % static_cast<unsigned>(log2(d))) == 0;
}


/** Find whether a given number is a power of 4 or not
 *
 * @reference   https://www.geeksforgeeks.org/find-whether-a-given-number-is-a-power-of-4-or-not/
 *
 * Given an integer n, find whether it is a power of 4 or not.
 */
auto IsPowerOf4(const unsigned num) {
    return IsPowerOfPowerOf2(num, 4);
}


/** Check if a number is power of 8 or not
 *
 * @reference   https://www.geeksforgeeks.org/check-number-power-8-not/
 *
 * Given a number check whether it is power of 8 or not.
 */
auto IsPowerOf8(const unsigned num) {
    return IsPowerOfPowerOf2(num, 8);
}

auto IsPowerOf8_Const(const unsigned num) {
    return IsPowerOf2(num) and not(num & 0xB6DB6DB6);
}

}//namespace


SIMPLE_BENCHMARK(IsPowerOf4, 1);
SIMPLE_BENCHMARK(IsPowerOf4, 0);
SIMPLE_BENCHMARK(IsPowerOf4, std::numeric_limits<unsigned>::max());

SIMPLE_TEST(IsPowerOf4, TestSample1, true, 1);
SIMPLE_TEST(IsPowerOf4, TestSample2, false, 0);
SIMPLE_TEST(IsPowerOf4, TestSample3, false, std::numeric_limits<int>::max());
SIMPLE_TEST(IsPowerOf4, TestSample4, false, 20);
SIMPLE_TEST(IsPowerOf4, TestSample5, true, 16);
SIMPLE_TEST(IsPowerOf4, TestSample6, true, 64);


SIMPLE_BENCHMARK(IsPowerOfPowerOf2, 8, 2);

SIMPLE_TEST(IsPowerOfPowerOf2, TestSample1, false, 0, 2);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample2, true, 8, 2);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample3, false, 14, 8);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample4, false, 32, 16);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample5, true, 256, 16);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample6, true, 64, 8);


SIMPLE_BENCHMARK(IsPowerOf8, 8);

SIMPLE_TEST(IsPowerOf8, TestSample1, true, 64);
SIMPLE_TEST(IsPowerOf8, TestSample2, false, 75);
SIMPLE_TEST(IsPowerOf8, TestSample3, false, 14);
SIMPLE_TEST(IsPowerOf8, TestSample4, false, 65);


SIMPLE_BENCHMARK(IsPowerOf8_Const, 8);

SIMPLE_TEST(IsPowerOf8_Const, TestSample1, true, 64);
SIMPLE_TEST(IsPowerOf8_Const, TestSample2, false, 75);
SIMPLE_TEST(IsPowerOf8_Const, TestSample3, false, 14);
SIMPLE_TEST(IsPowerOf8_Const, TestSample4, false, 65);