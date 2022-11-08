#include "common_header.h"

#include "matrix.h"


namespace {

using ArrayType = std::vector<int>;

/** Where Will the Ball Fall
 *
 * @reference   https://leetcode.com/problems/where-will-the-ball-fall/
 *
 * You have a 2-D grid of size m x n representing a box, and you have n balls. The box is open on the
 * top and bottom sides.
 * Each cell in the box has a diagonal board spanning two corners of the cell that can redirect a ball
 * to the right or to the left.
 *  A board that redirects the ball to the right spans the top-left corner to the bottom-right corner
 *      and is represented in the grid as 1.
 *  A board that redirects the ball to the left spans the top-right corner to the bottom-left corner and
 *      is represented in the grid as -1.
 * We drop one ball at the top of each column of the box. Each ball can get stuck in the box or fall out
 * of the bottom. A ball gets stuck if it hits a "V" shaped pattern between two boards or if a board
 * redirects the ball into either wall of the box.
 * Return an array answer of size n where answer[i] is the column that the ball falls out of at the
 * bottom after dropping the ball from the ith column at the top, or -1 if the ball gets stuck in the
 * box.
 */
auto findBallDropColumn(const std::size_t row, const int column, const MatrixType &grid) {
    if (row == grid.size()) {
        return column;
    }

    const int next_column = column + grid[row][column];
    const int N = grid.front().size();
    if (next_column < 0 or next_column > N - 1 or grid[row][column] != grid[row][next_column]) {
        return -1;
    }

    return findBallDropColumn(row + 1, next_column, grid);
}

auto FindBall_Recursive(const MatrixType &grid) {
    ArrayType result;
    for (std::size_t i = 0; i < grid.front().size(); ++i) {
        result.push_back(findBallDropColumn(0, i, grid));
    }

    return result;
}


auto FindBall_Iterative(const MatrixType &grid) {
    const int N = grid.front().size();
    ArrayType result;

    for (int column = 0; column < N; ++column) {
        int current_column = column;
        for (std::size_t row = 0; row < grid.size(); ++row) {
            const int next_column = current_column + grid[row][current_column];
            if (next_column < 0 or next_column > N - 1 or
                grid[row][current_column] != grid[row][next_column]) {
                current_column = -1;
                break;
            }
            current_column = next_column;
        }
        result.push_back(current_column);
    }

    return result;
}


auto FindBall_DP(const MatrixType &grid) {
    const int N = grid.front().size();
    const int M = grid.size();
    ArrayType result;
    MatrixType dp(M + 1, std::vector(N, 0));

    for (int row = M; row >= 0; --row) {
        for (int column = 0; column < N; ++column) {
            if (row == M) {
                dp[row][column] = column;
                continue;
            }

            const int next_column = column + grid[row][column];
            if (next_column < 0 or next_column > N - 1 or
                grid[row][column] != grid[row][next_column]) {
                dp[row][column] = -1;
            } else {
                dp[row][column] = dp[row + 1][next_column];
            }

            if (row == 0) {
                result.push_back(dp[row][column]);
            }
        }
    }

    return result;
}

} //namespace


// clang-format off
const MatrixType SAMPLE1 = {
    {1, 1, 1, -1, -1},
    {1, 1, 1, -1, -1},
    {-1, -1, -1, 1, 1},
    {1, 1, 1, 1, -1},
    {-1, -1, -1, -1, -1}
};
// clang-format on
const ArrayType EXPECTED1 = {1, -1, -1, -1, -1};

const MatrixType SAMPLE2 = {{-1}};
const ArrayType EXPECTED2 = {-1};

// clang-format off
const MatrixType SAMPLE3 = {
    {1, 1, 1, 1, 1, 1},
    {-1, -1, -1, -1, -1, -1},
    {1, 1, 1, 1, 1, 1},
    {-1, -1, -1, -1, -1, -1}
};
// clang-format on
const ArrayType EXPECTED3 = {0, 1, 2, 3, 4, -1};


THE_BENCHMARK(FindBall_Recursive, SAMPLE1);

SIMPLE_TEST(FindBall_Recursive, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindBall_Recursive, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(FindBall_Recursive, TestSAMPLE3, EXPECTED3, SAMPLE3);


THE_BENCHMARK(FindBall_Iterative, SAMPLE1);

SIMPLE_TEST(FindBall_Iterative, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindBall_Iterative, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(FindBall_Iterative, TestSAMPLE3, EXPECTED3, SAMPLE3);


THE_BENCHMARK(FindBall_DP, SAMPLE1);

SIMPLE_TEST(FindBall_DP, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindBall_DP, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(FindBall_DP, TestSAMPLE3, EXPECTED3, SAMPLE3);
