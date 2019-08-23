#include "common_header.h"

#include "mathematics/numbers/prime/largest_power_of_p_divides_factorial_n.h"
#include "mathematics/numbers/prime/primes_below_n.h"


namespace {

typedef unsigned InputType;

/**
 * @reference   Count Divisors of Factorial
 *              https://www.geeksforgeeks.org/count-divisors-of-factorial/
 *
 * Given a number n, count total number of divisors of n!.
 *
 * Input : n = 5
 * Output : 16
 * 5! is 120. Divisors of 120 are 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24 30, 40, 60 and 120
 */
unsigned long long CountDivisorsOfFactorial(const InputType n) {
    if (n == 0) {
        return 0;
    }

    auto primes_below_n_plus_1 = PrimesBelowN(n + 1);

    unsigned long long count = 1ULL;
    for (auto prime : primes_below_n_plus_1) {
        //The 1 is for p^0
        count *= (LargestPowerOfPDividesFactorialN(prime, n) + 1);
    }

    return count;
}

}//namespace


const InputType LOWER = 0;

SIMPLE_BENCHMARK(CountDivisorsOfFactorial, LOWER);

SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE1, 0u, LOWER);
SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE2, 1u, 1);
SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE3, 8u, 4);
SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE4, 16u, 5);
SIMPLE_TEST(CountDivisorsOfFactorial, TestSAMPLE5, 30u, 6);
