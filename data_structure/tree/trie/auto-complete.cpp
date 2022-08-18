#include "common_header.h"

#include "trie.h"
#include "trie_traversal.h"


using ArrayType = std::vector<std::string>;
using OutputType = std::vector<ArrayType>;

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
        if (current_node->value) {
            results.push_back(prefix);
        }
    } else {
        Display(current_node, prefix, results);
    }

    return results;
}

inline auto AutoComplete(const ArrayType &keys, const std::string &prefix) {
    return BuildTrie(keys).Visit([&prefix](const auto &root) {
        return AutoComplete(&root, prefix);
    });
}


/**
 * @reference   Search Suggestions System
 *              https://leetcode.com/problems/search-suggestions-system/
 *
 * You are given an array of strings products and a string searchWord.
 * Design a system that suggests at most three product names from products after each character of
 * searchWord is typed. Suggested products should have common prefix with searchWord. If there are more
 * than three products with a common prefix return the three lexicographically minimums products.
 * Return a list of lists of the suggested products after each character of searchWord is typed.
 * All the strings of products are unique.
 */
auto SuggestedProducts(ArrayType products, const std::string_view search_word) {
    std::sort(products.begin(), products.end());

    int left = 0;
    int right = products.size() - 1;

    OutputType results;
    for (std::size_t i = 0; i < search_word.size() and left <= right; ++i) {
        while (left <= right and
               (products[left].size() <= i or products[left][i] != search_word[i])) {
            ++left;
        }

        while (left <= right and
               (products[right].size() <= i or products[right][i] != search_word[i])) {
            --right;
        }

        results.emplace_back();
        for (int k = left; k <= right and k < left + 3; ++k) {
            results.back().push_back(products[k]);
        }
    }

    return results;
}

} //namespace


const ArrayType SAMPLE1 = {"hello", "dog", "hell", "cat", "a", "hel", "help", "helps", "helping"};
const ArrayType EXPECTED1 = {"hel", "hell", "hello", "help", "helping", "helps"};
const ArrayType EXPECTED2 = {"cat"};


THE_BENCHMARK(AutoComplete, SAMPLE1, "hel");

SIMPLE_TEST(AutoComplete, TestSAMPLE1, EXPECTED1, SAMPLE1, "hel");
SIMPLE_TEST(AutoComplete, TestSAMPLE2, EXPECTED2, SAMPLE1, EXPECTED2.front());
SIMPLE_TEST(AutoComplete, TestSAMPLE3, {}, SAMPLE1, "helped");


const ArrayType SAMPLE1P = {"mobile", "mouse", "moneypot", "monitor", "mousepad"};
const OutputType EXPECTED1P = {{"mobile", "moneypot", "monitor"},
                               {"mobile", "moneypot", "monitor"},
                               {"mouse", "mousepad"},
                               {"mouse", "mousepad"},
                               {"mouse", "mousepad"}};

const ArrayType SAMPLE2P = {"bags", "baggage", "banner", "box", "cloths"};
const OutputType EXPECTED2P = {
    {"baggage", "bags", "banner"}, {"baggage", "bags", "banner"}, {"baggage", "bags"}, {"bags"}};

const ArrayType SAMPLE3P = {"havana"};
const OutputType EXPECTED3P = {
    {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}};


THE_BENCHMARK(SuggestedProducts, SAMPLE1P, "mouse");

SIMPLE_TEST(SuggestedProducts, TestSAMPLE1, EXPECTED1P, SAMPLE1P, "mouse");
SIMPLE_TEST(SuggestedProducts, TestSAMPLE2, EXPECTED2P, SAMPLE2P, "bags");
SIMPLE_TEST(SuggestedProducts, TestSAMPLE3, EXPECTED3P, SAMPLE3P, "havana");
