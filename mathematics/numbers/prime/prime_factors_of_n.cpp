#include "common_header.h"

#include "prime_factors_of_n.h"
#include "is_prime.h"

#include "least_prime_factor_of_numbers_till_n.h"

typedef unsigned InputType;


std::string PrintAllPrimeFactors(const InputType N) {
    std::string output;
    const auto prime_factors = PrimeFactorsOf(N);
    for (const auto factor : prime_factors) {
        output.append(std::to_string(factor));
    }
    return output;
}


auto PrimeFactorsOfNSieve(unsigned N) {
    const auto smallest_prime_factors = LeastPrimeFactorOfNumbers(N);

    std::vector<unsigned> output;
    while (N != 1) {
        output.push_back(smallest_prime_factors[N]);
        N /= smallest_prime_factors[N];
    }

    return output;
}


/** Pollard’s Rho Algorithm for Prime Factorization
 *
 * @reference   https://www.geeksforgeeks.org/pollards-rho-algorithm-prime-factorization/
 *
 * Given a positive integer n, and that it is composite, find a divisor of it.
 * Note: Algorithm will run indefinitely for prime numbers.
 *  The algorithm may not find the factors and return a failure for composite n.
 *  In that case, we use a different set of x, y and c and try again.
 *  The above algorithm only finds a divisor. To find a prime factor, we may
 *  recursively factorize the divisor d, run algorithm for d and n/d. The cycle
 *  length is typically of the order √d.
 */
long OneDivisorOfNPollardsRho(const long N) {
    if (N < 4) {
        return N;
    }
    if (N % 2 == 0) {
        return 2;
    }
    assert(not IsPrimeOptimizedSchoolMethod(N));

    auto x = Random_Number<long>(2, N - 1);
    auto y = x;
    auto c = Random_Number<long>(1, N - 1);
    long d = 1;

    while (d == 1) {
        x = (((x * x) % N) + c + N) % N;
        y = ((y * y % N) + c + N) % N;
        y = ((y * y % N) + c + N) % N;

        d = std::gcd(static_cast<long>(abs(x - y)), N);

        if (d == N) {
            return OneDivisorOfNPollardsRho(N);
        }
    }

    return d;
}

INT_BOOL testOneDivisorOfNPollardsRho(const long N) {
    const auto factors = UniquePrimeFactorsOf(N);
    const auto one_of_factors = OneDivisorOfNPollardsRho(N);

    const auto iter = std::find(factors.cbegin(), factors.cend(), one_of_factors);
    return iter != factors.cend();
}


/** Product of unique prime factors of a number
 *
 * @reference   https://www.geeksforgeeks.org/product-unique-prime-factors-number/
 *
 * Given a number n, we need to find the product of all of its unique prime factors.
 * Prime factors: It is basically a factor of the number that is a prime number itself.
 */
auto ProductOfUniquePrimeFactorsOfN(const unsigned N) {
    const auto unique_primes = UniquePrimeFactorsOf(N);
    return std::accumulate(unique_primes.cbegin(), unique_primes.cend(), 1u,
                           std::multiplies<unsigned>());
}


constexpr InputType LOWER = 1;
constexpr InputType SAMPLE1 = 12;
constexpr InputType SAMPLE2 = 315;

SIMPLE_BENCHMARK(PrintAllPrimeFactors, LOWER);
SIMPLE_BENCHMARK(PrintAllPrimeFactors, SAMPLE1);
RANDOM_BENCHMARK(PrintAllPrimeFactors, LOWER, std::numeric_limits<InputType>::max());

SIMPLE_TEST(PrintAllPrimeFactors, TestLOWER, "", LOWER);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE1, "223", SAMPLE1);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE2, "3357", SAMPLE2);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE3, "11", 11);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE4, "311", 33);


const std::vector<unsigned> EXPECTED2 = {3, 5, 7};

SIMPLE_BENCHMARK(UniquePrimeFactorsOf, SAMPLE2);

SIMPLE_TEST(UniquePrimeFactorsOf, TestSAMPLE2, EXPECTED2, SAMPLE2);


const std::vector<unsigned> EXPECTED3 = {3, 3, 5, 7};
const std::vector<unsigned> EXPECTED4 = {2, 3, 13, 157};

SIMPLE_BENCHMARK(PrimeFactorsOfNSieve, 12246);

SIMPLE_TEST(PrimeFactorsOfNSieve, TestSAMPLE3, EXPECTED3, SAMPLE2);
SIMPLE_TEST(PrimeFactorsOfNSieve, TestSAMPLE4, EXPECTED4, 12246);


SIMPLE_BENCHMARK(testOneDivisorOfNPollardsRho, 39);

SIMPLE_TEST(testOneDivisorOfNPollardsRho, TestSAMPLE1, TRUE, 39);


SIMPLE_BENCHMARK(ProductOfUniquePrimeFactorsOfN, 44);

SIMPLE_TEST(ProductOfUniquePrimeFactorsOfN, TestSAMPLE1, 22, 44);
SIMPLE_TEST(ProductOfUniquePrimeFactorsOfN, TestSAMPLE2, 10, 10);
SIMPLE_TEST(ProductOfUniquePrimeFactorsOfN, TestSAMPLE3, 5, 25);
