#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<int>;

/** Longest Harmonious Subsequence
 *
 * @reference   https://leetcode.com/problems/longest-harmonious-subsequence/
 *
 * We define a harmonious array as an array where the difference between its maximum
 * value and its minimum value is exactly 1. Given an integer array nums, return the
 * length of its longest harmonious subsequence among all its possible subsequences.
 * A subsequence of array is a sequence that can be derived from the array by deleting
 * some or no elements without changing the order of the remaining elements.
 */
auto LongestHarmoniousSubsequence_Sorting(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    const auto N = nums.size();
    std::size_t max_length = 0;
    std::size_t left = 0;
    for (std::size_t right = 0; right < N; ++right) {
        while (nums[right] - nums[left] > 1) {
            ++left;
        }

        if (nums[right] - nums[left] == 1) {
            max_length = std::max(max_length, right - left + 1);
        }
    }

    return max_length;
}


auto LongestHarmoniousSubsequence_Hash(const ArrayType &nums) {
    const auto counts = ToFrequencyHashTable(nums);

    int max_length = 0;
    for (const auto [x, c] : counts) {
        const auto iter = counts.find(x + 1);
        if (iter != counts.cend()) {
            max_length = std::max(max_length, c + iter->second);
        }
    }

    return max_length;
}

}//namespace


const ArrayType SAMPLE1 = {1, 3, 2, 2, 5, 2, 3, 7};
const ArrayType SAMPLE2 = {1, 2, 3, 4};
const ArrayType SAMPLE3 = {1, 1, 1, 1};


THE_BENCHMARK(LongestHarmoniousSubsequence_Sorting, SAMPLE1);

SIMPLE_TEST(LongestHarmoniousSubsequence_Sorting, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(LongestHarmoniousSubsequence_Sorting, TestSAMPLE2, 2, SAMPLE2);
SIMPLE_TEST(LongestHarmoniousSubsequence_Sorting, TestSAMPLE3, 0, SAMPLE3);


THE_BENCHMARK(LongestHarmoniousSubsequence_Hash, SAMPLE1);

SIMPLE_TEST(LongestHarmoniousSubsequence_Hash, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(LongestHarmoniousSubsequence_Hash, TestSAMPLE2, 2, SAMPLE2);
SIMPLE_TEST(LongestHarmoniousSubsequence_Hash, TestSAMPLE3, 0, SAMPLE3);
