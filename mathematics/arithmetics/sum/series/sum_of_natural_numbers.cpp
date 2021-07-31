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


/**
 * @reference   Arranging Coins
 *              https://leetcode.com/problems/arranging-coins/
 *
 * You have n coins and you want to build a staircase with these coins. The staircase
 * consists of k rows where the ith row has exactly i coins. The last row of the
 * staircase may be incomplete. Given the integer n, return the number of complete rows
 * of the staircase you will build.
 */
constexpr auto ArrangingCoins_BinarySearch(const long n) {
    long left = 0, right = n;
    while (left <= right) {
        const auto mid = (left + right) / 2;
        const long sum = SumOfNaturals(mid);

        if (sum == n) {
            return mid;
        }

        if (n < sum) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return right;
}

inline constexpr int ArrangingCoins_Formula(const long n) {
    return std::sqrt(2 * n + 0.25) - 0.5;
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


THE_BENCHMARK(ArrangingCoins_BinarySearch, 5);

SIMPLE_TEST(ArrangingCoins_BinarySearch, TestSAMPLE1, 2, 5);
SIMPLE_TEST(ArrangingCoins_BinarySearch, TestSAMPLE2, 3, 8);
SIMPLE_TEST(ArrangingCoins_BinarySearch, TestSAMPLE3, 2, 3);


THE_BENCHMARK(ArrangingCoins_Formula, 5);

SIMPLE_TEST(ArrangingCoins_Formula, TestSAMPLE1, 2, 5);
SIMPLE_TEST(ArrangingCoins_Formula, TestSAMPLE2, 3, 8);
SIMPLE_TEST(ArrangingCoins_Formula, TestSAMPLE3, 2, 3);
