#include "common_header.h"

#include "is_prime.h"

#include "least_prime_factor_of_numbers_till_n.h"


namespace {

#include "prime_factors_of_n.h"

std::string PrintAllPrimeFactors(const unsigned N) {
    std::string output;
    const auto prime_factors = PrimeFactorsOf(N);
    for (const auto factor : prime_factors) {
        output.append(std::to_string(factor));
    }
    return output;
}


auto PrimeFactorsOfN_Sieve(const unsigned N) {
    const auto smallest_prime_factors = LeastPrimeFactorOfNumbers(N);
    return PrimeFactorsOfN_Sieve(N, smallest_prime_factors);
}


/** Pollard’s Rho Algorithm for Prime Factorization
 *
 * @reference   https://www.geeksforgeeks.org/pollards-rho-algorithm-prime-factorization/
 *
 * Given a positive integer n, and that it is composite, find a divisor of it.
 * @note    Algorithm will run indefinitely for prime numbers. The algorithm may not find
 *  the factors and return a failure for composite n. In that case, we use a different set
 *  of x, y and c and try again. The above algorithm only finds a divisor. To find a prime
 *  factor, we may recursively factorize the divisor d, run algorithm for d and n/d. The
 *  cycle length is typically of the order √d.
 */
long OneDivisorOfN_PollardsRho(const long N) {
    if (N < 4) {
        return N;
    }
    if (N % 2 == 0) {
        return 2;
    }
    assert(not IsPrime_OptimizedSchoolMethod(N));

    auto x = Random_Number(2, N - 1);
    auto y = x;
    auto c = Random_Number(1, N - 1);
    long d = 1;

    while (d == 1) {
        x = (((x * x) % N) + c + N) % N;
        y = ((y * y % N) + c + N) % N;
        y = ((y * y % N) + c + N) % N;

        d = std::gcd(static_cast<long>(abs(x - y)), N);

        if (d == N) {
            return OneDivisorOfN_PollardsRho(N);
        }
    }

    return d;
}

auto testOneDivisorOfN_PollardsRho(const long N) {
    const auto factors = UniquePrimeFactorsOf(N);
    const auto one_of_factors = OneDivisorOfN_PollardsRho(N);

    const auto iter = std::find(factors.cbegin(), factors.cend(), one_of_factors);
    return iter != factors.cend();
}


/** Product of unique prime factors of a number
 *
 * @reference   https://www.geeksforgeeks.org/product-unique-prime-factors-number/
 * @reference   C/C++ Program to find Product of unique prime factors of a number
 *              https://www.geeksforgeeks.org/c-program-for-product-of-unique-prime-factors-of-a-number/
 *
 * Given a number n, we need to find the product of all of its unique prime factors.
 * Prime factors: It is basically a factor of the number that is a prime number itself.
 */
auto ProductOfUniquePrimeFactorsOfN(const unsigned N) {
    const auto unique_primes = UniquePrimeFactorsOf(N);
    return std::accumulate(unique_primes.cbegin(), unique_primes.cend(), 1u,
                           std::multiplies<unsigned>());
}


/** N-th prime factor of a given number
 *
 * @reference   https://www.geeksforgeeks.org/n-th-prime-factor-of-a-given-number/
 *
 * Given Q queries which consist of two integers, one is number(1 <= number <= 106) and
 * the other is N, the task is to find the N-th prime factor of the given number.
 */
using Query = std::pair<unsigned, unsigned>;

auto QueryNthPrimeFactorOfNumbers(const std::vector<Query> &queries) {
    const auto max_number =
        std::max_element(queries.cbegin(), queries.cend(),
    [](const auto & lhs, const auto & rhs) {
        return lhs.first < rhs.first;
    });

    const auto smallest_prime_factors = LeastPrimeFactorOfNumbers(max_number->first);

    std::vector<unsigned> outputs;
    for (const auto [number, N] : queries) {
        const auto prime_factors = PrimeFactorsOfN_Sieve(number, smallest_prime_factors);
        outputs.push_back(prime_factors[N - 1]);
    }

    return outputs;
}

}//namespace


constexpr unsigned LOWER = 1;
constexpr unsigned SAMPLE1 = 12;
constexpr unsigned SAMPLE2 = 315;


SIMPLE_BENCHMARK(PrintAllPrimeFactors, Sample1, LOWER);
SIMPLE_BENCHMARK(PrintAllPrimeFactors, Sample2, SAMPLE1);

SIMPLE_TEST(PrintAllPrimeFactors, TestLOWER, "", LOWER);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE1, "223", SAMPLE1);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE2, "3357", SAMPLE2);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE3, "11", 11);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE4, "311", 33);


const std::vector<unsigned> EXPECTED2 = {3, 5, 7};


SIMPLE_BENCHMARK(UniquePrimeFactorsOf, Sample1, SAMPLE2);

SIMPLE_TEST(UniquePrimeFactorsOf, TestSAMPLE2, EXPECTED2, SAMPLE2);


const std::vector<unsigned> EXPECTED3 = {3, 3, 5, 7};
const std::vector<unsigned> EXPECTED4 = {2, 3, 13, 157};


SIMPLE_BENCHMARK(PrimeFactorsOfN_Sieve, Sample1, 12246);

SIMPLE_TEST(PrimeFactorsOfN_Sieve, TestSAMPLE3, EXPECTED3, SAMPLE2);
SIMPLE_TEST(PrimeFactorsOfN_Sieve, TestSAMPLE4, EXPECTED4, 12246);


SIMPLE_BENCHMARK(testOneDivisorOfN_PollardsRho, Sample1, 39);

SIMPLE_TEST(testOneDivisorOfN_PollardsRho, TestSAMPLE1, true, 39);


SIMPLE_BENCHMARK(ProductOfUniquePrimeFactorsOfN, Sample1, 44);

SIMPLE_TEST(ProductOfUniquePrimeFactorsOfN, TestSAMPLE1, 22u, 44);
SIMPLE_TEST(ProductOfUniquePrimeFactorsOfN, TestSAMPLE2, 10u, 10);
SIMPLE_TEST(ProductOfUniquePrimeFactorsOfN, TestSAMPLE3, 5u, 25);


const std::vector<Query> SAMPLE_QUERIES = {{6, 1}, {210, 3}, {210, 2}, {60, 2}};
const std::vector<unsigned> EXPECTED_QUERIES = {2, 5, 3, 2};


SIMPLE_BENCHMARK(QueryNthPrimeFactorOfNumbers, Sample1, SAMPLE_QUERIES);

SIMPLE_TEST(QueryNthPrimeFactorOfNumbers, TestSAMPLE1, EXPECTED_QUERIES,
            SAMPLE_QUERIES);
