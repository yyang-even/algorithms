#include "common_header.h"

#include "is_prime.h"
#include "primes_below_n.h"


namespace {

/** Total number of divisors for a given number
 *
 * @reference   https://www.geeksforgeeks.org/total-number-divisors-given-number/
 */
auto CountDivisorsOfN(unsigned N) {
    const auto prime_factors = PrimesBelowN(N + 1);

    unsigned total = 1;
    for (const auto prime : prime_factors) {
        if (N % prime == 0) {
            unsigned count = 1;
            do {
                N /= prime;
                ++count;
            } while (N % prime == 0);
            total *= count;
        }
    }

    return total;
}


/**
 * @reference   Count Divisors of n in O(n^1/3)
 *              https://www.geeksforgeeks.org/count-divisors-n-on13/
 *
 * @note    More expensive than the solution above.
 */


/**
 * @reference   Check if a number has prime count of divisors
 *              https://www.geeksforgeeks.org/check-if-a-number-has-prime-count-of-divisors/
 */
auto IsCountDivisorsOfNPrime(unsigned N) {
    const auto prime_factors = PrimesBelowN(N);

    for (const auto prime : prime_factors) {
        if (N % prime == 0) {
            unsigned count = 1;
            do {
                N /= prime;
                ++count;
            } while (N % prime == 0);

            return (N == 1) and IsPrime_OptimizedSchoolMethod(count);
        }
    }

    return true;
}

}//namespace


SIMPLE_BENCHMARK(CountDivisorsOfN, 25);

SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE1, 3, 25);
SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE2, 8, 24);
SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE3, 6, 18);
SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE4, 9, 100);


SIMPLE_BENCHMARK(IsCountDivisorsOfNPrime, 13);

SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE1, true, 13);
SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE2, false, 8);
SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE3, true, 25);
SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE4, false, 100);
