#include "common_header.h"

/** Program to find sum of first n natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/program-find-sum-first-n-natural-numbers/
 *
 * Given a number n, find sum of first natural numbers.
 */
auto SumOfNaturals(const unsigned N) {
    return N * (N + 1) / 2;
}


SIMPLE_BENCHMARK(SumOfNaturals, 7);

SIMPLE_TEST(SumOfNaturals, TestSAMPLE1, 6, 3);
SIMPLE_TEST(SumOfNaturals, TestSAMPLE2, 15, 5);
