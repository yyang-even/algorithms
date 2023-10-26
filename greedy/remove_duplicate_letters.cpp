#include "common_header.h"


namespace {

/** Remove Duplicate Letters
 *
 * @reference   https://leetcode.com/problems/remove-duplicate-letters/
 *
 * Given a string s, remove duplicate letters so that every letter appears once and only once. You must
 * make sure your result is the smallest in lexicographical order among all possible results.
 *
 * @reference   Smallest Subsequence of Distinct Characters
 *              https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
 *
 * Given a string s, return the lexicographically smallest subsequence of s that contains all the
 * distinct characters of s exactly once.
 */
std::string SmallestSubsequenceDistinctChars(const std::string_view s) {
    if (s.empty()) {
        return "";
    }

    std::vector<int> counts(256, 0);
    for (const int c : s) {
        ++counts[c];
    }

    std::size_t selected = 0;
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] < s[selected]) {
            selected = i;
        }
        if (counts[s[i]]-- == 1) {
            break;
        }
    }

    std::string result(s.substr(selected + 1));
    result.erase(std::remove(result.begin(), result.end(), s[selected]), result.end());
    return s[selected] + SmallestSubsequenceDistinctChars(result);
}


auto SmallestSubsequenceDistinctChars_Stack(const std::string_view s) {
    std::size_t last[256] = {};
    for (std::size_t i = 0; i < s.size(); ++i) {
        const int c = s[i];
        last[c] = i;
    }

    bool seen[256] = {};
    std::string result;
    for (std::size_t i = 0; i < s.size(); ++i) {
        const int c = s[i];
        if (seen[c]) {
            continue;
        }
        seen[c] = true;

        while (not result.empty() and result.back() > c and
               i < last[static_cast<int>(result.back())]) {
            seen[static_cast<int>(result.back())] = false;
            result.pop_back();
        }

        result.push_back(c);
    }

    return result;
}

} //namespace


THE_BENCHMARK(SmallestSubsequenceDistinctChars, "bcabc");

SIMPLE_TEST(SmallestSubsequenceDistinctChars, TestSAMPLE1, "abc", "bcabc");
SIMPLE_TEST(SmallestSubsequenceDistinctChars, TestSAMPLE2, "acdb", "cbacdcbc");
SIMPLE_TEST(SmallestSubsequenceDistinctChars, TestSAMPLE3, "abc", "abacb");


THE_BENCHMARK(SmallestSubsequenceDistinctChars_Stack, "bcabc");

SIMPLE_TEST(SmallestSubsequenceDistinctChars_Stack, TestSAMPLE1, "abc", "bcabc");
SIMPLE_TEST(SmallestSubsequenceDistinctChars_Stack, TestSAMPLE2, "acdb", "cbacdcbc");
SIMPLE_TEST(SmallestSubsequenceDistinctChars_Stack, TestSAMPLE3, "abc", "abacb");
