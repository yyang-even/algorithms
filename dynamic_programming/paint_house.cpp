#include "common_header.h"


namespace {

using ArrayType = std::vector<std::vector<int>>;

/** Paint House
 *
 * @reference   https://kennyzhuang.gitbooks.io/leetcode-lock/content/256_paint_house.html
 *
 * There are a row of n houses, each house can be painted with one of the three colors: red, blue
 * or green. The cost of painting each house with a certain color is different. You have to paint
 * all the houses such that no two adjacent houses have the same color.
 * The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For
 * example, costs[0][0] is the cost of painting house 0 with color red;costs[1][2] is the cost of
 * painting house 1 with color green, and so on... Find the minimum cost to paint all houses.
 * Note: All costs are positive integers.
 */
auto PaintHouse(const ArrayType &costs) {
    ArrayType dp;
    dp.push_back(costs.front());

    for (std::size_t i = 1; i < costs.size(); ++i) {
        dp.push_back({costs[i][0] + std::min(dp[i - 1][1], dp[i - 1][2]),
                      costs[i][1] + std::min(dp[i - 1][0], dp[i - 1][2]),
                      costs[i][2] + std::min(dp[i - 1][0], dp[i - 1][1])});
    }

    return *std::min_element(dp.back().cbegin(), dp.back().cend());
}


/** Paint House II
 *
 * @reference   https://kennyzhuang.gitbooks.io/leetcode-lock/content/265_paint_house_ii.html
 *
 * There are a row of n houses, each house can be painted with one of the k colors. The cost of
 * painting each house with a certain color is different. You have to paint all the houses such
 * that no two adjacent houses have the same color.
 * The cost of painting each house with a certain color is represented by a n x k cost matrix. For
 * example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of
 * painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.
 * Note: All costs are positive integers.
 * Follow up: Could you solve it in O(nk) runtime?
 */
auto Min2Indices(const std::vector<int> &nums) {
    std::size_t min_index = 0;
    std::size_t second_min_index = 1;
    if (nums[min_index] > nums[second_min_index]) {
        std::swap(min_index, second_min_index);
    }

    for (std::size_t i = 2; i < nums.size(); ++i) {
        if (nums[i] < nums[min_index]) {
            second_min_index = min_index;
            min_index = i;
        } else if (nums[i] < nums[second_min_index]) {
            second_min_index = i;
        }
    }

    return std::pair(min_index, second_min_index);
}

auto PaintHouseK(const ArrayType &costs) {
    const auto K = costs.front().size();

    ArrayType dp;
    dp.push_back(costs.front());

    for (std::size_t i = 1; i < costs.size(); ++i) {
        const auto [min_index, second_min_index] = Min2Indices(dp.back());

        dp.emplace_back();

        for (std::size_t j = 0; j < K; ++j) {
            if (j == min_index) {
                dp.back().push_back(costs[i][j] + dp[i - 1][second_min_index]);
            } else {
                dp.back().push_back(costs[i][j] + dp[i - 1][min_index]);
            }
        }
    }

    return *std::min_element(dp.back().cbegin(), dp.back().cend());
}

} //namespace


const ArrayType SAMPLE1 = {{17, 2, 17}, {16, 16, 5}, {14, 3, 19}};
const ArrayType SAMPLE2 = {{1, 5, 3}, {2, 9, 4}};


THE_BENCHMARK(PaintHouse, SAMPLE1);

SIMPLE_TEST(PaintHouse, TestSAMPLE1, 10, SAMPLE1);
SIMPLE_TEST(PaintHouse, TestSAMPLE2, 5, SAMPLE2);


THE_BENCHMARK(PaintHouseK, SAMPLE1);

SIMPLE_TEST(PaintHouseK, TestSAMPLE1, 10, SAMPLE1);
SIMPLE_TEST(PaintHouseK, TestSAMPLE2, 5, SAMPLE2);
