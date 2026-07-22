#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/**
 * @reference   Longest Common Prefix
 *              https://leetcode.com/problems/longest-common-prefix/
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
 * @hint    If strs are sorted, then the result is the common prefix of the first and last string.
 *
 * Write a function to find the longest common prefix string amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 *
 * @tags    #sorting
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

auto LongestCommonPrefix_Sort(ArrayType strs) {
    std::sort(strs.begin(), strs.end());

    const auto first = strs.front();
    const auto last = strs.back();
    const int SIZE = std::min(first.size(), last.size());
    for (int i = 0; i < SIZE; ++i) {
        if (first[i] != last[i]) {
            return first.substr(0, i);
        }
    }

    return first;
}


/**
 * @reference   Find the Length of the Longest Common Prefix
 *              https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/
 *
 * You are given two arrays with positive integers arr1 and arr2.
 * A prefix of a positive integer is an integer formed by one or more of its digits, starting from its
 * leftmost digit. For example, 123 is a prefix of the integer 12345, while 234 is not.
 * A common prefix of two integers a and b is an integer c, such that c is a prefix of both a and b. For
 * example, 5655359 and 56554 have common prefixes 565 and 5655 while 1223 and 43456 do not have a
 * common prefix.
 * You need to find the length of the longest common prefix between all pairs of integers (x, y) such
 * that x belongs to arr1 and y belongs to arr2.
 * Return the length of the longest common prefix among all pairs. If no common prefix exists among
 * them, return 0.
 *
 * @tags    #digit-traverse #hash-table #trie
 */
auto LengthOfLongestCommonPrefix(const std::vector<int> &arr1, const std::vector<int> &arr2) {
    std::unordered_set<int> prefix;
    for (auto n : arr1) {
        for (; n; n /= 10) {
            prefix.insert(n);
        }
    }

    int result = 0;
    for (auto n : arr2) {
        for (; n; n /= 10) {
            if (prefix.find(n) != prefix.cend()) {
                const int l = std::to_string(n).size();
                result = std::max(result, l);
                break;
            }
        }
    }

    return result;
}

} //namespace


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


THE_BENCHMARK(LongestCommonPrefix_Sort, SAMPLE1);

SIMPLE_TEST(LongestCommonPrefix_Sort, TestSAMPLE1, "fl", SAMPLE1);
SIMPLE_TEST(LongestCommonPrefix_Sort, TestSAMPLE2, "", SAMPLE2);
SIMPLE_TEST(LongestCommonPrefix_Sort, TestSAMPLE3, "gee", SAMPLE3);
SIMPLE_TEST(LongestCommonPrefix_Sort, TestSAMPLE4, "ap", SAMPLE4);
SIMPLE_TEST(LongestCommonPrefix_Sort, TestSAMPLE5, "ap", SAMPLE5);
SIMPLE_TEST(LongestCommonPrefix_Sort, TestSAMPLE6, "ap", SAMPLE6);


const std::vector SAMPLE1L_LCP = {1, 10, 100};
const std::vector SAMPLE1R_LCP = {1000};

const std::vector SAMPLE2L_LCP = {1, 2, 3};
const std::vector SAMPLE2R_LCP = {4, 4, 4};


THE_BENCHMARK(LengthOfLongestCommonPrefix, SAMPLE1L_LCP, SAMPLE1R_LCP);

SIMPLE_TEST(LengthOfLongestCommonPrefix, TestSAMPLE1, 3, SAMPLE1L_LCP, SAMPLE1R_LCP);
SIMPLE_TEST(LengthOfLongestCommonPrefix, TestSAMPLE2, 0, SAMPLE2L_LCP, SAMPLE2R_LCP);
