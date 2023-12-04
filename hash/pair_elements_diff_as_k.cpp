#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Count Number of Pairs With Absolute Difference K
 *
 * @reference   https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/
 *
 * Given an integer array nums and an integer k, return the number of pairs (i, j) where i < j such that
 * |nums[i] - nums[j]| == k.
 * The value of |x| is defined as:
 *  x if x >= 0.
 *  -x if x < 0.
 * 1 <= nums[i] <= 100
 * 1 <= k <= 99
 */
auto CountPairsDiffAsK(const ArrayType &nums, const int k) {
    const int N = 101;
    int counts[N] = {};
    for (const auto n : nums) {
        ++counts[n];
    }

    int result = 0;
    for (int i = k + 1; i < N; ++i) {
        result += counts[i] * counts[i - k];
    }

    return result;
}


/**
 * @reference   Count Nice Pairs in an Array
 *              https://leetcode.com/problems/count-nice-pairs-in-an-array/
 *
 * You are given an array nums that consists of non-negative integers. Let us define rev(x) as the
 * reverse of the non-negative integer x. For example, rev(123) = 321, and rev(120) = 21. A pair of
 * indices (i, j) is nice if it satisfies all of the following conditions:
 *  0 <= i < j < nums.length
 *  nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
 * Return the number of nice pairs of indices. Since that number can be too large, return it modulo
 * 10^9 + 7.
 */


/**
 * @reference   K-diff Pairs in an Array
 *              https://leetcode.com/problems/k-diff-pairs-in-an-array/
 *
 * Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the
 * array.
 * A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
 *  0 <= i < j < nums.length
 *  |nums[i] - nums[j]| == k
 * Notice that |val| denotes the absolute value of val.
 */
auto KDiffUniquePairs(const ArrayType &nums, const int k) {
    std::unordered_map<int, int> counts;
    for (const auto n : nums) {
        ++counts[n];
    }

    int result = 0;
    for (const auto [n, c] : counts) {
        if (k == 0) {
            if (c > 1) {
                ++result;
            }
        } else {
            if (counts.find(n + k) != counts.cend()) {
                ++result;
            }
        }
    }

    return result;
}


auto KDiffUniquePairs_TwoPointers(ArrayType nums, const int k) {
    if (nums.size() < 2) {
        return 0;
    }

    std::sort(nums.begin(), nums.end());

    int result = 0;
    for (std::size_t i = 0, j = 1; j < nums.size(); ++j) {
        while (i < j and nums[j] - nums[i] > k) {
            ++i;
        }

        if (i < j and nums[j] - nums[i] == k) {
            ++result;
            while (i + 1 < nums.size() and nums[i + 1] == nums[i]) {
                ++i;
            }
            ++i;
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 2, 1};
const ArrayType SAMPLE2 = {1, 3};
const ArrayType SAMPLE3 = {3, 2, 1, 5, 4};


THE_BENCHMARK(CountPairsDiffAsK, SAMPLE1, 1);

SIMPLE_TEST(CountPairsDiffAsK, TestSAMPLE1, 4, SAMPLE1, 1);
SIMPLE_TEST(CountPairsDiffAsK, TestSAMPLE2, 0, SAMPLE2, 3);
SIMPLE_TEST(CountPairsDiffAsK, TestSAMPLE3, 3, SAMPLE3, 2);


const ArrayType SAMPLE1U = {3, 1, 4, 1, 5};
const ArrayType SAMPLE2U = {1, 2, 3, 4, 5};
const ArrayType SAMPLE3U = {1, 3, 1, 5, 4};


THE_BENCHMARK(KDiffUniquePairs, SAMPLE1U, 1);

SIMPLE_TEST(KDiffUniquePairs, TestSAMPLE1, 2, SAMPLE1U, 2);
SIMPLE_TEST(KDiffUniquePairs, TestSAMPLE2, 4, SAMPLE2U, 1);
SIMPLE_TEST(KDiffUniquePairs, TestSAMPLE3, 1, SAMPLE3U, 0);


THE_BENCHMARK(KDiffUniquePairs_TwoPointers, SAMPLE1U, 1);

SIMPLE_TEST(KDiffUniquePairs_TwoPointers, TestSAMPLE1, 2, SAMPLE1U, 2);
SIMPLE_TEST(KDiffUniquePairs_TwoPointers, TestSAMPLE2, 4, SAMPLE2U, 1);
SIMPLE_TEST(KDiffUniquePairs_TwoPointers, TestSAMPLE3, 1, SAMPLE3U, 0);
