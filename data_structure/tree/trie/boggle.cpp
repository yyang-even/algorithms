#include "common_header.h"

#include "trie.h"


using ArrayType = std::vector<std::string_view>;
using RowType = std::vector<char>;
using BoolRowType = std::vector<bool>;
using BoardType = std::vector<RowType>;
using OutputType = std::unordered_multiset<std::string>;

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

    if (node->value) {
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


/**
 * @reference   Word Search
 *              https://leetcode.com/problems/word-search/
 *
 * Given an m x n grid of characters board and a string word, return true if word exists
 * in the grid. The word can be constructed from letters of sequentially adjacent cells,
 * where adjacent cells are horizontally or vertically neighboring. The same letter cell
 * may not be used more than once.
 * Follow up: Could you use search pruning to make your solution faster with a larger board?
 */
auto
WordSearch(BoardType &board, const std::string_view word, const std::size_t i,
           const int x, const int y) {
    const int M = board.size();
    const int N = board.front().size();
    if (x < 0 or x == M or y < 0 or y == N or word[i] != board[x][y]) {
        return false;
    }

    if (i + 1 == word.size()) {
        return true;
    }

    const auto current = board[x][y];
    board[x][y] = 0;
    const auto found = WordSearch(board, word, i + 1, x + 1, y)
                       or WordSearch(board, word, i + 1, x - 1, y)
                       or WordSearch(board, word, i + 1, x, y + 1)
                       or WordSearch(board, word, i + 1, x, y - 1);
    board[x][y] = current;

    return found;
}

auto WordSearch(BoardType board, const std::string_view word) {
    for (std::size_t i = 0; i < board.size(); ++i) {
        for (std::size_t j = 0; j < board.front().size(); ++j) {
            if (WordSearch(board, word, 0, i, j)) {
                return true;
            }
        }
    }

    return false;
}


/**
 * @reference   Word Search II
 *              https://leetcode.com/problems/word-search-ii/
 *
 * Given an m x n board of characters and a list of strings words, return all words on
 * the board. Each word must be constructed from letters of sequentially adjacent cells,
 * where adjacent cells are horizontally or vertically neighboring. The same letter cell
 * may not be used more than once in a word.
 * words[i] consists of lowercase English letters.
 * All the strings of words are unique.
 */
using Node = TrieNode<std::string_view>;
using ResultType = std::unordered_multiset<std::string_view>;

auto buildTrie(const ArrayType &words) {
    Node root;
    for (const auto a_word : words) {
        TrieInsert(root, a_word, a_word);
    }

    return root;
}

void ManyWordSearch(BoardType &board, Node &trie_node,
                    const int x, const int y, ResultType &result) {
    const int M = board.size();
    const int N = board.front().size();

    if (x < 0 or x == M or y < 0 or y == N or board[x][y] == 0) {
        return;
    }

    const auto curr = board[x][y];
    const auto next = trie_node.children[Node::ToIndex(curr)];

    if (not next) {
        return;
    }

    if (not next->value.empty()) {
        result.insert(next->value);
        next->value = {};
    }

    board[x][y] = 0;
    ManyWordSearch(board, *next, x + 1, y, result);
    ManyWordSearch(board, *next, x - 1, y, result);
    ManyWordSearch(board, *next, x, y + 1, result);
    ManyWordSearch(board, *next, x, y - 1, result);
    board[x][y] = curr;
}

auto ManyWordSearch(BoardType board, const ArrayType &words) {
    auto trie_root = buildTrie(words);

    ResultType result;
    for (std::size_t i = 0; i < board.size(); ++i) {
        for (std::size_t j = 0; j < board.front().size(); ++j) {
            ManyWordSearch(board, trie_root, i, j, result);
        }
    }

    return result;
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


const BoardType BOARD2 = {
    {'A', 'B', 'C', 'E'},
    {'S', 'F', 'C', 'S'},
    {'A', 'D', 'E', 'E'}
};


THE_BENCHMARK(WordSearch, BOARD2, "ABCCED");

SIMPLE_TEST(WordSearch, TestSAMPLE1, true, BOARD2, "ABCCED");
SIMPLE_TEST(WordSearch, TestSAMPLE2, true, BOARD2, "SEE");
SIMPLE_TEST(WordSearch, TestSAMPLE3, false, BOARD2, "ABCB");


const ArrayType KEYS1S = {"oath", "pea", "eat", "rain"};
const BoardType BOARD1S = {
    {'o', 'a', 'a', 'n'},
    {'e', 't', 'a', 'e'},
    {'i', 'h', 'k', 'r'},
    {'i', 'f', 'l', 'v'}
};
const ResultType EXPECTED1S = {"eat", "oath"};

const ArrayType KEYS2S = {"abcb"};
const BoardType BOARD2S = {
    {'a', 'b'},
    {'c', 'd'}
};
const ResultType EXPECTED2S = {};


THE_BENCHMARK(ManyWordSearch, BOARD1S, KEYS1S);

SIMPLE_TEST(ManyWordSearch, TestSAMPLE1, EXPECTED1S, BOARD1S, KEYS1S);
SIMPLE_TEST(ManyWordSearch, TestSAMPLE2, EXPECTED2S, BOARD2S, KEYS2S);
