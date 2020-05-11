#include "common_header.h"


namespace {

/** Program to find sum of first n natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/program-find-sum-first-n-natural-numbers/
 * @reference   Natural Numbers
 *              https://www.geeksforgeeks.org/natural-numbers/
 *
 * Given a number n, find sum of first natural numbers.
 */
auto SumOfNaturals(const unsigned N) {
    return N * (N + 1) / 2;
}


/** Find the average of first N natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/find-average-first-n-natural-numbers/
 */
auto AverageOfNaturalNumbers(const unsigned N) {
    return static_cast<double>(N + 1) / 2.0;
}

}//namespace


SIMPLE_BENCHMARK(SumOfNaturals, 7);

SIMPLE_TEST(SumOfNaturals, TestSAMPLE1, 6u, 3);
SIMPLE_TEST(SumOfNaturals, TestSAMPLE2, 15u, 5);


SIMPLE_BENCHMARK(AverageOfNaturalNumbers, 7);

SIMPLE_TEST(AverageOfNaturalNumbers, TestSAMPLE1, 5.5, 10);
SIMPLE_TEST(AverageOfNaturalNumbers, TestSAMPLE2, 4, 7);
SIMPLE_TEST(AverageOfNaturalNumbers, TestSAMPLE3, 10.5, 20);
