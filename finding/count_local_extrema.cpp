#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Number of local extrema in an array
 *              https://www.geeksforgeeks.org/maximum-number-local-extrema/
 *
 * You are given an array on n-elements. An extrema is an elements which is either greater than its both
 * of neighbors or less than its both neighbors. You have to calculate the number of local extrema in
 * given array.
 * Note: 1st and last elements are not extrema.
 *
 * @tags    #sliding-window
 */
auto CountLocalExtrema(const ArrayType &elements) {
    assert(elements.size() > 2);

    auto count = 0;
    auto prev = elements.cbegin();
    auto iter = std::next(prev);
    for (auto next = std::next(iter); next != elements.cend(); ++prev, ++iter, ++next)
        count += (*prev < *iter and *iter > *next) or (*prev > *iter and *iter < *next);

    return count;
}


/**
 * @reference   Count Hills and Valleys in an Array
 *              https://leetcode.com/problems/count-hills-and-valleys-in-an-array/
 *
 * You are given a 0-indexed integer array nums. An index i is part of a hill in nums if the closest
 * non-equal neighbors of i are smaller than nums[i]. Similarly, an index i is part of a valley in nums
 * if the closest non-equal neighbors of i are larger than nums[i]. Adjacent indices i and j are part of
 * the same hill or valley if nums[i] == nums[j].
 * Note that for an index to be part of a hill or valley, it must have a non-equal neighbor on both the
 * left and right of the index.
 * Return the number of hills and valleys in nums.
 *
 * @tags    #sliding-window
 */
auto CountLocalExtremaWithDuplicates(const ArrayType &nums) {
    int result = 0;
    for (std::size_t i = 1, j = 0; i < nums.size() - 1; ++i) {
        if ((nums[j] < nums[i] and nums[i] > nums[i + 1]) or
            (nums[j] > nums[i] and nums[i] < nums[i + 1])) {
            ++result;
            j = i;
        }
    }
    return result;
}


/**
 * @reference   Wiggle Subsequence
 *              https://leetcode.com/problems/wiggle-subsequence/
 *
 * A wiggle sequence is a sequence where the differences between successive numbers strictly alternate
 * between positive and negative. The first difference (if one exists) may be either positive or
 * negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle
 * sequences.
 *  For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences (6, -3, 5, -7, 3)
 *      alternate between positive and negative.
 *  In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences. The first is not because
 *      its first two differences are positive, and the second is not because its last difference is
 *      zero.
 * A subsequence is obtained by deleting some elements (possibly zero) from the original sequence,
 * leaving the remaining elements in their original order.
 * Given an integer array nums, return the length of the longest wiggle subsequence of nums.
 * Follow up: Could you solve this in O(n) time?
 *
 * @tags    #greedy
 */
int WiggleSubsequence(const ArrayType &nums) {
    if (nums.size() < 2) {
        return nums.size();
    }

    int up = 1;
    int down = 1;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] > nums[i - 1]) {
            up = down + 1;
        } else if (nums[i] < nums[i - 1]) {
            down = up + 1;
        }
    }

    return std::max(up, down);
}

} //namespace


const ArrayType SAMPLE1 = {1, 5, 2, 5};
const ArrayType SAMPLE2 = {1, 2, 3};
const ArrayType SAMPLE3 = {1, 0, 2, 1};


THE_BENCHMARK(CountLocalExtrema, SAMPLE1);

SIMPLE_TEST(CountLocalExtrema, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(CountLocalExtrema, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(CountLocalExtrema, TestSAMPLE3, 2, SAMPLE3);


const ArrayType SAMPLE4 = {2, 4, 1, 1, 6, 5};
const ArrayType SAMPLE5 = {6, 6, 5, 5, 4, 1};


THE_BENCHMARK(CountLocalExtremaWithDuplicates, SAMPLE1);

SIMPLE_TEST(CountLocalExtremaWithDuplicates, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(CountLocalExtremaWithDuplicates, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(CountLocalExtremaWithDuplicates, TestSAMPLE3, 2, SAMPLE3);
SIMPLE_TEST(CountLocalExtremaWithDuplicates, TestSAMPLE4, 3, SAMPLE4);
SIMPLE_TEST(CountLocalExtremaWithDuplicates, TestSAMPLE5, 0, SAMPLE5);


const ArrayType SAMPLE6 = {1, 7, 4, 9, 2, 5};
const ArrayType SAMPLE7 = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
const ArrayType SAMPLE8 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const ArrayType SAMPLE9 = {0};
const ArrayType SAMPLE10 = {0, 0};
const ArrayType SAMPLE11 = {0, 0, 0};


THE_BENCHMARK(WiggleSubsequence, SAMPLE1);

SIMPLE_TEST(WiggleSubsequence, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE2, 2, SAMPLE2);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE3, 4, SAMPLE3);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE4, 5, SAMPLE4);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE5, 2, SAMPLE5);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE6, 6, SAMPLE6);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE7, 7, SAMPLE7);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE8, 2, SAMPLE8);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE9, 1, SAMPLE9);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE10, 1, SAMPLE10);
SIMPLE_TEST(WiggleSubsequence, TestSAMPLE11, 1, SAMPLE11);
