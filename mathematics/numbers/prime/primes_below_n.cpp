#include "common_header.h"

#include "primes_below_n.h"


namespace {

using InputType = unsigned long;

/**
 * @reference   An interesting solution to get all prime numbers smaller than n
 *              https://www.geeksforgeeks.org/solution-get-prime-numbers-smaller-n/
 *
 * @note    This method doesn't get all the primes.
 */


/** Program to find sum of prime numbers between 1 to n
 *
 * @reference   https://www.geeksforgeeks.org/program-find-sum-prime-numbers-1-n/
 */
inline auto SumOfPrimesBelowN(const InputType N) {
    const auto primes = PrimesBelowN(N + 1);
    return std::accumulate(primes.cbegin(), primes.cend(), 0ULL);
}


/** Find product of prime numbers between 1 to n
 *
 * @reference   https://www.geeksforgeeks.org/find-product-prime-numbers-1-n/
 *
 * Given a number n, we need to find the product of all prime numbers between 1 to n.
 */
inline auto ProductOfPrimesBetween1ToN(const InputType N) {
    const auto primes = PrimesBelowN(N + 1);
    return std::accumulate(primes.cbegin(), primes.cend(), 1ULL, std::multiplies<InputType> {});
}


/** Program to find the Nth Prime Number
 *
 * @reference   https://www.geeksforgeeks.org/program-to-find-the-nth-prime-number/
 */


/** Find the Product of first N Prime Numbers
 *
 * @reference   https://www.geeksforgeeks.org/find-the-product-of-first-n-prime-numbers/
 *
 * Given an positive integer N, calculate the product of the first N prime numbers.
 */
inline auto ProductOfFirstNPrimes(const InputType N) {
    const auto primes = PrimesBelowN(std::numeric_limits<short>::max());
    assert(N < primes.size());
    return std::accumulate(primes.cbegin(), primes.cbegin() + N, 1ULL,
                           std::multiplies<InputType> {});
}


/** Sum of the first N Prime numbers
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-the-first-n-prime-numbers/
 */


/** Segmented Sieve (Print Primes in a Range)
 *
 * @reference   https://www.geeksforgeeks.org/segmented-sieve-print-primes-in-a-range/
 * @reference   Print prime numbers in a given range using C++ STL
 *              https://www.geeksforgeeks.org/print-prime-numbers-given-range-using-c-stl/
 * @reference   Prime numbers in a given range using STL | Set 2
 *              https://www.geeksforgeeks.org/prime-numbers-in-a-given-range-using-stl-set-2/
 * @reference   Program to find Prime Numbers Between given Interval
 *              https://www.geeksforgeeks.org/program-to-find-prime-numbers-between-given-interval/
 *
 * Given a range [low, high], print all primes in this range? For example, if the given
 * range is [10, 20], then output is 11, 13, 17, 19.
 */
inline auto primesInRange_LowerBound(const InputType low, const InputType high) {
    auto base_primes = PrimesBelowN(high + 1);
    const auto low_bound = std::lower_bound(base_primes.cbegin(), base_primes.cend(), low);
    base_primes.erase(base_primes.begin(), low_bound);
    return base_primes;
}

auto primesInRange(const InputType low, const InputType high,
                   const std::vector<InputType> &base_primes) {
    assert(low > 2);

    std::vector<bool> prime_marks(high - low + 1, true);
    for (const auto prime : base_primes) {
        for (InputType i =
                 static_cast<InputType>(ceil(static_cast<double>(low) / prime)) * prime;
             i <= high;
             i += prime) {
            prime_marks[i - low] = false;
        }
    }

    std::vector<InputType> output;
    for (std::size_t i = 0; i < prime_marks.size(); ++i) {
        if (prime_marks[i]) {
            output.push_back(i + low);
        }
    }

    return output;
}

inline auto PrimesInRange(const InputType low, const InputType high) {
    if (low < 3) {
        return PrimesBelowN(high + 1);
    }
    const InputType limit = std::sqrt(high) + 1;
    if (low <= limit) {
        return primesInRange_LowerBound(low, high);
    } else {
        return primesInRange(low, high, PrimesBelowN(limit));
    }
}


/** Sum of all the prime numbers in a given range
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-all-the-prime-numbers-in-a-given-range/
 *
 * Given a range [l, r], the task is to find the sum of all the prime numbers within
 * that range.
 */
inline auto SumOfPrimesInRange(const InputType low, const InputType high) {
    const auto primes = PrimesInRange(low, high);
    return std::accumulate(primes.cbegin(), primes.cend(), 0ULL);
}


auto SegmentedPrimesBelowN(const InputType N) {
    const InputType limit = std::sqrt(N) + 1;
    const auto base_primes = PrimesBelowN(limit);
    auto output = base_primes;

    for (auto low = limit; low < N; low += limit) {
        const auto high = std::min(N - 1, low + limit);
        auto primes_in_range = primesInRange(low, high, base_primes);
        output.insert(output.end(), std::make_move_iterator(primes_in_range.begin()),
                      std::make_move_iterator(primes_in_range.end()));
    }
    return output;
}


/**
 * @reference   Sieve of Sundaram to print all primes smaller than n
 *              https://www.geeksforgeeks.org/sieve-sundaram-print-primes-smaller-n/
 */
std::vector<InputType> PrimesBelowN_SieveOfSundaram(InputType N) {
    if (N <= 2)
        return {};

    std::vector<unsigned long> primes = {2};

    N = (N - 2) / 2;
    std::vector<bool> marks(N, true);

    for (InputType i = 1; i <= N; ++i) {
        for (InputType j = i; (i + j + 2 * i * j) <= N; ++j) {
            marks[i + j + 2 * i * j] = false;
        }

        if (marks[i]) {
            primes.push_back(2 * i + 1);
        }
    }

    return primes;
}

}//namespace


