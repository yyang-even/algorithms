#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::multiset<ArrayType>;

/** Non-decreasing Subsequences
 *
 * @reference   https://leetcode.com/problems/non-decreasing-subsequences/
 *
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the
 * given array with at least two elements. You may return the answer in any order.
 */
void NondecreasingSubsequences(const ArrayType &nums,
                               const std::size_t start,
                               ArrayType &current,
                               OutputType &result) {
    if (current.size() > 1) {
        result.insert(current);
    }

    std::unordered_set<int> seen;
    for (auto i = start; i < nums.size(); ++i) {
        if ((current.empty() or nums[i] >= current.back()) and
            (seen.find(nums[i]) == seen.cend())) {
            current.push_back(nums[i]);
            NondecreasingSubsequences(nums, i + 1, current, result);
            current.pop_back();
            seen.insert(nums[i]);
        }
    }
}

inline auto NondecreasingSubsequences(const ArrayType &nums) {
    ArrayType current;
    OutputType result;

    NondecreasingSubsequences(nums, 0, current, result);

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {4, 6, 7, 7};
const OutputType EXPECTED1 = {
    {4, 6}, {4, 6, 7}, {4, 6, 7, 7}, {4, 7}, {4, 7, 7}, {6, 7}, {6, 7, 7}, {7, 7}};

const ArrayType SAMPLE2 = {4, 4, 3, 2, 1};
const OutputType EXPECTED2 = {{4, 4}};

const ArrayType SAMPLE3 = {1, 2, 1, 1};
const OutputType EXPECTED3 = {{1, 1}, {1, 1, 1}, {1, 2}};


THE_BENCHMARK(NondecreasingSubsequences, SAMPLE1);

SIMPLE_TEST(NondecreasingSubsequences, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(NondecreasingSubsequences, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(NondecreasingSubsequences, TestSAMPLE3, EXPECTED3, SAMPLE3);
