#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** 0-1 Knapsack Problem
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 16.2. Exercises 16.2-2.
 * @reference   0-1 Knapsack Problem | DP-10
 *              https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
 *
 * Given weights and values of n items, put these items in a knapsack of capacity W to get
 * the maximum total value in the knapsack. In other words, given two integer arrays
 * val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items
 * respectively. Also given an integer W which represents knapsack capacity, find out the
 * maximum value subset of val[] such that sum of the weights of this subset is smaller
 * than or equal to W. You cannot break an item, either pick the complete item, or don't
 * pick it (0-1 property).
 */
auto Knapsack01(const ArrayType &weights, const ArrayType &values,
                const ArrayType::value_type W, ArrayType *const selected_items = nullptr) {
    assert(weights.size() == values.size());

    ArrayType::value_type max_values[weights.size() + 1][W + 1] = {};
    for (ArrayType::size_type i = 1; i <= weights.size(); ++i) {
        for (ArrayType::value_type capacity = 1; capacity <= W; ++capacity) {
            if (weights[i - 1] <= capacity)
                max_values[i][capacity] = std::max(values[i - 1] + max_values[i - 1][capacity - weights[i - 1]],
                                                   max_values[i - 1][capacity]);
            else {
                max_values[i][capacity] = max_values[i - 1][capacity];
            }
        }
    }

    if (selected_items) {
        auto the_max_value = max_values[weights.size()][W];
        auto capacity = W;
        for (int i = weights.size() - 1; i >= 0; --i) {
            if (the_max_value != max_values[i][capacity]) {
                selected_items->push_back(i);
                the_max_value -= values[i];
                capacity -= weights[i];
            }
        }
    }

    return max_values[weights.size()][W];
}


/**
 * @reference   A Space Optimized DP solution for 0-1 Knapsack Problem
 *              https://www.geeksforgeeks.org/space-optimized-dp-solution-0-1-knapsack-problem/
 */
auto Knapsack01_SpaceOptimized(const ArrayType &weights, const ArrayType &values,
                               const ArrayType::value_type W) {
    assert(weights.size() == values.size());

    auto row_size = 2;  //work around a GCC bug.
    ArrayType::value_type max_values[row_size][W + 1] = {};
    for (ArrayType::size_type i = 1; i <= weights.size(); ++i) {
        const auto current_row = i % 2;
        for (ArrayType::value_type capacity = 1; capacity <= W; ++capacity) {
            if (weights[i - 1] <= capacity)
                max_values[current_row][capacity] =
                    std::max(values[i - 1] + max_values[1 - current_row][capacity - weights[i - 1]],
                             max_values[1 - current_row][capacity]);
            else {
                max_values[current_row][capacity] = max_values[1 - current_row][capacity];
            }
        }
    }

    return max_values[weights.size() % 2][W];
}


auto Knapsack01_OneDimension(const ArrayType &weights, const ArrayType &values,
                             const ArrayType::value_type W) {
    assert(weights.size() == values.size());

    ArrayType::value_type max_values[W + 1] = {};
    for (ArrayType::size_type i = 0; i < weights.size(); ++i) {
        for (auto j = W; j >= weights[i]; --j) {
            max_values[j] = std::max(max_values[j], values[i] + max_values[j - weights[i]]);
        }
    }

    return max_values[W];
}


/**
 * @reference   Printing Items in 0/1 Knapsack
 *              https://www.geeksforgeeks.org/printing-items-01-knapsack/
 */
auto Knapsack01ItemIndices(const ArrayType &weights, const ArrayType &values,
                           const ArrayType::value_type W) {
    ArrayType selected_items;
    Knapsack01(weights, values, W, &selected_items);
    return selected_items;
}


