#include "common_header.h"

#include "trie.h"


using ArrayType = std::vector<std::string_view>;
using OutputType = std::vector<std::pair<int, int>>;

namespace {

/** Index Pairs of a String
 *
 * @reference   https://xingxingpark.com/Leetcode-1065-Index-Pairs-of-a-String/
 *
 * Given a text string and words (a list of strings), return all index pairs [i, j] so
 * that the substring text[i]...text[j] is in the list of words.
 * Return the pairs [i,j] in sorted order (i.e. sort them by their first coordinate in
 * case of ties sort them by their second coordinate).
 */
auto IndexPairsOfString(const std::string_view text, const ArrayType &words) {
    return BuildTrie(words).Visit([text](auto & root) {
        OutputType result;
        for (std::size_t left = 0; left < text.size(); ++left) {
            auto *current = &root;
            for (auto right = left; right < text.size() and current; ++right) {
                const auto index = Trie::Node::ToIndex(text[right]);
                current = current->children[index].get();
                if (current and current->value) {
                    result.emplace_back(left, right);
                }
            }
        }

        return result;
    });
}

}


const ArrayType SAMPLE1 = {"story", "fleet", "leetcode"};
const OutputType EXPECTED1 = {{3, 7}, {9, 13}, {10, 17}};

const ArrayType SAMPLE2 = {"aba", "ab"};
const OutputType EXPECTED2 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};


THE_BENCHMARK(IndexPairsOfString, "thestoryofleetcodeandme", SAMPLE1);

SIMPLE_TEST(IndexPairsOfString, TestSAMPLE1, EXPECTED1,
            "thestoryofleetcodeandme", SAMPLE1);
SIMPLE_TEST(IndexPairsOfString, TestSAMPLE2, EXPECTED2, "ababa", SAMPLE2);
