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
 */
auto CheckIfArraySortedAndRotated(const ArrayType &values) {
    const auto minimum_element = std::min_element(values.cbegin(), values.cend());

    if (minimum_element == values.cbegin()) {
        return false;
    }

    const auto is_first_part_sorted = std::is_sorted(values.cbegin(), minimum_element);
    const auto is_second_part_sorted = std::is_sorted(std::next(minimum_element), values.cend());
    return is_first_part_sorted and is_second_part_sorted and
           values.back() < *std::prev(minimum_element);
}

}//namespace


const ArrayType SAMPLE1 = {3, 4, 5, 1, 2};
const ArrayType SAMPLE2 = {7, 9, 11, 12, 5};
const ArrayType SAMPLE3 = {1, 2, 3};
const ArrayType SAMPLE4 = {4, 9, 1, 5, 2};


SIMPLE_BENCHMARK(CheckIfArraySortedAndRotated, SAMPLE1);

SIMPLE_TEST(CheckIfArraySortedAndRotated, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(CheckIfArraySortedAndRotated, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(CheckIfArraySortedAndRotated, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(CheckIfArraySortedAndRotated, TestSAMPLE4, false, SAMPLE4);
