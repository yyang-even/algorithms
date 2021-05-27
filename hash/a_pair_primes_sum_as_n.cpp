#include "common_header.h"

#include "a_pair_elements_sum_as_n.h"
#include "mathematics/numbers/prime/primes_below_n.h"


namespace {

/** Pair of prime numbers with a given sum and minimum absolute difference
 *
 * @reference   https://www.geeksforgeeks.org/pair-of-prime-numbers-with-a-given-sum-and-minimum-absolute-difference/
 *
 * Given an integer 'sum' (less than 10^8), the task is to find a pair of prime numbers
 * whose sum is equal to the given 'sum'. Out of all the possible pairs, the absolute
 * difference between the chosen pair must be minimum. If the 'sum' cannot be represented
 * as a sum of two prime numbers then print "Cannot be represented as sum of two primes".
 */

/** Find two prime numbers with given sum
 *
 * @reference   https://www.geeksforgeeks.org/find-two-prime-numbers-with-given-sum/
 * @reference   Program for Goldbach’s Conjecture (Two Primes with given Sum)
 *              https://www.geeksforgeeks.org/program-for-goldbachs-conjecture-two-primes-with-given-sum/
 *
 * Given an even number (greater than 2), print two prime numbers whose sum will be equal
 * to given number. There may be several combinations possible. An interesting point is,
 * a solution always exist according to Goldbach's conjecture.
 */
inline auto PairPrimesSumAsN(const unsigned N) {
    assert((N > 2) and (N % 2 == 0));

    const auto primes = PrimesBelowN(N);
    auto output = std::pair(primes[0], primes[0]);
    PairOfElementsSumAsN_Hashmap(primes, N, &output);
    return output;
}

}//namespace


THE_BENCHMARK(PairPrimesSumAsN, 74);

SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE1, std::pair(31ul, 43ul), 74);
SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE2, std::pair(503ul, 521ul), 1024);
SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE3, std::pair(29ul, 37ul), 66);
SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE4, std::pair(4987ul, 5003ul), 9990);
SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE5, std::pair(499ul, 503ul), 1002);
SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE6, std::pair(983ul, 1019ul), 2002);
