#include "common_header.h"

#include "trie.h"
#include "trie_traversal.h"


using ArrayType = std::vector<std::string>;

namespace {

/** Auto-complete feature using Trie
 *
 * @reference   https://www.geeksforgeeks.org/auto-complete-feature-using-trie/
 */
auto AutoComplete(const Trie::Node *root, std::string prefix) {
    const auto *current_node = root;

    ArrayType results;
    for (const auto c : prefix) {
        const auto index = Trie::Node::ToIndex(c);
        if (not current_node->children[index]) {
            return results;
        }

        current_node = current_node->children[index].get();
    }

    if (current_node->Empty()) {
        if (current_node->isEndOfWord) {
            results.push_back(prefix);
        }
    } else {
        Display(current_node, prefix, results);
    }

    return results;
}

inline auto
AutoComplete(const ArrayType &keys, const std::string &prefix) {
    return BuildTrie(keys).Visit([&prefix](const auto & root) {
        return AutoComplete(&root, prefix);
    });
}

}//namespace


const ArrayType SAMPLE1 = {"hello", "dog", "hell", "cat", "a", "hel", "help", "helps", "helping"};
const ArrayType EXPECTED1 = {"hel", "hell", "hello", "help", "helping", "helps"};
const ArrayType EXPECTED2 = {"cat"};


THE_BENCHMARK(AutoComplete, SAMPLE1, "hel");

SIMPLE_TEST(AutoComplete, TestSAMPLE1, EXPECTED1, SAMPLE1, "hel");
SIMPLE_TEST(AutoComplete, TestSAMPLE2, EXPECTED2, SAMPLE1, EXPECTED2.front());
SIMPLE_TEST(AutoComplete, TestSAMPLE3, {}, SAMPLE1, "helped");
