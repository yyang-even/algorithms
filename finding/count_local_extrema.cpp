#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Number of local extrema in an array
 *
 * @reference   https://www.geeksforgeeks.org/maximum-number-local-extrema/
 *
 * You are given an array on n-elements. An extrema is an elements which is either
 * greater than its both of neighbors or less than its both neighbors. You have to
 * calculate the number of local extrema in given array.
 * Note: 1st and last elements are not extrema.
 */
auto CountLocalExtrema(const ArrayType &elements) {
    assert(elements.size() > 2);

    auto count = 0;
    auto prev = elements.cbegin();
    auto iter = std::next(prev);
    for (auto next = std::next(iter); next != elements.cend(); ++prev, ++iter, ++next)
        count += (*prev < *iter and *iter > *next) or
                 (*prev > *iter and * iter < *next);

    return count;
}


/**
 * @reference   Count Hills and Valleys in an Array
 *              https://leetcode.com/problems/count-hills-and-valleys-in-an-array/
 *
 * You are given a 0-indexed integer array nums. An index i is part of a hill in nums if
 * the closest non-equal neighbors of i are smaller than nums[i]. Similarly, an index i is
 * part of a valley in nums if the closest non-equal neighbors of i are larger than nums[i].
 * Adjacent indices i and j are part of the same hill or valley if nums[i] == nums[j].
 * Note that for an index to be part of a hill or valley, it must have a non-equal neighbor
 * on both the left and right of the index.
 * Return the number of hills and valleys in nums.
 */
auto CountLocalExtremaWithDuplicates(const ArrayType &nums) {
    int result = 0;
    for (std::size_t i = 1, j = 0; i < nums.size() - 1; ++i) {
        if ((nums[j] < nums[i] and nums[i] > nums [i + 1]) or
            (nums[j] > nums[i] and nums[i] < nums [i + 1])) {
            ++result;
            j = i;
        }
    }
    return result;
}

}//namespace


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
