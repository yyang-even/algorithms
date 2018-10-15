#include "common_header.h"

#include "a_pair_elements_sum_as_n.h"
#include "mathematics/numbers/prime/primes_below_n.h"


using InputType = unsigned;
/** Find two prime numbers with given sum
 *
 * @reference   https://www.geeksforgeeks.org/find-two-prime-numbers-with-given-sum/
 *
 * Given an even number (greater than 2), print two prime numbers whose sum
 * will be equal to given number. There may be several combinations possible.
 * An interesting point is, a solution always exist according to Goldbach’s
 * conjecture.
 */
auto PairPrimesSumAsN(const InputType N) {
    const auto primes = SieveOfEratosthenes(N);
    auto output = std::make_pair(primes[0], primes[0]);
    PairOfElementsSumAsNHashmap(primes, N, &output);
    return output;
}


SIMPLE_BENCHMARK(PairPrimesSumAsN, 74);

SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE1, std::make_pair(31ul, 43ul), 74);
SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE2, std::make_pair(503ul, 521ul), 1024);
SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE3, std::make_pair(29ul, 37ul), 66);
SIMPLE_TEST(PairPrimesSumAsN, TestSAMPLE4, std::make_pair(4987ul, 5003ul), 9990);
