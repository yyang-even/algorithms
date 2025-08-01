#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Bitwise ORs of Subarrays
 *              https://leetcode.com/problems/bitwise-ors-of-subarrays/
 *
 * Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays
 * of arr.
 * The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a
 * subarray of one integer is that integer.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * @tags    #DP #hash-table #frontier-set
 */
auto BitwiseOrsOfSubarrays(const ArrayType &arr) {
    std::unordered_set<int> result;
    std::unordered_set<int> prev;

    for (const auto n : arr) {
        std::unordered_set<int> curr {n};
        for (const auto m : prev) {
            curr.insert(m | n);
        }

        result.insert(curr.cbegin(), curr.cend());

        prev = std::move(curr);
    }

    return result.size();
}

} //namespace


const ArrayType SAMPLE1 = {0};
const ArrayType SAMPLE2 = {1, 1, 2};
const ArrayType SAMPLE3 = {1, 2, 4};


THE_BENCHMARK(BitwiseOrsOfSubarrays, SAMPLE1);

SIMPLE_TEST(BitwiseOrsOfSubarrays, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(BitwiseOrsOfSubarrays, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(BitwiseOrsOfSubarrays, TestSAMPLE3, 6, SAMPLE3);
