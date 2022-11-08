#include "common_header.h"


namespace {

using DictType = std::unordered_set<std::string_view>;
using ArrayType = std::vector<std::vector<std::string_view>>;

/** Word Ladder (Length of shortest chain to reach a target word)
 *
 * @reference   https://www.geeksforgeeks.org/word-ladder-length-of-shortest-chain-to-reach-a-target-word/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.10.
 *
 * Given a dictionary, and two words 'start' and 'target' (both of same length). Find length of the
 * smallest chain from 'start' to 'target' if it exists, such that adjacent words in the chain only
 * differ by one character and each word in the chain is a valid word i.e., it exists in the dictionary.
 * It may be assumed that the 'target' word exists in dictionary and length of all dictionary words is
 * same.
 *
 * @reference   Word Ladder
 *              https://leetcode.com/problems/word-ladder/
 *
 * A transformation sequence from word beginWord to word endWord using a dictionary wordList is a
 * sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
 *  Every adjacent pair of words differs by a single letter.
 *  Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
 *  sk == endWord
 * Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the
 * shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.
 *
 * @reference   Minimum Genetic Mutation
 *              https://leetcode.com/problems/minimum-genetic-mutation/
 *
 * A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and
 * 'T'.
 * Suppose we need to investigate a mutation from a gene string startGene to a gene string endGene where
 * one mutation is defined as one single character changed in the gene string.
 *  For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
 * There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to
 * make it a valid gene string.
 * Given the two gene strings startGene and endGene and the gene bank bank, return the minimum number of
 * mutations needed to mutate from startGene to endGene. If there is no such a mutation, return -1.
 * Note that the starting point is assumed to be valid, so it might not be included in the bank.
 */
auto WordLadder(const std::string_view start,
                const std::string_view target,
                DictType dictionary) {
    assert(not start.empty());
    assert(start.size() == target.size());

    if (start == target) {
        return 0;
    }

    if (dictionary.erase(target) == 0) {
        return 0;
    }

    std::queue<std::string_view> adjacent_words;
    adjacent_words.push(start);
    dictionary.erase(start);

    int chain_length = 1;
    while (not adjacent_words.empty()) {
        ++chain_length;

        for (auto level_size = adjacent_words.size(); level_size-- > 0;) {
            std::string word {adjacent_words.front()};
            adjacent_words.pop();

            for (std::size_t i = 0; i < start.size(); ++i) {
                const auto original_char = word[i];

                for (auto c = 'A'; c <= 'Z'; ++c) {
                    word[i] = c;

                    if (word == target) {
                        return chain_length;
                    }

                    const auto iter = dictionary.find(word);
                    if (iter != dictionary.cend()) {
                        adjacent_words.push(*iter);
                        dictionary.erase(iter);
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
 *
 * @reference   Word Ladder II
 *              https://leetcode.com/problems/word-ladder-ii/
 *
 * A transformation sequence from word beginWord to word endWord using a dictionary wordList is a
 * sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
 *  Every adjacent pair of words differs by a single letter.
 *  Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in
 *  wordList.
 *  sk == endWord
 * Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest
 * transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each
 * sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].
 */
auto findNeighbors(std::string word, const DictType &word_list) {
    std::vector<std::string_view> neighbors;

    for (auto &c : word) {
        const auto original = c;

        for (auto replacement = 'a'; replacement <= 'z'; ++replacement) {
            if (replacement != original) {
                c = replacement;

                const auto iter = word_list.find(word);
                if (iter != word_list.cend()) {
                    neighbors.push_back(*iter);
                }
            }
        }

        c = original;
    }

    return neighbors;
}

using GraphType = std::unordered_map<std::string_view, std::vector<std::string_view>>;

void AllWordLadders(const std::string_view source,
                    const std::string_view destination,
                    const GraphType &dag_adjacent_list,
                    std::vector<std::string_view> &path,
                    ArrayType &results) {
    if (source == destination) {
        results.push_back(path);
    }

    const auto iter = dag_adjacent_list.find(source);
    if (iter != dag_adjacent_list.cend()) {
        for (const auto a_neighbor : iter->second) {
            path.push_back(a_neighbor);
            AllWordLadders(a_neighbor, destination, dag_adjacent_list, path, results);
            path.pop_back();
        }
    }
}

auto buildDAG(const std::string_view begin_word, DictType &word_list) {
    GraphType dag_adjacent_list;
    std::queue<std::string_view> q;
    q.push(begin_word);
    word_list.erase(begin_word);

    std::unordered_set<std::string_view> enqueued_words;
    enqueued_words.insert(begin_word);

    while (not q.empty()) {
        std::vector<std::string_view> level_words;

        for (int i = q.size(); i > 0; --i) {
            const auto a_word = q.front();
            q.pop();

            auto neighbors = findNeighbors(std::string {a_word}, word_list);
            for (const auto a_neighbor : neighbors) {
                level_words.push_back(a_neighbor);

                if (enqueued_words.insert(a_neighbor).second) {
                    q.push(a_neighbor);
                }
            }

            dag_adjacent_list[a_word] = std::move(neighbors);
        }

        for (const auto a_word : level_words) {
            word_list.erase(a_word);
        }
    }

    return dag_adjacent_list;
}

auto AllWordLadders(const std::string_view begin_word,
                    const std::string_view end_word,
                    DictType word_list) {
    const auto dag_adjacent_list = buildDAG(begin_word, word_list);

    std::vector<std::string_view> path = {begin_word};
    ArrayType results;
    AllWordLadders(begin_word, end_word, dag_adjacent_list, path, results);

    return results;
}

} //namespace


const DictType SAMPLE1 = {"POON", "PLEE", "SAME", "POIE", "PLEA", "PLIE", "POIN"};
const DictType SAMPLE2 = {"ABCD", "EBAD", "EBCD", "XYZA"};
const DictType SAMPLE3 = {"HOT", "DOT", "DOG", "LOT", "LOG", "COG"};
const DictType SAMPLE4 = {"HOT", "DOT", "DOG", "LOT", "LOG"};


THE_BENCHMARK(WordLadder, "TOON", "PLEA", SAMPLE1);

SIMPLE_TEST(WordLadder, TestSAMPLE1, 7, "TOON", "PLEA", SAMPLE1);
SIMPLE_TEST(WordLadder, TestSAMPLE2, 4, "ABCV", "EBAD", SAMPLE2);
SIMPLE_TEST(WordLadder, TestSAMPLE3, 5, "HIT", "COG", SAMPLE3);
SIMPLE_TEST(WordLadder, TestSAMPLE4, 0, "HIT", "COG", SAMPLE4);


const DictType SAMPLE6 = {"hot", "dot", "dog", "lot", "log", "cog"};
const ArrayType EXPECTED6 = {{"hit", "hot", "dot", "dog", "cog"},
                             {"hit", "hot", "lot", "log", "cog"}};

const DictType SAMPLE7 = {"hot", "dot", "dog", "lot", "log"};
const ArrayType EXPECTED7 = {};


THE_BENCHMARK(AllWordLadders, "hit", "cog", SAMPLE6);

SIMPLE_TEST(AllWordLadders, TestSAMPLE6, EXPECTED6, "hit", "cog", SAMPLE6);
SIMPLE_TEST(AllWordLadders, TestSAMPLE7, EXPECTED7, "hit", "cog", SAMPLE7);
