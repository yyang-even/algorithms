#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Count Special Triplets
 *              https://leetcode.com/problems/count-special-triplets/
 *
 * You are given an integer array nums.
 *
 * A special triplet is defined as a triplet of indices (i, j, k) such that:
 *  0 <= i < j < k < n, where n = nums.length
 *  nums[i] == nums[j] * 2
 *  nums[k] == nums[j] * 2
 *  Return the total number of special triplets in the array.
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * @tags    #hash-table #binary-search
 */
auto CountSpecialTriplets(const ArrayType &nums) {
    std::unordered_map<int, int> total_counts;
    for (const auto n : nums) {
        ++total_counts[n];
    }

    std::unordered_map<int, int> left_counts;
    unsigned long long result = 0;
    for (const auto n : nums) {
        const auto other = n * 2;
        if (left_counts[other]) {
            const unsigned long long left = left_counts[other];
            const unsigned long long right = total_counts[other] - left - (n == 0);
            result += left * right;
        }

        ++left_counts[n];
    }

    return result % LARGE_PRIME;
}


auto CountSpecialTriplets_BinarySearch(const ArrayType &nums) {
    std::unordered_map<int, std::vector<int>> position_map;
    const int N = nums.size();
    for (int i = 0; i < N; ++i) {
        position_map[nums[i]].push_back(i);
    }

    unsigned long long result = 0;
    for (int i = 1; i < N - 1; ++i) {
        const auto target = nums[i] * 2;
        const auto &positions = position_map[target];
        if (positions.size() <= 1 or positions.front() >= i) {
            continue;
        }

        const auto split = std::upper_bound(positions.cbegin(), positions.cend(), i);
        const unsigned long long left = split - positions.cbegin() - (target == 0);
        const unsigned long long right = positions.cend() - split;

        result += left * right;
    }

    return result % LARGE_PRIME;
}

} //namespace


const ArrayType SAMPLE1 = {6, 3, 6};
const ArrayType SAMPLE2 = {0, 1, 0, 0};
const ArrayType SAMPLE3 = {8, 4, 2, 8, 4};


THE_BENCHMARK(CountSpecialTriplets, SAMPLE1);

SIMPLE_TEST(CountSpecialTriplets, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(CountSpecialTriplets, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(CountSpecialTriplets, TestSAMPLE3, 2, SAMPLE3);


THE_BENCHMARK(CountSpecialTriplets_BinarySearch, SAMPLE1);

SIMPLE_TEST(CountSpecialTriplets_BinarySearch, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(CountSpecialTriplets_BinarySearch, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(CountSpecialTriplets_BinarySearch, TestSAMPLE3, 2, SAMPLE3);
