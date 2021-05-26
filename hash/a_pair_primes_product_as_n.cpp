#include "common_header.h"

#include "a_pair_elements_product_as_n.h"
#include "mathematics/numbers/prime/primes_below_n.h"


namespace {

/** Find two distinct prime numbers with given product
 *
 * @reference   https://www.geeksforgeeks.org/find-two-distinct-prime-numbers-with-given-product/
 *
 * Given a number N (greater than 2). The task is to find two distinct prime numbers whose
 * product will be equal to the given number. There may be several combinations possible.
 * Print only first such pair. If it is not possible to express N as a product of two
 * distinct primes, print "Not Possible".
 */
inline auto PairPrimesProductAsN(const unsigned N) {
    assert(N > 2);
    const auto primes = PrimesBelowN(N);
    auto output = std::pair(1ul, 1ul);
    PairElementsProductAsN(primes, N, &output);
    return output;
}

}//namespace


THE_BENCHMARK(PairPrimesProductAsN, 74);

SIMPLE_TEST(PairPrimesProductAsN, TestSAMPLE1, std::pair(3ul, 5ul), 15);
SIMPLE_TEST(PairPrimesProductAsN, TestSAMPLE2, std::pair(3ul, 13ul), 39);
