#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using BoardType = MatrixTypeTemplate<char>;

/** Valid Sudoku
 *
 * @reference   https://leetcode.com/problems/valid-sudoku/
 *
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated
 * according to the following rules:
 *  Each row must contain the digits 1-9 without repetition.
 *  Each column must contain the digits 1-9 without repetition.
 *  Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without
 *      repetition.
 * Note:
 *  A Sudoku board (partially filled) could be valid but is not necessarily solvable.
 *  Only the filled cells need to be validated according to the mentioned rules.
 *
 * @note    Alternatively, one may also use arrays, or binary numbers to record
 * previously seen numbers.
 */
constexpr std::size_t N = 9;

inline constexpr auto
boxIndex(const std::size_t i, const std::size_t j) {
    return (i / 3) * 3 + j / 3;
}

auto ValidSudoku(const BoardType &board) {
    assert(board.size() == N);
    assert(board.front().size() == N);

    std::unordered_set<char> rows[N] = {};
    std::unordered_set<char> columns[N] = {};
    std::unordered_set<char> boxes[N] = {};

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            const auto c = board[i][j];
            if (std::isdigit(c)) {
                if (not rows[i].insert(c).second) {
                    return false;
                }

                if (not columns[j].insert(c).second) {
                    return false;
                }

                if (not boxes[boxIndex(i, j)].insert(c).second) {
                    return false;
                }
            }
        }
    }

    return true;
}


/**
 * @reference   Check if Every Row and Column Contains All Numbers
 *              https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/
 *
 * An n x n matrix is valid if every row and every column contains all the integers from
 * 1 to n (inclusive).
 * Given an n x n integer matrix matrix, return true if the matrix is valid. Otherwise,
 * return false.
 */


/**
 * @reference   Sudoku Solver
 *              https://leetcode.com/problems/sudoku-solver/
 *
 * Write a program to solve a Sudoku puzzle by filling the empty cells. A sudoku solution
 * must satisfy all of the following rules:
 *
 * Each of the digits 1-9 must occur exactly once in each row.
 * Each of the digits 1-9 must occur exactly once in each column.
 * Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
 * The '.' character indicates empty cells.
 */
inline constexpr void
unset(const std::size_t i, const std::size_t j,  bool rows[N][N],
      bool columns[N][N], bool boxes[N][N], const char c) {
    const auto c_index = c - '1';
    rows[i][c_index] = columns[j][c_index] = boxes[boxIndex(i, j)][c_index] = false;
}

inline constexpr void
set(const std::size_t i, const std::size_t j,  bool rows[N][N],
    bool columns[N][N], bool boxes[N][N], const char c) {
    const auto c_index = c - '1';
    rows[i][c_index] = columns[j][c_index] = boxes[boxIndex(i, j)][c_index] = true;
}

void buildBoards(const BoardType &board, bool rows[N][N],
                 bool columns[N][N], bool boxes[N][N]) {
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            const auto c = board[i][j];
            if (std::isdigit(c)) {
                set(i, j, rows, columns, boxes, c);
            }
        }
    }
}

inline constexpr auto
valid(const std::size_t i, const std::size_t j,  bool rows[N][N],
      bool columns[N][N], bool boxes[N][N], const char c) {
    const auto c_index = c - '1';
    return not(rows[i][c_index] or columns[j][c_index] or boxes[boxIndex(i, j)][c_index]);
}

auto SudokuSolver(BoardType &board, const std::size_t i, const std::size_t j,
                  bool rows[N][N], bool columns[N][N], bool boxes[N][N]) {
    if (i == N) {
        return true;
    }

    if (j >= N) {
        return SudokuSolver(board, i + 1, 0, rows, columns, boxes);
    }

    if (board[i][j] != '.') {
        return SudokuSolver(board, i, j + 1, rows, columns, boxes);
    }

    for (auto c = '1'; c <= '9'; ++c) {
        if (valid(i, j, rows, columns, boxes, c)) {
            board[i][j] = c;
            set(i, j, rows, columns, boxes, c);

            if (SudokuSolver(board, i, j + 1, rows, columns, boxes)) {
                return true;
            }

            board[i][j] = '.';
            unset(i, j, rows, columns, boxes, c);
        }
    }

    return false;
}

auto SudokuSolver(BoardType board) {
    assert(board.size() == N);
    assert(board.front().size() == N);

    bool rows[N][N] = {};
    bool columns[N][N] = {};
    bool boxes[N][N] = {};

    buildBoards(board, rows, columns, boxes);

    SudokuSolver(board, 0, 0, rows, columns, boxes);

    return board;
}

}//namespace


const BoardType SAMPLE1 = {
    {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
    {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
    {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
    {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
    {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
    {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
    {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
    {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
    {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
};

const BoardType SAMPLE2 = {
    {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
    {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
    {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
    {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
    {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
    {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
    {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
    {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
    {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
};

const BoardType EXPECTED1 = {
    {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
    {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
    {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
    {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
    {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
    {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
    {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
    {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
    {'3', '4', '5', '2', '8', '6', '1', '7', '9'}
};


THE_BENCHMARK(ValidSudoku, SAMPLE1);

SIMPLE_TEST(ValidSudoku, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(ValidSudoku, TestSAMPLE2, false, SAMPLE2);


THE_BENCHMARK(SudokuSolver, SAMPLE1);

SIMPLE_TEST(SudokuSolver, TestSAMPLE1, EXPECTED1, SAMPLE1);
