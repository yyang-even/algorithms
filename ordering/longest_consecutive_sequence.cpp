#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Longest Consecutive Sequence
 *              https://leetcode.com/problems/longest-consecutive-sequence/
 *
 * Given an unsorted array of integers nums, return the length of the longest consecutive elements
 * sequence.
 * You must write an algorithm that runs in O(n) time.
 *
 * @tags    #sort #hash-table #disjoint-set
 */
auto LongestConsecutiveSequence_Sort(ArrayType nums) {
    if (nums.empty()) {
        return 0;
    }

    std::sort(nums.begin(), nums.end());

    int length = 1;
    int result = 1;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] != nums[i - 1]) {
            if (nums[i] == nums[i - 1] + 1) {
                ++length;
            } else {
                result = std::max(result, length);
                length = 1;
            }
        }
    }

    return std::max(result, length);
}


auto LongestConsecutiveSequence_Set(const ArrayType &nums) {
    std::unordered_set<int> s(nums.cbegin(), nums.cend());

    int result = 0;
    for (const auto n : nums) {
        if (s.find(n - 1) == s.cend()) {
            int end = n + 1;
            for (; s.find(end) != s.cend(); ++end)
                ;
            result = std::max(result, end - n);
        }
    }

    return result;
}


inline auto Find(const std::unordered_map<int, int> &m, const int x) {
    const auto iter = m.find(x);
    return iter == m.cend() ? 0 : iter->second;
}

auto LongestConsecutiveSequence_UnionFind(const ArrayType &nums) {
    std::unordered_map<int, int> boundary;
    int result = 0;

    for (const auto n : nums) {
        if (const auto [iter, inserted] = boundary.emplace(n, 1); inserted) {
            const auto left = Find(boundary, n - 1);
            const auto right = Find(boundary, n + 1);
            const auto total = left + right + 1;

            iter->second = total;

            result = std::max(result, total);

            boundary[n - left] = total;
            boundary[n + right] = total;
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {};
const ArrayType SAMPLE2 = {100, 4, 200, 1, 3, 2};
const ArrayType SAMPLE3 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};


THE_BENCHMARK(LongestConsecutiveSequence_Sort, SAMPLE1);

SIMPLE_TEST(LongestConsecutiveSequence_Sort, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(LongestConsecutiveSequence_Sort, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(LongestConsecutiveSequence_Sort, TestSAMPLE3, 9, SAMPLE3);


THE_BENCHMARK(LongestConsecutiveSequence_UnionFind, SAMPLE1);

SIMPLE_TEST(LongestConsecutiveSequence_UnionFind, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(LongestConsecutiveSequence_UnionFind, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(LongestConsecutiveSequence_UnionFind, TestSAMPLE3, 9, SAMPLE3);


THE_BENCHMARK(LongestConsecutiveSequence_Set, SAMPLE1);

SIMPLE_TEST(LongestConsecutiveSequence_Set, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(LongestConsecutiveSequence_Set, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(LongestConsecutiveSequence_Set, TestSAMPLE3, 9, SAMPLE3);
