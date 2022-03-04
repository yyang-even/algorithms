#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

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
 * Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 10^9,
 * and you want to check one by one to see if t has its subsequence. In this scenario,
 * how would you change your code?
 */
constexpr auto
isSubsequence(const std::string_view sub, const std::string_view text) {
    assert(not sub.empty());

    if (sub.size() > text.size()) {
        return false;
    }

    std::size_t i = 0;
    for (const auto c : text) {
        if (sub[i] == c) {
            ++i;
        }
    }

    return i == sub.size();
}


/** Longest Uncommon Subsequence
 *
 * @reference   Longest Uncommon Subsequence I
 *              https://leetcode.com/problems/longest-uncommon-subsequence-i/
 *
 * Given two strings a and b, return the length of the longest uncommon subsequence
 * between a and b. If the longest uncommon subsequence does not exist, return -1. An
 * uncommon subsequence between two strings is a string that is a subsequence of one but
 * not the other. A subsequence of a string s is a string that can be obtained after
 * deleting any number of characters from s. For example, "abc" is a subsequence of
 * "aebdc" because you can delete the underlined characters in "aebdc" to get "abc".
 * Other subsequences of "aebdc" include "aebdc", "aeb", and "" (empty string).
 */
inline constexpr int
LongestUncommonSubsequence(const std::string_view one, const std::string_view another) {
    if (one == another) {
        return -1;
    }
    return std::max(one.size(), another.size());
}


/**
 * @reference   Longest Uncommon Subsequence II
 *              https://leetcode.com/problems/longest-uncommon-subsequence-ii/
 * @reference   https://xiaoguan.gitbooks.io/leetcode/content/LeetCode/522-longest-uncommon-subsequence-ii-medium.html
 *
 * Given an array of strings strs, return the length of the longest uncommon subsequence
 * between them. If the longest uncommon subsequence does not exist, return -1. An
 * uncommon subsequence between an array of strings is a string that is a subsequence of
 * one string but not the others. A subsequence of a string s is a string that can be
 * obtained after deleting any number of characters from s. For example, "abc" is a
 * subsequence of "aebdc" because you can delete the underlined characters in "aebdc" to
 * get "abc". Other subsequences of "aebdc" include "aebdc", "aeb", and "" (empty string).
 * 1 <= strs[i].length <= 10
 */
int LongestUncommonSubsequenceArray_Sort(ArrayType strs) {
    std::sort(strs.begin(), strs.end(),
    [](const auto lhs, const auto rhs) {
        return lhs.size() > rhs.size();
    });

    const auto N = strs.size();
    for (std::size_t i = 0; i < N; ++i) {
        std::size_t j = 0;
        for (; j < N; ++j) {
            if (i != j and isSubsequence(strs[i], strs[j])) {
                break;
            }
        }
        if (j == N) {
            return strs[i].size();
        }
    }

    return -1;
}


int LongestUncommonSubsequenceArray(const ArrayType &strs) {
    std::size_t result = 0;
    for (std::size_t i = 0; i < strs.size(); ++i) {
        std::size_t j = 0;
        for (; j < strs.size(); ++j) {
            if (i != j and isSubsequence(strs[i], strs[j])) {
                break;
            }
        }
        if (j == strs.size()) {
            result = std::max(result, strs[i].size());
        }
    }

    return result ? result : -1;
}


/**
 * @reference   Long Pressed Name
 *              https://leetcode.com/problems/long-pressed-name/
 *
 * Your friend is typing his name into a keyboard. Sometimes, when typing a character c,
 * the key might get long pressed, and the character will be typed 1 or more times. You
 * examine the typed characters of the keyboard. Return True if it is possible that it
 * was your friends name, with some characters (possibly none) being long pressed.
 */
constexpr auto
LongPressedName(const std::string_view name, const std::string_view typed) {
    if (name.front() != typed.front()) {
        return false;
    }

    std::size_t i = 1;
    std::size_t j = 1;
    for (; j < typed.size(); ++j) {
        if (i < name.size() and name[i] == typed[j]) {
            ++i;
        } else if (typed[j] != typed[j - 1]) {
            return false;
        }
    }

    return i == name.size() and j == typed.size();
}

}//namespace


THE_BENCHMARK(isSubsequence, "AXY", "ADXCPY");

SIMPLE_TEST(isSubsequence, TestSAMPLE1, true, "AXY", "ADXCPY");
SIMPLE_TEST(isSubsequence, TestSAMPLE2, false, "AXY", "YADXCP");
SIMPLE_TEST(isSubsequence, TestSAMPLE3, true, "gksrek", "geeksforgeeks");


THE_BENCHMARK(LongestUncommonSubsequence, "aba", "cdc");

SIMPLE_TEST(LongestUncommonSubsequence, TestSAMPLE1, 3, "aba", "cdc");
SIMPLE_TEST(LongestUncommonSubsequence, TestSAMPLE2, -1, "aaa", "aaa");
SIMPLE_TEST(LongestUncommonSubsequence, TestSAMPLE3, 3, "aa", "aaa");


const ArrayType SAMPLE1 = {"aba", "cdc", "eae"};
const ArrayType SAMPLE2 = {"aaa", "aaa", "aa"};
const ArrayType SAMPLE3 = {"aabbcc", "aabbcc", "cb"};


THE_BENCHMARK(LongestUncommonSubsequenceArray_Sort, SAMPLE1);

SIMPLE_TEST(LongestUncommonSubsequenceArray_Sort, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(LongestUncommonSubsequenceArray_Sort, TestSAMPLE2, -1, SAMPLE2);
SIMPLE_TEST(LongestUncommonSubsequenceArray_Sort, TestSAMPLE3, 2, SAMPLE3);


THE_BENCHMARK(LongestUncommonSubsequenceArray, SAMPLE1);

SIMPLE_TEST(LongestUncommonSubsequenceArray, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(LongestUncommonSubsequenceArray, TestSAMPLE2, -1, SAMPLE2);
SIMPLE_TEST(LongestUncommonSubsequenceArray, TestSAMPLE3, 2, SAMPLE3);


THE_BENCHMARK(LongPressedName, "alex", "aaleex");

SIMPLE_TEST(LongPressedName, TestSAMPLE1, true, "alex", "aaleex");
SIMPLE_TEST(LongPressedName, TestSAMPLE2, false, "saeed", "ssaaedd");
SIMPLE_TEST(LongPressedName, TestSAMPLE3, true, "leelee", "leelee");
SIMPLE_TEST(LongPressedName, TestSAMPLE4, true, "laiden", "laiden");
SIMPLE_TEST(LongPressedName, TestSAMPLE5, false, "alex", "aaleexa");
