#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Eat Pizzas!
 *              https://leetcode.com/problems/eat-pizzas/
 *
 * You are given an integer array pizzas of size n, where pizzas[i] represents the weight of the ith
 * pizza. Every day, you eat exactly 4 pizzas. Due to your incredible metabolism, when you eat pizzas of
 * weights W, X, Y, and Z, where W <= X <= Y <= Z, you gain the weight of only 1 pizza!
 *  On odd-numbered days (1-indexed), you gain a weight of Z.
 *  On even-numbered days, you gain a weight of Y.
 * Find the maximum total weight you can gain by eating all pizzas optimally.
 * Note: It is guaranteed that n is a multiple of 4, and each pizza can be eaten only once.
 *
 * @tags    #greedy #sorting #accumulate
 */
auto MaxWeightGain(ArrayType pizzas) {
    const int total_days = pizzas.size() / 4;
    const int odd_days = (total_days + 1) / 2;
    const auto even_days = total_days - odd_days;
    const auto total_elements = odd_days + even_days * 2;

    const auto nth = pizzas.begin() + total_elements;
    std::nth_element(pizzas.begin(), nth, pizzas.end(), std::greater<int> {});
    std::sort(pizzas.begin(), nth, std::greater<int> {});

    auto result = std::accumulate(pizzas.cbegin(), pizzas.cbegin() + odd_days, 0ll);
    for (int j = 0; j < even_days; ++j) {
        const auto i = odd_days + 1 + j * 2;
        result += pizzas[i];
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5, 6, 7, 8};
const ArrayType SAMPLE2 = {2, 1, 1, 1, 1, 1, 1, 1};
const ArrayType SAMPLE3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};


THE_BENCHMARK(MaxWeightGain, SAMPLE1);

SIMPLE_TEST(MaxWeightGain, TestSAMPLE1, 14, SAMPLE1);
SIMPLE_TEST(MaxWeightGain, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(MaxWeightGain, TestSAMPLE3, 32, SAMPLE3);
