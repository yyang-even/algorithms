#include "common_header.h"

#include "trie.h"


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
    const auto dictionary = BuildTrie(keys);
    return dictionary.Visit([](const auto & root) {
        return CountUniqueWords(&root);
    });
}

}//namespace


const ArrayType SAMPLE1 = {"the", "a", "there", "answer", "any", "by", "bye", "their"};


SIMPLE_BENCHMARK(CountUniqueWords, SAMPLE1);

SIMPLE_TEST(CountUniqueWords, TestSAMPLE1, 8, SAMPLE1);
