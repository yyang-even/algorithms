#include "common_header.h"

#include "sum_of_factors_of_a_number.h"


namespace {

/**
 * @reference   Check if sum of divisors of two numbers are same
 *              https://www.geeksforgeeks.org/check-if-sum-of-divisors-of-two-numbers-are-same/
 *
 * Given two numbers n1 & n2, We need to check whether these numbers are equivalent
 * numbers or not. Equivalent numbers are numbers such that the sums of their proper
 * divisors are the same.
 */
inline auto HaveSameSumsOfProperDivisors(const unsigned N1, const unsigned N2) {
    return SumOfProferDivisors(N1) == SumOfProferDivisors(N2);
}

}//namespace


THE_BENCHMARK(SumOfFactorsOfN, 1100);

SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE1, 28, 12);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE2, 168, 60);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE3, 2604, 1100);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE4, 72, 30);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE5, 24, 15);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE6, 14, 13);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE7, 60, 24);


THE_BENCHMARK(HaveSameSumsOfProperDivisors, 559, 703);

SIMPLE_TEST(HaveSameSumsOfProperDivisors, TestSAMPLE1, true, 559, 703);
SIMPLE_TEST(HaveSameSumsOfProperDivisors, TestSAMPLE2, false, 36, 57);
