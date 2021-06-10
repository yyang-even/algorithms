#include "common_header.h"

#include "mathematics/arithmetics/multiplication/multiplication.h"


namespace {

/** Write a program to calculate pow(x,n)
 *
 * @reference   Write a program to calculate pow(x,n)
 *              https://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/
 *
 * Given two integers x and n, write a function to compute x^n. We may assume that x
 * and n are small and overflow doesn't happen.
 *
 * @complexity: O(lgn)
 */
inline constexpr long
Power_Recursive(const long x, const unsigned int n) {
    if (n == 0) {
        return 1;
    }

    const auto x_power_half_n = Power_Recursive(x, n / 2);
    if (n % 2 == 0) {
        return x_power_half_n * x_power_half_n;
    } else {
        return x * x_power_half_n * x_power_half_n;
    }
}

inline constexpr double
Power_Recursive(const double x, const int n) {
    if (n == 0) {
        return 1;
    }

    const auto x_power_half_n = Power_Recursive(x, n / 2);
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


/** Write an iterative O(Log y) function for pow(x, y)
 *
 * @reference   https://www.geeksforgeeks.org/write-an-iterative-olog-y-function-for-powx-y/
 */
constexpr auto
Power_Iterative(long x, unsigned y) {
    long result = 1;
    for (; y ; y >>= 1, x *= x) {
        if (y & 1) {
            result *= x;
        }
    }

    return result;
}


/** Write you own Power without using multiplication(*) and division(/) operators
 *
 * @reference   https://www.geeksforgeeks.org/write-you-own-power-without-using-multiplication-and-division/
 */
constexpr unsigned
Power_Loop(const unsigned x, unsigned n) {
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


constexpr long LOWER = 0;
constexpr double DOUBLE_LOWER = 0.0;


SIMPLE_BENCHMARK(Power_Recursive, Sample1, 2, 7);

SIMPLE_TEST(Power_Recursive, TestLOWER, 1, LOWER, LOWER);
SIMPLE_TEST(Power_Recursive, TestSAMPLE1, 8, 2, 3);
SIMPLE_TEST(Power_Recursive, TestSAMPLE2, 49, 7, 2);
SIMPLE_TEST(Power_Recursive, TestSAMPLE3, 125, 5, 3);

SIMPLE_BENCHMARK(Power_Recursive, Sample2, 2.0, 7);

SIMPLE_TEST(Power_Recursive, TestDoubleLOWER, 1.0, DOUBLE_LOWER, DOUBLE_LOWER);
SIMPLE_TEST(Power_Recursive, TestDoubleSAMPLE1, 8.0, 2.0, 3);
SIMPLE_TEST(Power_Recursive, TestDoubleSAMPLE2, 49.0, 7.0, 2);
SIMPLE_TEST(Power_Recursive, TestDoubleSAMPLE3, 0.125, 2.0, -3);


THE_BENCHMARK(Power_Loop, 2, 7);

SIMPLE_TEST(Power_Loop, TestLOWER, 1, LOWER, LOWER);
SIMPLE_TEST(Power_Loop, TestSAMPLE1, 8, 2, 3);
SIMPLE_TEST(Power_Loop, TestSAMPLE2, 49, 7, 2);
SIMPLE_TEST(Power_Loop, TestSAMPLE3, 125, 5, 3);


THE_BENCHMARK(Power_Iterative, 2, 7);

SIMPLE_TEST(Power_Iterative, TestLOWER, 1, LOWER, LOWER);
SIMPLE_TEST(Power_Iterative, TestSAMPLE1, 8, 2, 3);
SIMPLE_TEST(Power_Iterative, TestSAMPLE2, 49, 7, 2);
SIMPLE_TEST(Power_Iterative, TestSAMPLE3, 125, 5, 3);
