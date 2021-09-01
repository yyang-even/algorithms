#include "common_header.h"

#include "finding.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Search an element in a sorted and rotated array
 *              https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.3.
 *
 * Given a sorted array of n integers that has been rotated an unknown number of times,
 * write code to find an element in the array. You may assume that the array was
 * originally sorted in increasing order.
 *
 * @reference   Search in Rotated Sorted Array
 *              https://leetcode.com/problems/search-in-rotated-sorted-array/
 *
 * There is an integer array nums sorted in ascending order (with distinct values). Prior
 * to being passed to your function, nums is rotated at an unknown pivot index k
 * (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ...,
 * nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7]
 * might be rotated at pivot index 3 and become [4,5,6,7,0,1,2]. Given the array nums
 * after the rotation and an integer target, return the index of target if it is in nums,
 * or -1 if it is not in nums. You must write an algorithm with O(log n) runtime
 * complexity.
 */
auto SearchRotatedArray(const ArrayType &nums, const ArrayType::value_type target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        const auto mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[left] <= nums[mid]) {
            if (target >= nums[left] and target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (target <= nums[right] and target > nums[mid]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return NOT_FOUND;
}


/**
 * @reference   Search an element in a sorted and rotated array with duplicates
 *              https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-rotated-array-with-duplicates/
 *
 * @reference   Search in Rotated Sorted Array II
 *              https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
 *
 * There is an integer array nums sorted in non-decreasing order (not necessarily with
 * distinct values). Before being passed to your function, nums is rotated at an unknown
 * pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k],
 * nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example,
 * [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].
 * Given the array nums after the rotation and an integer target, return true if target
 * is in nums, or false if it is not in nums. You must decrease the overall operation
 * steps as much as possible.
 * Follow up: This problem is similar to Search in Rotated Sorted Array, but nums may
 * contain duplicates. Would this affect the runtime complexity? How and why?
 */
auto
SearchRotatedArrayWithDup(const ArrayType &elements, const ArrayType::value_type key,
                          const int left, const int right) {
    if (left > right) {
        return NOT_FOUND;
    }

    const auto mid = (left + right) / 2;

    if (elements[mid] == key) {
        return mid;
    }

    if (elements[left] == elements[mid] and elements[mid] == elements[right]) {
        return SearchRotatedArrayWithDup(elements, key, left + 1, right - 1);
    }

    if (elements[left] <= elements[mid]) {
        if (key >= elements[left] and key <= elements[mid]) {
            return SearchRotatedArrayWithDup(elements, key, left, mid - 1);
        } else {
            return SearchRotatedArrayWithDup(elements, key, mid + 1, right);
        }
    }

    if (key >= elements[mid] and key <= elements[right]) {
        return SearchRotatedArrayWithDup(elements, key, mid + 1, right);
    }

    return SearchRotatedArrayWithDup(elements, key, left, mid - 1);
}

inline auto
SearchRotatedArrayWithDup(const ArrayType &elements, const ArrayType::value_type key) {
    return SearchRotatedArrayWithDup(elements, key, 0, elements.size() - 1) != NOT_FOUND;
}


auto SearchRotatedArrayWithDup_Iterative(const ArrayType &nums,
                                         const ArrayType::value_type target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        const auto mid = (left + right) / 2;
        if (nums[mid] == target) {
            return true;
        }

        if (nums[left] == nums[mid] and nums[right] == nums[mid]) {
            ++left;
            --right;
        } else if (nums[left] <= nums[mid]) {
            if (target >= nums[left] and target <= nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (target <= nums[right] and target >= nums[mid]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return false;
}

}//namespace


const ArrayType SAMPLE1 = {5, 6, 7, 8, 9, 10, 1, 2, 3};
const ArrayType SAMPLE2 = {4, 5, 6, 7, 8, 9, 10, 1, 2, 3};
const ArrayType SAMPLE3 = {30, 40, 50, 10, 20};
const ArrayType SAMPLE4 = {3, 3, 3, 1, 2, 3};
const ArrayType SAMPLE5 = {3, 3, 1, 2, 3, 3};
const ArrayType SAMPLE6 = {2, 5, 6, 0, 0, 1, 2};


THE_BENCHMARK(SearchRotatedArrayWithDup, SAMPLE1, 3);

SIMPLE_TEST(SearchRotatedArrayWithDup, TestSAMPLE1, true, SAMPLE1, 3);
SIMPLE_TEST(SearchRotatedArrayWithDup, TestSAMPLE2, true, SAMPLE2, 6);
SIMPLE_TEST(SearchRotatedArrayWithDup, TestSAMPLE3, false, SAMPLE2, 30);
SIMPLE_TEST(SearchRotatedArrayWithDup, TestSAMPLE4, true, SAMPLE3, 10);
SIMPLE_TEST(SearchRotatedArrayWithDup, TestSAMPLE5, true, SAMPLE4, 3);
SIMPLE_TEST(SearchRotatedArrayWithDup, TestSAMPLE6, false, SAMPLE4, 11);
SIMPLE_TEST(SearchRotatedArrayWithDup, TestSAMPLE7, true, SAMPLE5, 3);
SIMPLE_TEST(SearchRotatedArrayWithDup, TestSAMPLE8, true, SAMPLE6, 0);
SIMPLE_TEST(SearchRotatedArrayWithDup, TestSAMPLE9, false, SAMPLE6, 3);


THE_BENCHMARK(SearchRotatedArrayWithDup_Iterative, SAMPLE1, 3);

SIMPLE_TEST(SearchRotatedArrayWithDup_Iterative, TestSAMPLE1, true, SAMPLE1, 3);
SIMPLE_TEST(SearchRotatedArrayWithDup_Iterative, TestSAMPLE2, true, SAMPLE2, 6);
SIMPLE_TEST(SearchRotatedArrayWithDup_Iterative, TestSAMPLE3, false, SAMPLE2, 30);
SIMPLE_TEST(SearchRotatedArrayWithDup_Iterative, TestSAMPLE4, true, SAMPLE3, 10);
SIMPLE_TEST(SearchRotatedArrayWithDup_Iterative, TestSAMPLE5, true, SAMPLE4, 3);
SIMPLE_TEST(SearchRotatedArrayWithDup_Iterative, TestSAMPLE6, false, SAMPLE4, 11);
SIMPLE_TEST(SearchRotatedArrayWithDup_Iterative, TestSAMPLE7, true, SAMPLE5, 3);
SIMPLE_TEST(SearchRotatedArrayWithDup_Iterative, TestSAMPLE8, true, SAMPLE6, 0);
SIMPLE_TEST(SearchRotatedArrayWithDup_Iterative, TestSAMPLE9, false, SAMPLE6, 3);


THE_BENCHMARK(SearchRotatedArray, SAMPLE1, 3);

SIMPLE_TEST(SearchRotatedArray, TestSAMPLE1, 8, SAMPLE1, 3);
SIMPLE_TEST(SearchRotatedArray, TestSAMPLE2, 2, SAMPLE2, 6);
SIMPLE_TEST(SearchRotatedArray, TestSAMPLE3, NOT_FOUND, SAMPLE2, 30);
SIMPLE_TEST(SearchRotatedArray, TestSAMPLE4, 3, SAMPLE3, 10);
