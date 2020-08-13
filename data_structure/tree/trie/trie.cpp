#include "common_header.h"

#include "trie.h"


using ArrayType = std::vector<std::string>;

namespace {

inline auto TestSearch(const ArrayType &keys, const std::string &str) {
    Trie dictionary;

    for (const auto &one_key : keys) {
        dictionary.Insert(one_key);
    }

    return dictionary.Search(str);
}

}//namespace


const ArrayType SAMPLE1 = {"the", "a", "there", "answer", "any", "by", "bye", "their"};


SIMPLE_TEST(TestSearch, TestSAMPLE1, true, SAMPLE1, "the");
SIMPLE_TEST(TestSearch, TestSAMPLE2, false, SAMPLE1, "these");
