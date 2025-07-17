#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the Maximum Length of Valid Subsequence I
 *
 * @reference   https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/
 *
 * You are given an integer array nums.
 * A subsequence sub of nums with length x is called valid if it satisfies:
 *  (sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
 * Return the length of the longest valid subsequence of nums.
 * A subsequence is an array that can be derived from another array by deleting some or no elements
 * without changing the order of the remaining elements.
 */
auto FindMaxValidEvenOddSubsequence(const ArrayType &nums) {
    if (nums.empty()) {
        return 0;
    }

    int odd_count = 0;
    int even_count = 0;
    int alter_count = 1;
    bool is_prev_even = (nums[0] % 2 == 0);
    for (const auto n : nums) {
        const auto is_even = (n % 2 == 0);
        if (is_even) {
            ++even_count;
        } else {
            ++odd_count;
        }

        if (is_prev_even != is_even) {
            ++alter_count;
            is_prev_even = is_even;
        }
    }

    return std::max({odd_count, even_count, alter_count});
}


/**
 * @reference   Find the Maximum Length of Valid Subsequence II
 *              https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/
 *
 * You are given an integer array nums and a positive integer k.
 * A subsequence sub of nums with length x is called valid if it satisfies:
 *  (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
 * Return the length of the longest valid subsequence of nums.
 */
auto FindMaxValidKSubsequence(const ArrayType &nums, const int k) {
    assert(k > 0);

    auto dp = std::vector(k, std::vector(k, 0));

    for (const auto n : nums) {
        const auto remain = n % k;

        for (int other = 0; other < k; ++other) {
            dp[remain][other] = dp[other][remain] + 1;
        }
    }

    int result = 2;
    for (const auto &counts : dp) {
        for (const auto c : counts) {
            result = std::max(result, c);
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5};
const ArrayType SAMPLE2 = {1, 2, 1, 1, 2, 1, 2};
const ArrayType SAMPLE3 = {1, 3};


THE_BENCHMARK(FindMaxValidEvenOddSubsequence, SAMPLE1);

SIMPLE_TEST(FindMaxValidEvenOddSubsequence, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(FindMaxValidEvenOddSubsequence, TestSAMPLE2, 6, SAMPLE2);
SIMPLE_TEST(FindMaxValidEvenOddSubsequence, TestSAMPLE3, 2, SAMPLE3);


const ArrayType SAMPLE2_MK = {1, 4, 2, 3, 1, 4};


THE_BENCHMARK(FindMaxValidKSubsequence, SAMPLE1, 2);

SIMPLE_TEST(FindMaxValidKSubsequence, TestSAMPLE1, 5, SAMPLE1, 2);
SIMPLE_TEST(FindMaxValidKSubsequence, TestSAMPLE2, 4, SAMPLE2_MK, 3);
