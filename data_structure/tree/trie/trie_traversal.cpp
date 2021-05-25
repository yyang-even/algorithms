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

inline auto CountUniqueWords(const ArrayType &keys) {
    return BuildTrie(keys).Visit([](const auto & root) {
        return CountUniqueWords(&root);
    });
}


inline auto DisplayTrie(const ArrayType &keys) {
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
 * Given an array of strings, print them in alphabetical (dictionary) order. If there are
 * duplicates in input array, we need to print all the occurrences.
 */


/** Bottom-up traversal of a Trie
 *
 * @reference   https://www.geeksforgeeks.org/bottom-up-traversal-of-a-trie/
 */
void Display_BottomUp(const Trie::Node *node, std::string &results) {
    assert(node);

    for (std::size_t i = 0; i < node->children.size(); ++i) {
        if (node->children[i]) {
            Display_BottomUp(node->children[i].get(), results);
            results.push_back(Trie::Node::ToChar(i));
        }
    }
}

inline auto Display_BottomUp(const ArrayType &keys) {
    std::string results;
    BuildTrie(keys).Visit([&results](const auto & root) {
        Display_BottomUp(&root, results);
    });

    return results;
}


/**
 * @reference   Print Strings In Reverse Dictionary Order Using Trie
 *              https://www.geeksforgeeks.org/print-strings-in-reverse-dictionary-order-using-trie/
 */
void Display_Reverse(const Trie::Node *node, std::string &prefix, ArrayType &results) {
    assert(node);

    if (node->isEndOfWord) {
        results.push_back(prefix);
    }

    for (int i = node->children.size() - 1; i >= 0; --i) {
        if (node->children[i]) {
            prefix.push_back(Trie::Node::ToChar(i));

            Display_Reverse(node->children[i].get(), prefix, results);

            prefix.pop_back();
        }
    }
}

inline auto Display_Reverse(const ArrayType &keys) {
    ArrayType results;
    BuildTrie(keys).Visit([&results](const auto & root) {
        std::string prefix;
        Display_Reverse(&root, prefix, results);
    });

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
const ArrayType EXPECTED1 = {"a", "answer", "any", "by", "bye", "the", "their", "there"};

const ArrayType SAMPLE2 = {"abc", "xy", "bcd"};
const ArrayType EXPECTED2 = {"abc", "bcd", "xy"};
const ArrayType EXPECTED_REVERSE2 = {"xy", "bcd", "abc"};

const ArrayType SAMPLE3 = {"geeks", "for", "geeks", "a", "portal", "to", "learn", "can", "be", "computer", "science", "zoom", "yup", "fire", "in", "data"};
const ArrayType EXPECTED3 = {"a", "be", "can", "computer", "data", "fire", "for", "geeks", "in", "learn", "portal", "science", "to", "yup", "zoom"};


THE_BENCHMARK(CountUniqueWords, SAMPLE1);

SIMPLE_TEST(CountUniqueWords, TestSAMPLE1, 8, SAMPLE1);


THE_BENCHMARK(DisplayTrie, SAMPLE1);

SIMPLE_TEST(DisplayTrie, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(DisplayTrie, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(DisplayTrie, TestSAMPLE3, EXPECTED3, SAMPLE3);


const ArrayType SAMPLE4 = {"their", "there", "answer", "any"};
const ArrayType EXPECTED_REVERSE4 = {"there", "their", "any", "answer"};


THE_BENCHMARK(Display_BottomUp, SAMPLE4);

SIMPLE_TEST(Display_BottomUp, TestSAMPLE4, "rewsynariereht", SAMPLE4);


THE_BENCHMARK(Display_Reverse, SAMPLE1);

SIMPLE_TEST(Display_Reverse, TestSAMPLE2, EXPECTED_REVERSE2, SAMPLE2);
SIMPLE_TEST(Display_Reverse, TestSAMPLE4, EXPECTED_REVERSE4, SAMPLE4);
