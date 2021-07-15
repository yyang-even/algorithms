#include "common_header.h"

#include "mathematics/arithmetics/sum/largest_sum_contiguous_subarray.h"


namespace {

using ArrayType = std::vector<int>;

/** Best Time to Buy and Sell Stock
 *
 * @reference   https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 *
 * You are given an array prices where prices[i] is the price of a given stock on the
 * ith day. You want to maximize your profit by choosing a single day to buy one stock
 * and choosing a different day in the future to sell that stock. Return the maximum
 * profit you can achieve from this transaction. If you cannot achieve any profit,
 * return 0.
 */
auto StockBuyAndSell_SingleTransaction(const ArrayType &prices) {
    int min_price = INT_MAX;
    int max_profit = 0;
    for (const auto a_price : prices) {
        if (min_price > a_price) {
            min_price = a_price;
        } else {
            const auto new_profit = a_price - min_price;
            if (new_profit > max_profit) {
                max_profit = new_profit;
            }
        }
    }

    return max_profit;
}


/**
 * @reference   Maximum difference between two elements such that larger element appears after the smaller number
 *              https://www.geeksforgeeks.org/maximum-difference-between-two-elements/
 *
 * Given an array arr[] of integers, find out the maximum difference between any two
 * elements such that larger element appears after the smaller number.
 */
auto MaxDiffBetweenTwoElementsNoSort_SubarraySum(const ArrayType &elements) {
    assert(elements.size() > 1);

    ArrayType diff_array{};
    for (auto iter = elements.cbegin() + 1; iter != elements.cend(); ++iter) {
        diff_array.push_back(*iter - * (iter - 1));
    }

    return LargestSumContiguousSubarray_Kadane(diff_array);
}


/**
 * @reference   Best Time to Buy and Sell Stock II
 *              https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
 *
 * You are given an array prices where prices[i] is the price of a given stock on the
 * ith day. Find the maximum profit you can achieve. You may complete as many
 * transactions as you like (i.e., buy one and sell one share of the stock multiple
 * times). Note: You may not engage in multiple transactions simultaneously (i.e., you
 * must sell the stock before you buy again).
 *
 * @reference   Stock Buy Sell to Maximize Profit
 *              https://www.geeksforgeeks.org/stock-buy-sell/
 */
auto StockBuyAndSell_Unlimited_Greedy(const ArrayType &prices) {
    int max_profit = 0;
    for (ArrayType::size_type i = 1; i < prices.size(); ++i) {
        if (prices[i] > prices[i - 1]) {
            max_profit += prices[i] - prices[i - 1];
        }
    }

    return max_profit;
}


/**
 * @reference   Best Time to Buy and Sell Stock III
 *              https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
 *
 * You are given an array prices where prices[i] is the price of a given stock on the
 * ith day. Find the maximum profit you can achieve. You may complete at most two
 * transactions. Note: You may not engage in multiple transactions simultaneously
 * (i.e., you must sell the stock before you buy again).
 *
 * @reference   Maximum profit by buying and selling a share at most twice
 *              https://www.geeksforgeeks.org/maximum-profit-by-buying-and-selling-a-share-at-most-twice/
 */
auto StockBuyAndSell_2Transactions(const ArrayType &prices) {
    ArrayType left(prices.size(), 0);
    int minimum = prices.front();
    for (std::size_t i = 1; i < prices.size(); ++i) {
        if (minimum > prices[i]) {
            minimum = prices[i];
        }

        left[i] = std::max(left[i - 1], prices[i] - minimum);
    }

    ArrayType right(prices.size(), 0);
    int maximum = prices.back();
    for (int i = prices.size() - 2; i >= 0; --i) {
        if (maximum < prices[i]) {
            maximum = prices[i];
        }

        right[i] = std::max(right[i + 1], maximum - prices[i]);
    }

    int profit = 0;
    for (std::size_t i = 0; i < prices.size(); ++i) {
        const auto current = left[i] + right[i];
        if (profit < current) {
            profit = current;
        }
    }

    return profit;
}


auto StockBuyAndSell_2Transactions_1Array(const ArrayType &prices) {
    ArrayType profit(prices.size(), 0);
    int maximum = prices.back();
    for (int i = prices.size() - 2; i >= 0; --i) {
        if (maximum < prices[i]) {
            maximum = prices[i];
        }

        profit[i] = std::max(profit[i + 1], maximum - prices[i]);
    }

    int minimum = prices.front();
    for (std::size_t i = 1; i < prices.size(); ++i) {
        if (minimum > prices[i]) {
            minimum = prices[i];
        }

        profit[i] = std::max(profit[i - 1], profit[i] + prices[i] - minimum);
    }

    return profit.back();
}


/**
 * @reference   Maximum profit by buying and selling a stock at most twice | Set 2
 *              https://www.geeksforgeeks.org/maximum-profit-by-buying-and-selling-a-stock-at-most-twice-set-2/
 */
auto StockBuyAndSell_2Transactions_O1(const ArrayType &prices) {
    int cost1 = INT_MAX;
    int cost2 = INT_MAX;
    int profit1 = 0;
    int profit2 = 0;
    for (const auto a_price : prices) {
        cost1 = std::min(a_price, cost1);
        profit1 = std::max(profit1, a_price - cost1);
        cost2 = std::min(cost2, a_price - profit1);
        profit2 = std::max(profit2, a_price - cost2);
    }

    return profit2;
}


/**
 * @reference   Best Time to Buy and Sell Stock IV
 *              https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
 *
 * You are given an integer array prices where prices[i] is the price of a given stock
 * on the ith day, and an integer k. Find the maximum profit you can achieve. You may
 * complete at most k transactions. Note: You may not engage in multiple transactions
 * simultaneously (i.e., you must sell the stock before you buy again).
 *
 * @reference   Maximum profit by buying and selling a share at most k times
 *              https://www.geeksforgeeks.org/maximum-profit-by-buying-and-selling-a-share-at-most-k-times/
 */
auto StockBuyAndSell_K_Transactions_DP(const ArrayType &prices, const int K) {
    if (prices.empty()) {
        return 0;
    }

    int profit[K + 1][prices.size()] = {};

    for (int i = 1; i <= K; ++i) {
        for (std::size_t j = 1; j < prices.size(); ++j) {
            int max_so_far = INT_MIN;

            for (std::size_t m = 0; m < j; ++m) {
                max_so_far = std::max(max_so_far, prices[j] - prices[m] + profit[i - 1][m]);
            }

            profit[i][j] = std::max(profit[i][j - 1], max_so_far);
        }
    }

    return profit[K][prices.size() - 1];
}


auto StockBuyAndSell_K_Transactions_DP_Optimized(const ArrayType &prices, const int K) {
    if (prices.empty()) {
        return 0;
    }

    int profit[K + 1][prices.size()] = {};

    for (int i = 1; i <= K; ++i) {
        int prevDiff = INT_MIN;
        for (std::size_t j = 1; j < prices.size(); ++j) {
            prevDiff = std::max(prevDiff, profit[i - 1][j - 1] - prices[j - 1]);
            profit[i][j] = std::max(profit[i][j - 1], prices[j] + prevDiff);
        }
    }

    return profit[K][prices.size() - 1];
}

}//namespace


