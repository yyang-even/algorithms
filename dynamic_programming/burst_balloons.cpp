#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using MemoType = std::vector<ArrayType>;

/** Burst Balloons
 *
 * @reference   https://leetcode.com/problems/burst-balloons/
 *
 * You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a
 * number on it represented by an array nums. You are asked to burst all the balloons.
 * If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins.
 * If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a
 * balloon with a 1 painted on it. Return the maximum coins you can collect by bursting
 * the balloons wisely.
 */
auto patch(const ArrayType &balloons) {
    ArrayType result = {1};
    for (const auto n : balloons) {
        if (n) {
            result.push_back(n);
        }
    }
    result.push_back(1);

    return result;
}

auto BurstBalloons_Memo(const ArrayType &balloons, const int left, const int right,
                        MemoType &memo) {
    if (left + 1 == right) {
        return 0;
    }

    if (memo[left][right] > 0) {
        return memo[left][right];
    }

    int result = 0;
    for (auto i = left + 1; i < right; ++i)
        result = std::max(result, balloons[left] * balloons[i] * balloons[right] +
                          BurstBalloons_Memo(balloons, left, i, memo) +
                          BurstBalloons_Memo(balloons, i, right, memo));
    memo[left][right] = result;

    return result;
}

auto BurstBalloons_Memo(const ArrayType &balloons) {
    const auto patched_balloons = patch(balloons);

    std::vector memo(patched_balloons.size(), std::vector(patched_balloons.size(), 0));
    return BurstBalloons_Memo(patched_balloons, 0, patched_balloons.size() - 1, memo);
}


auto BurstBalloons_DP(const ArrayType &balloons) {
    const auto nums = patch(balloons);

    const int N = nums.size();
    int dp[N][N] = {};
    for (int k = 2; k < N; ++k) {
        for (int left = 0; left < N - k; ++left) {
            const auto right = left + k;
            for (auto i = left + 1; i < right; ++i)
                dp[left][right] = std::max(dp[left][right],
                                           nums[left] * nums[i] * nums[right] + dp[left][i] + dp[i][right]);
        }
    }

    return dp[0][N - 1];
}

}//namespace


const ArrayType SAMPLE1 = {3, 1, 5, 8};
const ArrayType SAMPLE2 = {1, 5};


THE_BENCHMARK(BurstBalloons_Memo, SAMPLE1);

SIMPLE_TEST(BurstBalloons_Memo, TestSAMPLE1, 167, SAMPLE1);
SIMPLE_TEST(BurstBalloons_Memo, TestSAMPLE2, 10, SAMPLE2);


THE_BENCHMARK(BurstBalloons_DP, SAMPLE1);

SIMPLE_TEST(BurstBalloons_DP, TestSAMPLE1, 167, SAMPLE1);
SIMPLE_TEST(BurstBalloons_DP, TestSAMPLE2, 10, SAMPLE2);
