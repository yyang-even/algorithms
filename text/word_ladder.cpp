#include "common_header.h"


namespace {

using DictType = std::unordered_set<std::string_view>;

/** Word Ladder (Length of shortest chain to reach a target word)
 *
 * @reference   https://www.geeksforgeeks.org/word-ladder-length-of-shortest-chain-to-reach-a-target-word/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.10.
 *
 * Given a dictionary, and two words 'start' and 'target' (both of same length). Find
 * length of the smallest chain from 'start' to 'target' if it exists, such that adjacent
 * words in the chain only differ by one character and each word in the chain is a valid
 * word i.e., it exists in the dictionary. It may be assumed that the 'target' word
 * exists in dictionary and length of all dictionary words is same.
 */
auto WordLadder(const std::string &start, const std::string_view target,
                DictType dictionary) {
    assert(not start.empty());
    assert(start.size() == target.size());

    if (start == target) {
        return 0;
    }

    std::queue<std::string> adjacent_words;
    adjacent_words.push(start);
    dictionary.erase(start);

    int chain_length = 1;
    while (not adjacent_words.empty()) {
        ++chain_length;

        for (auto level_size = adjacent_words.size(); level_size-- > 0;) {
            auto word = std::move(adjacent_words.front());
            adjacent_words.pop();

            for (std::size_t i = 0; i < start.size(); ++i) {
                const auto original_char = word[i];

                for (auto c = 'A'; c <= 'Z'; ++c) {
                    word[i] = c;

                    if (word == target) {
                        return chain_length;
                    }

                    if (dictionary.erase(word) != 0) {
                        adjacent_words.push(word);
                    }
                }

                word[i] = original_char;
            }
        }
    }

    return 0;
}


/**
 * @reference   Word Ladder – Set 2 ( Bi-directional BFS )
 *              https://www.geeksforgeeks.org/word-ladder-set-2-bi-directional-bfs/
 *
 * @hint    Search from both ends, and meet-in-the-middle.
 */


/**
 * @reference   Print all possible shortest chains to reach a target word
 *              https://www.geeksforgeeks.org/print-all-possible-shortest-chains-to-reach-a-target-word/
 */

}//namespace


const DictType SAMPLE1 = {"POON", "PLEE", "SAME", "POIE", "PLEA", "PLIE", "POIN"};
const DictType SAMPLE2 = {"ABCD", "EBAD", "EBCD", "XYZA"};
const DictType SAMPLE3 = {"ABCD", "EBCD", "XYZA"};


THE_BENCHMARK(WordLadder, "TOON", "PLEA", SAMPLE1);

SIMPLE_TEST(WordLadder, TestSAMPLE1, 7, "TOON", "PLEA", SAMPLE1);
SIMPLE_TEST(WordLadder, TestSAMPLE2, 4, "ABCV", "EBAD", SAMPLE2);
SIMPLE_TEST(WordLadder, TestSAMPLE3, 4, "ABCV", "EBAD", SAMPLE3);
