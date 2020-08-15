#include "common_header.h"

#include "trie.h"


using ArrayType = std::vector<std::string>;

namespace {

inline auto TestSearch(const ArrayType &keys, const std::string &str) {
    const auto dictionary = BuildTrie(keys);
    return dictionary.Search(str);
}

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
