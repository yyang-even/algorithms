#pragma once


#include "trie.h"


/**
 * @reference   Trie | (Display Content)
 *              https://www.geeksforgeeks.org/trie-display-content/
 *
 * @reference   Sorting array of strings (or words) using Trie
 *              https://www.geeksforgeeks.org/sorting-array-strings-words-using-trie/
 *
 * Given an array of strings, print them in alphabetical (dictionary) order.
 * If there are duplicates in input array, we need to print them only once.
 */
void Display(const Trie::Node *node, std::string &prefix, std::vector<std::string> &results) {
    assert(node);

    if (node->isEndOfWord) {
        results.push_back(prefix);
    }

    for (std::size_t i = 0; i < node->children.size(); ++i) {
        if (node->children[i]) {
            prefix.push_back(Trie::Node::ToChar(i));

            Display(node->children[i].get(), prefix, results);

            prefix.pop_back();
        }
    }
}
