#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/**
 * @reference   Program to check if two strings are same or not
 *              https://www.geeksforgeeks.org/program-to-check-if-two-strings-are-same-or-not/
 */


/** Check if two strings are same ignoring their cases
 *
 * @reference   https://www.geeksforgeeks.org/check-if-two-strings-are-same-ignoring-their-cases/
 */
inline auto
CaseInsensitiveCompare(const std::string_view lhs, const std::string_view rhs) {
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(),
    [](const auto a, const auto b) {
        return std::tolower(a) == std::tolower(b);
    });
}


/**
 * @reference   Check if One String Swap Can Make Strings Equal
 *              https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/
 *
 * You are given two strings s1 and s2 of equal length. A string swap is an operation
 * where you choose two indices in a string (not necessarily different) and swap the
 * characters at these indices. Return true if it is possible to make both strings
 * equal by performing at most one string swap on exactly one of the strings. Otherwise,
 * return false.
 */
constexpr auto
EqualAfterOneSwap(const std::string_view one, const std::string_view another) {
    if (one.size() != another.size()) {
        return false;
    }

    int diffs[2] = {};
    int diff_count = 0;
    for (std::size_t i = 0; i < one.size(); ++i) {
        if (one[i] != another[i]) {
            if (diff_count == 2) {
                return false;
            }
            diffs[diff_count++] = i;
        }
    }

    return diff_count == 0 or
           (diff_count == 2 and
            one[diffs[0]] == another[diffs[1]] and
            one[diffs[1]] == another[diffs[0]]);
}


/**
 * @reference   Buddy Strings
 *              https://leetcode.com/problems/buddy-strings/
 *
 * Given two strings s and goal, return true if you can swap two letters in s so the
 * result is equal to goal, otherwise, return false. Swapping letters is defined as
 * taking two indices i and j (0-indexed) such that i != j and swapping the characters
 * at s[i] and s[j]. For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
 * s and goal consist of lowercase letters.
 */
constexpr auto
EqualAfterOneSwapNoSameIndices(const std::string_view one,
                               const std::string_view another) {
    if (one.size() != another.size()) {
        return false;
    }

    int diffs[2] = {};
    int diff_count = 0;
    int counts[26] = {};
    for (std::size_t i = 0; i < one.size(); ++i) {
        if (one[i] != another[i]) {
            if (diff_count == 2) {
                return false;
            }
            diffs[diff_count++] = i;
        }

        ++counts[one[i] - 'a'];
    }

    if (diff_count == 0) {
        for (const auto c : counts) {
            if (c > 1) {
                return true;
            }
        }

        return false;
    }

    return diff_count == 2 and
           one[diffs[0]] == another[diffs[1]] and
           one[diffs[1]] == another[diffs[0]];
}


/**
 * @reference   Check If Two String Arrays are Equivalent
 *              https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/
 *
 * Given two string arrays word1 and word2, return true if the two arrays represent the
 * same string, and false otherwise.
 * A string is represented by an array if the array elements concatenated in order forms
 * the string.
 * word1[i] and word2[i] consist of lowercase letters.
 */
auto ArrayStringsAreEqual(const ArrayType &word1, const ArrayType &word2) {
    std::size_t w_i = 0, w_j = 0;
    std::size_t c_m = 0, c_n = 0; // char pointers

    while (w_i < word1.size() and w_j < word2.size()) {
        if (word1[w_i][c_m++] != word2[w_j][c_n++]) {
            return false;
        }

        if (c_m >= word1[w_i].size()) {
            ++w_i;
            c_m = 0;
        }

        if (c_n >= word2[w_j].size()) {
            ++w_j;
            c_n = 0;
        }
    }

    return w_i == word1.size() and w_j == word2.size();
}

}//namespace


THE_BENCHMARK(CaseInsensitiveCompare, "Geeks", "geeks");

SIMPLE_TEST(CaseInsensitiveCompare, TestSAMPLE1, true, "Geeks", "geeks");
SIMPLE_TEST(CaseInsensitiveCompare, TestSAMPLE2, false, "Geek", "geeksforgeeks");


THE_BENCHMARK(EqualAfterOneSwap, "bank", "kanb");

SIMPLE_TEST(EqualAfterOneSwap, TestSAMPLE1, true, "bank", "kanb");
SIMPLE_TEST(EqualAfterOneSwap, TestSAMPLE2, false, "attack", "defend");
SIMPLE_TEST(EqualAfterOneSwap, TestSAMPLE3, true, "kelb", "kelb");
SIMPLE_TEST(EqualAfterOneSwap, TestSAMPLE4, false, "abcd", "dcba");


THE_BENCHMARK(EqualAfterOneSwapNoSameIndices, "bank", "kanb");

SIMPLE_TEST(EqualAfterOneSwapNoSameIndices, TestSAMPLE1, true, "bank", "kanb");
SIMPLE_TEST(EqualAfterOneSwapNoSameIndices, TestSAMPLE2, false, "attack", "defend");
SIMPLE_TEST(EqualAfterOneSwapNoSameIndices, TestSAMPLE3, true, "ab", "ba");
SIMPLE_TEST(EqualAfterOneSwapNoSameIndices, TestSAMPLE4, false, "abcd", "dcba");
SIMPLE_TEST(EqualAfterOneSwapNoSameIndices, TestSAMPLE5, false, "ab", "ab");
SIMPLE_TEST(EqualAfterOneSwapNoSameIndices, TestSAMPLE6, true, "aa", "aa");
SIMPLE_TEST(EqualAfterOneSwapNoSameIndices, TestSAMPLE7, true, "aaaaaaabc",
            "aaaaaaacb");


const ArrayType SAMPLE1L = {"ab", "c"};
const ArrayType SAMPLE1R = {"a", "bc"};

const ArrayType SAMPLE2R = {"bc", "a"};

const ArrayType SAMPLE3R = {"a", "cb"};

const ArrayType SAMPLE4L = {"abc", "d", "defg"};
const ArrayType SAMPLE4R = {"abcddefg"};


THE_BENCHMARK(ArrayStringsAreEqual, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(ArrayStringsAreEqual, TestSAMPLE1, true, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(ArrayStringsAreEqual, TestSAMPLE2, false, SAMPLE1L, SAMPLE2R);
SIMPLE_TEST(ArrayStringsAreEqual, TestSAMPLE3, false, SAMPLE1L, SAMPLE3R);
SIMPLE_TEST(ArrayStringsAreEqual, TestSAMPLE4, true, SAMPLE4L, SAMPLE4R);
