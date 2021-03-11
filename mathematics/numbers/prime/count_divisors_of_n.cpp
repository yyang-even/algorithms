#include "common_header.h"

#include "is_prime.h"

#include "count_divisors_of_n.h"


namespace {

using ArrayType = std::vector<unsigned>;

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


/**
 * @reference   Generating all divisors of a number using its prime factorization
 *              https://www.geeksforgeeks.org/generating-all-divisors-of-a-number-using-its-prime-factorization/
 */
using PrimeCountPairsType = std::vector<std::pair<unsigned, unsigned>>;

void AllDivisorsOf(const PrimeCountPairsType::const_iterator iter,
                   const PrimeCountPairsType::const_iterator cend,
                   unsigned current_divisor, ArrayType &results) {
    if (iter == cend) {
        results.push_back(current_divisor);
    } else {
        const auto [prime, count] = *iter;
        for (unsigned i = 0; i < count; ++i) {
            AllDivisorsOf(std::next(iter), cend, current_divisor, results);
            current_divisor *= prime;
        }
    }
}

auto AllDivisorsOf(const unsigned N) {
    std::vector<std::pair<unsigned, unsigned>> prime_count_pairs;
    CountPrimeFactors(N, [&prime_count_pairs](const auto prime_factor, const auto count) {
        prime_count_pairs.emplace_back(prime_factor, count);
    });

    ArrayType results;
    AllDivisorsOf(prime_count_pairs.cbegin(), prime_count_pairs.cend(), 1, results);

    std::sort(results.begin(), results.end());
    return results;
}

}//namespace


SIMPLE_BENCHMARK(CountDivisorsOfN, Sample1, 25);

SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE1, 3, 25);
SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE2, 8, 24);
SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE3, 6, 18);
SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE4, 9, 100);


SIMPLE_BENCHMARK(IsCountDivisorsOfNPrime, Sample1, 13);

SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE1, true, 13);
SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE2, false, 8);
SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE3, true, 25);
SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE4, false, 100);


const ArrayType EXPECTED1 = {1, 2, 3, 6};
const ArrayType EXPECTED2 = {1, 2, 5, 10};


SIMPLE_BENCHMARK(AllDivisorsOf, Sample1, 10);

SIMPLE_TEST(AllDivisorsOf, TestSAMPLE1, EXPECTED1, 6);
SIMPLE_TEST(AllDivisorsOf, TestSAMPLE2, EXPECTED2, 10);