const ArrayType SAMPLE1 = {};
const ArrayType SAMPLE2 = {7, 1, 5, 3, 6, 4};
const ArrayType SAMPLE3 = {7, 6, 4, 3, 1};
const ArrayType SAMPLE4 = {1, 2, 3, 4, 5};
const ArrayType SAMPLE5 = {2, 3, 10, 6, 4, 8, 1};
const ArrayType SAMPLE6 = {7, 9, 5, 6, 3, 2};


THE_BENCHMARK(StockBuyAndSell_SingleTransaction, SAMPLE2);

SIMPLE_TEST(StockBuyAndSell_SingleTransaction, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(StockBuyAndSell_SingleTransaction, TestSAMPLE2, 5, SAMPLE2);
SIMPLE_TEST(StockBuyAndSell_SingleTransaction, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(StockBuyAndSell_SingleTransaction, TestSAMPLE4, 4, SAMPLE4);
SIMPLE_TEST(StockBuyAndSell_SingleTransaction, TestSAMPLE5, 8, SAMPLE5);
SIMPLE_TEST(StockBuyAndSell_SingleTransaction, TestSAMPLE6, 2, SAMPLE6);


THE_BENCHMARK(MaxDiffBetweenTwoElementsNoSort_SubarraySum, SAMPLE2);

SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort_SubarraySum, TestSAMPLE2, 5, SAMPLE2);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort_SubarraySum, TestSAMPLE3, -1, SAMPLE3);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort_SubarraySum, TestSAMPLE4, 4, SAMPLE4);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort_SubarraySum, TestSAMPLE5, 8, SAMPLE5);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort_SubarraySum, TestSAMPLE6, 2, SAMPLE6);


THE_BENCHMARK(StockBuyAndSell_Unlimited_Greedy, SAMPLE2);

