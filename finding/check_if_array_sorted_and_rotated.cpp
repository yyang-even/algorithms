#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Check if an array is sorted and rotated
 *
 * @reference   https://www.geeksforgeeks.org/check-if-an-array-is-sorted-and-rotated/
 *
 * Given an array of N distinct integers. The task is to write a program to check if
 * this array is sorted and rotated counter-clockwise. A sorted array is not considered
 * as sorted and rotated, i.e., there should at least one rotation.
 *
 * @reference   Check if an array is sorted and rotated using Binary Search
 *              https://www.geeksforgeeks.org/check-if-an-array-is-sorted-and-rotated-using-binary-search/
 *
 * @reference   Check if Array Is Sorted and Rotated
 *              https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/
 *
 * Given an array nums, return true if the array was originally sorted in non-decreasing
 * order, then rotated some number of positions (including zero). Otherwise, return false.
 * There may be duplicates in the original array.
 * Note: An array A rotated by x positions results in an array B of the same length such
 * that A[i] == B[(i+x) % A.length], where % is the modulo operation.
 * 1 <= nums.length <= 100
 */
auto isSortedAndRotated(const ArrayType &nums) {
    int violation = nums.back() > nums.front();
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[i - 1] > nums[i]) {
            if (violation++ == 1) {
                return false;
            }
        }
    }

    return true;
}


/** Check if it is possible to make array increasing or decreasing by rotating the array
 *
 * @reference   https://www.geeksforgeeks.org/check-if-it-is-possible-to-make-array-increasing-or-decreasing-by-rotating-the-array/
 *
 * Given an array arr[] of N distinct elements, the task is to check if it is possible
 * to make the array increasing or decreasing by rotating the array in any direction.
 */


/** Check if it is possible to sort the array after rotating it
 *
 * @reference   https://www.geeksforgeeks.org/check-if-it-is-possible-to-sort-the-array-after-rotating-it/
 *
 * Given an array of size N, the task is to determine whether its possible to sort the array
 * or not by just one shuffle. In one shuffle, we can shift some contiguous elements from the
 * end of the array and place it in the front of the array.
 */

}//namespace


const ArrayType SAMPLE1 = {3, 4, 5, 1, 2};
const ArrayType SAMPLE2 = {7, 9, 11, 12, 5};
const ArrayType SAMPLE3 = {1, 2, 3};
const ArrayType SAMPLE4 = {4, 9, 1, 5, 2};
const ArrayType SAMPLE5 = {3, 4, 5, 1, 2};
const ArrayType SAMPLE6 = {2, 1, 3, 4};
const ArrayType SAMPLE7 = {3, 2, 1};


THE_BENCHMARK(isSortedAndRotated, SAMPLE1);

SIMPLE_TEST(isSortedAndRotated, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isSortedAndRotated, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isSortedAndRotated, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(isSortedAndRotated, TestSAMPLE4, false, SAMPLE4);
SIMPLE_TEST(isSortedAndRotated, TestSAMPLE5, true, SAMPLE5);
SIMPLE_TEST(isSortedAndRotated, TestSAMPLE6, false, SAMPLE6);
SIMPLE_TEST(isSortedAndRotated, TestSAMPLE7, false, SAMPLE7);
