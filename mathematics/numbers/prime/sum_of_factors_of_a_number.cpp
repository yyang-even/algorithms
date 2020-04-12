#include "common_header.h"

#include "least_prime_factor_of_numbers_till_n.h"


namespace {

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
auto SumOfFactorsOfN(unsigned N) {
    const auto smallest_prime_factors = LeastPrimeFactorOfNumbers(N);

    unsigned total_sum = 1;
    while (N > 1) {
        unsigned term = 1;
        unsigned sum = 1;
        for (auto current_factor = smallest_prime_factors[N]; current_factor == smallest_prime_factors[N];
             N /= current_factor) {
            term *= current_factor;
            sum += term;
        }

        total_sum *= sum;
    }

    return total_sum;
}

}//namespace


SIMPLE_BENCHMARK(SumOfFactorsOfN, 1100);

SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE1, 28, 12);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE2, 168, 60);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE3, 2604, 1100);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE4, 72, 30);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE5, 24, 15);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE6, 14, 13);
