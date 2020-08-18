#include "common_header.h"

#include "trie.h"
#include "trie_traversal.h"


using ArrayType = std::vector<std::string>;

namespace {

/** Counting the number of words in a Trie
 *
 * @reference   https://www.geeksforgeeks.org/counting-number-words-trie/
 */
std::size_t CountUniqueWords(const Trie::Node *node) {
    std::size_t result = 0;

    if (node->isEndOfWord) {
        ++result;
    }

    for (const auto &kid : node->children) {
        if (kid) {
            result += CountUniqueWords(kid.get());
        }
    }

    return result;
}

auto CountUniqueWords(const ArrayType &keys) {
    return BuildTrie(keys).Visit([](const auto & root) {
        return CountUniqueWords(&root);
    });
}


auto DisplayTrie(const ArrayType &keys) {
    ArrayType results;
    BuildTrie(keys).Visit([&results](const auto & root) {
        std::string prefix;
        Display(&root, prefix, results);
    });

    return results;
}


/**
 * @reference   Sorting array of strings (or words) using Trie | Set-2 (Handling Duplicates)
 *              https://www.geeksforgeeks.org/sorting-array-strings-words-using-trie-set-2-handling-duplicates/
 *
 * Given an array of strings, print them in alphabetical (dictionary) order. If
 * there are duplicates in input array, we need to print all the occurrences.
 */

}//namespace


const ArrayType SAMPLE1 = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
const ArrayType EXPECTED1 = {"a", "answer", "any", "by", "bye", "the", "their", "there"};

const ArrayType SAMPLE2 = {"abc", "xy", "bcd"};
const ArrayType EXPECTED2 = {"abc", "bcd", "xy"};

const ArrayType SAMPLE3 = {"geeks", "for", "geeks", "a", "portal", "to", "learn", "can", "be", "computer", "science", "zoom", "yup", "fire", "in", "data"};
const ArrayType EXPECTED3 = {"a", "be", "can", "computer", "data", "fire", "for", "geeks", "in", "learn", "portal", "science", "to", "yup", "zoom"};

SIMPLE_BENCHMARK(CountUniqueWords, SAMPLE1);

SIMPLE_TEST(CountUniqueWords, TestSAMPLE1, 8, SAMPLE1);


SIMPLE_BENCHMARK(DisplayTrie, SAMPLE1);

SIMPLE_TEST(DisplayTrie, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(DisplayTrie, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(DisplayTrie, TestSAMPLE3, EXPECTED3, SAMPLE3);
