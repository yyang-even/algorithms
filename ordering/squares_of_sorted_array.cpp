#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Squares of a Sorted Array
 *
 * @reference   https://leetcode.com/problems/squares-of-a-sorted-array/
 *
 * Given an integer array nums sorted in non-decreasing order, return an array of the
 * squares of each number sorted in non-decreasing order.
 * Follow up: Squaring each element and sorting the new array is very trivial, could you
 * find an O(n) solution using a different approach?
 */
auto SortedSquares(const ArrayType &nums) {
    ArrayType result(nums.size(), 0);
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        if (std::abs(nums[left]) <= std::abs(nums[right])) {
            result[right - left] = nums[right] * nums[right];
            --right;
        } else {
            result[right - left] = nums[left] * nums[left];
            ++left;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {-4, -1, 0, 3, 10};
const ArrayType EXPECTED1 = {0, 1, 9, 16, 100};

const ArrayType SAMPLE2 = {-7, -3, 2, 3, 11};
const ArrayType EXPECTED2 = {4, 9, 9, 49, 121};


THE_BENCHMARK(SortedSquares, SAMPLE1);

SIMPLE_TEST(SortedSquares, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortedSquares, TestSAMPLE2, EXPECTED2, SAMPLE2);
