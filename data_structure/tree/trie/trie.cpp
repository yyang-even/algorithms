#include "common_header.h"

#include "trie.h"


using ArrayType = std::vector<std::string_view>;

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
 * Given a string array of M words and a dictionary of N words. The task is to check if
 * the given string of words can be formed from words present in the dictionary.
 */

}//namespace


#ifdef WANT_TESTS
TEST(TrieTest, TestDelete) {
    const ArrayType keys = {"the", "a", "there", "answer", "any", "by", "bye", "their", "hero", "heroplane"};
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
