#include "common_header.h"


namespace {

using ArrayType = std::vector<long long>;

/**
 * @reference   Minimum Operations to Make All Array Elements Equal
 *              https://leetcode.com/problems/minimum-operations-to-make-all-array-elements-equal/
 *
 * You are given an array nums consisting of positive integers.
 * You are also given an integer array queries of size m. For the ith query, you want to make all of the
 * elements of nums equal to queries[i]. You can perform the following operation on the array any number
 * of times:
 *  Increase or decrease an element of the array by 1.
 * Return an array answer of size m where answer[i] is the minimum number of operations to make all
 * elements of nums equal to queries[i].
 * Note that after each query the array is reset to its original state.
 *
 * @tags    #sorting #prefix-sum #binary-search
 */
auto OperationsMakeElementsEqual(ArrayType nums, const ArrayType &queries) {
    std::sort(nums.begin(), nums.end());
    std::vector<long long> prefix_sum {0};

    for (const auto n : nums) {
        prefix_sum.push_back(prefix_sum.back() + n);
    }

    std::vector<long long> result;
    for (const auto q : queries) {
        const auto iter = std::lower_bound(nums.cbegin(), nums.cend(), q);

        const auto i = iter - nums.cbegin();
        const auto left_sum = prefix_sum[i];
        const auto right_sum = prefix_sum.back() - prefix_sum[i];
        const auto right_size = nums.size() - i;
        result.push_back(q * i - left_sum + right_sum - q * right_size);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {3, 1, 6, 8};
const ArrayType SAMPLE1Q = {1, 5};
const ArrayType EXPECTED1 = {14, 10};

const ArrayType SAMPLE2 = {2, 9, 6, 3};
const ArrayType SAMPLE2Q = {10};
const ArrayType EXPECTED2 = {20};


THE_BENCHMARK(OperationsMakeElementsEqual, SAMPLE1, SAMPLE1Q);

SIMPLE_TEST(OperationsMakeElementsEqual, TestSAMPLE1, EXPECTED1, SAMPLE1, SAMPLE1Q);
SIMPLE_TEST(OperationsMakeElementsEqual, TestSAMPLE2, EXPECTED2, SAMPLE2, SAMPLE2Q);
