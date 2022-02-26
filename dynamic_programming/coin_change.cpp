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
 *
 * @reference   Coin Change 2
 *              https://leetcode.com/problems/coin-change-2/
 *
 * You are given an integer array coins representing coins of different denominations and
 * an integer amount representing a total amount of money.
 * Return the number of combinations that make up that amount. If that amount of money
 * cannot be made up by any combination of the coins, return 0.
 * You may assume that you have an infinite number of each kind of coin.
 * The answer is guaranteed to fit into a signed 32-bit integer.
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


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 16-1.
 * @reference   Find minimum number of coins that make a given value
 *              https://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
 *
 * Given a value V, if we want to make change for V cents, and we have infinite supply of
 * each of C = {C1, C2, .. , Cm} valued coins, what is the minimum number of coins to
 * make the change?
 *
 * @reference   Coin Change
 *              https://leetcode.com/problems/coin-change/
 *
 * You are given an integer array coins representing coins of different denominations and
 * an integer amount representing a total amount of money.
 * Return the fewest number of coins that you need to make up that amount. If that amount
 * of money cannot be made up by any combination of the coins, return -1.
 * You may assume that you have an infinite number of each kind of coin.
 */
auto MinimumCoinChange_DP(const ArrayType &coins, const int amount) {
    ArrayType dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        for (const auto c : coins) {
            if (c <= i) {
                dp[i] = std::min(dp[i], dp[i - c] + 1);
            }
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
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
 * @reference   Lemonade Change
 *              https://leetcode.com/problems/lemonade-change/
 *
 * At a lemonade stand, each lemonade costs $5. Customers are standing in a queue to buy
 * from you, and order one at a time (in the order specified by bills). Each customer
 * will only buy one lemonade and pay with either a $5, $10, or $20 bill. You must provide
 * the correct change to each customer so that the net transaction is that the customer
 * pays $5. Note that you don't have any change in hand at first. Given an integer array
 * bills where bills[i] is the bill the ith customer pays, return true if you can provide
 * every customer with correct change, or false otherwise.
 */
auto LemonadeChange(const ArrayType &bills) {
    int five = 0, ten = 0;
    for (const auto b : bills) {
        if (b == 5) {
            ++five;
        } else if (b == 10) {
            if (five-- == 0) {
                return false;
            }
            ++ten;
        } else {
            if (five > 0 and ten > 0) {
                --five;
                --ten;
            } else if (five >= 3) {
                five -= 3;
            } else {
                return false;
            }
        }
    }

    return true;
}


/**
 * @reference   Combination Sum IV
 *              https://leetcode.com/problems/combination-sum-iv/
 *
 * Given an array of distinct integers nums and a target integer target, return the
 * number of possible combinations that add up to target.
 * The test cases are generated so that the answer can fit in a 32-bit integer.
 * Follow up: What if negative numbers are allowed in the given array? How does it change
 * the problem? What limitation we need to add to the question to allow negative numbers?
 */
auto PermutationSum(const ArrayType &nums, const int target) {
    unsigned dp[target + 1] = {1};

    for (auto i = 1; i <= target; ++i) {
        for (const auto n : nums) {
            if (i >= n) {
                dp[i] += dp[i - n];
            }
        }
    }

    return dp[target];
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3};
const ArrayType SAMPLE2 = {2, 3, 5, 6};
const ArrayType SAMPLE3 = {1, 5, 10};
const ArrayType SAMPLE5 = {5, 10, 25};
const ArrayType SAMPLE6 = {1, 5, 6, 9};
const ArrayType SAMPLE7 = {1, 2, 5, 10, 20, 50, 100, 500, 1000};
const ArrayType SAMPLE9 = {1, 10, 25};
const ArrayType SAMPLE11 = {1, 2, 5};
const ArrayType SAMPLE12 = {2};
const ArrayType SAMPLE13 = {1};


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
SIMPLE_TEST(CoinChange_SpaceOptimized, TestSAMPLE11, 4, SAMPLE11, 5);
SIMPLE_TEST(CoinChange_SpaceOptimized, TestSAMPLE12, 0, SAMPLE12, 3);
SIMPLE_TEST(CoinChange_SpaceOptimized, TestSAMPLE13, 1, SAMPLE13, 1);


THE_BENCHMARK(MinimumCoinChange_Greedy, SAMPLE7, 70);

SIMPLE_TEST(MinimumCoinChange_Greedy, TestSAMPLE7, 2, SAMPLE7, 70);
SIMPLE_TEST(MinimumCoinChange_Greedy, TestSAMPLE8, 3, SAMPLE7, 121);
SIMPLE_TEST(MinimumCoinChange_Greedy, TestSAMPLE9, 5, SAMPLE9, 14);
SIMPLE_TEST(MinimumCoinChange_Greedy, TestSAMPLE10, 7, SAMPLE9, 88);


THE_BENCHMARK(MinimumCoinChange_DP, SAMPLE7, 70);

SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE1, 2, SAMPLE1, 4);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE2, 2, SAMPLE2, 10);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE3, 4, SAMPLE3, 8);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE4, 1, SAMPLE3, 10);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE5, 2, SAMPLE5, 30);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE6, 2, SAMPLE6, 11);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE7, 2, SAMPLE7, 70);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE8, 3, SAMPLE7, 121);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE9, 5, SAMPLE9, 14);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE10, 7, SAMPLE9, 88);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE11, 3, SAMPLE11, 11);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE12, -1, SAMPLE12, 3);
SIMPLE_TEST(MinimumCoinChange_DP, TestSAMPLE13, 0, SAMPLE13, 0);


const ArrayType SAMPLE1B = {5, 5, 5, 10, 20};
const ArrayType SAMPLE2B = {5, 5, 10, 10, 20};
const ArrayType SAMPLE3B = {5, 5, 10};
const ArrayType SAMPLE4B = {10, 10};


THE_BENCHMARK(LemonadeChange, SAMPLE1B);

SIMPLE_TEST(LemonadeChange, TestSAMPLE1, true, SAMPLE1B);
SIMPLE_TEST(LemonadeChange, TestSAMPLE2, false, SAMPLE2B);
SIMPLE_TEST(LemonadeChange, TestSAMPLE3, true, SAMPLE3B);
SIMPLE_TEST(LemonadeChange, TestSAMPLE4, false, SAMPLE4B);


THE_BENCHMARK(PermutationSum, SAMPLE1, 4);

SIMPLE_TEST(PermutationSum, TestSAMPLE1, 7, SAMPLE1, 4);
SIMPLE_TEST(PermutationSum, TestSAMPLE2, 0, SAMPLE12, 1);