SIMPLE_TEST(StockBuyAndSell_Unlimited_Greedy, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(StockBuyAndSell_Unlimited_Greedy, TestSAMPLE2, 7, SAMPLE2);
SIMPLE_TEST(StockBuyAndSell_Unlimited_Greedy, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(StockBuyAndSell_Unlimited_Greedy, TestSAMPLE4, 4, SAMPLE4);


const ArrayType SAMPLE7 = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
const ArrayType SAMPLE8 = {3, 3, 5, 0, 0, 3, 1, 4};
const ArrayType SAMPLE9 = {10, 22, 5, 75, 65, 80};
const ArrayType SAMPLE10 = {2, 30, 15, 10, 8, 25, 80};
const ArrayType SAMPLE11 = {100, 30, 15, 10, 8, 25, 80};


THE_BENCHMARK(StockBuyAndSell_2Transactions, SAMPLE7);

SIMPLE_TEST(StockBuyAndSell_2Transactions, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(StockBuyAndSell_2Transactions, TestSAMPLE4, 4, SAMPLE4);
SIMPLE_TEST(StockBuyAndSell_2Transactions, TestSAMPLE7, 13, SAMPLE7);
SIMPLE_TEST(StockBuyAndSell_2Transactions, TestSAMPLE8, 6, SAMPLE8);
SIMPLE_TEST(StockBuyAndSell_2Transactions, TestSAMPLE9, 87, SAMPLE9);
SIMPLE_TEST(StockBuyAndSell_2Transactions, TestSAMPLE10, 100, SAMPLE10);
SIMPLE_TEST(StockBuyAndSell_2Transactions, TestSAMPLE11, 72, SAMPLE11);


THE_BENCHMARK(StockBuyAndSell_2Transactions_1Array, SAMPLE7);

SIMPLE_TEST(StockBuyAndSell_2Transactions_1Array, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(StockBuyAndSell_2Transactions_1Array, TestSAMPLE4, 4, SAMPLE4);
SIMPLE_TEST(StockBuyAndSell_2Transactions_1Array, TestSAMPLE7, 13, SAMPLE7);
SIMPLE_TEST(StockBuyAndSell_2Transactions_1Array, TestSAMPLE8, 6, SAMPLE8);
SIMPLE_TEST(StockBuyAndSell_2Transactions_1Array, TestSAMPLE9, 87, SAMPLE9);
SIMPLE_TEST(StockBuyAndSell_2Transactions_1Array, TestSAMPLE10, 100, SAMPLE10);
SIMPLE_TEST(StockBuyAndSell_2Transactions_1Array, TestSAMPLE11, 72, SAMPLE11);


THE_BENCHMARK(StockBuyAndSell_2Transactions_O1, SAMPLE7);

SIMPLE_TEST(StockBuyAndSell_2Transactions_O1, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(StockBuyAndSell_2Transactions_O1, TestSAMPLE4, 4, SAMPLE4);
SIMPLE_TEST(StockBuyAndSell_2Transactions_O1, TestSAMPLE7, 13, SAMPLE7);
SIMPLE_TEST(StockBuyAndSell_2Transactions_O1, TestSAMPLE8, 6, SAMPLE8);
SIMPLE_TEST(StockBuyAndSell_2Transactions_O1, TestSAMPLE9, 87, SAMPLE9);
SIMPLE_TEST(StockBuyAndSell_2Transactions_O1, TestSAMPLE10, 100, SAMPLE10);
SIMPLE_TEST(StockBuyAndSell_2Transactions_O1, TestSAMPLE11, 72, SAMPLE11);


const ArrayType SAMPLE12 = {12, 14, 17, 10, 14, 13, 12, 15};


THE_BENCHMARK(StockBuyAndSell_K_Transactions_DP, SAMPLE12, 3);

SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE1, 0, SAMPLE1, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE2, 5, SAMPLE2, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE3, 0, SAMPLE3, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE4, 4, SAMPLE4, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE5, 8, SAMPLE5, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE6, 2, SAMPLE6, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE7, 0, SAMPLE1, SAMPLE1.size());
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE8, 7, SAMPLE2, SAMPLE2.size());
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE9, 0, SAMPLE3, SAMPLE3.size());
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE10, 4,
            SAMPLE4, SAMPLE4.size());
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE11, 0, SAMPLE3, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE12, 4, SAMPLE4, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE13, 13, SAMPLE7, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE14, 6, SAMPLE8, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE15, 87, SAMPLE9, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE16, 100, SAMPLE10, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE17, 72, SAMPLE11, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE18, 12, SAMPLE12, 3);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP, TestSAMPLE19, 72, SAMPLE11, 3);


THE_BENCHMARK(StockBuyAndSell_K_Transactions_DP_Optimized, SAMPLE12, 3);

SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE1, 0, SAMPLE1, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE2, 5, SAMPLE2, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE3, 0, SAMPLE3, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE4, 4, SAMPLE4, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE5, 8, SAMPLE5, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE6, 2, SAMPLE6, 1);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE7, 0,
            SAMPLE1, SAMPLE1.size());
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE8, 7,
            SAMPLE2, SAMPLE2.size());
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE9, 0,
            SAMPLE3, SAMPLE3.size());
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE10, 4,
            SAMPLE4, SAMPLE4.size());
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE11, 0, SAMPLE3, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE12, 4, SAMPLE4, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE13, 13, SAMPLE7, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE14, 6, SAMPLE8, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE15, 87, SAMPLE9, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE16, 100,
            SAMPLE10, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE17, 72, SAMPLE11, 2);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE18, 12, SAMPLE12, 3);
SIMPLE_TEST(StockBuyAndSell_K_Transactions_DP_Optimized, TestSAMPLE19, 72, SAMPLE11, 3);
