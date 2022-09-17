#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using MemoType = std::vector<ArrayType>;

/** Maximum Score from Performing Multiplication Operations
 *
 * @reference   https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/
 *
 * You are given two integer arrays nums and multipliers of size n and m respectively, where n >= m. The
 * arrays are 1-indexed.
 * You begin with a score of 0. You want to perform exactly m operations. On the ith operation
 * (1-indexed), you will:
 *  Choose one integer x from either the start or the end of the array nums.
 *  Add multipliers[i] * x to your score.
 *  Remove x from the array nums.
 * Return the maximum score after performing m operations.
 */
auto MaxScorePerformingMultiplication_Memo(const ArrayType &nums,
                                           const std::size_t left,
                                           const ArrayType &multipliers,
                                           const std::size_t i,
                                           MemoType &memo) {
    if (i == multipliers.size()) {
        return 0;
    }

    if (memo[i][left] != -1) {
        return memo[i][left];
    }

    const int left_result =
        nums[left] * multipliers[i] +
        MaxScorePerformingMultiplication_Memo(nums, left + 1, multipliers, i + 1, memo);
    const int right_result =
        nums[(nums.size() - 1) - (i - left)] * multipliers[i] +
        MaxScorePerformingMultiplication_Memo(nums, left, multipliers, i + 1, memo);

    return memo[i][left] = std::max(left_result, right_result);
}

inline auto MaxScorePerformingMultiplication_Memo(const ArrayType &nums,
                                                  const ArrayType &multipliers) {
    MemoType memo(multipliers.size(), std::vector(multipliers.size(), -1));
    return MaxScorePerformingMultiplication_Memo(nums, 0, multipliers, 0, memo);
}


auto MaxScorePerformingMultiplication_DP(const ArrayType &nums, const ArrayType &multipliers) {
    ArrayType dp(multipliers.size() + 1, 0);

    for (int i = multipliers.size() - 1; i >= 0; --i) {
        auto next_row = dp;
        for (auto left = i; left >= 0; --left) {
            dp[left] =
                std::max(multipliers[i] * nums[left] + next_row[left + 1],
                         multipliers[i] * nums[nums.size() - 1 - (i - left)] + next_row[left]);
        }
    }

    return dp[0];
}

} //namespace


const ArrayType SAMPLE1N = {1, 2, 3};
const ArrayType SAMPLE1M = {3, 2, 1};

const ArrayType SAMPLE2N = {-5, -3, -3, -2, 7, 1};
const ArrayType SAMPLE2M = {-10, -5, 3, 4, 6};


THE_BENCHMARK(MaxScorePerformingMultiplication_Memo, SAMPLE1N, SAMPLE1M);

SIMPLE_TEST(MaxScorePerformingMultiplication_Memo, TestSAMPLE1, 14, SAMPLE1N, SAMPLE1M);
SIMPLE_TEST(MaxScorePerformingMultiplication_Memo, TestSAMPLE2, 102, SAMPLE2N, SAMPLE2M);


THE_BENCHMARK(MaxScorePerformingMultiplication_DP, SAMPLE1N, SAMPLE1M);

SIMPLE_TEST(MaxScorePerformingMultiplication_DP, TestSAMPLE1, 14, SAMPLE1N, SAMPLE1M);
SIMPLE_TEST(MaxScorePerformingMultiplication_DP, TestSAMPLE2, 102, SAMPLE2N, SAMPLE2M);
