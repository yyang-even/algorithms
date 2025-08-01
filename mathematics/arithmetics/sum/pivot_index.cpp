#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Find Pivot Index
 *              https://leetcode.com/problems/find-pivot-index/
 *
 * Given an array of integers nums, calculate the pivot index of this array.
 * The pivot index is the index where the sum of all the numbers strictly to the left of the index is
 * equal to the sum of all the numbers strictly to the index's right.
 * If the index is on the left edge of the array, then the left sum is 0 because there are no elements
 * to the left. This also applies to the right edge of the array.
 * Return the leftmost pivot index. If no such index exists, return -1.
 *
 * @reference   Find the Middle Index in Array
 *              https://leetcode.com/problems/find-the-middle-index-in-array/
 *
 * Given a 0-indexed integer array nums, find the leftmost middleIndex (i.e., the smallest amongst all
 * the possible ones).
 * A middleIndex is an index where nums[0] + nums[1] + ... + nums[middleIndex-1] == nums[middleIndex+1]
 * + nums[middleIndex+2] + ... + nums[nums.length-1].
 * If middleIndex == 0, the left side sum is considered to be 0. Similarly, if middleIndex ==
 * nums.length - 1, the right side sum is considered to be 0.
 * Return the leftmost middleIndex that satisfies the condition, or -1 if there is no such index.
 *
 * @tags    #prefix-sum
 */
int PivotIndex(const ArrayType &nums) {
    const auto total_sum = std::accumulate(nums.cbegin(), nums.cend(), 0);

    int prefix_sum = 0;
    for (std::size_t i = 0; i < nums.size();) {
        if (prefix_sum * 2 == total_sum - nums[i]) {
            return i;
        }
        prefix_sum += nums[i++];
    }

    return -1;
}

} //namespace


const ArrayType SAMPLE1 = {1, 7, 3, 6, 5, 6};
const ArrayType SAMPLE2 = {1, 2, 3};
const ArrayType SAMPLE3 = {2, 1, -1};


THE_BENCHMARK(PivotIndex, SAMPLE1);

SIMPLE_TEST(PivotIndex, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(PivotIndex, TestSAMPLE2, -1, SAMPLE2);
SIMPLE_TEST(PivotIndex, TestSAMPLE3, 0, SAMPLE3);
