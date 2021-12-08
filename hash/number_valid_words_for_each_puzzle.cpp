#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Number of Valid Words for Each Puzzle
 *
 * @reference   https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/
 *
 * With respect to a given puzzle string, a word is valid if both the following conditions
 * are satisfied:
 *  word contains the first letter of puzzle.
 *  For each letter in word, that letter is in puzzle.
 *      For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage",
 *      and "baggage", while invalid words are "beefed" (does not include 'a') and "based"
 *      (includes 's' which is not in the puzzle).
 * Return an array answer, where answer[i] is the number of words in the given word list
 * words that is valid with respect to the puzzle puzzles[i].
 * puzzles[i].length == 7
 * words[i] and puzzles[i] consist of lowercase English letters.
 * Each puzzles[i] does not contain repeated characters.
 */
constexpr auto ToBitmask(const std::string_view word) {
    unsigned mask = 0;
    for (const auto c : word) {
        mask |= 1 << (c - 'a');
    }

    return mask;
}

auto
NumberValidWordsForEachPuzzle_Bitmask(const ArrayType &words,
                                      const ArrayType &puzzles) {
    std::unordered_map<unsigned, int> word_bins;

    for (const auto a_word : words) {
        ++word_bins[ToBitmask(a_word)];
    }

    std::vector<int> result;
    for (const auto a_puzzle : puzzles) {
        const auto first = ToBitmask(a_puzzle.substr(0, 1));
        auto count = word_bins[first];

        const auto sub_mask = ToBitmask(a_puzzle.substr(1));

        for (auto i = sub_mask; i; i = (i - 1) & sub_mask) {
            count += word_bins[i | first];
        }

        result.push_back(count);
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1W = {"aaaa", "asas", "able", "ability", "actt", "actor", "access"};
const ArrayType SAMPLE1P = {"aboveyz", "abrodyz", "abslute", "absoryz", "actresz", "gaswxyz"};
const std::vector EXPECTED1 = {1, 1, 3, 2, 4, 0};

const ArrayType SAMPLE2W = {"apple", "pleas", "please"};
const ArrayType SAMPLE2P = {"aelwxyz", "aelpxyz", "aelpsxy", "saelpxy", "xaelpsy"};
const std::vector EXPECTED2 = {0, 1, 3, 2, 0};


THE_BENCHMARK(NumberValidWordsForEachPuzzle_Bitmask, SAMPLE1W, SAMPLE1P);

SIMPLE_TEST(NumberValidWordsForEachPuzzle_Bitmask, TestSAMPLE1, EXPECTED1,
            SAMPLE1W, SAMPLE1P);
SIMPLE_TEST(NumberValidWordsForEachPuzzle_Bitmask, TestSAMPLE2, EXPECTED2,
            SAMPLE2W, SAMPLE2P);
