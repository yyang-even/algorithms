#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Number of Matching Subsequences
 *
 * @reference   https://leetcode.com/problems/number-of-matching-subsequences/
 *
 * Given a string s and an array of strings words, return the number of words[i] that is
 * a subsequence of s. A subsequence of a string is a new string generated from the
 * original string with some characters (can be none) deleted without changing the
 * relative order of the remaining characters. For example, "ace" is a subsequence of
 * "abcde".
 * s and words[i] consist of only lowercase English letters.
 */
auto NumMatchingSubsequences(const std::string_view text, const ArrayType &words) {
    std::vector<std::vector<const char *>> candidates('z' + 1);

    for (const auto &a_word : words) {
        if (not a_word.empty()) {
            candidates[a_word.front()].push_back(a_word.c_str());
        }
    }

    for (const auto c : text) {
        const auto matches = std::move(candidates[c]);
        candidates[c].clear();
        for (auto a_node : matches) {
            candidates[*++a_node].push_back(a_node);
        }
    }

    return candidates[0].size();
}

}//namespace


const ArrayType SAMPLE1 = {"a", "bb", "acd", "ace"};
const ArrayType SAMPLE2 = {"ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"};
const ArrayType SAMPLE3 = {"btovxbku", "to", "zueoxxxjme", "yjkclbkbtl"};


THE_BENCHMARK(NumMatchingSubsequences, "abcde", SAMPLE1);

SIMPLE_TEST(NumMatchingSubsequences, TestSAMPLE1, 3, "abcde", SAMPLE1);
SIMPLE_TEST(NumMatchingSubsequences, TestSAMPLE2, 2, "dsahjpjauf", SAMPLE2);
SIMPLE_TEST(NumMatchingSubsequences, TestSAMPLE3, 2, "btovxbkumc", SAMPLE3);