const InputType LOWER = 2;
const InputType SAMPLE1 = 12;
const InputType SAMPLE2 = 42;

const std::vector<InputType> RESULT1 = {2, 3, 5, 7, 11};
const std::vector<InputType> RESULT2 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};


SIMPLE_BENCHMARK(PrimesBelowN, Sample1, LOWER);
SIMPLE_BENCHMARK(PrimesBelowN, Sample2, SAMPLE1);

SIMPLE_TEST(PrimesBelowN, TestLOWER, {}, LOWER);
SIMPLE_TEST(PrimesBelowN, TestSAMPLE1, RESULT1, SAMPLE1);
SIMPLE_TEST(PrimesBelowN, TestSAMPLE2, RESULT2, SAMPLE2);


SIMPLE_BENCHMARK(PrimesBelowN_SieveOfSundaram, Sample1, LOWER);
SIMPLE_BENCHMARK(PrimesBelowN_SieveOfSundaram, Sample2, SAMPLE1);

SIMPLE_TEST(PrimesBelowN_SieveOfSundaram, TestLOWER, {}, LOWER);
SIMPLE_TEST(PrimesBelowN_SieveOfSundaram, TestSAMPLE1, RESULT1, SAMPLE1);
SIMPLE_TEST(PrimesBelowN_SieveOfSundaram, TestSAMPLE2, RESULT2, SAMPLE2);


SIMPLE_BENCHMARK(SumOfPrimesBelowN, Sample1, LOWER);
SIMPLE_BENCHMARK(SumOfPrimesBelowN, Sample2, SAMPLE1);

SIMPLE_TEST(SumOfPrimesBelowN, TestLOWER, 2, LOWER);
SIMPLE_TEST(SumOfPrimesBelowN, TestSAMPLE1, 28, SAMPLE1);
SIMPLE_TEST(SumOfPrimesBelowN, TestSAMPLE2, 37550402023, 1000000);
SIMPLE_TEST(SumOfPrimesBelowN, TestSAMPLE3, 17, 10);
SIMPLE_TEST(SumOfPrimesBelowN, TestSAMPLE4, 28, 11);


SIMPLE_BENCHMARK(ProductOfPrimesBetween1ToN, Sample1, LOWER);
SIMPLE_BENCHMARK(ProductOfPrimesBetween1ToN, Sample2, SAMPLE1);

SIMPLE_TEST(ProductOfPrimesBetween1ToN, TestLOWER, 2, LOWER);
SIMPLE_TEST(ProductOfPrimesBetween1ToN, TestSAMPLE1, 30, 5);
SIMPLE_TEST(ProductOfPrimesBetween1ToN, TestSAMPLE2, 210, 7);


SIMPLE_BENCHMARK(ProductOfFirstNPrimes, Sample1, LOWER);
SIMPLE_BENCHMARK(ProductOfFirstNPrimes, Sample2, SAMPLE1);

SIMPLE_TEST(ProductOfFirstNPrimes, TestSAMPLE1, 2310, 5);
SIMPLE_TEST(ProductOfFirstNPrimes, TestSAMPLE2, 30, 3);


const std::vector<InputType> RESULT3 = {11, 13, 17, 19};
const std::vector<InputType> RESULT4 = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
                                        53, 59, 61, 67, 71, 73, 79, 83, 89, 97
                                       };
const std::vector<InputType> RESULT5 = {2, 3, 5, 7};


THE_BENCHMARK(PrimesInRange, 10, 20);

SIMPLE_TEST(PrimesInRange, TestSAMPLE3, RESULT3, 10, 20);
SIMPLE_TEST(PrimesInRange, TestSAMPLE4, RESULT4, 10, 100);
SIMPLE_TEST(PrimesInRange, TestSAMPLE5, RESULT5, 1, 10);
SIMPLE_TEST(PrimesInRange, TestSAMPLE6, RESULT3, 10, 19);
SIMPLE_TEST(PrimesInRange, TestSAMPLE7, {}, 14, 16);
SIMPLE_TEST(PrimesInRange, TestSAMPLE8, {}, 14, 14);
SIMPLE_TEST(PrimesInRange, TestSAMPLE9, {19}, 19, 19);


THE_BENCHMARK(SumOfPrimesInRange, 1, 6);

SIMPLE_TEST(SumOfPrimesInRange, TestSAMPLE1, 10, 1, 6);
SIMPLE_TEST(SumOfPrimesInRange, TestSAMPLE2, 36, 4, 13);


const std::vector<InputType> RESULT6 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};


SIMPLE_BENCHMARK(SegmentedPrimesBelowN, Sample1, LOWER);
SIMPLE_BENCHMARK(SegmentedPrimesBelowN, Sample2, SAMPLE1);

SIMPLE_TEST(SegmentedPrimesBelowN, TestLOWER, {}, LOWER);
SIMPLE_TEST(SegmentedPrimesBelowN, TestSAMPLE1, RESULT1, SAMPLE1);
SIMPLE_TEST(SegmentedPrimesBelowN, TestSAMPLE2, RESULT2, SAMPLE2);
SIMPLE_TEST(SegmentedPrimesBelowN, TestSAMPLE6, RESULT6, 41);
