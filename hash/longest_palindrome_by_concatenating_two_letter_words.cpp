#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Longest Palindrome by Concatenating Two Letter Words
 *
 * @reference   https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/
 *
 * You are given an array of strings words. Each element of words consists of two lowercase English
 * letters.
 * Create the longest possible palindrome by selecting some elements from words and concatenating them
 * in any order. Each element can be selected at most once.
 * Return the length of the longest palindrome that you can create. If it is impossible to create any
 * palindrome, return 0.
 * A palindrome is a string that reads the same forward and backward.
 */
auto LongestPalindromeByConcatenatingWords(const ArrayType &words) {
    std::unordered_map<std::string_view, int> counts;
    int center = 0;
    int result = 0;

    for (const auto &w : words) {
        if (w[0] == w[1]) {
            const auto [iter, _] = counts.emplace(w, 0);
            if (iter->second == 0) {
                ++(iter->second);
                ++center;
            } else {
                --(iter->second);
                --center;
                result += 4;
            }
        } else {
            const std::string other {w[1], w[0]};
            const auto iter = counts.find(other);
            if (iter != counts.cend() and iter->second > 0) {
                --(iter->second);
                result += 4;
            } else {
                ++(counts[w]);
            }
        }
    }

    if (center) {
        result += 2;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {"lc", "cl", "gg"};
const ArrayType SAMPLE2 = {"ab", "ty", "yt", "lc", "cl", "ab"};
const ArrayType SAMPLE3 = {"cc", "ll", "xx"};
const ArrayType SAMPLE4 = {
    "dd", "aa", "bb", "dd", "aa", "dd", "bb", "dd", "aa", "cc", "bb", "cc", "dd", "cc"};


THE_BENCHMARK(LongestPalindromeByConcatenatingWords, SAMPLE1);

SIMPLE_TEST(LongestPalindromeByConcatenatingWords, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(LongestPalindromeByConcatenatingWords, TestSAMPLE2, 8, SAMPLE2);
SIMPLE_TEST(LongestPalindromeByConcatenatingWords, TestSAMPLE3, 2, SAMPLE3);
SIMPLE_TEST(LongestPalindromeByConcatenatingWords, TestSAMPLE4, 22, SAMPLE4);
