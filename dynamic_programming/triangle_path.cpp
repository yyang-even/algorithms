#include "common_header.h"


namespace {

using TriangleType = std::vector<std::vector<int>>;

/**
 * @reference   Triangle
 *              https://leetcode.com/problems/triangle/
 *
 * Given a triangle array, return the minimum path sum from top to bottom.
 * For each step, you may move to an adjacent number of the row below.  More formally, if you are on
 * index i on the current row, you may move to either index i or index i + 1 on the next row.
 * Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the
 * triangle?
 *
 * @tags    #DP
 */
auto TrianglePath(const TriangleType &triangle) {
    const int N = triangle.size();
    auto dp = triangle.back();
    for (int layer = N - 2; layer >= 0; --layer) {
        for (int i = 0; i <= layer; ++i) {
            dp[i] = std::min(dp[i], dp[i + 1]) + triangle[layer][i];
        }
    }

    return dp[0];
}

} //namespace


// clang-format off
const TriangleType SAMPLE1 = {
    {2},
    {3, 4},
    {6, 5, 7},
    {4, 1, 8, 3}
};

const TriangleType SAMPLE2 = {{-10}};
// clang-format on


THE_BENCHMARK(TrianglePath, SAMPLE1);

SIMPLE_TEST(TrianglePath, TestSAMPLE1, 11, SAMPLE1);
SIMPLE_TEST(TrianglePath, TestSAMPLE2, -10, SAMPLE2);
