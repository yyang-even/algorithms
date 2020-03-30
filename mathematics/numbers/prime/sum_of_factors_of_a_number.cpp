#include "common_header.h"

#include "prime_factors_of_n.h"


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
auto SumOfFactorsOfN(const unsigned N) {
    const auto prime_factors = PrimeFactorsOf(N);

    unsigned power = 1;
    unsigned current = 1;
    unsigned sub_sum = 1;
    unsigned sum = 1;
    for (const auto prime : prime_factors) {
        if (prime != current) {
            sum *= sub_sum;
            current = prime;
            sub_sum = 1;
            power = 1;
        }
        power *= prime;
        sub_sum += power;
    }

    return sum * sub_sum;
}

}//namespace


SIMPLE_BENCHMARK(SumOfFactorsOfN, 1100);

SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE1, 28, 12);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE2, 168, 60);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE3, 2604, 1100);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE4, 72, 30);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE5, 24, 15);
