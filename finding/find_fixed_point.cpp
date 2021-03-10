#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find a Fixed Point (Value equal to index) in a given array
 *
 * @reference   https://www.geeksforgeeks.org/find-a-fixed-point-in-a-given-array/
 *
 * Given an array of n distinct integers sorted in ascending order, write a function that
 * returns a Fixed Point in the array, if there is any Fixed Point present in array, else
 * returns -1. Fixed Point in an array is an index i such that arr[i] is equal to i. Note
 * that integers in array can be negative.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.3.
 */
auto FindOneFixedPoint(const ArrayType &elements, const int low, const int high) {
    if (high >= low) {
        const auto mid = (high + low) / 2;
        if (mid == elements[mid]) {
            return mid;
        }
        if (mid > elements[mid]) {
            return FindOneFixedPoint(elements, mid + 1, high);
        } else {
            return FindOneFixedPoint(elements, low, mid - 1);
        }
    }

    return -1;
}

auto FindOneFixedPoint(const ArrayType &elements) {
    return FindOneFixedPoint(elements, 0, elements.size() - 1);
}


/** Find a Fixed Point (Value equal to index) in a given array | Duplicates Allowed
 *
 * @reference   https://www.geeksforgeeks.org/find-fixed-point-value-equal-index-given-array-duplicates-allowed/
 * @reference   Find a Fixed Point in an array with duplicates allowed
 *              https://www.geeksforgeeks.org/find-fixed-point-array-duplicates-allowed/
 */
auto FindOneFixedPointInArrayWithDuplicates(const ArrayType &elements,
                                            const int low, const int high) {
    if (high < low) {
        return -1;
    }

    const auto mid = (high + low) / 2;

    if (mid == elements[mid]) {
        return mid;
    }

    const auto result_of_left_side = FindOneFixedPointInArrayWithDuplicates(elements,
                                     low, std::min(mid - 1, elements[mid]));
    if (result_of_left_side >= 0) {
        return result_of_left_side;
    }

    return FindOneFixedPointInArrayWithDuplicates(
               elements, std::max(elements[mid], mid + 1), high);
}

auto FindOneFixedPointInArrayWithDuplicates(const ArrayType &elements) {
    return FindOneFixedPointInArrayWithDuplicates(elements, 0, elements.size() - 1);
}

}//namespace


const ArrayType EMPTY = {};
const ArrayType SAMPLE1 = {-10, -5, 0, 3, 7};
const ArrayType SAMPLE_FRONT = {0, 2, 5, 8, 17};
const ArrayType SAMPLE3 = {-10, -5, 3, 4, 7, 9};
const ArrayType SAMPLE4 = {-10, -1, 0, 3, 10, 11, 30, 50, 100};
const ArrayType SAMPLE_BACK = {-1, 0, 1, 2, 4};
const ArrayType UNDERFLOW = {2};


THE_BENCHMARK(FindOneFixedPoint, SAMPLE1);

SIMPLE_TEST(FindOneFixedPoint, TestEMPTY, -1, EMPTY);
SIMPLE_TEST(FindOneFixedPoint, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(FindOneFixedPoint, Test_FRONT, SAMPLE_FRONT.front(), SAMPLE_FRONT);
SIMPLE_TEST(FindOneFixedPoint, TestSAMPLE3, -1, SAMPLE3);
SIMPLE_TEST(FindOneFixedPoint, TestSAMPLE4, 3, SAMPLE4);
SIMPLE_TEST(FindOneFixedPoint, Test_BACK, SAMPLE_BACK.back(), SAMPLE_BACK);
SIMPLE_TEST(FindOneFixedPoint, TestUnderflow, -1, UNDERFLOW);


const ArrayType SAMPLE5 = {-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13};


THE_BENCHMARK(FindOneFixedPointInArrayWithDuplicates, SAMPLE1);

SIMPLE_TEST(FindOneFixedPointInArrayWithDuplicates, TestEMPTY, -1, EMPTY);
SIMPLE_TEST(FindOneFixedPointInArrayWithDuplicates, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(FindOneFixedPointInArrayWithDuplicates, Test_FRONT, SAMPLE_FRONT.front(),
            SAMPLE_FRONT);
SIMPLE_TEST(FindOneFixedPointInArrayWithDuplicates, TestSAMPLE3, -1, SAMPLE3);
SIMPLE_TEST(FindOneFixedPointInArrayWithDuplicates, TestSAMPLE4, 3, SAMPLE4);
SIMPLE_TEST(FindOneFixedPointInArrayWithDuplicates, Test_BACK, SAMPLE_BACK.back(),
            SAMPLE_BACK);
SIMPLE_TEST(FindOneFixedPointInArrayWithDuplicates, TestUnderflow, -1, UNDERFLOW);
SIMPLE_TEST(FindOneFixedPointInArrayWithDuplicates, TestSAMPLE5, 2, SAMPLE5);
