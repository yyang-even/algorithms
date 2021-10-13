#include "common_header.h"

#include "text/text.h"

#include "trie.h"


namespace {

using Operation = std::tuple<bool, std::string_view, int>;
using ArrayType = std::vector<Operation>;
using OutputType = std::vector<int>;

/** Map Sum Pairs
 *
 * @reference   https://leetcode.com/problems/map-sum-pairs/
 *
 * Implement the MapSum class:
 *  MapSum() Initializes the MapSum object.
 *  void insert(String key, int val) Inserts the key-val pair into the map. If the key
 *      already existed, the original key-value pair will be overridden to the new one.
 *  int sum(string prefix) Returns the sum of all the pairs' value whose key starts with
 *      the prefix.
 */
auto MapSumPairs_Naive(const ArrayType &operations) {
    std::unordered_map<std::string_view, int> hash_table;

    OutputType results;
    for (const auto [is_insert, str, new_value] : operations) {
        if (is_insert) {
            hash_table[str] = new_value;
        } else {
            int total = 0;
            for (const auto [key, value] : hash_table) {
                if (StartsWith(key, str)) {
                    total += value;
                }
            }
            results.push_back(total);
        }
    }

    return results;
}


auto MapSumPairs_TwoMap(const ArrayType &operations) {
    std::unordered_map<std::string_view, int> originals;
    std::unordered_map<std::string_view, int> prefixs;

    OutputType results;
    for (const auto [is_insert, str, new_value] : operations) {
        if (is_insert) {
            const auto [iter, inserted] = originals.emplace(str, new_value);
            int delta = new_value;
            if (not inserted) {
                delta -= iter->second;
                iter->second = new_value;
            }

            for (std::size_t length = 1; length <= str.size(); ++length) {
                prefixs[str.substr(0, length)] += delta;
            }
        } else {
            results.push_back(prefixs[str]);
        }
    }

    return results;
}


using Node = TrieNode<int>;

auto MapSumPairs_Trie(const ArrayType &operations) {
    std::unordered_map<std::string_view, int> originals;
    Node root;

    OutputType results;
    for (const auto [is_insert, str, new_value] : operations) {
        if (is_insert) {
            const auto [iter, inserted] = originals.emplace(str, new_value);
            int delta = new_value;
            if (not inserted) {
                delta -= iter->second;
                iter->second = new_value;
            }

            auto *current = &root;
            for (const auto c : str) {
                const auto index = Node::ToIndex(c);
                if (not current->children[index]) {
                    current->children[index].reset(new Node{});
                }

                current = current->children[index].get();
                current->value += delta;
            }
        } else {
            results.push_back(TrieGet(root, str));
        }
    }

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {{true, "apple", 3}, {false, "ap", 0}, {true, "app", 2}, {false, "app", 0}};
const OutputType EXPECTED1 = {3, 5};


THE_BENCHMARK(MapSumPairs_Naive, SAMPLE1);

SIMPLE_TEST(MapSumPairs_Naive, TestSAMPLE1, EXPECTED1, SAMPLE1);


THE_BENCHMARK(MapSumPairs_TwoMap, SAMPLE1);

SIMPLE_TEST(MapSumPairs_TwoMap, TestSAMPLE1, EXPECTED1, SAMPLE1);


THE_BENCHMARK(MapSumPairs_Trie, SAMPLE1);

SIMPLE_TEST(MapSumPairs_Trie, TestSAMPLE1, EXPECTED1, SAMPLE1);
