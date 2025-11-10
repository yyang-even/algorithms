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


/**
 * @reference   Make Array Elements Equal to Zero
 *              https://leetcode.com/problems/make-array-elements-equal-to-zero/
 *
 * You are given an integer array nums.
 * Start by selecting a starting position curr such that nums[curr] == 0, and choose a movement
 * direction of either left or right.
 * After that, you repeat the following process:
 *  If curr is out of the range [0, n - 1], this process ends.
 *  If nums[curr] == 0, move in the current direction by incrementing curr if you are moving right, or
 *      decrementing curr if you are moving left.
 *  Else if nums[curr] > 0:
 *      Decrement nums[curr] by 1.
 *      Reverse your movement direction (left becomes right and vice versa).
 *      Take a step in your new direction.
 * A selection of the initial position curr and movement direction is considered valid if every element
 * in nums becomes 0 by the end of the process.
 * Return the number of possible valid selections.
 *
 * @tags    #prefix-sum
 */
auto CountValidSelections(const ArrayType &nums) {
    const auto total = std::accumulate(nums.cbegin(), nums.cend(), 0);

    int left_sum = 0;
    int result = 0;
    for (const auto n : nums) {
        if (n == 0) {
            const auto right_sum = total - left_sum;
            result += (std::abs(left_sum - right_sum) <= 1);
            result += (left_sum == right_sum);
        } else {
            left_sum += n;
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 7, 3, 6, 5, 6};
const ArrayType SAMPLE2 = {1, 2, 3};
const ArrayType SAMPLE3 = {2, 1, -1};


THE_BENCHMARK(PivotIndex, SAMPLE1);

SIMPLE_TEST(PivotIndex, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(PivotIndex, TestSAMPLE2, -1, SAMPLE2);
SIMPLE_TEST(PivotIndex, TestSAMPLE3, 0, SAMPLE3);


const ArrayType SAMPLE1CVS = {1, 0, 2, 0, 3};
const ArrayType SAMPLE2CVS = {2, 3, 4, 0, 4, 1, 0};
const ArrayType SAMPLE3CVS = {16, 13, 10, 0, 0, 0, 10, 6, 7, 8, 7};


THE_BENCHMARK(CountValidSelections, SAMPLE2CVS);

SIMPLE_TEST(CountValidSelections, TestSAMPLE1, 2, SAMPLE1CVS);
SIMPLE_TEST(CountValidSelections, TestSAMPLE2, 0, SAMPLE2CVS);
SIMPLE_TEST(CountValidSelections, TestSAMPLE3, 3, SAMPLE3CVS);
