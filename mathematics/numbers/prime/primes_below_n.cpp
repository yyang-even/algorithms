#include "common_header.h"

typedef unsigned long InputType;
/** Primes Below N
 * @reference Ronald Graham, Oren Patashnik, Donald Knuth.
 *            Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.2.
 *
 * A positive integer p is called prime if it has just two divisors, namely 1 and p.
 * By convention, 1 isn't prime, so the sequence of primes starts out like this:
 *  2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,...
 *
 * Sieve of Eratosthenes:
 * First write down all integers from 2 through N.
 * Next circle 2, marking it prime, and cross out all other multiples of 2.
 * The repeatedly circle the smallest uncircled, uncrossed number and cross out its other multiples.
 * When everything has been circled or crossed out, the circled numbers are the primes.
 */
std::vector<InputType> SieveOfEratosthenes(const InputType N) {
    std::vector<InputType> output;
    if (N > 2) {
        std::vector<bool> numbers(N, true);
        InputType j;
        for (InputType i = 2; i < N; ++i) {
            if (numbers[i]) {
                output.push_back(i);
                for (j = i * 2; j < N; j += i) {
                    numbers[j] = false;
                }
            }
        }
    }
    return output;
}

/** Sum of all prime numbers below N
 */
unsigned long long SumOfPrimesBelowN(const InputType N) {
    auto primes = SieveOfEratosthenes(N);
    return std::accumulate(primes.cbegin(), primes.cend(), 0ULL);
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
