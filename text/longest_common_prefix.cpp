#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Longest Common Prefix
 *
 * @reference   https://leetcode.com/problems/longest-common-prefix/
 * @reference   Longest Common Prefix using Word by Word Matching
 *              https://www.geeksforgeeks.org/longest-common-prefix-using-word-by-word-matching/
 * @reference   Longest Common Prefix using Character by Character Matching
 *              https://www.geeksforgeeks.org/longest-common-prefix-using-character-by-character-matching/
 * @reference   Longest Common Prefix using Divide and Conquer Algorithm
 *              https://www.geeksforgeeks.org/longest-common-prefix-using-divide-and-conquer-algorithm/
 * @reference   Longest Common Prefix using Binary Search
 *              https://www.geeksforgeeks.org/longest-common-prefix-using-binary-search/
 * @reference   Longest Common Prefix using Trie
 *              https://www.geeksforgeeks.org/longest-common-prefix-using-trie/
 *
 * @reference   Longest Common Prefix using Sorting
 *              https://www.geeksforgeeks.org/longest-common-prefix-using-sorting/
 * @reference   Longest Common Prefix Matching | Set-6
 *              https://www.geeksforgeeks.org/longest-common-prefix-matching-set-6/
 *
 * @hint    If strs are sorted, then the result is the common prefix of the first and
 * last string.
 *
 * Write a function to find the longest common prefix string amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 */
auto LongestCommonPrefix(const ArrayType &strs) {
    assert(not strs.empty());

    const auto first = strs.front();

    for (std::size_t i = 0; i < first.size(); ++i) {
        for (std::size_t j = 1; j < strs.size(); ++j) {
            const auto a_str = strs[j];
            if ((i >= a_str.size()) or (a_str[i] != first[i])) {
                return first.substr(0, i);
            }
        }
    }

    return first;
}

}//namespace


const ArrayType SAMPLE1 = {"flower", "flow", "flight"};
const ArrayType SAMPLE2 = {"dog", "racecar", "car"};
const ArrayType SAMPLE3 = {"geeksforgeeks", "geeks", "geek", "geezer"};
const ArrayType SAMPLE4 = {"apple", "ape", "april"};
const ArrayType SAMPLE5 = {"ap", "apple", "ape", "april"};
const ArrayType SAMPLE6 = {"ap"};


THE_BENCHMARK(LongestCommonPrefix, SAMPLE1);

SIMPLE_TEST(LongestCommonPrefix, TestSAMPLE1, "fl", SAMPLE1);
SIMPLE_TEST(LongestCommonPrefix, TestSAMPLE2, "", SAMPLE2);
SIMPLE_TEST(LongestCommonPrefix, TestSAMPLE3, "gee", SAMPLE3);
SIMPLE_TEST(LongestCommonPrefix, TestSAMPLE4, "ap", SAMPLE4);
SIMPLE_TEST(LongestCommonPrefix, TestSAMPLE5, "ap", SAMPLE5);
SIMPLE_TEST(LongestCommonPrefix, TestSAMPLE6, "ap", SAMPLE6);
