#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Longest String Chain
 *
 * @reference   https://leetcode.com/problems/longest-string-chain/
 *
 * You are given an array of words where each word consists of lowercase English letters.
 * wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in
 * wordA without changing the order of the other characters to make it equal to wordB.
 *  For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
 * A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a
 * predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a
 * word chain with k == 1.
 * Return the length of the longest possible word chain with words chosen from the given list of
 * words.
 */
auto LongestStrChain(ArrayType words) {
    std::sort(words.begin(), words.end(), [](const auto one, const auto another) {
        return one.size() < another.size();
    });

    std::unordered_map<std::string_view, int> dp;
    int result = 0;

    for (const auto w : words) {
        int current = 1;
        for (std::size_t i = 0; i < w.size(); ++i) {
            const auto predecessor = std::string(w.substr(0, i)) + std::string(w.substr(i + 1));
            if (const auto iter = dp.find(predecessor); iter != dp.cend()) {
                current = std::max(current, iter->second + 1);
            }
        }

        result = std::max(result, dp[w] = current);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {"a", "b", "ba", "bca", "bda", "bdca"};
const ArrayType SAMPLE2 = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
const ArrayType SAMPLE3 = {"abcd", "dbqca"};


THE_BENCHMARK(LongestStrChain, SAMPLE1);

SIMPLE_TEST(LongestStrChain, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(LongestStrChain, TestSAMPLE2, 5, SAMPLE2);
SIMPLE_TEST(LongestStrChain, TestSAMPLE3, 1, SAMPLE3);
