#include "common_header.h"

#include "trie.h"


using ArrayType = std::vector<std::string_view>;
using OutputType = std::vector<bool>;

namespace {

inline auto TestSearch(const ArrayType &keys, const std::string_view str) {
    return BuildTrie(keys).Search(str);
}


inline auto BuildTrie_Recursive(const ArrayType &keys) {
    Trie dictionary;

    for (const auto &one_key : keys) {
        dictionary.Insert_Recursive(one_key);
    }

    return dictionary;
}

inline auto TestSearch_Recursive(const ArrayType &keys, const std::string_view str) {
    return BuildTrie_Recursive(keys).Search_Recursive(str);
}


/**
 * @reference   Check if the given string of words can be formed from words present in the dictionary
 *              https://www.geeksforgeeks.org/check-if-the-given-string-of-words-can-be-formed-from-words-present-in-the-dictionary/
 *
 * Given a string array of M words and a dictionary of N words. The task is to check if the given string
 * of words can be formed from words present in the dictionary.
 */


/**
 * @reference   Design Add and Search Words Data Structure
 *              https://leetcode.com/problems/design-add-and-search-words-data-structure/
 *
 * Design a data structure that supports adding new words and finding if a string matches any previously
 * added string.
 * Implement the WordDictionary class:
 *  WordDictionary() Initializes the object.
 *  void addWord(word) Adds word to the data structure, it can be matched later.
 *  bool search(word) Returns true if there is any string in the data structure that matches
 *      word or false otherwise. word may contain dots '.' where dots can be matched with any letter.
 */
inline bool WildcardSearch(const Trie::Node &root, const std::string_view key) {
    const auto *current = &root;

    for (std::size_t i = 0; i < key.size(); ++i) {
        const auto c = key[i];
        if (c == '.') {
            for (const auto &node : current->children) {
                if (node and WildcardSearch(*node, key.substr(i + 1))) {
                    return true;
                }
            }
            return false;
        } else {
            const auto index = Trie::Node::ToIndex(c);

            if (not current->children[index]) {
                return false;
            }
            current = current->children[index].get();
        }
    }

    return current->value;
}

class WordDictionary {
    Trie dictionary;

public:
    void addWord(const std::string_view word) {
        dictionary.Insert(word);
    }

    bool search(const std::string_view word) {
        return dictionary.Visit([word](const auto &root) {
            return WildcardSearch(root, word);
        });
    }
};

inline auto testWordDictionary(const ArrayType &keys, const ArrayType &query) {
    WordDictionary dictionary;
    for (const auto k : keys) {
        dictionary.addWord(k);
    }

    OutputType result;
    for (const auto q : query) {
        result.push_back(dictionary.search(q));
    }

    return result;
}


/**
 * @reference   Number of Strings That Appear as Substrings in Word
 *              https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/
 *
 * Given an array of strings patterns and a string word, return the number of strings in patterns that
 * exist as a substring in word.
 * A substring is a contiguous sequence of characters within a string.
 */
auto buildSuffixTrie(const std::string_view s) {
    Trie dictionary;

    for (std::size_t i = 0; i < s.size(); ++i) {
        dictionary.Insert(s.substr(i));
    }

    return dictionary;
}

template<typename NodeType>
auto isSubstr(const NodeType &root, const std::string_view key) {
    const auto *current = &root;

    for (const auto c : key) {
        const auto index = NodeType::ToIndex(c);

        if (not current->children[index]) {
            return false;
        }
        current = current->children[index].get();
    }

    return true;
}

auto NumberSubstrsInWord(const ArrayType &patterns, const std::string_view word) {
    const auto dictionary = buildSuffixTrie(word);

    int result = 0;
    for (const auto p : patterns) {
        if (dictionary.Visit([p](const auto &root) {
                return isSubstr(root, p);
            })) {
            ++result;
        }
    }

    return result;
}

} //namespace


#ifdef WANT_TESTS
TEST(TrieTest, TestDelete) {
    const ArrayType keys = {
        "the", "a", "there", "answer", "any", "by", "bye", "their", "hero", "heroplane"};
    const auto str = "heroplane";

    auto dictionary = BuildTrie(keys);
    dictionary.Insert(str);

    EXPECT_TRUE(dictionary.Search(str));

    dictionary.Delete(str);

    EXPECT_FALSE(dictionary.Search(str));

    for (const auto &one_key : keys) {
        if (one_key != str) {
            EXPECT_TRUE(dictionary.Search(one_key));
        }
    }
}
#endif


const ArrayType SAMPLE1 = {"the", "a", "there", "answer", "any", "by", "bye", "their"};


SIMPLE_TEST(TestSearch, TestSAMPLE1, true, SAMPLE1, "the");
SIMPLE_TEST(TestSearch, TestSAMPLE2, false, SAMPLE1, "these");


SIMPLE_TEST(TestSearch_Recursive, TestSAMPLE1, true, SAMPLE1, "the");
SIMPLE_TEST(TestSearch_Recursive, TestSAMPLE2, false, SAMPLE1, "these");


const ArrayType SAMPLE1K = {"bad", "dad", "mad"};
const ArrayType SAMPLE1Q = {"pad", "bad", ".ad", "b.."};
const OutputType EXPECTED1 = {false, true, true, true};


SIMPLE_TEST(testWordDictionary, TestSAMPLE1, EXPECTED1, SAMPLE1K, SAMPLE1Q);


const ArrayType SAMPLE1P = {"a", "abc", "bc", "d"};
const ArrayType SAMPLE2P = {"a", "b", "c"};
const ArrayType SAMPLE3P = {"a", "a", "a"};


THE_BENCHMARK(NumberSubstrsInWord, SAMPLE1P, "abc");

SIMPLE_TEST(NumberSubstrsInWord, TestSAMPLE1, 3, SAMPLE1P, "abc");
SIMPLE_TEST(NumberSubstrsInWord, TestSAMPLE2, 2, SAMPLE2P, "aaaaabbbbb");
SIMPLE_TEST(NumberSubstrsInWord, TestSAMPLE3, 3, SAMPLE3P, "ab");
