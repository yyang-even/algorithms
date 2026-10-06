#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Pairs of Songs With Total Durations Divisible by 60
 *              https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/
 *
 * You are given a list of songs where the ith song has a duration of time[i] seconds.
 * Return the number of pairs of songs for which their total duration in seconds is divisible by 60.
 * Formally, we want the number of indices i, j such that i < j with (time[i] + time[j]) % 60 == 0.
 *
 * @tags    #hash-table #modulo
 */
auto NumPairsDivisibleBy60(const ArrayType &durations) {
    int counts[60] = {};
    for (const auto n : durations) {
        ++counts[n % 60];
    }

    int result = counts[0] * (counts[0] - 1) / 2;
    for (int i = 1; i < 30; ++i) {
        result += counts[i] * counts[60 - i];
    }
    result += counts[30] * (counts[30] - 1) / 2;

    return result;
}


/**
 * @reference   Destroy Sequential Targets
 *              https://leetcode.com/problems/destroy-sequential-targets/
 *
 * You are given a 0-indexed array nums consisting of positive integers, representing targets on a
 * number line. You are also given an integer space.
 * You have a machine which can destroy targets. Seeding the machine with some nums[i] allows it to
 * destroy all targets with values that can be represented as nums[i] + c * space, where c is any
 * non-negative integer. You want to destroy the maximum number of targets in nums.
 * Return the minimum value of nums[i] you can seed the machine with to destroy the maximum number of
 * targets.
 *
 * @tags    #hash-table #min-max-element #modulo
 */

} //namespace


const ArrayType SAMPLE1 = {30, 20, 150, 100, 40};
const ArrayType SAMPLE2 = {60, 60, 60};


THE_BENCHMARK(NumPairsDivisibleBy60, SAMPLE1);

SIMPLE_TEST(NumPairsDivisibleBy60, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(NumPairsDivisibleBy60, TestSAMPLE2, 3, SAMPLE2);
