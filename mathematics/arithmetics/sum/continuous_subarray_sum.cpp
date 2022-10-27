#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Continuous Subarray Sum
 *
 * @reference   https://leetcode.com/problems/continuous-subarray-sum/
 *
 * Given an integer array nums and an integer k, return true if nums has a continuous subarray of size
 * at least two whose elements sum up to a multiple of k, or false otherwise.
 * An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a
 * multiple of k.
 */
auto ContinuousSubarraySum(const ArrayType &nums, const int k) {
    long sum = 0;
    std::unordered_map<int, std::size_t> seen_sums {{0, 0}};

    for (std::size_t i = 0; i < nums.size(); ++i) {
        sum += nums[i];

        const auto [iter, inserted] = seen_sums.emplace(sum % k, i + 1);
        if (not inserted and iter->second < i) {
            return true;
        }
    }

    return false;
}

} //namespace


const ArrayType SAMPLE1 = {23, 2, 4, 6, 7};
const ArrayType SAMPLE2 = {23, 2, 6, 4, 7};
const ArrayType SAMPLE3 = {0};
const ArrayType SAMPLE4 = {23, 2, 4, 6, 6};


THE_BENCHMARK(ContinuousSubarraySum, SAMPLE1, 6);

SIMPLE_TEST(ContinuousSubarraySum, TestSAMPLE1, true, SAMPLE1, 6);
SIMPLE_TEST(ContinuousSubarraySum, TestSAMPLE2, true, SAMPLE2, 6);
SIMPLE_TEST(ContinuousSubarraySum, TestSAMPLE3, false, SAMPLE2, 13);
SIMPLE_TEST(ContinuousSubarraySum, TestSAMPLE4, false, SAMPLE3, 1);
SIMPLE_TEST(ContinuousSubarraySum, TestSAMPLE5, true, SAMPLE4, 7);
