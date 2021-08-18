#include "common_header.h"

#include "hash/hash.h"


namespace {

/** Minimum Window Substring
 *
 * @reference   https://leetcode.com/problems/minimum-window-substring/
 *
 * Given two strings s and t of lengths m and n respectively, return the minimum window
 * substring of s such that every character in t (including duplicates) is included in
 * the window. If there is no such substring, return the empty string "". The testcases
 * will be generated such that the answer is unique. A substring is a contiguous sequence
 * of characters within the string.
 * Follow up: Could you find an algorithm that runs in O(m + n) time?
 */
std::string_view
MinimumWindowSubstring_TwoPointer(const std::string_view s, const std::string_view t) {
    if (s.empty() or t.empty()) {
        return "";
    }

    const auto t_counts = ToFrequencyHashTable(t);

    std::size_t left = 0, right = 0;
    std::size_t formed_size = 0;
    std::unordered_map<char, int> window_counts;
    int min_length = -1;
    int result_left = 0;

    for (; right < s.size(); ++right) {
        const auto c = s[right];
        if (const auto iter = t_counts.find(c);
            iter != t_counts.cend()) {
            if (++window_counts[c] == iter->second) {
                ++formed_size;
            }

            while (left <= right and formed_size == t_counts.size()) {
                const int length = right - left + 1;
                if (min_length == -1 or length < min_length) {
                    min_length = length;
                    result_left = left;
                }

                const auto c = s[left++];
                if (const auto iter = t_counts.find(c);
                    iter != t_counts.cend()) {
                    if (--window_counts[c] < iter->second) {
                        --formed_size;
                    }
                }
            }
        }
    }

    return min_length == -1 ? "" : s.substr(result_left, min_length);
}


std::string_view
MinimumWindowSubstring(const std::string_view s, const std::string_view t) {
    if (s.empty() or t.empty()) {
        return "";
    }

    int remaining[128] = {};
    int required = t.size();
    for (const int c : t) {
        ++remaining[c];
    }

    std::size_t min_length = INT_MAX, left = 0, result_left = 0, right = 0;
    while (right <= s.size() and left < s.size()) {
        if (required) {
            if (right == s.size()) {
                break;
            }
            const int c = s[right++];
            if (--remaining[c] >= 0) {
                --required;
            }
        } else {
            if (right - left < min_length) {
                min_length = right - left;
                result_left = left;
            }
            const int c = s[left++];
            if (++remaining[c] > 0) {
                ++required;
            }
        }
    }

    return min_length == INT_MAX ? "" : s.substr(result_left, min_length);
}

}//namespace


THE_BENCHMARK(MinimumWindowSubstring_TwoPointer, "ADOBECODEBANC", "ABC");

SIMPLE_TEST(MinimumWindowSubstring_TwoPointer, TestSAMPLE1, "BANC",
            "ADOBECODEBANC", "ABC");
SIMPLE_TEST(MinimumWindowSubstring_TwoPointer, TestSAMPLE2, "a", "a", "a");
SIMPLE_TEST(MinimumWindowSubstring_TwoPointer, TestSAMPLE3, "", "a", "aa");


THE_BENCHMARK(MinimumWindowSubstring, "ADOBECODEBANC", "ABC");

SIMPLE_TEST(MinimumWindowSubstring, TestSAMPLE1, "BANC",
            "ADOBECODEBANC", "ABC");
SIMPLE_TEST(MinimumWindowSubstring, TestSAMPLE2, "a", "a", "a");
SIMPLE_TEST(MinimumWindowSubstring, TestSAMPLE3, "", "a", "aa");
