#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Arithmetic Slices
 *
 * @reference   https://leetcode.com/problems/arithmetic-slices/
 *
 * An integer array is called arithmetic if it consists of at least three elements and
 * if the difference between any two consecutive elements is the same.
 *  For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.
 * Given an integer array nums, return the number of arithmetic subarrays of nums. A
 * subarray is a contiguous subsequence of the array.
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
 * Given an integer array nums, return the number of all the arithmetic subsequences of
 * nums. A sequence of numbers is called arithmetic if it consists of at least three
 * elements and if the difference between any two consecutive elements is the same.
 *  For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic
 *      sequences.
 *  For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
 * A subsequence of an array is a sequence that can be formed by removing some elements
 * (possibly none) of the array.
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

}//namespace


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
