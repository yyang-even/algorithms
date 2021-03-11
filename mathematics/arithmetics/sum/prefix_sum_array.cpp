#include "common_header.h"

#include "prefix_sum_array.h"


namespace {

using ArrayType = std::vector<int>;
using RangeType = std::pair<ArrayType::size_type, ArrayType::size_type>;
using RangeArray = std::vector<RangeType>;


/**
 * @reference   Constant time range add operation on an array
 *              https://www.geeksforgeeks.org/constant-time-range-add-operation-array/
 *
 * Given an array of size N which is initialized with all zeros. We are given many range
 * add queries, which should be applied to this array. We need to print final updated
 * array as our result.
 */
auto RangesOfAdditions(const ArrayType::size_type size, const ArrayType::value_type d,
                       const RangeArray &ranges) {
    ArrayType elements(size, 0);

    for (const auto [left, right] : ranges) {
        elements[left] += d;
        if (right + 1 < size) {
            elements[right + 1] -= d;
        }
    }

    return PrefixSumArray(std::move(elements));
}


/**
 * reference    Print modified array after multiple array range increment operations
 *              https://www.geeksforgeeks.org/print-modified-array-multiple-array-range-increment-operations/
 *
 * Given an array containing n integers and a value d. m queries are given. Each query
 * has two values start and end. For each query, the problem is to increment the values
 * from the start to end index in the given array by the given value d. A linear time
 * efficient solution is required for handling such multiple queries.
 */
auto RangesOfAdditions(const ArrayType &elements, const ArrayType::value_type d,
                       const RangeArray &ranges) {
    auto sums = RangesOfAdditions(elements.size(), d, ranges);

    std::transform(sums.cbegin(), sums.cend(), elements.cbegin(), sums.begin(),
                   std::plus<ArrayType::value_type> {});

    return sums;
}


/**
 * @reference   Prefix Sum Array – Implementation and Applications in Competitive Programming
 *              https://www.geeksforgeeks.org/prefix-sum-array-implementation-applications-competitive-programming/
 *
 * Consider an array of size n with all initial values as 0. Perform given 'm' add
 * operations from index 'a' to 'b' and evaluate highest element in array. An add
 * operation adds 100 to all elements from a to b (both inclusive).
 *
 * @reference   Maximum occurred integer in n ranges
 *              https://www.geeksforgeeks.org/maximum-occurred-integer-n-ranges/
 * @reference   Maximum occurred integer in n ranges | Set-2
 *              https://www.geeksforgeeks.org/maximum-occurred-integer-in-n-ranges-set-2/
 *
 * Given n ranges of the form L and R, the task is to find the maximum occurred integer
 * in all the ranges. If more than one such integer exists, print the smallest one.
 * Note: 1 <= L <= R <= 10^6
 *
 * @reference   Maximum value in an array after m range increment operations
 *              https://www.geeksforgeeks.org/maximum-value-array-m-range-increment-operations/
 *
 * Consider an array of size n with all initial values as 0, we need to perform following
 * m range increment operations.
 *      increment(a, b, k) : Increment values from 'a' to 'b' by 'k'.
 * After m operations, we need to calculate the maximum of the values in the array.
 */
auto MaxAfterRangesOfAdditions(const ArrayType::size_type size,
                               const RangeArray &ranges) {
    const auto prefix_sums = RangesOfAdditions(size, 100, ranges);
    return *std::max_element(prefix_sums.cbegin(), prefix_sums.cend());
}

}//namespace


const ArrayType SAMPLE1 = {10, 20, 10, 5, 15};
const ArrayType EXPECTED1 = {10, 30, 40, 45, 60};

const ArrayType SAMPLE2 = {10, 4, 16, 20};
const ArrayType EXPECTED2 = {10, 14, 30, 50};


SIMPLE_BENCHMARK(PrefixSumArray, Sample1, SAMPLE1);

SIMPLE_TEST(PrefixSumArray, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(PrefixSumArray, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = {3, 5, 4, 8, 6, 1};
const RangeArray SAMPLE_RANGES3 = {{0, 3}, {4, 5}, {1, 4}, {0, 1}, {2, 5}};
const ArrayType EXPECTED3 = {7, 11, 10, 14, 12, 5};

const RangeArray SAMPLE_RANGES4 = {{0, 2}, {1, 5}, {2, 3}};
const ArrayType EXPECTED4 = {100, 200, 300, 200, 100, 100};

const RangeArray SAMPLE_RANGES5 = {{2, 4}, {1, 3}, {1, 2}};


SIMPLE_BENCHMARK(RangesOfAdditions, Sample1, SAMPLE3, 2, SAMPLE_RANGES3);

SIMPLE_TEST(RangesOfAdditions, TestSAMPLE3, EXPECTED3, SAMPLE3, 2, SAMPLE_RANGES3);


SIMPLE_BENCHMARK(RangesOfAdditions, Sample2, 6, 100, SAMPLE_RANGES4);

SIMPLE_TEST(RangesOfAdditions, TestSAMPLE4, EXPECTED4, 6, 100, SAMPLE_RANGES4);


SIMPLE_BENCHMARK(MaxAfterRangesOfAdditions, Sample1, 5, SAMPLE_RANGES5);

SIMPLE_TEST(MaxAfterRangesOfAdditions, TestSAMPLE5, 300, 5, SAMPLE_RANGES5);
