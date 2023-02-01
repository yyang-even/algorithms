#include "common_header.h"

#include "trie.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/**
 * @reference   Find the longest string that can be made up of other strings from the array
 *              https://www.geeksforgeeks.org/find-the-longest-string-that-can-be-made-up-of-other-strings-from-the-array/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.7.
 *
 * Given an array of strings arr[], the task is to find the largest string in the array which is made up
 * of the other strings from the array after concatenating one after another.
 */
enum class WordType { not_a_word, single, concatenated };

WordType CheckWordType(const Trie::Node *root, const std::string_view word, std::size_t i) {
    assert(root);

    const auto *current = root;
    for (; i < word.size(); ++i) {
        if (current->value) {
            if (CheckWordType(root, word, i) != WordType::not_a_word) {
                return WordType::concatenated;
            }
        }

        const auto c = word[i];
        const auto index = Trie::Node::ToIndex(c);

        if (not current->children[index]) {
            return WordType::not_a_word;
        }
        current = current->children[index].get();
    }

    return (current and current->value) ? WordType::single : WordType::not_a_word;
}

inline auto LongestConcatenatedString(const ArrayType &arr) {
    return BuildTrie(arr).Visit([&arr](const auto &root) {
        std::string_view longest_concatenated;
        for (const auto &word : arr) {
            if (word.size() > longest_concatenated.size() and
                CheckWordType(&root, word, 0) == WordType::concatenated) {
                longest_concatenated = word;
            }
        }

        return longest_concatenated;
    });
}


/**
 * @reference   Word Break
 *              https://leetcode.com/problems/word-break/
 *
 * Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a
 * space-separated sequence of one or more dictionary words.
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 */
bool WordBreak(const std::string_view s, const ArrayType &wordDict) {
    std::unordered_set<std::string_view> dictionary(wordDict.cbegin(), wordDict.cend());

    std::vector<bool> dp(s.size() + 1, false);
    dp[0] = true;

    for (std::size_t i = 1; i <= s.size(); ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (dp[j]) {
                const auto word = s.substr(j, i - j);
                if (dictionary.find(word) != dictionary.cend()) {
                    dp[i] = true;
                    break;
                }
            }
        }
    }

    return dp[s.size()];
}


/**
 * @reference   Concatenated Words
 *              https://leetcode.com/problems/concatenated-words/
 *
 * Given an array of strings words (without duplicates), return all the concatenated words in the given
 * list of words.
 * A concatenated word is defined as a string that is comprised entirely of at least two shorter words
 * in the given array.
 */

} //namespace


const ArrayType SAMPLE1 = {"geeks", "for", "geeksfor", "geeksforgeeks", "geeksforgeeksabc"};
const ArrayType SAMPLE2 = {"Hey", "you", "stop", "right", "there"};


THE_BENCHMARK(LongestConcatenatedString, SAMPLE1);

SIMPLE_TEST(LongestConcatenatedString, TestSAMPLE1, "geeksforgeeks", SAMPLE1);
SIMPLE_TEST(LongestConcatenatedString, TestSAMPLE2, "", SAMPLE2);


const ArrayType SAMPLE3 = {"leet", "code"};
const ArrayType SAMPLE4 = {"apple", "pen"};
const ArrayType SAMPLE5 = {"cats", "dog", "sand", "and", "cat"};


THE_BENCHMARK(WordBreak, "leetcode", SAMPLE3);

SIMPLE_TEST(WordBreak, TestSAMPLE3, true, "leetcode", SAMPLE3);
SIMPLE_TEST(WordBreak, TestSAMPLE4, true, "applepenapple", SAMPLE4);
SIMPLE_TEST(WordBreak, TestSAMPLE5, false, "catsandog", SAMPLE5);
