#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<int>;

/** Find a peak element
 *
 * @reference   https://www.geeksforgeeks.org/find-a-peak-in-a-given-array/
 *
 * Given an array of integers. Find a peak element in it. An array element is peak if it
 * is NOT smaller than its neighbors. For corner elements, we need to consider only one
 * neighbor. For example, for input array {5, 10, 20, 15}, 20 is the only peak element.
 * For input array {10, 20, 15, 2, 23, 90, 67}, there are two peak elements: 20 and 90.
 * Note that we need to return any one peak element.
 *
 * @reference   Find the maximum element in an array which is first increasing and then decreasing
 *              https://www.geeksforgeeks.org/find-the-maximum-element-in-an-array-which-is-first-increasing-and-then-decreasing/
 * @reference   Find Peak Element
 *              https://leetcode.com/problems/find-peak-element/
 *
 * A peak element is an element that is strictly greater than its neighbors. Given an
 * integer array nums, find a peak element, and return its index. If the array contains
 * multiple peaks, return the index to any of the peaks. You may imagine that
 * nums[-1] = nums[n] = -∞.
 * You must write an algorithm that runs in O(log n) time.
 *
 * @reference   Peak Index in a Mountain Array
 *              https://leetcode.com/problems/peak-index-in-a-mountain-array/
 *
 * Let's call an array arr a mountain if the following properties hold:
 *  arr.length >= 3
 *  There exists some i with 0 < i < arr.length - 1 such that:
 *      arr[0] < arr[1] < ... arr[i-1] < arr[i]
 *      arr[i] > arr[i+1] > ... > arr[arr.length - 1]
 * Given an integer array arr that is guaranteed to be a mountain, return any i such that
 * arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1].
 * Follow up: Finding the O(n) is straightforward, could you find an O(log(n)) solution?
 */
auto FindOnePeakElement_Iter(const ArrayType &elements,
                             const ArrayType::const_iterator cbegin,
                             const ArrayType::size_type length) {
    const auto half = length / 2;
    const auto mid = cbegin + half;
    const auto mid_next = std::next(mid);

    if ((mid == elements.cbegin() or * std::prev(mid) <= *mid)
        and (mid_next == elements.cend() or * mid_next <= *mid)) {
        return mid;
    }
    if (mid != elements.cbegin() and * std::prev(mid) > *mid) {
        return FindOnePeakElement_Iter(elements, cbegin, half);
    }
    return FindOnePeakElement_Iter(elements, mid_next, length - half - 1);
}

inline auto
FindOnePeakElement_Iter(const ArrayType &elements) {
    return *FindOnePeakElement_Iter(elements, elements.cbegin(), elements.size());
}


inline auto
FindOnePeakElement_Index(const ArrayType &elements,
                         const int left, const int right) {
    if (left == right) {
        return left;
    }

    const auto mid = (left + right) / 2;
    if (elements[mid] > elements[mid + 1]) {
        return FindOnePeakElement_Index(elements, left, mid);
    }
    return FindOnePeakElement_Index(elements, mid + 1, right);
}

inline auto
FindOnePeakElement_Index(const ArrayType &elements) {
    assert(not elements.empty());
    return elements[FindOnePeakElement_Index(elements, 0, elements.size() - 1)];
}


