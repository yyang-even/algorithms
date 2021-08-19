#include "common_header.h"

#include "prefix_sum_array.h"


namespace {

using ArrayType = std::vector<int>;
using RangeType = std::pair<ArrayType::size_type, ArrayType::size_type>;
using RangeArray = std::vector<RangeType>;
using UpdateType = std::tuple<std::size_t, std::size_t, int>;
using UpdateArray = std::vector<UpdateType>;

void update(ArrayType &elements, const std::size_t left, const std::size_t right,
            const int increment) {
    elements[left] += increment;
    if (right + 1 < elements.size()) {
        elements[right + 1] -= increment;
    }
}

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
        update(elements, left, right, d);
    }

    return PrefixSumArray(std::move(elements));
}


/**
 * @reference   Range Addition
 *              https://xiaoguan.gitbooks.io/leetcode/content/LeetCode/370-range-addition-medium.html
 *
 * Assume you have an array of length n initialized with all 0's and are given k update
 * operations. Each operation is represented as a triplet: [startIndex, endIndex, inc]
 * which increments each element of subarray A[startIndex ... endIndex] (startIndex and
 * endIndex inclusive) with inc. Return the modified array after all k operations were
 * executed.
 */
auto RangeAddition(const std::size_t N, const UpdateArray &updates) {
    ArrayType elements(N, 0);

    for (const auto [left, right, inc] : updates) {
        update(elements, left, right, inc);
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
inline auto
RangesOfAdditions(const ArrayType &elements, const ArrayType::value_type d,
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
inline auto MaxAfterRangesOfAdditions(const ArrayType::size_type size,
                                      const RangeArray &ranges) {
    const auto prefix_sums = RangesOfAdditions(size, 100, ranges);
    return *std::max_element(prefix_sums.cbegin(), prefix_sums.cend());
}


/**
 * @reference   Range Addition II
 *              https://leetcode.com/problems/range-addition-ii/
 *
 * You are given an m x n matrix M initialized with all 0's and an array of operations
 * ops, where ops[i] = [ai, bi] means M[x][y] should be incremented by one for all
 * 0 <= x < ai and 0 <= y < bi. Count and return the number of maximum integers in the
 * matrix after performing all the operations.
 */
auto
CountMaxAfterRangeAddition(std::size_t m, std::size_t n, const RangeArray &operations) {
    for (const auto [i, j] : operations) {
        m = std::min(m, i);
        n = std::min(n, j);
    }

    return m * n;
}

}//namespace


const ArrayType SAMPLE1 = {10, 20, 10, 5, 15};
const ArrayType EXPECTED1 = {10, 30, 40, 45, 60};

const ArrayType SAMPLE2 = {10, 4, 16, 20};
const ArrayType EXPECTED2 = {10, 14, 30, 50};


THE_BENCHMARK(PrefixSumArray, SAMPLE1);

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


THE_BENCHMARK(MaxAfterRangesOfAdditions, 5, SAMPLE_RANGES5);

SIMPLE_TEST(MaxAfterRangesOfAdditions, TestSAMPLE5, 300, 5, SAMPLE_RANGES5);


const UpdateArray SAMPLE1U = {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}};
const ArrayType EXPECTED1U = {-2, 0, 3, 5, 3};


THE_BENCHMARK(RangeAddition, 5, SAMPLE1U);

SIMPLE_TEST(RangeAddition, TestSAMPLE1, EXPECTED1U, 5, SAMPLE1U);


const RangeArray SAMPLE1o = {{2, 2}, {3, 3}};
const RangeArray SAMPLE2o = {};


THE_BENCHMARK(CountMaxAfterRangeAddition, 3, 3, SAMPLE1o);

SIMPLE_TEST(CountMaxAfterRangeAddition, TestSAMPLE1, 4, 3, 3, SAMPLE1o);
SIMPLE_TEST(CountMaxAfterRangeAddition, TestSAMPLE2, 9, 3, 3, SAMPLE2o);
