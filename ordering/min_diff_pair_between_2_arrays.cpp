#include "common_header.h"

#include "min_diff_pair_between_2_arrays.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::vector<std::pair<int, int>>;

/** Smallest Difference pair of values between two unsorted Arrays
 *
 * @reference   https://www.geeksforgeeks.org/smallest-difference-pair-values-two-unsorted-arrays/
 *
 * Given two arrays of integers, compute the pair of values (one value in each array)
 * with the smallest (non-negative) difference. Return the difference.
 */
inline auto MinDiffPairOf2UnsortedArrays(ArrayType one, ArrayType another) {
    std::sort(one.begin(), one.end());
    std::sort(another.begin(), another.end());

    return MinDiffPairOf2SortedArrays(one, another);
}


/**
 * @reference   Minimum Absolute Difference
 *              https://leetcode.com/problems/minimum-absolute-difference/
 *
 * Given an array of distinct integers arr, find all pairs of elements with the minimum
 * absolute difference of any two elements. Return a list of pairs in ascending order
 * (with respect to pairs), each pair [a, b] follows:
 *  a, b are from arr
 *  a < b
 *  b - a equals to the minimum absolute difference of any two elements in arr
 */
auto MinDiffPairsOfAnUnsortedArray(ArrayType elements) {
    std::sort(elements.begin(), elements.end());

    int min_diff = INT_MAX;
    const auto N = elements.size();
    for (std::size_t i = 1; i < N; ++i) {
        min_diff = std::min(min_diff, elements[i] - elements[i - 1]);
    }

    OutputType result;
    for (std::size_t i = 1; i < N; ++i) {
        if (elements[i] - elements[i - 1] == min_diff) {
            result.emplace_back(elements[i - 1], elements[i]);
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1_L = {1, 3, 15, 11, 2};
const ArrayType SAMPLE1_R = {23, 127, 235, 19, 8};

const ArrayType SAMPLE2_L = {10, 5, 40};
const ArrayType SAMPLE2_R = {50, 90, 80};


THE_BENCHMARK(MinDiffPairOf2UnsortedArrays, SAMPLE1_L, SAMPLE1_R);

SIMPLE_TEST(MinDiffPairOf2UnsortedArrays, TestSAMPLE1, 3, SAMPLE1_L, SAMPLE1_R);
SIMPLE_TEST(MinDiffPairOf2UnsortedArrays, TestSAMPLE2, 10, SAMPLE2_L, SAMPLE2_R);


const ArrayType SAMPLE1 = {4, 2, 1, 3};
const OutputType EXPECTED1 = {{1, 2}, {2, 3}, {3, 4}};

const ArrayType SAMPLE2 = {1, 3, 6, 10, 15};
const OutputType EXPECTED2 = {{1, 3}};

const ArrayType SAMPLE3 = {3, 8, -10, 23, 19, -4, -14, 27};
const OutputType EXPECTED3 = {{-14, -10}, {19, 23}, {23, 27}};


THE_BENCHMARK(MinDiffPairsOfAnUnsortedArray, SAMPLE1);

SIMPLE_TEST(MinDiffPairsOfAnUnsortedArray, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(MinDiffPairsOfAnUnsortedArray, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(MinDiffPairsOfAnUnsortedArray, TestSAMPLE3, EXPECTED3, SAMPLE3);
