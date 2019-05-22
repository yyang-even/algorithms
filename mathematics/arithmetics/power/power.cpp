#include "common_header.h"

#include "mathematics/arithmetics/multiplication/multiplication.h"

namespace {

/** Write a program to calculate pow(x,n)
 * @reference   Write a program to calculate pow(x,n)
 *              http://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/
 *
 * Given two integers x and n, write a function to compute x^n.
 * We may assume that x and n are small and overflow doesn’t happen.
 *
 * @complexity: O(lgn)
 */
long Power(const long x, const unsigned int n) {
    if (n == 0) {
        return 1;
    }

    const auto x_power_half_n = Power(x, n / 2);
    if (n % 2 == 0) {
        return x_power_half_n * x_power_half_n;
    } else {
        return x * x_power_half_n * x_power_half_n;
    }
}

double Power(const double x, const int n) {
    if (n == 0) {
        return 1;
    }

    const auto x_power_half_n = Power(x, n / 2);
    if (n % 2 == 0) {
        return x_power_half_n * x_power_half_n;
    } else {
        if (n > 0) {
            return x * x_power_half_n * x_power_half_n;
        } else {
            return x_power_half_n * x_power_half_n / x;
        }
    }
}


/** Write you own Power without using multiplication(*) and division(/) operators
 *
 * @reference   https://www.geeksforgeeks.org/write-you-own-power-without-using-multiplication-and-division/
 */
unsigned Power_Loop(const unsigned x, unsigned n) {
    if (n == 0) {
        return 1;
    }

    unsigned power = 1;
    for (; n ; --n) {
        power = Multiply_RussianPeasant(power, x);
    }

    return power;
}

}//namespace


const long LOWER = 0;
const double DOUBLE_LOWER = 0.0;


SIMPLE_BENCHMARK(Power, LOWER, LOWER);
SIMPLE_BENCHMARK(Power, 2, 7);

SIMPLE_TEST(Power, TestLOWER, 1, LOWER, LOWER);
SIMPLE_TEST(Power, TestSAMPLE1, 8, 2, 3);
SIMPLE_TEST(Power, TestSAMPLE2, 49, 7, 2);
SIMPLE_TEST(Power, TestSAMPLE3, 125, 5, 3);

SIMPLE_BENCHMARK(Power, DOUBLE_LOWER, DOUBLE_LOWER);
SIMPLE_BENCHMARK(Power, 2.0, 7);

SIMPLE_TEST(Power, TestDoubleLOWER, 1.0, DOUBLE_LOWER, DOUBLE_LOWER);
SIMPLE_TEST(Power, TestDoubleSAMPLE1, 8.0, 2.0, 3);
SIMPLE_TEST(Power, TestDoubleSAMPLE2, 49.0, 7.0, 2);
SIMPLE_TEST(Power, TestDoubleSAMPLE3, 0.125, 2.0, -3);


SIMPLE_BENCHMARK(Power_Loop, LOWER, LOWER);
SIMPLE_BENCHMARK(Power_Loop, 2, 7);

SIMPLE_TEST(Power_Loop, TestLOWER, 1u, LOWER, LOWER);
SIMPLE_TEST(Power_Loop, TestSAMPLE1, 8u, 2, 3);
SIMPLE_TEST(Power_Loop, TestSAMPLE2, 49u, 7, 2);
SIMPLE_TEST(Power_Loop, TestSAMPLE3, 125u, 5, 3);
