#include "common_header.h"

#include "mathematics/arithmetics/sum/largest_sum_contiguous_subarray.h"


namespace {

using ArrayType = std::vector<int>;

/** Maximum difference between two elements such that larger element appears after the smaller number
 *
 * @reference   https://www.geeksforgeeks.org/maximum-difference-between-two-elements/
 *
 * Given an array arr[] of integers, find out the maximum difference between any two
 * elements such that larger element appears after the smaller number.
 */
auto MaxDiffBetweenTwoElementsNoSort(const ArrayType &elements) {
    assert(elements.size() > 1);

    auto max_diff = elements[1] - elements[0];
    auto min_element = elements.front();

    for (auto iter = elements.cbegin() + 1; iter != elements.cend(); ++iter) {
        const auto diff = *iter - min_element;
        if (diff > max_diff) {
            max_diff = diff;
        }
        if (min_element > *iter) {
            min_element = *iter;
        }
    }

    return max_diff;
}


auto MaxDiffBetweenTwoElementsNoSort_SubarraySum(const ArrayType &elements) {
    assert(elements.size() > 1);

    ArrayType diff_array{};
    for (auto iter = elements.cbegin() + 1; iter != elements.cend(); ++iter) {
        diff_array.push_back(*iter - * (iter - 1));
    }

    return LargestSumContiguousSubarray_Kadane(diff_array);
}

}//namespace


const ArrayType SAMPLE1 = {2, 3, 10, 6, 4, 8, 1};
const ArrayType SAMPLE2 = {7, 9, 5, 6, 3, 2};
const ArrayType SAMPLE3 = {1, 2, 90, 10, 110};
const ArrayType SAMPLE4 = {80, 2, 6, 3, 100};


THE_BENCHMARK(MaxDiffBetweenTwoElementsNoSort, SAMPLE1);

SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort, TestSample1, 8, SAMPLE1);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort, TestSample2, 2, SAMPLE2);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort, TestSample3, 109, SAMPLE3);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort, TestSample4, 98, SAMPLE4);


THE_BENCHMARK(MaxDiffBetweenTwoElementsNoSort_SubarraySum, SAMPLE1);

SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort_SubarraySum, TestSample1, 8, SAMPLE1);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort_SubarraySum, TestSample2, 2, SAMPLE2);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort_SubarraySum, TestSample3, 109, SAMPLE3);
SIMPLE_TEST(MaxDiffBetweenTwoElementsNoSort_SubarraySum, TestSample4, 98, SAMPLE4);
