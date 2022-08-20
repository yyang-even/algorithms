#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Split Array into Consecutive Subsequences
 *
 * @reference   https://leetcode.com/problems/split-array-into-consecutive-subsequences/
 *
 * You are given an integer array nums that is sorted in non-decreasing order.
 * Determine if it is possible to split nums into one or more subsequences such that both of the
 * following conditions are true:
 *  Each subsequence is a consecutive increasing sequence (i.e. each integer is exactly one more than
 *      the previous integer).
 *  All subsequences have a length of 3 or more.
 * Return true if you can split nums according to the above conditions, or false otherwise.
 * A subsequence of an array is a new array that is formed from the original array by deleting some (can
 * be none) of the elements without disturbing the relative positions of the remaining elements. (i.e.,
 * [1,3,5] is a subsequence of [1,2,3,4,5] while [1,3,2] is not).
 */
auto SplitArrayIntoConsecutiveSubsequences_ThreeMap(const ArrayType &nums) {
    std::unordered_map<int, int> ones;
    std::unordered_map<int, int> twos;
    std::unordered_map<int, int> more;

    for (const auto n : nums) {
        if (const auto iter = ones.find(n - 1); iter != ones.cend()) {
            if (iter->second-- == 1)
                ones.erase(iter);
            twos[n]++;
        } else if (const auto iter = twos.find(n - 1); iter != twos.cend()) {
            if (iter->second-- == 1)
                twos.erase(iter);
            more[n]++;
        } else if (const auto iter = more.find(n - 1); iter != more.cend()) {
            if (iter->second-- == 1)
                more.erase(iter);
            more[n]++;
        } else {
            ones[n]++;
        }
    }

    return ones.empty() and twos.empty();
}


auto SplitArrayIntoConsecutiveSubsequences_TwoMap(const ArrayType &nums) {
    std::unordered_map<int, int> left;
    for (const auto n : nums) {
        ++left[n];
    }

    std::unordered_map<int, int> end;
    for (const auto n : nums) {
        if (left[n]-- <= 0) {
            continue;
        }

        if (end[n - 1] > 0) {
            --end[n - 1];
            ++end[n];
        } else if (left[n + 1] > 0 and left[n + 2] > 0) {
            --left[n + 1];
            --left[n + 2];
            ++end[n + 2];
        } else {
            return false;
        }
    }

    return true;
}


auto SplitArrayIntoConsecutiveSubsequences(const ArrayType &nums) {
    int prev = INT_MIN;
    int prev_count_one = 0;
    int prev_count_two = 0;
    int prev_count_more = 0;

    for (std::size_t i = 0; i < nums.size();) {
        const auto curr = nums[i];
        int count = 1;
        int count_one = 0;
        int count_two = 0;
        int count_more = 0;
        for (++i; i < nums.size() and curr == nums[i]; ++i) {
            ++count;
        }

        if (curr != prev + 1) {
            if (prev_count_one or prev_count_two) {
                return false;
            }

            count_one = count;
            count_two = 0;
            count_more = 0;

        } else {
            if (count < prev_count_one + prev_count_two) {
                return false;
            }

            count_one = std::max(0, count - (prev_count_one + prev_count_two + prev_count_more));
            count_two = prev_count_one;
            count_more = prev_count_two +
                         std::min(prev_count_more, count - (prev_count_one + prev_count_two));
        }

        prev = curr;
        prev_count_one = count_one;
        prev_count_two = count_two;
        prev_count_more = count_more;
    }

    return prev_count_one == 0 and prev_count_two == 0;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 3, 4, 5};
const ArrayType SAMPLE2 = {1, 2, 3, 3, 4, 4, 5, 5};
const ArrayType SAMPLE3 = {1, 2, 3, 4, 4, 5};


THE_BENCHMARK(SplitArrayIntoConsecutiveSubsequences_ThreeMap, SAMPLE1);

SIMPLE_TEST(SplitArrayIntoConsecutiveSubsequences_ThreeMap, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(SplitArrayIntoConsecutiveSubsequences_ThreeMap, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(SplitArrayIntoConsecutiveSubsequences_ThreeMap, TestSAMPLE3, false, SAMPLE3);


THE_BENCHMARK(SplitArrayIntoConsecutiveSubsequences_TwoMap, SAMPLE1);

SIMPLE_TEST(SplitArrayIntoConsecutiveSubsequences_TwoMap, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(SplitArrayIntoConsecutiveSubsequences_TwoMap, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(SplitArrayIntoConsecutiveSubsequences_TwoMap, TestSAMPLE3, false, SAMPLE3);


THE_BENCHMARK(SplitArrayIntoConsecutiveSubsequences, SAMPLE1);

SIMPLE_TEST(SplitArrayIntoConsecutiveSubsequences, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(SplitArrayIntoConsecutiveSubsequences, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(SplitArrayIntoConsecutiveSubsequences, TestSAMPLE3, false, SAMPLE3);
