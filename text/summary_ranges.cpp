#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::vector<std::string>;

/** Summary Ranges
 *
 * @reference   https://leetcode.com/problems/summary-ranges/
 *
 * You are given a sorted unique integer array nums. Return the smallest sorted list of
 * ranges that cover all the numbers in the array exactly. That is, each element of nums
 * is covered by exactly one of the ranges, and there is no integer x such that x is in
 * one of the ranges but not in nums. Each range [a,b] in the list should be output as:
 *  "a->b" if a != b
 *  "a" if a == b
 */
auto SummaryRanges(const ArrayType &nums) {
    std::size_t left = 0;
    std::size_t right = 1;
    OutputType results;
    while (left < nums.size()) {
        while (right < nums.size() and nums[right - 1] + 1 == nums[right]) {
            ++right;
        }

        results.push_back(std::to_string(nums[left]));
        if (left < right - 1) {
            results.back().append("->");
            results.back().append(std::to_string(nums[right - 1]));
        }
        left = right++;
    }

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {0, 1, 2, 4, 5, 7};
const OutputType EXPECTED1 = {"0->2", "4->5", "7"};

const ArrayType SAMPLE2 = {0, 2, 3, 4, 6, 8, 9};
const OutputType EXPECTED2 = {"0", "2->4", "6", "8->9"};


THE_BENCHMARK(SummaryRanges, SAMPLE1);

SIMPLE_TEST(SummaryRanges, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SummaryRanges, TestSAMPLE2, EXPECTED2, SAMPLE2);
