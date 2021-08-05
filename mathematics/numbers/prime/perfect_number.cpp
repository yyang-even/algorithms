#include "common_header.h"

#include "sum_of_factors_of_a_number.h"


namespace {

/** Perfect Number
 *
 * @reference   https://www.geeksforgeeks.org/perfect-number/
 *
 * A number is a perfect number if is equal to sum of its proper divisors, that is, sum
 * of its positive divisors excluding the number itself. Write a function to check if a
 * given number is perfect or not.
 */
inline auto isPerfectNumber(const unsigned N) {
    return SumOfProferDivisors(N) == N;
}


/**
 * @reference   Perfect Number
 *              https://leetcode.com/problems/perfect-number/
 *
 * A perfect number is a positive integer that is equal to the sum of its positive
 * divisors, excluding the number itself. A divisor of an integer x is an integer that
 * can divide x evenly. Given an integer n, return true if n is a perfect number,
 * otherwise return false.
 */
constexpr auto isPerfectNumber_Sqrt(const unsigned num) {
    unsigned sum = 0;
    for (unsigned i = 1; i * i <= num; ++i) {
        if (num % i == 0) {
            sum += i;
            if (i * i != num) {
                sum += num / i;
            }
        }
    }

    return sum - num == num;
}


inline constexpr auto perfectNumber(const unsigned p) {
    return (1u << (p - 1)) * ((1 << p) - 1);
}

constexpr auto isPerfectNumber_EuclidEuler(const unsigned num) {
    constexpr unsigned primes[] = {2, 3, 5, 7, 13, 17, 19, 31};
    for (const auto p : primes) {
        if (perfectNumber(p) == num) {
            return true;
        }
    }

    return false;
}

}//namespace


THE_BENCHMARK(isPerfectNumber, 15);

SIMPLE_TEST(isPerfectNumber, TestSAMPLE1, false, 15);
SIMPLE_TEST(isPerfectNumber, TestSAMPLE2, true, 6);


THE_BENCHMARK(isPerfectNumber_Sqrt, 15);

SIMPLE_TEST(isPerfectNumber_Sqrt, TestSAMPLE1, false, 15);
SIMPLE_TEST(isPerfectNumber_Sqrt, TestSAMPLE2, true, 6);


THE_BENCHMARK(isPerfectNumber_EuclidEuler, 15);

SIMPLE_TEST(isPerfectNumber_EuclidEuler, TestSAMPLE1, false, 15);
SIMPLE_TEST(isPerfectNumber_EuclidEuler, TestSAMPLE2, true, 6);
