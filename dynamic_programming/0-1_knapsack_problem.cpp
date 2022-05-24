#include "common_header.h"

#include "mathematics/arithmetics/sum/prefix_sum_array.h"


namespace {

using ArrayType = std::vector<int>;
using PairArrayType = std::vector<std::pair<int, int>>;
using StrArray = std::vector<std::string_view>;

/** 0-1 Knapsack Problem
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 16.2. Exercises 16.2-2.
 * @reference   0-1 Knapsack Problem | DP-10
 *              https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
 *
 * Given weights and values of n items, put these items in a knapsack of capacity W to get the
 * maximum total value in the knapsack. In other words, given two integer arrays val[0..n-1] and
 * wt[0..n-1] which represent values and weights associated with n items respectively. Also given
 * an integer W which represents knapsack capacity, find out the maximum value subset of val[]
 * such that sum of the weights of this subset is smaller than or equal to W. You cannot break an
 * item, either pick the complete item, or don't pick it (0-1 property).
 */
auto Knapsack01(const ArrayType &weights,
                const ArrayType &values,
                const ArrayType::value_type W,
                ArrayType *const selected_items = nullptr) {
    assert(weights.size() == values.size());

    ArrayType::value_type max_values[weights.size() + 1][W + 1] = {};
    for (ArrayType::size_type i = 1; i <= weights.size(); ++i) {
        for (ArrayType::value_type capacity = 1; capacity <= W; ++capacity) {
            if (weights[i - 1] <= capacity)
                max_values[i][capacity] =
                    std::max(values[i - 1] + max_values[i - 1][capacity - weights[i - 1]],
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
auto Knapsack01_SpaceOptimized(const ArrayType &weights,
                               const ArrayType &values,
                               const ArrayType::value_type W) {
    assert(weights.size() == values.size());

    auto row_size = 2; //work around a GCC bug.
    ArrayType::value_type max_values[row_size][W + 1] = {};
    for (ArrayType::size_type i = 1; i <= weights.size(); ++i) {
        const auto current_row = i % 2;
        for (ArrayType::value_type capacity = 1; capacity <= W; ++capacity) {
            if (weights[i - 1] <= capacity)
                max_values[current_row][capacity] = std::max(
                    values[i - 1] + max_values[1 - current_row][capacity - weights[i - 1]],
                    max_values[1 - current_row][capacity]);
            else {
                max_values[current_row][capacity] = max_values[1 - current_row][capacity];
            }
        }
    }

    return max_values[weights.size() % 2][W];
}


auto Knapsack01_OneDimension(const ArrayType &weights,
                             const ArrayType &values,
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
inline auto Knapsack01ItemIndices(const ArrayType &weights,
                                  const ArrayType &values,
                                  const ArrayType::value_type W) {
    ArrayType selected_items;
    Knapsack01(weights, values, W, &selected_items);
    return selected_items;
}


/**
 * @reference   0-1 knapsack queries
 *              https://www.geeksforgeeks.org/0-1-knapsack-queries/
 *
 * Given an integer array W[] consisting of weights of the items and some queries consisting of
 * capacity C of knapsack, for each query find maximum weight we can put in the knapsack. Value
 * of C does’t exceed a certain integer C_MAX.
 */


/**
 * @reference   Ones and Zeroes
 *              https://leetcode.com/problems/ones-and-zeroes/
 *
 * You are given an array of binary strings strs and two integers m and n.
 * Return the size of the largest subset of strs such that there are at most m 0's and n 1's in
 * the subset.
 * A set x is a subset of a set y if all elements of x are also elements of y.
 */
auto OnesAndZeros(const StrArray &strs, const int m, const int n) {
    std::vector dp(m + 1, std::vector<int>(n + 1));

    for (const auto s : strs) {
        const int zeros = std::count(s.cbegin(), s.cend(), '0');
        const int ones = s.size() - zeros;

        for (int i = m; i >= zeros; --i) {
            for (int j = n; j >= ones; --j) {
                dp[i][j] = std::max(dp[i][j], dp[i - zeros][j - ones] + 1);
            }
        }
    }

    return dp[m][n];
}


int OnesAndZeros_Recursive(const StrArray &strs,
                           const int m,
                           const int n,
                           const std::size_t i,
                           std::vector<std::vector<std::vector<int>>> &dp) {
    if (i == size(strs)) {
        return 0;
    }

    if (dp[i][m][n]) {
        return dp[i][m][n];
    }

    const auto s = strs[i];
    const int zeros = std::count(s.cbegin(), s.cend(), '0');
    const int ones = s.size() - zeros;

    dp[i][m][n] = OnesAndZeros_Recursive(strs, m, n, i + 1, dp);
    if (m - zeros >= 0 and n - ones >= 0) {
        dp[i][m][n] = std::max(dp[i][m][n],
                               1 + OnesAndZeros_Recursive(strs, m - zeros, n - ones, i + 1, dp));
    }

    return dp[i][m][n];
}

inline auto OnesAndZeros_Recursive(const StrArray &strs, const int m, const int n) {
    std::vector dp(strs.size(), std::vector(m + 1, std::vector<int>(n + 1)));
    return OnesAndZeros_Recursive(strs, m, n, 0, dp);
}


/** Fractional Knapsack Problem
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 16.2.
 * @reference   Fractional Knapsack Problem
 *              https://www.geeksforgeeks.org/fractional-knapsack-problem/
 *
 * Given weights and values of n items, we need to put these items in a knapsack of capacity W to
 * get the maximum total value in the knapsack.
 * In the 0-1 Knapsack problem, we are not allowed to break items. We either take the whole item
 * or don’t take it.
 * In Fractional Knapsack, we can break items for maximizing the total value of knapsack.
 * This problem in which we can break an item is also called the fractional knapsack problem.
 */
auto FractionalKnapsack01(const ArrayType &weights,
                          const ArrayType &values,
                          ArrayType::value_type W) {
    assert(weights.size() == values.size());

    using RatioIndexPair = std::pair<double, ArrayType::size_type>;
    std::vector<RatioIndexPair> ratios;
    for (ArrayType::size_type i = 0; i < weights.size(); ++i) {
        ratios.emplace_back(values[i] / weights[i], i);
    }

    std::sort(ratios.begin(), ratios.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.first > rhs.first;
    });

    auto final_value = 0.0;
    for (const auto [ration, index] : ratios) {
        if (weights[index] <= W) {
            W -= weights[index];
            final_value += values[index];
        } else {
            final_value += ration * W;
            break;
        }
    }

    return final_value;
}


/**
 * @reference   Fractional Knapsack Queries
 *              https://www.geeksforgeeks.org/fractional-knapsack-queries/
 */
auto FractionalKnapsack01Queries(const ArrayType &weights,
                                 const ArrayType &values,
                                 const ArrayType &queries) {
    assert(weights.size() == values.size());

    using ValueWeightPair = std::pair<ArrayType::value_type, ArrayType::value_type>;
    std::vector<ValueWeightPair> items;

    for (ArrayType::size_type i = 0; i < weights.size(); ++i) {
        items.emplace_back(values[i], weights[i]);
    }

    std::sort(items.begin(), items.end(), [](const auto &lhs, const auto &rhs) {
        return (lhs.first / static_cast<double>(lhs.second)) >
               (rhs.first / static_cast<double>(rhs.second));
    });

    const auto prefix_sums =
        PrefixSumArray(std::move(items), [](const auto &lhs, const auto &rhs) {
            return std::pair(lhs.first + rhs.first, lhs.second + rhs.second);
        });

    std::vector<double> max_values;
    for (const auto W : queries) {
        if (prefix_sums.back().second <= W) {
            max_values.emplace_back(prefix_sums.back().first);
            continue;
        }

        const auto upper = std::upper_bound(
            prefix_sums.cbegin(), prefix_sums.cend(), W, [](const auto &w, const auto &one_item) {
                return w < one_item.second;
            });

        if (upper == prefix_sums.cbegin()) {
            max_values.emplace_back(static_cast<double>(W) * upper->first / upper->second);
        } else {
            const auto previous_item = std::prev(upper);
            max_values.emplace_back(previous_item->first +
                                    static_cast<double>(W - previous_item->second) *
                                        (upper->first - previous_item->first) /
                                        (upper->second - previous_item->second));
        }
    }

    return max_values;
}


/**
 * @reference   How Many Apples Can You Put into the Basket
 *              http://lixinchengdu.github.io/algorithmbook/leetcode/how-many-apples-can-you-put-into-the-basket.html
 *
 * You have some apples, where arr[i] is the weight of the i-th apple.  You also have a basket
 * that can carry up to 5000 units of weight.
 * Return the maximum number of apples you can put in the basket.
 */


/**
 * @reference   Maximum Units on a Truck
 *              https://leetcode.com/problems/maximum-units-on-a-truck/
 *
 * You are assigned to put some amount of boxes onto one truck. You are given a 2D array boxTypes,
 * where boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]:
 *  numberOfBoxesi is the number of boxes of type i.
 *  numberOfUnitsPerBoxi is the number of units in each box of the type i.
 * You are also given an integer truckSize, which is the maximum number of boxes that can be put
 * on the truck. You can choose any boxes to put on the truck as long as the number of boxes does
 * not exceed truckSize.
 * Return the maximum total number of units that can be put on the truck.
 * 1 <= numberOfBoxesi, numberOfUnitsPerBoxi <= 1000
 */
auto MaxUnits(const PairArrayType &boxTypes, int truckSize) {
    int counts[1001] = {};
    for (const auto [number, unit] : boxTypes) {
        counts[unit] += number;
    }

    int result = 0;
    for (int i = 1000; i >= 1; --i) {
        if (counts[i]) {
            if (counts[i] >= truckSize) {
                result += i * truckSize;
                break;
            } else {
                result += counts[i] * i;
                truckSize -= counts[i];
            }
        }
    }

    return result;
}

} //namespace


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


THE_BENCHMARK(Knapsack01, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);

SIMPLE_TEST(Knapsack01, TestSAMPLE1, 220, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);
SIMPLE_TEST(Knapsack01, TestSAMPLE2, 11, SAMPLE2_WEIGHT, SAMPLE2_VALUES, 10);
SIMPLE_TEST(Knapsack01, TestSAMPLE3, 200, SAMPLE3_WEIGHT, SAMPLE3_VALUES, 60);
SIMPLE_TEST(Knapsack01, TestSAMPLE4, 9, SAMPLE4_WEIGHT, SAMPLE4_VALUES, 7);


THE_BENCHMARK(Knapsack01_SpaceOptimized, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);

SIMPLE_TEST(Knapsack01_SpaceOptimized, TestSAMPLE1, 220, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);
SIMPLE_TEST(Knapsack01_SpaceOptimized, TestSAMPLE2, 11, SAMPLE2_WEIGHT, SAMPLE2_VALUES, 10);
SIMPLE_TEST(Knapsack01_SpaceOptimized, TestSAMPLE3, 200, SAMPLE3_WEIGHT, SAMPLE3_VALUES, 60);
SIMPLE_TEST(Knapsack01_SpaceOptimized, TestSAMPLE4, 9, SAMPLE4_WEIGHT, SAMPLE4_VALUES, 7);


THE_BENCHMARK(Knapsack01_OneDimension, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);

SIMPLE_TEST(Knapsack01_OneDimension, TestSAMPLE1, 220, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);
SIMPLE_TEST(Knapsack01_OneDimension, TestSAMPLE2, 11, SAMPLE2_WEIGHT, SAMPLE2_VALUES, 10);
SIMPLE_TEST(Knapsack01_OneDimension, TestSAMPLE3, 200, SAMPLE3_WEIGHT, SAMPLE3_VALUES, 60);
SIMPLE_TEST(Knapsack01_OneDimension, TestSAMPLE4, 9, SAMPLE4_WEIGHT, SAMPLE4_VALUES, 7);


THE_BENCHMARK(Knapsack01ItemIndices, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);

SIMPLE_TEST(Knapsack01ItemIndices, TestSAMPLE1, EXPECTED1, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);
SIMPLE_TEST(Knapsack01ItemIndices, TestSAMPLE2, EXPECTED2, SAMPLE2_WEIGHT, SAMPLE2_VALUES, 10);
SIMPLE_TEST(Knapsack01ItemIndices, TestSAMPLE3, EXPECTED3, SAMPLE3_WEIGHT, SAMPLE3_VALUES, 60);
SIMPLE_TEST(Knapsack01ItemIndices, TestSAMPLE4, EXPECTED4, SAMPLE4_WEIGHT, SAMPLE4_VALUES, 7);


THE_BENCHMARK(FractionalKnapsack01, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);

SIMPLE_DOUBLE_TEST(FractionalKnapsack01, TestSAMPLE1, 240, SAMPLE1_WEIGHT, SAMPLE1_VALUES, 50);


const ArrayType SAMPLE5_VALUES = {2, 8, 9};
const ArrayType SAMPLE5_WEIGHT = {1, 2, 3};
const ArrayType SAMPLE5_QUERY = {1, 2, 3, 4, 5, 6, 7};
const std::vector<double> EXPECTED5 = {4, 8, 11, 14, 17, 19, 19};


THE_BENCHMARK(FractionalKnapsack01Queries, SAMPLE5_WEIGHT, SAMPLE5_VALUES, SAMPLE5_QUERY);

SIMPLE_TEST(FractionalKnapsack01Queries,
            TestSAMPLE5,
            EXPECTED5,
            SAMPLE5_WEIGHT,
            SAMPLE5_VALUES,
            SAMPLE5_QUERY);


const PairArrayType SAMPLE1B = {{1, 3}, {2, 2}, {3, 1}};
const PairArrayType SAMPLE2B = {{5, 10}, {2, 5}, {4, 7}, {3, 9}};


THE_BENCHMARK(MaxUnits, SAMPLE1B, 4);

SIMPLE_TEST(MaxUnits, TestSAMPLE1, 8, SAMPLE1B, 4);
SIMPLE_TEST(MaxUnits, TestSAMPLE2, 91, SAMPLE2B, 10);


const StrArray SAMPLE1Z = {"10", "0001", "111001", "1", "0"};
const StrArray SAMPLE2Z = {"10", "0", "1"};


THE_BENCHMARK(OnesAndZeros, SAMPLE1Z, 5, 3);

SIMPLE_TEST(OnesAndZeros, TestSAMPLE1, 4, SAMPLE1Z, 5, 3);
SIMPLE_TEST(OnesAndZeros, TestSAMPLE2, 2, SAMPLE2Z, 1, 1);


THE_BENCHMARK(OnesAndZeros_Recursive, SAMPLE1Z, 5, 3);

SIMPLE_TEST(OnesAndZeros_Recursive, TestSAMPLE1, 4, SAMPLE1Z, 5, 3);
SIMPLE_TEST(OnesAndZeros_Recursive, TestSAMPLE2, 2, SAMPLE2Z, 1, 1);
