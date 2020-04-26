#include "common_header.h"

#include "is_prime.h"
#include "least_prime_factor_of_numbers_till_n.h"


namespace {

/** Legendre’s formula (Given p and n, find the largest x such that p^x divides n!)
 *
 * @reference   https://www.geeksforgeeks.org/legendres-formula-highest-power-of-prime-number-that-divides-n/
 */
auto LegendresFormula(const unsigned p, unsigned n) {
    assert(IsPrime_OptimizedSchoolMethod(p));

    unsigned x = 0;

    while (n) {
        n /= p;
        x += n;
    }

    return x;
}


/**
 * @reference   Largest power of k in n! (factorial) where k may not be prime
 *              https://www.geeksforgeeks.org/largest-power-k-n-factorial-k-may-not-prime/
 */
auto LargestPowerOfKInNFactorial(unsigned k, const unsigned n) {
    assert(k > 1);

    const auto smallest_prime_factors = LeastPrimeFactorOfNumbers(k);

    std::unordered_map<unsigned, unsigned> factor_count_map;
    while (k != 1) {
        const auto prime_factor = smallest_prime_factors[k];
        ++factor_count_map[prime_factor];
        k /= prime_factor;
    }

    auto x = std::numeric_limits<unsigned>::max();
    for (const auto &factor_count_pair : factor_count_map) {
        std::cout << factor_count_pair << std::endl;
        x = std::min(x, LegendresFormula(factor_count_pair.first, n) / factor_count_pair.second);
    }

    return x;
}

}//namespace


SIMPLE_BENCHMARK(LegendresFormula, 3, 7);

SIMPLE_TEST(LegendresFormula, TestSAMPLE1, 2, 3, 7);
SIMPLE_TEST(LegendresFormula, TestSAMPLE2, 4, 3, 10);


SIMPLE_BENCHMARK(LargestPowerOfKInNFactorial, 3, 7);

SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE1, 2, 3, 7);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE2, 4, 3, 10);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE3, 4, 2, 7);
SIMPLE_TEST(LargestPowerOfKInNFactorial, TestSAMPLE4, 2, 9, 10);
