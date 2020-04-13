#pragma once

#include "primes_below_n.h"


/** Total number of divisors for a given number
 *
 * @reference   https://www.geeksforgeeks.org/total-number-divisors-given-number/
 */
static inline auto CountDivisorsOfN(unsigned N) {
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
