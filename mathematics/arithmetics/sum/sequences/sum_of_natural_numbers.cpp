#include "common_header.h"


namespace {

/** Program to find sum of first n natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/program-find-sum-first-n-natural-numbers/
 *
 * Given a number n, find sum of first natural numbers.
 */
auto SumOfNaturals(const unsigned N) {
    return N * (N + 1) / 2;
}

}//namespace


SIMPLE_BENCHMARK(SumOfNaturals, 7);

SIMPLE_TEST(SumOfNaturals, TestSAMPLE1, 6u, 3);
SIMPLE_TEST(SumOfNaturals, TestSAMPLE2, 15u, 5);
