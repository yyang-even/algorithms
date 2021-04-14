#include "common_header.h"

#include "trie.h"


namespace {

using ArrayType = std::vector<std::string>;

/**
 * @reference   Find the longest string that can be made up of other strings from the array
 *              https://www.geeksforgeeks.org/find-the-longest-string-that-can-be-made-up-of-other-strings-from-the-array/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.7.
 *
 * Given an array of strings arr[], the task is to find the largest string in the array
 * which is made up of the other strings from the array after concatenating one after
 * another.
 */
enum class WordType {
    not_a_word,
    single,
    concatenated
};

WordType CheckWordType(const Trie::Node *root,
                       const std::string &word,
                       std::string::size_type i) {
    assert(root);

    const auto *current = root;
    for (; i < word.size(); ++i) {
        if (current->isEndOfWord) {
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

    return (current and current->isEndOfWord) ? WordType::single : WordType::not_a_word;
}

std::string LongestConcatenatedString(const ArrayType &arr) {
    return BuildTrie(arr).Visit([&arr](const auto & root) {
        std::string longest_concatenated;
        for (const auto &word : arr) {
            if (CheckWordType(&root, word, 0) == WordType::concatenated and
                word.size() > longest_concatenated.size()) {
                longest_concatenated = word;
            }
        }

        return longest_concatenated;
    });
}

}//namespace


const ArrayType SAMPLE1 = {"geeks", "for", "geeksfor", "geeksforgeeks", "geeksforgeeksabc"};
const ArrayType SAMPLE2 = {"Hey", "you", "stop", "right", "there"};


THE_BENCHMARK(LongestConcatenatedString, SAMPLE1);

SIMPLE_TEST(LongestConcatenatedString, TestSAMPLE1, "geeksforgeeks", SAMPLE1);
SIMPLE_TEST(LongestConcatenatedString, TestSAMPLE2, "", SAMPLE2);
