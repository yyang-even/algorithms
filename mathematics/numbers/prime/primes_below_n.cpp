#include "common_header.h"

#include "primes_below_n.h"

typedef unsigned long InputType;

/** Sum of all prime numbers below N
 */
auto SumOfPrimesBelowN(const InputType N) {
    const auto primes = SieveOfEratosthenes(N);
    return std::accumulate(primes.cbegin(), primes.cend(), 0ULL);
}


/** Find product of prime numbers between 1 to n
 *
 * @reference   https://www.geeksforgeeks.org/find-product-prime-numbers-1-n/
 *
 * Given a number n, we need to find the product of all prime numbers between 1 to n.
 */
auto ProductOfPrimesBetween1ToN(const InputType N) {
    const auto primes = SieveOfEratosthenes(N + 1ul);
    return std::accumulate(primes.cbegin(), primes.cend(), 1ULL, std::multiplies<InputType> {});
}


/** Find the Product of first N Prime Numbers
 *
 * @reference   https://www.geeksforgeeks.org/find-the-product-of-first-n-prime-numbers/
 *
 * Given an positive integer N, calculate the product of the first N prime numbers.
 */
auto ProductOfFirstNPrimes(const InputType N) {
    const auto primes = SieveOfEratosthenes(std::numeric_limits<short>::max());
    assert(N < primes.size());
    return std::accumulate(primes.cbegin(), primes.cbegin() + N, 1ULL, std::multiplies<InputType> {});
}


const InputType LOWER = 2;
const InputType SAMPLE1 = 12;
const InputType SAMPLE2 = 42;

SIMPLE_BENCHMARK(SieveOfEratosthenes, LOWER);
SIMPLE_BENCHMARK(SieveOfEratosthenes, SAMPLE1);

SIMPLE_TEST(SieveOfEratosthenes, TestLOWER, std::vector<InputType> {}, LOWER);
const std::vector<InputType> RESULT1 = {2, 3, 5, 7, 11};
SIMPLE_TEST(SieveOfEratosthenes, TestSAMPLE1, RESULT1, SAMPLE1);
const std::vector<InputType> RESULT2 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
SIMPLE_TEST(SieveOfEratosthenes, TestSAMPLE2, RESULT2, SAMPLE2);


SIMPLE_BENCHMARK(SumOfPrimesBelowN, LOWER);
SIMPLE_BENCHMARK(SumOfPrimesBelowN, SAMPLE1);

SIMPLE_TEST(SumOfPrimesBelowN, TestLOWER, 0, LOWER);
SIMPLE_TEST(SumOfPrimesBelowN, TestSAMPLE1, 28, SAMPLE1);
SIMPLE_TEST(SumOfPrimesBelowN, TestSAMPLE2, 37550402023, 1000000);


SIMPLE_BENCHMARK(ProductOfPrimesBetween1ToN, LOWER);
SIMPLE_BENCHMARK(ProductOfPrimesBetween1ToN, SAMPLE1);

SIMPLE_TEST(ProductOfPrimesBetween1ToN, TestLOWER, 2, LOWER);
SIMPLE_TEST(ProductOfPrimesBetween1ToN, TestSAMPLE1, 30, 5);
SIMPLE_TEST(ProductOfPrimesBetween1ToN, TestSAMPLE2, 210, 7);


SIMPLE_BENCHMARK(ProductOfFirstNPrimes, LOWER);
SIMPLE_BENCHMARK(ProductOfFirstNPrimes, SAMPLE1);

SIMPLE_TEST(ProductOfFirstNPrimes, TestSAMPLE1, 2310, 5);
SIMPLE_TEST(ProductOfFirstNPrimes, TestSAMPLE2, 30, 3);
