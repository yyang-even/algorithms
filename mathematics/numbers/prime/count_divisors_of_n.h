#pragma once

#include "primes_below_n.h"


/**
 * @reference   Total number of divisors for a given number
 *              https://www.geeksforgeeks.org/total-number-divisors-given-number/
 *
 * @tags    #prime #factorization
 */
static inline auto
CountPrimeFactors(unsigned N,
                  const std::function<void(const unsigned prime, const unsigned count)>
                      for_each_prime_factor = {}) {
    const auto prime_factors = PrimesBelowN(N + 1);

    for (const auto prime : prime_factors) {
        if (N % prime == 0) {
            unsigned count = 1;
            do {
                N /= prime;
                ++count;
            } while (N % prime == 0);

            if (for_each_prime_factor) {
                for_each_prime_factor(prime, count);
            }
        }
    }
}


static inline auto CountDivisorsOfN(const unsigned N) {
    unsigned total = 1;
    CountPrimeFactors(N, [&total](const auto, const auto count) {
        total *= count;
    });

    return total;
}
