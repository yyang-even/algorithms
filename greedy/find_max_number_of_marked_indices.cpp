#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the Maximum Number of Marked Indices
 *
 * @reference   https://leetcode.com/problems/find-the-maximum-number-of-marked-indices/
 *
 * You are given a 0-indexed integer array nums.
 * Initially, all of the indices are unmarked. You are allowed to make this operation any number of
 * times:
 *  Pick two different unmarked indices i and j such that 2 * nums[i] <= nums[j], then mark i and j.
 * Return the maximum possible number of marked indices in nums using the above operation any number of
 * times.
 */
auto MaxNumOfMarkedIndices(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    std::size_t left = 0;
    std::size_t right = (nums.size() + 1) / 2;
    int result = 0;

    while (right < nums.size()) {
        if (nums[left] * 2 <= nums[right++]) {
            ++left;
            result += 2;
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {3, 5, 2, 4};
const ArrayType SAMPLE2 = {9, 2, 5, 4};
const ArrayType SAMPLE3 = {7, 6, 8};
const ArrayType SAMPLE4 = {2, 5, 12};
const ArrayType SAMPLE5 = {42, 83, 48, 10, 24, 55, 9,  100, 10, 17, 17, 99, 51,
                           32, 16, 98, 99, 31, 28, 68, 71,  14, 64, 29, 15, 40};


THE_BENCHMARK(MaxNumOfMarkedIndices, SAMPLE1);

SIMPLE_TEST(MaxNumOfMarkedIndices, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MaxNumOfMarkedIndices, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(MaxNumOfMarkedIndices, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(MaxNumOfMarkedIndices, TestSAMPLE4, 2, SAMPLE4);
SIMPLE_TEST(MaxNumOfMarkedIndices, TestSAMPLE5, SAMPLE5.size(), SAMPLE5);
