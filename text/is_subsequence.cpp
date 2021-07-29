#include "common_header.h"


namespace {

/** Given two strings, find if first string is a subsequence of second
 *
 * @reference   https://www.geeksforgeeks.org/given-two-strings-find-first-string-subsequence-second/
 *
 * Given two strings str1 and str2, find if str1 is a subsequence of str2. A subsequence
 * is a sequence that can be derived from another sequence by deleting some elements
 * without changing the order of the remaining elements. Expected time complexity is
 * linear.
 *
 * @reference   Is Subsequence
 *              https://leetcode.com/problems/is-subsequence/
 *
 * Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
 * A subsequence of a string is a new string that is formed from the original string by
 * deleting some (can be none) of the characters without disturbing the relative
 * positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while
 * "aec" is not).
 * Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 109,
 * and you want to check one by one to see if t has its subsequence. In this scenario,
 * how would you change your code?
 */
constexpr auto
isSubsequence(const std::string_view sub, const std::string_view text) {
    assert(sub.size() <= text.size());
    assert(not sub.empty());

    std::size_t i = 0;
    for (const auto c : text) {
        if (sub[i] == c) {
            ++i;
        }
    }

    return i == sub.size();
}

}//namespace


THE_BENCHMARK(isSubsequence, "AXY", "ADXCPY");

SIMPLE_TEST(isSubsequence, TestSAMPLE1, true, "AXY", "ADXCPY");
SIMPLE_TEST(isSubsequence, TestSAMPLE2, false, "AXY", "YADXCP");
SIMPLE_TEST(isSubsequence, TestSAMPLE3, true, "gksrek", "geeksforgeeks");
