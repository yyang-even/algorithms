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
auto ValidSudoku(const BoardType &board) {
    constexpr std::size_t N = 9;
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

                const auto index = (i / 3) * 3 + j / 3;
                if (not boxes[index].insert(c).second) {
                    return false;
                }
            }
        }
    }

    return true;
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


THE_BENCHMARK(ValidSudoku, SAMPLE1);

SIMPLE_TEST(ValidSudoku, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(ValidSudoku, TestSAMPLE2, false, SAMPLE2);
