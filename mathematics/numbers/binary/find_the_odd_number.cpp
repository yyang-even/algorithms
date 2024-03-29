#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Find the Number Occurring Odd Number of Times
 *
 * @reference   https://www.geeksforgeeks.org/find-the-number-occurring-odd-number-of-times/
 * @reference   Find the element that appears once in an array where every other element appears twice
 *              https://www.geeksforgeeks.org/find-element-appears-array-every-element-appears-twice/
 * @reference   Find single in an array of 2n+1 integer elements
 *              https://www.geeksforgeeks.org/find-single-array-2n1-integer-elements/
 * @reference   Single Number
 *              https://leetcode.com/problems/single-number/
 *
 * Given a non-empty array of integers nums, every element appears twice except for one. Find that
 * single one.
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 *
 * @complexity  O(n)
 */
inline auto FindTheOddNumber(const ArrayType &values) {
    return std::accumulate(
        values.cbegin(), values.cend(), 0u, std::bit_xor<ArrayType::value_type> {});
}


/** Find the element that appears once in a sorted array
 *
 * @reference   https://www.geeksforgeeks.org/find-the-element-that-appears-once-in-a-sorted-array/
 *
 * Given a sorted array in which all elements appear twice (one after one) and one element appears only
 * once. Find that element in O(log n) complexity.
 */
auto FindTheOddNumber_Sorted_BinarySearch(const ArrayType &values,
                                          const ArrayType::size_type low,
                                          const ArrayType::size_type high) {
    if (low == high) {
        return low;
    }

    const auto mid = (low + high) / 2;
    if (mid % 2 == 0) {
        if (values[mid] == values[mid + 1]) {
            return FindTheOddNumber_Sorted_BinarySearch(values, mid + 2, high);
        } else {
            return FindTheOddNumber_Sorted_BinarySearch(values, low, mid);
        }
    } else {
        if (values[mid] == values[mid - 1]) {
            return FindTheOddNumber_Sorted_BinarySearch(values, mid + 1, high);
        } else {
            return FindTheOddNumber_Sorted_BinarySearch(values, low, mid - 1);
        }
    }
}

inline auto FindTheOddNumber_Sorted_BinarySearch(const ArrayType &values) {
    assert(not values.empty());
    assert(std::is_sorted(values.cbegin(), values.cend()));

    return values[FindTheOddNumber_Sorted_BinarySearch(values, 0, values.size() - 1)];
}


/**
 * @reference   Single Element in a Sorted Array
 *              https://leetcode.com/problems/single-element-in-a-sorted-array/
 *
 * You are given a sorted array consisting of only integers where every element appears exactly twice,
 * except for one element which appears exactly once.
 * Return the single element that appears only once.
 * Your solution must run in O(log n) time and O(1) space.
 */
auto FindTheOddNumber_Sorted_Iterative(const ArrayType &nums) {
    int left = 0;
    int right = nums.size() - 2;

    while (left <= right) {
        const auto mid = (left + right) / 2;
        if (nums[mid] == nums[mid ^ 1]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return nums[left];
}


/**
 * @reference   Find the Difference
 *              https://leetcode.com/problems/find-the-difference/
 *
 * You are given two strings s and t.
 * String t is generated by random shuffling string s and then add one more letter at a random position.
 * Return the letter that was added to t.
 */


/**
 * @reference   Neighboring Bitwise XOR
 *              https://leetcode.com/problems/neighboring-bitwise-xor/
 *
 * A 0-indexed array derived with length n is derived by computing the bitwise XOR (⊕) of adjacent
 * values in a binary array original of length n.
 * Specifically, for each index i in the range [0, n - 1]:
 *  If i = n - 1, then derived[i] = original[i] ⊕ original[0].
 *  Otherwise, derived[i] = original[i] ⊕ original[i + 1].
 * Given an array derived, your task is to determine whether there exists a valid binary array original
 * that could have formed derived.
 * Return true if such an array exists or false otherwise.
 *  A binary array is an array containing only 0's and 1's
 */

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 2, 3, 1, 3};
const ArrayType SAMPLE2 = {5, 7, 2, 7, 5, 2, 5};
const ArrayType SAMPLE3 = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
const ArrayType SAMPLE4 = {7, 3, 5, 4, 5, 3, 4};


THE_BENCHMARK(FindTheOddNumber, SAMPLE1);

SIMPLE_TEST(FindTheOddNumber, TestSample1, 3, SAMPLE1);
SIMPLE_TEST(FindTheOddNumber, TestSample2, 5, SAMPLE2);
SIMPLE_TEST(FindTheOddNumber, TestSample3, 5, SAMPLE3);
SIMPLE_TEST(FindTheOddNumber, TestSample4, 7, SAMPLE4);


const ArrayType SORTED_SAMPLE1 = {1, 2, 2, 4, 4, 5, 5, 6, 6};
const ArrayType SORTED_SAMPLE2 = {1, 1, 2, 4, 4, 5, 5, 6, 6};
const ArrayType SORTED_SAMPLE3 = {1, 1, 2, 2, 4, 4, 5, 5, 6};
const ArrayType SORTED_SAMPLE4 = {3, 3, 7, 7, 10, 11, 11};


THE_BENCHMARK(FindTheOddNumber_Sorted_BinarySearch, SORTED_SAMPLE1);

SIMPLE_TEST(FindTheOddNumber_Sorted_BinarySearch,
            TestFront,
            SORTED_SAMPLE1.front(),
            SORTED_SAMPLE1);
SIMPLE_TEST(FindTheOddNumber_Sorted_BinarySearch, TestSample2, 2, SORTED_SAMPLE2);
SIMPLE_TEST(FindTheOddNumber_Sorted_BinarySearch,
            TestBack,
            SORTED_SAMPLE3.back(),
            SORTED_SAMPLE3);
SIMPLE_TEST(FindTheOddNumber_Sorted_BinarySearch, TestSample4, 10, SORTED_SAMPLE4);


THE_BENCHMARK(FindTheOddNumber_Sorted_Iterative, SORTED_SAMPLE1);

SIMPLE_TEST(FindTheOddNumber_Sorted_Iterative, TestFront, SORTED_SAMPLE1.front(), SORTED_SAMPLE1);
SIMPLE_TEST(FindTheOddNumber_Sorted_Iterative, TestSample2, 2, SORTED_SAMPLE2);
SIMPLE_TEST(FindTheOddNumber_Sorted_Iterative, TestBack, SORTED_SAMPLE3.back(), SORTED_SAMPLE3);
SIMPLE_TEST(FindTheOddNumber_Sorted_Iterative, TestSample4, 10, SORTED_SAMPLE4);
