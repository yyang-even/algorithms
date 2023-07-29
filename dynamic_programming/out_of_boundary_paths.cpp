#include "common_header.h"


namespace {

using MemoType = std::vector<std::vector<std::vector<int>>>;

/** Out of Boundary Paths
 *
 * @reference   https://leetcode.com/problems/out-of-boundary-paths/
 *
 * There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn].
 * You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the
 * grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
 * Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the
 * ball out of the grid boundary. Since the answer can be very large, return it modulo 10^9 + 7.
 */
auto OutOfBoundaryPaths_Memo(const int m,
                             const int n,
                             const int max_move,
                             const int start_row,
                             const int start_column,
                             MemoType &memo) {
    if (start_row == m or start_column == n or start_row < 0 or start_column < 0) {
        return 1;
    }
    if (max_move == 0) {
        return 0;
    }

    if (memo[start_row][start_column][max_move] >= 0) {
        return memo[start_row][start_column][max_move];
    }

    memo[start_row][start_column][max_move] =
        ((OutOfBoundaryPaths_Memo(m, n, max_move - 1, start_row - 1, start_column, memo) +
          OutOfBoundaryPaths_Memo(m, n, max_move - 1, start_row + 1, start_column, memo)) %
             LARGE_PRIME +
         (OutOfBoundaryPaths_Memo(m, n, max_move - 1, start_row, start_column - 1, memo) +
          OutOfBoundaryPaths_Memo(m, n, max_move - 1, start_row, start_column + 1, memo)) %
             LARGE_PRIME) %
        LARGE_PRIME;
    return memo[start_row][start_column][max_move];
}

inline auto OutOfBoundaryPaths_Memo(
    const int m, const int n, const int max_move, const int start_row, const int start_column) {
    auto memo = std::vector(m, std::vector(n, std::vector(max_move + 1, -1)));

    return OutOfBoundaryPaths_Memo(m, n, max_move, start_row, start_column, memo);
}


auto OutOfBoundaryPaths_DP(
    const int m, const int n, const int max_move, const int start_row, const int start_column) {
    auto dp = std::vector(m, std::vector(n, 0));
    dp[start_row][start_column] = 1;
    int count = 0;

    for (int moves = 1; moves <= max_move; ++moves) {
        auto temp = std::vector(m, std::vector(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == m - 1) {
                    count = (count + dp[i][j]) % LARGE_PRIME;
                }
                if (j == n - 1) {
                    count = (count + dp[i][j]) % LARGE_PRIME;
                }
                if (i == 0) {
                    count = (count + dp[i][j]) % LARGE_PRIME;
                }
                if (j == 0) {
                    count = (count + dp[i][j]) % LARGE_PRIME;
                }

                temp[i][j] =
                    (((i > 0 ? dp[i - 1][j] : 0) + (i < m - 1 ? dp[i + 1][j] : 0)) % LARGE_PRIME +
                     ((j > 0 ? dp[i][j - 1] : 0) + (j < n - 1 ? dp[i][j + 1] : 0)) %
                         LARGE_PRIME) %
                    LARGE_PRIME;
            }
        }
        dp.swap(temp);
    }

    return count;
}


/**
 * @reference   Knight Probability in Chessboard
 *              https://leetcode.com/problems/knight-probability-in-chessboard/
 *
 * On an n x n chessboard, a knight starts at the cell (row, column) and attempts to make exactly k
 * moves. The rows and columns are 0-indexed, so the top-left cell is (0, 0), and the bottom-right cell
 * is (n - 1, n - 1).
 * A chess knight has eight possible moves it can make, as illustrated below. Each move is two cells in
 * a cardinal direction, then one cell in an orthogonal direction.
 * Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if
 * the piece would go off the chessboard) and moves there.
 * The knight continues moving until it has made exactly k moves or has moved off the chessboard.
 * Return the probability that the knight remains on the board after it has stopped moving.
 */
auto KnightProbability(const int n, int k, const int row, const int column) {
    const std::vector<std::pair<int, int>> DIRECTIONS = {
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

    std::vector prev_dp(n, std::vector(n, 0.0));
    prev_dp[row][column] = 1;

    while (k--) {
        std::vector curr_dp(n, std::vector(n, 0.0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (const auto &[delta_i, delta_j] : DIRECTIONS) {
                    const auto prev_i = i - delta_i;
                    const auto prev_j = j - delta_j;

                    if (prev_i >= 0 and prev_i < n and prev_j >= 0 and prev_j < n) {
                        curr_dp[i][j] += prev_dp[prev_i][prev_j] / 8.0;
                    }
                }
            }
        }

        prev_dp.swap(curr_dp);
    }

    const auto result = std::accumulate(
        prev_dp.cbegin(), prev_dp.cend(), 0.0, [](const auto v, const auto &nums) {
            return v + std::accumulate(nums.cbegin(), nums.cend(), 0.0);
        });

    return result;
}

} //namespace


THE_BENCHMARK(OutOfBoundaryPaths_Memo, 2, 2, 2, 0, 0);

SIMPLE_TEST(OutOfBoundaryPaths_Memo, TestSAMPLE1, 6, 2, 2, 2, 0, 0);
SIMPLE_TEST(OutOfBoundaryPaths_Memo, TestSAMPLE2, 12, 1, 3, 3, 0, 1);


THE_BENCHMARK(OutOfBoundaryPaths_DP, 2, 2, 2, 0, 0);

SIMPLE_TEST(OutOfBoundaryPaths_DP, TestSAMPLE1, 6, 2, 2, 2, 0, 0);
SIMPLE_TEST(OutOfBoundaryPaths_DP, TestSAMPLE2, 12, 1, 3, 3, 0, 1);


THE_BENCHMARK(KnightProbability, 3, 2, 0, 0);

SIMPLE_DOUBLE_TEST(KnightProbability, TestSAMPLE1, 0.0625, 3, 2, 0, 0);
SIMPLE_DOUBLE_TEST(KnightProbability, TestSAMPLE2, 1.0, 1, 0, 0, 0);
