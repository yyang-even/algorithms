#include "common_header.h"


namespace {

/** Sum of first n even numbers
 *
 * @reference   https://www.geeksforgeeks.org/sum-first-n-even-numbers/
 */
auto SumOfFirstNEvenNumbers(const unsigned N) {
    return N * (N + 1);
}


/**
 * @reference   Average of first n even natural numbers
 *              https://www.geeksforgeeks.org/average-of-first-n-even-natural-numbers/
 */

}//namespace


SIMPLE_BENCHMARK(SumOfFirstNEvenNumbers, 10);

SIMPLE_TEST(SumOfFirstNEvenNumbers, TestSAMPLE1, 20u, 4);
SIMPLE_TEST(SumOfFirstNEvenNumbers, TestSAMPLE2, 420u, 20);
