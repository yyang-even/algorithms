#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

#include "find_minimum_in_sorted_and_rotated_array.h"


auto CheckIfArraySortedAndRotated(const ArrayType &values,
                                  const std::function<ArrayType::const_iterator(const ArrayType &)> min_element) {
    const auto minimum_element = min_element(values);

    if (minimum_element == values.cbegin()) {
        return false;
    }

    const auto is_first_part_sorted = std::is_sorted(values.cbegin(), minimum_element);
    const auto is_second_part_sorted =
        std::is_sorted(std::next(minimum_element), values.cend());
    return is_first_part_sorted and is_second_part_sorted and
           values.back() < *std::prev(minimum_element);
}

/** Check if an array is sorted and rotated
 *
 * @reference   https://www.geeksforgeeks.org/check-if-an-array-is-sorted-and-rotated/
 *
 * Given an array of N distinct integers. The task is to write a program to check if
 * this array is sorted and rotated counter-clockwise. A sorted array is not considered
 * as sorted and rotated, i.e., there should at least one rotation.
 */
auto CheckIfArraySortedAndRotated_LinearSearch(const ArrayType &values) {
    return CheckIfArraySortedAndRotated(values, [](const auto & values) {
        return std::min_element(values.cbegin(), values.cend());
    });
}


/**
 * @reference   Check if an array is sorted and rotated using Binary Search
 *              https://www.geeksforgeeks.org/check-if-an-array-is-sorted-and-rotated-using-binary-search/
 */
auto CheckIfArraySortedAndRotated_BinarySearch(const ArrayType &values) {
    return CheckIfArraySortedAndRotated(values, [](const auto & values) {
        return FindMinInSortedAndRotatedArray(values.cbegin(), values.size());
    });
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


SIMPLE_BENCHMARK(CheckIfArraySortedAndRotated_LinearSearch, Sample1, SAMPLE1);

SIMPLE_TEST(CheckIfArraySortedAndRotated_LinearSearch, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(CheckIfArraySortedAndRotated_LinearSearch, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(CheckIfArraySortedAndRotated_LinearSearch, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(CheckIfArraySortedAndRotated_LinearSearch, TestSAMPLE4, false, SAMPLE4);


SIMPLE_BENCHMARK(CheckIfArraySortedAndRotated_BinarySearch, Sample1, SAMPLE1);

SIMPLE_TEST(CheckIfArraySortedAndRotated_BinarySearch, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(CheckIfArraySortedAndRotated_BinarySearch, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(CheckIfArraySortedAndRotated_BinarySearch, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(CheckIfArraySortedAndRotated_BinarySearch, TestSAMPLE4, false, SAMPLE4);
