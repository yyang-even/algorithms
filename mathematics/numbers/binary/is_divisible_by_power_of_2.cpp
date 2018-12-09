#include "common_header.h"

#include "is_divisible_by_power_of_2.h"


/** Check if a number is divisible by 8 using bitwise operators
 *
 * @reference   https://www.geeksforgeeks.org/check-number-divisible-8-using-bitwise-operators/
 *
 * Given a number n, check if it is divisible by 8 using bitwise operators.
 */
inline auto IsDivisibleBy8(const unsigned num) {
    return IsDivisibleByPowerOf2Bitwise(num, 3);
}


SIMPLE_BENCHMARK(IsDivisibleByPowerOf2Arithmetic, 8, 2);

SIMPLE_TEST(IsDivisibleByPowerOf2Arithmetic, TestSample1, TRUE, 0, 2);
SIMPLE_TEST(IsDivisibleByPowerOf2Arithmetic, TestSample2, TRUE, 8, 2);
SIMPLE_TEST(IsDivisibleByPowerOf2Arithmetic, TestSample3, FALSE, 14, 3);


SIMPLE_BENCHMARK(IsDivisibleByPowerOf2Bitwise, 8, 2);

SIMPLE_TEST(IsDivisibleByPowerOf2Bitwise, TestSample1, TRUE, 0, 2);
SIMPLE_TEST(IsDivisibleByPowerOf2Bitwise, TestSample2, TRUE, 8, 2);
SIMPLE_TEST(IsDivisibleByPowerOf2Bitwise, TestSample3, FALSE, 14, 3);


SIMPLE_BENCHMARK(IsDivisibleBy8, 8);

SIMPLE_TEST(IsDivisibleBy8, TestSample1, TRUE, 0);
SIMPLE_TEST(IsDivisibleBy8, TestSample2, TRUE, 8);
SIMPLE_TEST(IsDivisibleBy8, TestSample3, FALSE, 14);
SIMPLE_TEST(IsDivisibleBy8, TestSample4, FALSE, 15);
SIMPLE_TEST(IsDivisibleBy8, TestSample5, TRUE, 16);