auto FindOnePeakElement_Iterative(const ArrayType &elements) {
    assert(not elements.empty());

    std::size_t left = 0, right = elements.size() - 1;
    while (left < right) {
        const auto mid = (left + right) / 2;
        if (elements[mid] > elements[mid + 1]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return elements[left];
}


/** Find a local minima in an array
 *
 * @reference   https://www.geeksforgeeks.org/find-local-minima-array/
 *
 * Given an array arr[0 .. n-1] of distinct integers, the task is to find a local minima
 * in it. We say that an element arr[x] is a local minimum if it is less than or equal
 * to both its neighbors.
 *
 * @reference   Minimum in an array which is first decreasing then increasing
 *              https://www.geeksforgeeks.org/minimum-in-an-array-which-is-first-decreasing-then-increasing/
 */


/** Check if an array is increasing or decreasing
 *
 * @reference   https://www.geeksforgeeks.org/check-if-an-array-is-increasing-or-decreasing/
 *
 * Given an array arr[] of N elements where N >= 2, the task is to check the type of
 * array whether it is:
 *  1. Increasing.
 *  2. Decreasing.
 *  3. Increasing then decreasing.
 *  4. Decreasing then increasing.
 * Note that the given array is definitely one of the given types.
 *
 * @reference   Valid Mountain Array
 *              https://leetcode.com/problems/valid-mountain-array/
 *
 * Given an array of integers arr, return true if and only if it is a valid mountain
 * array. Recall that arr is a mountain array if and only if:
 *  arr.length >= 3
 *  There exists some i with 0 < i < arr.length - 1 such that:
 *      arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 *      arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 */
auto ValidMountainArray(const ArrayType &nums) {
    std::size_t i = 0;

    while (i + 1 < nums.size() and nums[i] < nums[i + 1]) {
        ++i;
    }

    if (i == 0 || i + 1 == nums.size()) {
        return false;
    }

    while (i + 1 < nums.size() and nums[i] > nums[i + 1]) {
        ++i;
    }

    return i + 1 == nums.size();
}


/**
 * @reference   Find a Peak Element II
 *              https://leetcode.com/problems/find-a-peak-element-ii/
 *
 * A peak element in a 2D grid is an element that is strictly greater than all of its
 * adjacent neighbors to the left, right, top, and bottom. Given a 0-indexed m x n
 * matrix mat where no two adjacent cells are equal, find any peak element mat[i][j]
 * and return the length 2 array [i,j]. You may assume that the entire matrix is
 * surrounded by an outer perimeter with the value -1 in each cell.
 * You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.
 *
 * @reference   Find a peak element in a 2D array
 *              https://www.geeksforgeeks.org/find-peak-element-2d-array/
 */
auto FindOnePeakElement(const MatrixType &a_matrix, const int top, const int bottom) {
    const auto mid = (top + bottom) / 2;
    const auto &mid_row = a_matrix[mid];
    const auto max_index = std::max_element(mid_row.cbegin(), mid_row.cend()) -
                           mid_row.cbegin();

    if (top == bottom) {
        return a_matrix[mid][max_index];
    }

    if (a_matrix[mid][max_index] > a_matrix[mid + 1][max_index]) {
        return FindOnePeakElement(a_matrix, top, mid);
    }
    return FindOnePeakElement(a_matrix, mid + 1, bottom);
}

inline auto FindOnePeakElement(const MatrixType &a_matrix) {
    return FindOnePeakElement(a_matrix, 0, a_matrix.size() - 1);
}

}//namespace


const ArrayType SAMPLE1 = {5, 10, 20, 15};
const ArrayType INCREASING = {10, 20, 30, 40, 50};
const ArrayType DECREASING = {100, 80, 60, 50, 20};
const ArrayType ALL_SAME = {10, 10, 10, 10, 10};


THE_BENCHMARK(FindOnePeakElement_Iter, SAMPLE1);

SIMPLE_TEST(FindOnePeakElement_Iter, TestSAMPLE1, 20, SAMPLE1);
SIMPLE_TEST(FindOnePeakElement_Iter, TestINCREASING, INCREASING.back(), INCREASING);
SIMPLE_TEST(FindOnePeakElement_Iter, TestDECREASING, DECREASING.front(), DECREASING);
SIMPLE_TEST(FindOnePeakElement_Iter, TestALL_SAME, ALL_SAME.back(), ALL_SAME);


THE_BENCHMARK(FindOnePeakElement_Index, SAMPLE1);

SIMPLE_TEST(FindOnePeakElement_Index, TestSAMPLE1, 20, SAMPLE1);
SIMPLE_TEST(FindOnePeakElement_Index, TestINCREASING, INCREASING.back(), INCREASING);
SIMPLE_TEST(FindOnePeakElement_Index, TestDECREASING, DECREASING.front(), DECREASING);
SIMPLE_TEST(FindOnePeakElement_Index, TestALL_SAME, ALL_SAME.back(), ALL_SAME);


THE_BENCHMARK(FindOnePeakElement_Iterative, SAMPLE1);

SIMPLE_TEST(FindOnePeakElement_Iterative, TestSAMPLE1, 20, SAMPLE1);
SIMPLE_TEST(FindOnePeakElement_Iterative, TestINCREASING,
            INCREASING.back(), INCREASING);
SIMPLE_TEST(FindOnePeakElement_Iterative, TestDECREASING,
            DECREASING.front(), DECREASING);
SIMPLE_TEST(FindOnePeakElement_Iterative, TestALL_SAME, ALL_SAME.back(), ALL_SAME);


THE_BENCHMARK(ValidMountainArray, SAMPLE1);

SIMPLE_TEST(ValidMountainArray, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(ValidMountainArray, TestSAMPLE2, false, INCREASING);
SIMPLE_TEST(ValidMountainArray, TestSAMPLE3, false, DECREASING);
SIMPLE_TEST(ValidMountainArray, TestSAMPLE4, false, ALL_SAME);


const MatrixType SAMPLE1M = {
    {10, 20, 15},
    {21, 30, 14},
    {7, 16, 32},
};

const MatrixType SAMPLE2M = {
    {10, 7},
    {11, 17},
};

const MatrixType SAMPLE3M = {
    {1, 4},
    {3, 2},
};


THE_BENCHMARK(FindOnePeakElement, SAMPLE1M);

SIMPLE_TEST(FindOnePeakElement, TestSAMPLE1, 30, SAMPLE1M);
SIMPLE_TEST(FindOnePeakElement, TestSAMPLE2, 17, SAMPLE2M);
SIMPLE_TEST(FindOnePeakElement, TestSAMPLE3, 4, SAMPLE3M);
