#include "common_header.h"

#include "matrix.h"


namespace {

/** Transform to Chessboard
 *
 * @reference   https://leetcode.com/problems/transform-to-chessboard/
 *
 * You are given an n x n binary grid board. In each move, you can swap any two rows
 * with each other, or any two columns with each other. Return the minimum number of
 * moves to transform the board into a chessboard board. If the task is impossible,
 * return -1. A chessboard board is a board where no 0's and no 1's are 4-directionally
 * adjacent.
 */
auto ToChessboard(const MatrixType &board) {
    const int N = board.size();
    int row_sum = 0, column_sum = 0, misplaced_rows = 0, misplaced_columns = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[0][0]^board[i][0]^board[0][j]^board[i][j]) {
                return -1;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        row_sum += board[0][i];
        column_sum += board[i][0];
        misplaced_rows += (board[i][0] == i % 2);
        misplaced_columns += (board[0][i] == i % 2);
    }
    if (row_sum != N / 2 and row_sum != (N + 1) / 2) {
        return -1;
    }
    if (column_sum != N / 2 and column_sum != (N + 1) / 2) {
        return -1;
    }

    if (N % 2) {
        if (misplaced_columns % 2) {
            misplaced_columns = N - misplaced_columns;
        }
        if (misplaced_rows % 2) {
            misplaced_rows = N - misplaced_rows;
        }
    } else {
        misplaced_columns = std::min(N - misplaced_columns, misplaced_columns);
        misplaced_rows = std::min(N - misplaced_rows, misplaced_rows);
    }

    return (misplaced_columns + misplaced_rows) / 2;
}


/**
 * @reference   Determine Color of a Chessboard Square
 *              https://leetcode.com/problems/determine-color-of-a-chessboard-square/
 *
 * You are given coordinates, a string that represents the coordinates of a square of the
 * chessboard.
 * Return true if the square is white, and false if the square is black.
 * The coordinate will always represent a valid chessboard square. The coordinate will
 * always have the letter first, and the number second.
 */
inline constexpr bool IsWhite(const std::string_view c) {
    return (c[0] + c[1]) % 2;
}

}//namespace


const MatrixType SAMPLE1 = {
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1}
};

const MatrixType SAMPLE2 = {
    {0, 1},
    {1, 0}
};

const MatrixType SAMPLE3 = {
    {1, 0},
    {1, 0}
};


THE_BENCHMARK(ToChessboard, SAMPLE1);

SIMPLE_TEST(ToChessboard, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(ToChessboard, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(ToChessboard, TestSAMPLE3, -1, SAMPLE3);


THE_BENCHMARK(IsWhite, "a1");

SIMPLE_TEST(IsWhite, TestSAMPLE1, false, "a1");
SIMPLE_TEST(IsWhite, TestSAMPLE2, true, "h3");
SIMPLE_TEST(IsWhite, TestSAMPLE3, false, "c7");
