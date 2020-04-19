#pragma once


#include "least_prime_factor_of_numbers_till_n.h"


/** Sum of Factors of a Number using Prime Factorization
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-factors-of-a-number-using-prime-factorization/
 * @reference   Sum of all the factors of a number
 *              https://www.geeksforgeeks.org/sum-factors-number/
 * @reference   Finding the sum of the divisors of n
 *              https://www.math.upenn.edu/~deturck/m170/wk3/lecture/sumdiv.html
 *
 * Given a number N. The task is to find the sum of all factors of the given number N.
 */
static inline auto SumOfFactorsOfN(unsigned N) {
    const auto smallest_prime_factors = LeastPrimeFactorOfNumbers(N);

    unsigned total_sum = 1;
    while (N > 1) {
        unsigned term = 1;
        unsigned sum = 1;
        for (auto current_factor = smallest_prime_factors[N];
             current_factor == smallest_prime_factors[N]; N /= current_factor) {
            term *= current_factor;
            sum += term;
        }

        total_sum *= sum;
    }

    return total_sum;
}


static inline auto SumOfProferDivisors(const unsigned N) {
    return SumOfFactorsOfN(N) - N;
}
