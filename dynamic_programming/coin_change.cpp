#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Coin Change | DP-7
 *
 * @reference   https://www.geeksforgeeks.org/coin-change-dp-7/
 * @reference   C Program Coin Change
 *              https://www.geeksforgeeks.org/c-program-coin-change/
 *
 * Given a value N, if we want to make change for N cents, and we have infinite supply
 * of each of S = {S1, S2, .. , Sm} valued coins, how many ways can we make the change?
 * The order of coins doesn’t matter.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.8.
 */
auto CoinChange(const ArrayType &coins, const ArrayType::value_type N) {
    unsigned counts[N + 1][coins.size()] = {};

    for (ArrayType::size_type i = 0; i < coins.size(); ++i) {
        counts[0][i] = 1;
    }

    for (ArrayType::value_type i = 1; i <= N; ++i) {
        for (ArrayType::size_type j = 0; j < coins.size(); ++j) {
            const auto count_including_j = (i >= coins[j]) ? counts[i - coins[j]][j] : 0;
            const auto count_excluding_j = (j == 0) ? 0 : counts[i][j - 1];
            counts[i][j] = count_including_j + count_excluding_j;
        }
    }

    return counts[N][coins.size() - 1];
}


/**
 * @reference   Understanding The Coin Change Problem With Dynamic Programming
 *              https://www.geeksforgeeks.org/understanding-the-coin-change-problem-with-dynamic-programming/
 */
auto CoinChange_SpaceOptimized(const ArrayType &coins, const ArrayType::value_type N) {
    unsigned counts[N + 1] = {1};

    for (const auto one_coin : coins) {
        for (auto j = one_coin; j <= N; ++j) {
            counts[j] += counts[j - one_coin];
        }
    }

    return counts[N];
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 16-1.
 * @reference   Find minimum number of coins that make a given value
 *              https://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
 *
 * Given a value V, if we want to make change for V cents, and we have infinite supply of
 * each of C = {C1, C2, .. , Cm} valued coins, what is the minimum number of coins to
 * make the change?
 */
auto MinimumCoinChange(const ArrayType &coins, const ArrayType::value_type N) {
    std::vector<unsigned> min_counts(N + 1, std::numeric_limits<unsigned>::max() - 1);
    min_counts[0] = 0;

    for (const auto one_coin : coins) {
        for (auto j = one_coin; j <= N; ++j) {
            min_counts[j] = std::min(min_counts[j - one_coin] + 1, min_counts[j]);
        }
    }

    return min_counts[N];
}


/**
 * @reference   Coin Change | BFS Approach
 *              https://www.geeksforgeeks.org/coin-change-bfs-approach/
 *
 * Given an integer X and an array arr[] of length N consisting of positive integers, the
 * task is to pick minimum number of integers from the array such that they sum up to N.
 * Any number can be chosen infinite number of times. If no answer exists then print -1.
 *
 * @note    This approach is less efficient than the DP solution above.
 */


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 16-1.
 * @reference   Greedy Algorithm to find Minimum number of Coins
 *              https://www.geeksforgeeks.org/greedy-algorithm-to-find-minimum-number-of-coins/
 *
 * Given a value V, if we want to make a change for V Rs, and we have an infinite supply
 * of each of the denominations in Indian currency, i.e., we have an infinite supply of
 * {1, 2, 5, 10, 20, 50, 100, 500, 1000} valued coins/notes, what is the minimum number of
 * coins and/or notes needed to make the change?
 *
 * @reference   Find out the minimum number of coins required to pay total amount
 *              https://www.geeksforgeeks.org/find-out-the-minimum-number-of-coins-required-to-pay-total-amount/
 *
 * Given a total amount of N and unlimited number of coins worth 1,  10 and 25 currency
 * coins. Find out the minimum number of coins you need to use to pay exactly amount N.
 *
 * @note    This approach may not work for all denominations.
 */
auto MinimumCoinChange_Greedy(ArrayType coins, ArrayType::value_type N) {
    std::sort(coins.begin(), coins.end(), std::greater<ArrayType::value_type> {});

    unsigned min_count = 0;
    for (const auto one_coin : coins) {
        while (N >= one_coin) {
            N -= one_coin;
            ++min_count;
        }
    }

    return min_count;
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3};
const ArrayType SAMPLE2 = {2, 3, 5, 6};
const ArrayType SAMPLE3 = {1, 5, 10};


THE_BENCHMARK(CoinChange, SAMPLE1, 4);

SIMPLE_TEST(CoinChange, TestSAMPLE1, 4, SAMPLE1, 4);
SIMPLE_TEST(CoinChange, TestSAMPLE2, 5, SAMPLE2, 10);
SIMPLE_TEST(CoinChange, TestSAMPLE3, 2, SAMPLE3, 8);
SIMPLE_TEST(CoinChange, TestSAMPLE4, 4, SAMPLE3, 10);


THE_BENCHMARK(CoinChange_SpaceOptimized, SAMPLE1, 4);

SIMPLE_TEST(CoinChange_SpaceOptimized, TestSAMPLE1, 4, SAMPLE1, 4);
SIMPLE_TEST(CoinChange_SpaceOptimized, TestSAMPLE2, 5, SAMPLE2, 10);
SIMPLE_TEST(CoinChange_SpaceOptimized, TestSAMPLE3, 2, SAMPLE3, 8);
SIMPLE_TEST(CoinChange_SpaceOptimized, TestSAMPLE4, 4, SAMPLE3, 10);


const ArrayType SAMPLE5 = {5, 10, 25};
const ArrayType SAMPLE6 = {1, 5, 6, 9};
const ArrayType SAMPLE7 = {1, 2, 5, 10, 20, 50, 100, 500, 1000};
const ArrayType SAMPLE9 = {1, 10, 25};


THE_BENCHMARK(MinimumCoinChange, SAMPLE1, 4);

SIMPLE_TEST(MinimumCoinChange, TestSAMPLE1, 2, SAMPLE1, 4);
SIMPLE_TEST(MinimumCoinChange, TestSAMPLE2, 2, SAMPLE2, 10);
SIMPLE_TEST(MinimumCoinChange, TestSAMPLE3, 4, SAMPLE3, 8);
SIMPLE_TEST(MinimumCoinChange, TestSAMPLE4, 1, SAMPLE3, 10);
SIMPLE_TEST(MinimumCoinChange, TestSAMPLE5, 2, SAMPLE5, 30);
SIMPLE_TEST(MinimumCoinChange, TestSAMPLE6, 2, SAMPLE6, 11);
SIMPLE_TEST(MinimumCoinChange, TestSAMPLE7, 2, SAMPLE7, 70);
SIMPLE_TEST(MinimumCoinChange, TestSAMPLE8, 3, SAMPLE7, 121);
SIMPLE_TEST(MinimumCoinChange, TestSAMPLE9, 5, SAMPLE9, 14);
SIMPLE_TEST(MinimumCoinChange, TestSAMPLE10, 7, SAMPLE9, 88);


THE_BENCHMARK(MinimumCoinChange_Greedy, SAMPLE7, 70);

SIMPLE_TEST(MinimumCoinChange_Greedy, TestSAMPLE7, 2, SAMPLE7, 70);
SIMPLE_TEST(MinimumCoinChange_Greedy, TestSAMPLE8, 3, SAMPLE7, 121);
SIMPLE_TEST(MinimumCoinChange_Greedy, TestSAMPLE9, 5, SAMPLE9, 14);
SIMPLE_TEST(MinimumCoinChange_Greedy, TestSAMPLE10, 7, SAMPLE9, 88);
