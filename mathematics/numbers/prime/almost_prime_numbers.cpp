#include "common_header.h"

#include "least_prime_factor_of_numbers_till_n.h"
#include "prime_factors_of_n.h"


namespace {

/** Almost Prime Numbers
 *
 * @reference   https://www.geeksforgeeks.org/almost-prime-numbers/
 *
 * A k-Almost Prime Number is a number having exactly k prime factors (not necessary distinct).
 * All the 1-Almost Primes are called as Prime Numbers and all the 2-Almost Prime are called as semi-primes.
 * The task is to print first n numbers that are k prime.
 */
auto KAlmostPrimeNumbers(const unsigned K, unsigned N) {
    const auto smallest_prime_factors = LeastPrimeFactorOfNumbers(std::numeric_limits<short>::max());

    std::vector<unsigned> outputs;
    for (unsigned number = 2; N; ++number) {
        if (PrimeFactorsOfN_Sieve(number, smallest_prime_factors).size() == K) {
            outputs.push_back(number);
            --N;
        }
    }

    return outputs;
}

}//namespace


const std::vector<unsigned> EXPECTED1 = {4, 6, 9, 10, 14};
const std::vector<unsigned> EXPECTED2 = {1024, 1536};
const std::vector<unsigned> EXPECTED3 = {4, 6, 9, 10, 14, 15, 21, 22, 25, 26};


SIMPLE_BENCHMARK(KAlmostPrimeNumbers, 10, 2);

SIMPLE_TEST(KAlmostPrimeNumbers, TestSAMPLE1, EXPECTED1, 2, 5);
SIMPLE_TEST(KAlmostPrimeNumbers, TestSAMPLE2, EXPECTED2, 10, 2);
SIMPLE_TEST(KAlmostPrimeNumbers, TestSAMPLE3, EXPECTED3, 2, 10);
