#include "common_header.h"

#include "trie.h"


using ArrayType = std::vector<std::string_view>;
using RowType = std::vector<char>;
using BoolRowType = std::vector<bool>;
using BoardType = std::vector<RowType>;
using OutputType = std::unordered_set<std::string>;

namespace {

/** Boggle (Find all possible words in a board of characters) | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/boggle-find-possible-words-board-characters/
 * @reference   Boggle | Set 2 (Using Trie)
 *              https://www.geeksforgeeks.org/boggle-set-2-using-trie/
 *
 * Given a dictionary, a method to do a lookup in the dictionary and a M x N board where
 * every cell has one character. Find all possible words that can be formed by a sequence
 * of adjacent characters. Note that we can move to any of 8 adjacent characters, but a
 * word should not have multiple instances of the same cell.
 */
void Boggle(const Trie::Node::PointerType node,
            const BoardType &board,
            const int i, const int j,
            std::vector<BoolRowType> &visited,
            std::string &prefix,
            OutputType &results);

inline void
BoggleHelper(const Trie::Node *node,
             const BoardType &board,
             const int i, const int j,
             std::vector<BoolRowType> &visited,
             std::string &prefix,
             OutputType &results) {
    assert(node);

    const auto c = board[i][j];
    const auto index = Trie::Node::ToIndex(c);
    if (node->children[index]) {
        prefix.push_back(c);
        Boggle(node->children[index], board, i, j, visited, prefix, results);
        prefix.pop_back();
    }
}

void Boggle(const Trie::Node::PointerType node,
            const BoardType &board,
            const int i, const int j,
            std::vector<BoolRowType> &visited,
            std::string &prefix,
            OutputType &results) {
    assert(node);
    assert(i < static_cast<int>(board.size()));
    assert(j < static_cast<int>(board.front().size()));

    if (node->isEndOfWord) {
        results.insert(prefix);
    }

    if (not visited[i][j]) {
        visited[i][j] = true;

        for (auto new_i = i - 1; new_i <= i + 1; ++new_i) {
            for (auto new_j = j - 1; new_j <= j + 1; ++new_j) {
                if (new_i != i or new_j != j) {
                    if (new_i >= 0 and new_i < static_cast<int>(board.size()) and
                        new_j >= 0 and new_j < static_cast<int>(board.front().size())) {
                        BoggleHelper(node.get(), board, new_i, new_j, visited, prefix, results);
                    }
                }
            }
        }

        visited[i][j] = false;
    }
}

inline auto Boggle(const ArrayType &keys, const BoardType &board) {
    return BuildTrie(keys).Visit([&board](const auto & root) {
        std::string prefix;
        auto visited =
            std::vector<BoolRowType>(board.size(), BoolRowType(board.front().size(), false));
        OutputType results;

        for (std::size_t i = 0; i < board.size(); ++i) {
            for (std::size_t j = 0; j < board.front().size(); ++j) {
                BoggleHelper(&root, board, i, j, visited, prefix, results);
            }
        }

        return results;
    });
}

}//namespace


const ArrayType KEYS1 = {"geeks", "for", "quiz", "gee"};
const BoardType BOARD1 = {
    { 'g', 'i', 'z' },
    { 'u', 'e', 'k' },
    { 'q', 's', 'e' }
};
const OutputType EXPECTED1 = {"gee", "geeks", "quiz"};


THE_BENCHMARK(Boggle, KEYS1, BOARD1);

SIMPLE_TEST(Boggle, TestSAMPLE1, EXPECTED1, KEYS1, BOARD1);
