#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Partition Array for Maximum Sum
 *
 * @reference   https://leetcode.com/problems/partition-array-for-maximum-sum/
 *
 * Given an integer array arr, partition the array into (contiguous) subarrays of length at most k.
 * After partitioning, each subarray has their values changed to become the maximum value of that
 * subarray.
 * Return the largest sum of the given array after partitioning. Test cases are generated so that the
 * answer fits in a 32-bit integer.
 */
auto PartitionArrayForMaxSum(const ArrayType &nums, const int k) {
    const int size = nums.size();
    std::vector<int> dp(size + 1);

    for (int i = 1; i <= size; ++i) {
        int current_max = 0;
        int best = 0;

        for (int length = 1; length <= k and i - length >= 0; ++length) {
            current_max = std::max(current_max, nums[i - length]);
            best = std::max(best, dp[i - length] + current_max * length);
        }

        dp[i] = best;
    }

    return dp[size];
}

} //namespace


const ArrayType SAMPLE1 = {1, 15, 7, 9, 2, 5, 10};
const ArrayType SAMPLE2 = {1, 4, 1, 5, 7, 3, 6, 1, 9, 9, 3};
const ArrayType SAMPLE3 = {1};


THE_BENCHMARK(PartitionArrayForMaxSum, SAMPLE1, 3);

SIMPLE_TEST(PartitionArrayForMaxSum, TestSAMPLE1, 84, SAMPLE1, 3);
SIMPLE_TEST(PartitionArrayForMaxSum, TestSAMPLE2, 83, SAMPLE2, 4);
SIMPLE_TEST(PartitionArrayForMaxSum, TestSAMPLE3, 1, SAMPLE3, 1);
