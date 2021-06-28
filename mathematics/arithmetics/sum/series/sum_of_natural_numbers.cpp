#include "common_header.h"

#include "sum_of_natural_numbers.h"


namespace {

/** Find the average of first N natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/find-average-first-n-natural-numbers/
 */
inline constexpr auto AverageOfNaturalNumbers(const unsigned N) {
    return static_cast<double>(N + 1) / 2.0;
}


/**
 * @reference   Sum of first n natural numbers
 *              https://www.geeksforgeeks.org/sum-of-first-n-natural-numbers/
 *
 * Given a positive integer n. The task is to find the sum of the sum of first n natural
 * number.
 */
inline constexpr auto SumOfSumOfNaturals(const unsigned N) {
    return N * (N + 1) * (N + 2) / 6;
}


/**
 * @reference   Sum of all natural numbers in range L to R
 *              https://www.geeksforgeeks.org/sum-of-all-natural-numbers-in-range-l-to-r/
 */
inline constexpr auto
SumOfNaturalsInRange(const unsigned L, const unsigned R) {
    assert(L);
    assert(L <= R);

    return SumOfNaturals(R) - SumOfNaturals(L - 1);
}

}//namespace


THE_BENCHMARK(SumOfNaturals, 7);

SIMPLE_TEST(SumOfNaturals, TestSAMPLE1, 6, 3);
SIMPLE_TEST(SumOfNaturals, TestSAMPLE2, 15, 5);


THE_BENCHMARK(AverageOfNaturalNumbers, 7);

SIMPLE_TEST(AverageOfNaturalNumbers, TestSAMPLE1, 5.5, 10);
SIMPLE_TEST(AverageOfNaturalNumbers, TestSAMPLE2, 4, 7);
SIMPLE_TEST(AverageOfNaturalNumbers, TestSAMPLE3, 10.5, 20);


THE_BENCHMARK(SumOfSumOfNaturals, 3);

SIMPLE_TEST(SumOfSumOfNaturals, TestSAMPLE1, 10, 3);
SIMPLE_TEST(SumOfSumOfNaturals, TestSAMPLE2, 4, 2);
SIMPLE_TEST(SumOfSumOfNaturals, TestSAMPLE3, 20, 4);


THE_BENCHMARK(SumOfNaturalsInRange, 2, 5);

SIMPLE_TEST(SumOfNaturalsInRange, TestSAMPLE1, 14, 2, 5);
SIMPLE_TEST(SumOfNaturalsInRange, TestSAMPLE2, 165, 10, 20);
