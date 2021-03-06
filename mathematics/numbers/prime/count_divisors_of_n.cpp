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


/** Find all divisors of a natural number
 *
 * @reference   Find all divisors of a natural number | Set 1
 *              https://www.geeksforgeeks.org/find-divisors-natural-number-set-1/
 * @reference   Find all divisors of a natural number | Set 2
 *              https://www.geeksforgeeks.org/find-all-divisors-of-a-natural-number-set-2/
 * @reference   Program to find all Factors of a Number using recursion
 *              https://www.geeksforgeeks.org/program-to-find-all-factors-of-a-number-using-recursion/
 * @reference   Program to print factors of a number in pairs
 *              https://www.geeksforgeeks.org/program-to-print-factors-of-a-number-in-pairs/
 */
auto DivisorsOfN_Pairs(const int N) {
    ArrayType divisors;
    for (int i = 1; i <= sqrt(N); ++i) {
        if (N % i == 0) {
            divisors.push_back(i);

            const auto second = N / i;
            if (second != i) {
                divisors.push_back(second);
            }
        }
    }

    std::sort(divisors.begin(), divisors.end());

    return divisors;
}

}//namespace


THE_BENCHMARK(CountDivisorsOfN, 25);

SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE1, 3, 25);
SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE2, 8, 24);
SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE3, 6, 18);
SIMPLE_TEST(CountDivisorsOfN, TestSAMPLE4, 9, 100);


THE_BENCHMARK(IsCountDivisorsOfNPrime, 13);

SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE1, true, 13);
SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE2, false, 8);
SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE3, true, 25);
SIMPLE_TEST(IsCountDivisorsOfNPrime, TestSAMPLE4, false, 100);


const ArrayType EXPECTED1 = {1, 2, 3, 6};
const ArrayType EXPECTED2 = {1, 2, 5, 10};
const ArrayType EXPECTED3 = {1, 2, 4, 5, 10, 20, 25, 50, 100};
const ArrayType EXPECTED4 = {1, 5, 25, 125};


THE_BENCHMARK(AllDivisorsOf, 10);

SIMPLE_TEST(AllDivisorsOf, TestSAMPLE1, EXPECTED1, 6);
SIMPLE_TEST(AllDivisorsOf, TestSAMPLE2, EXPECTED2, 10);
SIMPLE_TEST(AllDivisorsOf, TestSAMPLE3, EXPECTED3, 100);
SIMPLE_TEST(AllDivisorsOf, TestSAMPLE4, EXPECTED4, 125);


THE_BENCHMARK(DivisorsOfN_Pairs, 10);

SIMPLE_TEST(DivisorsOfN_Pairs, TestSAMPLE1, EXPECTED1, 6);
SIMPLE_TEST(DivisorsOfN_Pairs, TestSAMPLE2, EXPECTED2, 10);
SIMPLE_TEST(DivisorsOfN_Pairs, TestSAMPLE3, EXPECTED3, 100);
SIMPLE_TEST(DivisorsOfN_Pairs, TestSAMPLE4, EXPECTED4, 125);
