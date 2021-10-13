#include "common_header.h"

#include "trie.h"


using ArrayType = std::vector<std::string_view>;

namespace {

/**
 * @reference   Implement Trie II (Prefix Tree)
 *              https://zhenchaogan.gitbook.io/leetcode-solution/leetcode-1804-implement-trie-ii-prefix-tree
 *
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently
 * store and retrieve keys in a dataset of strings. There are various applications of this
 * data structure, such as autocomplete and spellchecker. Implement the Trie class:
 *  Trie() Initializes the trie object.
 *  void insert(String word) Inserts the string word into the trie.
 *  int countWordsEqualTo(String word) Returns the number of instances of the string word
 *      in the trie.
 *  int countWordsStartingWith(String prefix)Returns the number of strings in the trie
 *      that have the string prefix as a prefix.
 *  void erase(String word) Erases the string wordfrom the trie.
 * word and prefix consist only of lowercase English letters.
 */
class MultiTrie {
    using PrefixCountWordCountPair = std::pair<int, int>;
    using Node = TrieNode<PrefixCountWordCountPair>;

    Node root;

public:

    void Insert(const std::string_view word) {
        auto *current = &root;
        for (const auto c : word) {
            const auto index = Node::ToIndex(c);
            if (not current->children[index]) {
                current->children[index].reset(new Node());
            }

            current = current->children[index].get();
            ++(current->value.first);
        }

        ++(current->value.second);
    }

    auto countWordsEqualTo(const std::string_view word) {
        return TrieGet(root, word).second;
    }

    auto countWordsStartingWith(const std::string_view word) {
        return TrieGet(root, word).first;
    }

    void Erase(const std::string_view word) {
        auto *current = &root;
        for (const auto c : word) {
            const auto index = Node::ToIndex(c);

            if (not current->children[index]) {
                return;
            }

            if ((current->children[index]->value.first)-- == 1) {
                current->children[index].reset();
                return;
            }
            current = current->children[index].get();
        }

        assert(current->value.second > 0);
        --(current->value.second);
    }
};

}//namespace


#ifdef WANT_TESTS
TEST(MultiTrieTest, TestSanity) {
    MultiTrie trie;

    trie.Insert("apple");
    trie.Insert("apple");
    EXPECT_EQ(2, trie.countWordsEqualTo("apple"));
    EXPECT_EQ(2, trie.countWordsStartingWith("app"));

    trie.Erase("apple");
    EXPECT_EQ(1, trie.countWordsEqualTo("apple"));
    EXPECT_EQ(1, trie.countWordsStartingWith("app"));

    trie.Erase("apple");
    EXPECT_EQ(0, trie.countWordsEqualTo("apple"));
    EXPECT_EQ(0, trie.countWordsStartingWith("app"));
}
#endif
