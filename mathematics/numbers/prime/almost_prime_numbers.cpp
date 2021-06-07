#include "common_header.h"

#include "least_prime_factor_of_numbers_till_n.h"
#include "primes_below_n.h"
#include "prime_factors_of_n.h"

#include "mathematics/numbers/perfect_square.h"


namespace {

/** Almost Prime Numbers
 *
 * @reference   https://www.geeksforgeeks.org/almost-prime-numbers/
 *
 * A k-Almost Prime Number is a number having exactly k prime factors (not necessary
 * distinct). All the 1-Almost Primes are called as Prime Numbers and all the 2-Almost
 * Prime are called as semi-primes. The task is to print first n numbers that are k prime.
 */
auto KAlmostPrimeNumbers_LeastPrimeFactor(const unsigned K, unsigned N) {
    const auto smallest_prime_factors =
        LeastPrimeFactorOfNumbers(std::numeric_limits<short>::max());

    std::vector<unsigned> outputs;
    for (unsigned number = 2; N; ++number) {
        if (PrimeFactorsOfN_Sieve(number, smallest_prime_factors).size() == K) {
            outputs.push_back(number);
            --N;
        }
    }

    return outputs;
}


auto KAlmostPrimeNumbers_Counter(const unsigned K, unsigned N) {
    const auto prime_factor_counters =
        SieveOfEratosthenes_Count(std::numeric_limits<short>::max());

    std::vector<unsigned> outputs;
    for (unsigned number = 2; N; ++number) {
        if (prime_factor_counters[number] == K) {
            outputs.push_back(number);
            --N;
        }
    }

    return outputs;
}


/** Check if each element of the given array is the product of exactly K prime numbers
 *
 * @reference   https://www.geeksforgeeks.org/check-if-each-element-of-the-given-array-is-the-product-of-exactly-k-prime-numbers/
 *
 * Given an array of numbers A = {a1, a2 ... an} and the value of k, check if each number
 * ai in A can be expressed as the product of exactly k prime numbers. For every element
 * of the array print 'YES' if the condition is satisfied, else print 'NO'.
 * Note: Repeating prime numbers may also be considered. For example, if k = 2, then
 * n = 4 (=2*2) is a valid input.
 */


/** Numbers less than N which are product of exactly two distinct prime numbers
 *
 * @reference   https://www.geeksforgeeks.org/numbers-less-than-n-which-are-product-of-exactly-two-distinct-prime-numbers/
 *
 * Given a number N. The task is to find all such numbers less than N and are a product
 * of exactly two distinct prime numbers.
 */
auto NumbersLessThanNHaveExactlyTwoDistinctPrimes_LeastPrimeFactor(const unsigned N) {
    const auto smallest_prime_factors =
        LeastPrimeFactorOfNumbers(std::numeric_limits<short>::max());

    std::vector<unsigned> outputs;
    for (unsigned i = 6; i <= N; ++i) {
        if (PrimeFactorsOfN_Sieve(i, smallest_prime_factors).size() == 2 and
            not IsPerfectSquare(i)) {
            outputs.push_back(i);
        }
    }

    return outputs;
}


auto NumbersLessThanNHaveExactlyTwoDistinctPrimes_Counter(const unsigned N) {
    const auto prime_factor_counters =
        SieveOfEratosthenes_Count(std::numeric_limits<short>::max());

    std::vector<unsigned> outputs;
    for (unsigned i = 6; i <= N; ++i) {
        if (prime_factor_counters[i] == 2 and not IsPerfectSquare(i)) {
            outputs.push_back(i);
        }
    }

    return outputs;
}


/** Find count of Almost Prime numbers from 1 to N
 *
 * @reference   https://www.geeksforgeeks.org/find-count-of-almost-prime-numbers-from-1-to-n/
 *
 * Given a number N. Find number of almost primes from 1 to n. A number is called almost
 * if it has exactly two distinct prime factors.
 */
auto CountOfAlmostPrimesBelowN(const unsigned N) {
    const auto unique_prime_factor_counters = SieveOfEratosthenes_UniqueCount(N + 1);

    std::vector<unsigned> outputs;
    for (unsigned number = 6; number <= N; ++number) {
        if (unique_prime_factor_counters[number] == 2) {
            outputs.push_back(number);
        }
    }

    return outputs.size();
}

}//namespace


const std::vector<unsigned> EXPECTED1 = {4, 6, 9, 10, 14};
const std::vector<unsigned> EXPECTED2 = {1024, 1536};
const std::vector<unsigned> EXPECTED3 = {4, 6, 9, 10, 14, 15, 21, 22, 25, 26};


THE_BENCHMARK(KAlmostPrimeNumbers_LeastPrimeFactor, 10, 2);

SIMPLE_TEST(KAlmostPrimeNumbers_LeastPrimeFactor, TestSAMPLE1, EXPECTED1, 2, 5);
SIMPLE_TEST(KAlmostPrimeNumbers_LeastPrimeFactor, TestSAMPLE2, EXPECTED2, 10, 2);
SIMPLE_TEST(KAlmostPrimeNumbers_LeastPrimeFactor, TestSAMPLE3, EXPECTED3, 2, 10);


THE_BENCHMARK(KAlmostPrimeNumbers_Counter, 10, 2);

SIMPLE_TEST(KAlmostPrimeNumbers_Counter, TestSAMPLE1, EXPECTED1, 2, 5);
SIMPLE_TEST(KAlmostPrimeNumbers_Counter, TestSAMPLE2, EXPECTED2, 10, 2);
SIMPLE_TEST(KAlmostPrimeNumbers_Counter, TestSAMPLE3, EXPECTED3, 2, 10);


const std::vector<unsigned> EXPECTED4 = {6, 10, 14, 15, 21, 22, 26, 33, 34, 35, 38, 39, 46};


THE_BENCHMARK(NumbersLessThanNHaveExactlyTwoDistinctPrimes_LeastPrimeFactor, 50);

SIMPLE_TEST(NumbersLessThanNHaveExactlyTwoDistinctPrimes_LeastPrimeFactor, TestSAMPLE1,
            EXPECTED4, 50);


THE_BENCHMARK(NumbersLessThanNHaveExactlyTwoDistinctPrimes_Counter, 50);

SIMPLE_TEST(NumbersLessThanNHaveExactlyTwoDistinctPrimes_Counter, TestSAMPLE1,
            EXPECTED4, 50);


THE_BENCHMARK(CountOfAlmostPrimesBelowN, 21);

SIMPLE_TEST(CountOfAlmostPrimesBelowN, TestSAMPLE1, 2, 10);
SIMPLE_TEST(CountOfAlmostPrimesBelowN, TestSAMPLE2, 8, 21);
