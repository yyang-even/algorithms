#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using BoardType = MatrixTypeTemplate<bool>;
using BoardArray = std::vector<BoardType>;

/** N Queen Problem | Backtracking-3
 *
 * @reference   https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/
 * @reference   N Queen Problem using Branch And Bound
 *              https://www.geeksforgeeks.org/n-queen-problem-using-branch-and-bound/
 * @reference   N Queen in O(n) space
 *              https://www.geeksforgeeks.org/n-queen-in-on-space/
 *
 * The N Queen is the problem of placing N chess queens on an N*N chessboard so that no two queens
 * attack each other.
 *
 * @reference   8 queen problem
 *              https://www.geeksforgeeks.org/8-queen-problem/
 *
 * The eight queens problem is the problem of placing eight queens on an 8*8 chessboard such that
 * none of them attack one another (no two are in the same row, column, or diagonal). More generally,
 * the n queens problem places n queens on an n*n chessboard.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.9.
 * @reference   Printing all solutions in N-Queen Problem
 *              https://www.geeksforgeeks.org/printing-solutions-n-queen-problem/
 *
 * @note    One easy optimization is to cache which diagonal is occupied, instead of checking every
 * cell.
 */
auto isSafeSoFar(const BoardType &board, const int row, const int column) {
    for (int j = 0; j < column; ++j) {
        if (board[row][j]) {
            return false;
        }
    }

    for (int i = row, j = column; i >= 0 and j >= 0; --i, --j) {
        if (board[i][j]) {
            return false;
        }
    }

    std::size_t i = row;
    for (int j = column; j >= 0 and i < board.size(); ++i, --j) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

auto FirstNQueenSolution(BoardType &board, const unsigned column = 0) {
    const auto N = board.size();
    if (column >= N) {
        return true;
    }

    for (BoardType::size_type i = 0; i < N; ++i) {
        if (isSafeSoFar(board, i, column)) {
            board[i][column] = true;

            if (FirstNQueenSolution(board, column + 1)) {
                return true;
            }

            board[i][column] = false;
        }
    }

    return false;
}

inline auto FirstNQueenSolution(const unsigned N) {
    auto board = std::vector(N, BoardType::value_type(N, false));
    FirstNQueenSolution(board);

    return board;
}


/**
 * @reference   N-Queens
 *              https://leetcode.com/problems/n-queens/
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two
 * queens attack each other.
 * Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the
 * answer in any order.
 * Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and
 * '.' both indicate a queen and an empty space, respectively.
 *
 * @reference   N-Queens II
 *              https://leetcode.com/problems/n-queens-ii/
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two
 * queens attack each other.
 * Given an integer n, return the number of distinct solutions to the n-queens puzzle.
 */
auto NQueen(BoardType &board, const std::size_t column, BoardArray &results) {
    const auto N = board.size();
    if (column >= N) {
        results.push_back(board);
        return true;
    }

    for (BoardType::size_type i = 0; i < N; ++i) {
        if (isSafeSoFar(board, i, column)) {
            board[i][column] = true;

            NQueen(board, column + 1, results);

            board[i][column] = false;
        }
    }

    return false;
}

inline auto NQueen(const unsigned N) {
    auto board = std::vector(N, BoardType::value_type(N, false));
    BoardArray results;
    NQueen(board, 0, results);

    return results;
}

} //namespace


// clang-format off
const BoardArray EXPECTED1A = {{
    {0, 0, 1, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 1},
    {0, 1, 0, 0}
}, {
    {0, 1, 0, 0},
    {0, 0, 0, 1},
    {1, 0, 0, 0},
    {0, 0, 1, 0}
}};

const BoardType EXPECTED2 = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0}
};
// clang-format on


THE_BENCHMARK(FirstNQueenSolution, 8);

SIMPLE_TEST(FirstNQueenSolution, TestSAMPLE1, EXPECTED1A.front(), 4);
SIMPLE_TEST(FirstNQueenSolution, TestSAMPLE2, EXPECTED2, 8);


THE_BENCHMARK(NQueen, 8);

SIMPLE_TEST(NQueen, TestSAMPLE1, EXPECTED1A, 4);
