#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Arithmetic Slices
 *
 * @reference   https://leetcode.com/problems/arithmetic-slices/
 *
 * An integer array is called arithmetic if it consists of at least three elements and if the difference
 * between any two consecutive elements is the same.
 *  For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.
 * Given an integer array nums, return the number of arithmetic subarrays of nums.
 * A subarray is a contiguous subsequence of the array.
 */
auto ArithmeticSlices(const ArrayType &nums) {
    int result = 0, length = 2;
    for (std::size_t i = 2; i < nums.size(); ++i) {
        if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
            ++length;
        } else {
            if (length > 2) {
                result += (length - 1) * (length - 2) / 2;
            }
            length = 2;
        }
    }
    if (length > 2) {
        result += (length - 1) * (length - 2) / 2;
    }

    return result;
}


auto ArithmeticSlices_DP(const ArrayType &nums) {
    int result = 0, dp = 0;
    for (std::size_t i = 2; i < nums.size(); ++i) {
        if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
            dp += 1;
            result += dp;
        } else {
            dp = 0;
        }
    }

    return result;
}


/**
 * @reference   Arithmetic Slices II - Subsequence
 *              https://leetcode.com/problems/arithmetic-slices-ii-subsequence/
 *
 * Given an integer array nums, return the number of all the arithmetic subsequences of nums.
 * A sequence of numbers is called arithmetic if it consists of at least three elements and if the
 * difference between any two consecutive elements is the same.
 *  For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
 *  For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
 * A subsequence of an array is a sequence that can be formed by removing some elements (possibly none)
 * of the array.
 *  For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
 * The test cases are generated so that the answer fits in 32-bit integer.
 */
auto ArithmeticSlicesSubsequence(const ArrayType &nums) {
    int result = 0;
    std::unordered_map<int, int> dp[nums.size()];
    for (std::size_t i = 0; i < nums.size(); ++i) {
        for (std::size_t j = 0; j < i; j++) {
            const auto diff = static_cast<long>(nums[i]) - nums[j];
            if (diff < INT_MIN or diff > INT_MAX) {
                continue;
            }
            dp[i][diff] += dp[j][diff] + 1;
            result += dp[j][diff];
        }
    }

    return result;
}


/**
 * @reference   Longest Arithmetic Subsequence
 *              https://leetcode.com/problems/longest-arithmetic-subsequence/
 *
 * Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.
 * Note that:
 *  A subsequence is an array that can be derived from another array by deleting some or no elements
 *  without changing the order of the remaining elements.
 *  A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value (for 0 <= i < seq.length
 *  - 1).
 */
auto LongestArithmeticSubsequence(const ArrayType &nums) {
    std::vector<std::unordered_map<int, int>> dp(nums.size());

    int result = 1;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            const auto diff = nums[i] - nums[j];
            const auto length = dp[j].emplace(diff, 1).first->second + 1;
            if (const auto [iter, inserted] = dp[i].emplace(diff, length); not inserted) {
                iter->second = std::max(iter->second, length);
            }
            result = std::max(result, length);
        }
    }

    return result;
}


/**
 * @reference   Longest Arithmetic Subsequence of Given Difference
 *              https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/
 *
 * Given an integer array arr and an integer difference, return the length of the longest subsequence in
 * arr which is an arithmetic sequence such that the difference between adjacent elements in the
 * subsequence equals difference.
 * A subsequence is a sequence that can be derived from arr by deleting some or no elements without
 * changing the order of the remaining elements.
 */
auto LongestSubsequenceWithDiff(const ArrayType &arr, const int difference) {
    std::unordered_map<int, int> dp;
    int result = 1;

    for (const auto n : arr) {
        const auto target = n - difference;
        const auto iter = dp.find(target);
        const auto length = ((iter == dp.cend()) ? 0 : iter->second) + 1;
        dp[n] = length;
        result = std::max(result, length);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {2, 3, 4};
const ArrayType SAMPLE2 = {1, 2, 3, 4};
const ArrayType SAMPLE3 = {1, 2, 3, 4, 5};
const ArrayType SAMPLE4 = {1};


THE_BENCHMARK(ArithmeticSlices, SAMPLE1);

SIMPLE_TEST(ArithmeticSlices, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(ArithmeticSlices, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(ArithmeticSlices, TestSAMPLE3, 6, SAMPLE3);
SIMPLE_TEST(ArithmeticSlices, TestSAMPLE4, 0, SAMPLE4);


THE_BENCHMARK(ArithmeticSlices_DP, SAMPLE1);

SIMPLE_TEST(ArithmeticSlices_DP, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(ArithmeticSlices_DP, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(ArithmeticSlices_DP, TestSAMPLE3, 6, SAMPLE3);
SIMPLE_TEST(ArithmeticSlices_DP, TestSAMPLE4, 0, SAMPLE4);


const ArrayType SAMPLE5 = {2, 4, 6, 8, 10};
const ArrayType SAMPLE6 = {7, 7, 7, 7, 7};


THE_BENCHMARK(ArithmeticSlicesSubsequence, SAMPLE5);

SIMPLE_TEST(ArithmeticSlicesSubsequence, TestSAMPLE5, 7, SAMPLE5);
SIMPLE_TEST(ArithmeticSlicesSubsequence, TestSAMPLE6, 16, SAMPLE6);


const ArrayType SAMPLE1L = {3, 6, 9, 12};
const ArrayType SAMPLE2L = {9, 4, 7, 2, 10};
const ArrayType SAMPLE3L = {20, 1, 15, 3, 10, 5, 8};


THE_BENCHMARK(LongestArithmeticSubsequence, SAMPLE1L);

SIMPLE_TEST(LongestArithmeticSubsequence, TestSAMPLE1, 4, SAMPLE1L);
SIMPLE_TEST(LongestArithmeticSubsequence, TestSAMPLE2, 3, SAMPLE2L);
SIMPLE_TEST(LongestArithmeticSubsequence, TestSAMPLE3, 4, SAMPLE3L);


const ArrayType SAMPLE2D = {1, 3, 5, 7};
const ArrayType SAMPLE3D = {1, 5, 7, 8, 5, 3, 4, 2, 1};


THE_BENCHMARK(LongestSubsequenceWithDiff, SAMPLE3D, -2);

SIMPLE_TEST(LongestSubsequenceWithDiff, TestSAMPLE1, 4, SAMPLE2, 1);
SIMPLE_TEST(LongestSubsequenceWithDiff, TestSAMPLE2, 1, SAMPLE2D, 1);
SIMPLE_TEST(LongestSubsequenceWithDiff, TestSAMPLE3, 4, SAMPLE3D, -2);
