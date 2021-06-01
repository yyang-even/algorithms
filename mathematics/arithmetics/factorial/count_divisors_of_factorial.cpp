#include "common_header.h"

#include "mathematics/numbers/prime/largest_power_of_p_divides_factorial_n.h"
#include "mathematics/numbers/prime/primes_below_n.h"


namespace {

/**
 * @reference   Count Divisors of Factorial
 *              https://www.geeksforgeeks.org/count-divisors-of-factorial/
 *
 * Given a number n, count total number of divisors of n!.
 */
unsigned long long CountDivisorsOfFactorial(const unsigned n) {
    if (n == 0) {
        return 0;
    }

    auto primes_below_n_plus_1 = PrimesBelowN(n + 1);

    unsigned long long count = 1;
    for (const auto prime : primes_below_n_plus_1) {
        //The 1 is for p^0
        count *= (LargestPowerOfPDividesFactorialN(prime, n) + 1);
    }

    return count;
}

}//namespace


constexpr unsigned LOWER = 0;


THE_BENCHMARK(CountDivisorsOfFactorial, LOWER);

SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE1, 0, LOWER);
SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE2, 1, 1);
SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE3, 8, 4);
SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE4, 16, 5);
SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE5, 30, 6);