/**
 * @reference   0-1 knapsack queries
 *              https://www.geeksforgeeks.org/0-1-knapsack-queries/
 *
 * Given an integer array W[] consisting of weights of the items and some queries
 * consisting of capacity C of knapsack, for each query find maximum weight we can
 * put in the knapsack. Value of C does’t exceed a certain integer C_MAX.
 */

}//namespace


const ArrayType SAMPLE1_VALUES = {60, 100, 120};
const ArrayType SAMPLE1_WEIGHT = {10, 20, 30};
const ArrayType EXPECTED1 = {2, 1};

const ArrayType SAMPLE2_VALUES = {7, 8, 4};
const ArrayType SAMPLE2_WEIGHT = {3, 8, 6};
const ArrayType EXPECTED2 = {2, 0};

const ArrayType SAMPLE3_VALUES = {40, 100, 50, 60};
const ArrayType SAMPLE3_WEIGHT = {20, 10, 40, 30};
const ArrayType EXPECTED3 = {3, 1, 0};

const ArrayType SAMPLE4_VALUES = {1, 4, 5, 7};
const ArrayType SAMPLE4_WEIGHT = {1, 3, 4, 5};
const ArrayType EXPECTED4 = {2, 1};


SIMPLE_BENCHMARK(Knapsack01, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);

SIMPLE_TEST(Knapsack01, TestSAMPLE1, 220, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);
SIMPLE_TEST(Knapsack01, TestSAMPLE2, 11, SAMPLE2_WEIGHT, SAMPLE2_VALUES, 10);
SIMPLE_TEST(Knapsack01, TestSAMPLE3, 200, SAMPLE3_WEIGHT, SAMPLE3_VALUES, 60);
SIMPLE_TEST(Knapsack01, TestSAMPLE4, 9, SAMPLE4_WEIGHT, SAMPLE4_VALUES, 7);


SIMPLE_BENCHMARK(Knapsack01_SpaceOptimized, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);

SIMPLE_TEST(Knapsack01_SpaceOptimized, TestSAMPLE1, 220, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);
SIMPLE_TEST(Knapsack01_SpaceOptimized, TestSAMPLE2, 11, SAMPLE2_WEIGHT, SAMPLE2_VALUES, 10);
SIMPLE_TEST(Knapsack01_SpaceOptimized, TestSAMPLE3, 200, SAMPLE3_WEIGHT, SAMPLE3_VALUES, 60);
SIMPLE_TEST(Knapsack01_SpaceOptimized, TestSAMPLE4, 9, SAMPLE4_WEIGHT, SAMPLE4_VALUES, 7);


SIMPLE_BENCHMARK(Knapsack01_OneDimension, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);

SIMPLE_TEST(Knapsack01_OneDimension, TestSAMPLE1, 220, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);
SIMPLE_TEST(Knapsack01_OneDimension, TestSAMPLE2, 11, SAMPLE2_WEIGHT, SAMPLE2_VALUES, 10);
SIMPLE_TEST(Knapsack01_OneDimension, TestSAMPLE3, 200, SAMPLE3_WEIGHT, SAMPLE3_VALUES, 60);
SIMPLE_TEST(Knapsack01_OneDimension, TestSAMPLE4, 9, SAMPLE4_WEIGHT, SAMPLE4_VALUES, 7);


SIMPLE_BENCHMARK(Knapsack01ItemIndices, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);

SIMPLE_TEST(Knapsack01ItemIndices, TestSAMPLE1, EXPECTED1, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);
SIMPLE_TEST(Knapsack01ItemIndices, TestSAMPLE2, EXPECTED2, SAMPLE2_WEIGHT, SAMPLE2_VALUES, 10);
SIMPLE_TEST(Knapsack01ItemIndices, TestSAMPLE3, EXPECTED3, SAMPLE3_WEIGHT, SAMPLE3_VALUES, 60);
SIMPLE_TEST(Knapsack01ItemIndices, TestSAMPLE4, EXPECTED4, SAMPLE4_WEIGHT, SAMPLE4_VALUES, 7);
