#include "common_header.h"


namespace {

using MemoType = std::vector<std::vector<std::vector<int>>>;

/** Out of Boundary Paths
 *
 * @reference   https://leetcode.com/problems/out-of-boundary-paths/
 *
 * There is an m x n grid with a ball. The ball is initially at the position
 * [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent
 * cells in the grid (possibly out of the grid crossing the grid boundary). You can
 * apply at most maxMove moves to the ball.
 * Given the five integers m, n, maxMove, startRow, startColumn, return the number of
 * paths to move the ball out of the grid boundary. Since the answer can be very large,
 * return it modulo 10^9 + 7.
 */
auto OutOfBoundaryPaths_Memo(const int m, const int n, const int max_move,
                             const int start_row, const int start_column, MemoType &memo) {
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
         LARGE_PRIME
        ) % LARGE_PRIME;
    return memo[start_row][start_column][max_move];
}

inline auto
OutOfBoundaryPaths_Memo(const int m, const int n, const int max_move,
                        const int start_row, const int start_column) {
    auto memo = std::vector(m, std::vector(n, std::vector(max_move + 1, -1)));

    return OutOfBoundaryPaths_Memo(m, n, max_move, start_row, start_column, memo);
}


auto OutOfBoundaryPaths_DP(const int m, const int n, const int max_move,
                           const int start_row, const int start_column) {
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
                     ((j > 0 ? dp[i][j - 1] : 0) + (j < n - 1 ? dp[i][j + 1] : 0)) % LARGE_PRIME
                    ) % LARGE_PRIME;
            }
        }
        dp.swap(temp);
    }

    return count;
}

}//namespace


THE_BENCHMARK(OutOfBoundaryPaths_Memo, 2, 2, 2, 0, 0);

SIMPLE_TEST(OutOfBoundaryPaths_Memo, TestSAMPLE1, 6, 2, 2, 2, 0, 0);
SIMPLE_TEST(OutOfBoundaryPaths_Memo, TestSAMPLE2, 12, 1, 3, 3, 0, 1);


THE_BENCHMARK(OutOfBoundaryPaths_DP, 2, 2, 2, 0, 0);

SIMPLE_TEST(OutOfBoundaryPaths_DP, TestSAMPLE1, 6, 2, 2, 2, 0, 0);
SIMPLE_TEST(OutOfBoundaryPaths_DP, TestSAMPLE2, 12, 1, 3, 3, 0, 1);
