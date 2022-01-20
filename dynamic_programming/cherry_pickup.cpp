#include "common_header.h"

#include "mathematics/matrix/matrix.h"


using MemoType = std::vector<std::vector<std::vector<int>>>;


namespace {

/** Cherry Pickup
 *
 * @reference   https://leetcode.com/problems/cherry-pickup/
 *
 * You are given an n x n grid representing a field of cherries, each cell is one of three
 * possible integers.
 *  0 means the cell is empty, so you can pass through,
 *  1 means the cell contains a cherry that you can pick up and pass through, or
 *  -1 means the cell contains a thorn that blocks your way.
 * Return the maximum number of cherries you can collect by following the rules below:
 *  Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down
 *      through valid path cells (cells with value 0 or 1).
 *  After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid
 *      path cells.
 *  When passing through a path cell containing a cherry, you pick it up, and the cell
 *      becomes an empty cell 0.
 *  If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be
 *      collected.
 *
 * @difficulty  Hard
 */
auto CherryPickRoundTrip(const MatrixType &grid) {
    const int N = grid.size();
    const auto M = (N << 1) - 1;
    std::vector dp(N, std::vector(N, 0));
    dp[0][0] = grid[0][0];

    for (int n = 1; n < M; ++n) {
        for (int i = N - 1; i >= 0; --i) {
            for (int p = N - 1; p >= 0; --p) {
                const auto j = n - i;
                const auto q = n - p;

                if (j < 0 or j >= N or q < 0 or q >= N or grid[i][j] < 0 or grid[p][q] < 0) {
                    dp[i][p] = -1;
                    continue;
                }

                if (i > 0) {
                    dp[i][p] = std::max(dp[i][p], dp[i - 1][p]);
                }
                if (p > 0) {
                    dp[i][p] = std::max(dp[i][p], dp[i][p - 1]);
                }
                if (i > 0 and p > 0) {
                    dp[i][p] = std::max(dp[i][p], dp[i - 1][p - 1]);
                }

                if (dp[i][p] >= 0) {
                    dp[i][p] += grid[i][j] + (i != p ? grid[p][q] : 0);
                }
            }
        }
    }

    return std::max(dp[N - 1][N - 1], 0);
}


/**
 * @reference   Cherry Pickup II
 *              https://leetcode.com/problems/cherry-pickup-ii/
 *
 * You are given a rows x cols matrix grid representing a field of cherries where grid[i][j]
 * represents the number of cherries that you can collect from the (i, j) cell. You have
 * two robots that can collect cherries for you:
 *  Robot #1 is located at the top-left corner (0, 0), and
 *  Robot #2 is located at the top-right corner (0, cols - 1).
 * Return the maximum number of cherries collection using both robots by following the
 * rules below:
 *  From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
 *  When any robot passes through a cell, It picks up all cherries, and the cell becomes
 *      an empty cell.
 *  When both robots stay in the same cell, only one takes the cherries.
 *  Both robots cannot move outside of the grid at any moment.
 *  Both robots should reach the bottom row in grid.
 */
auto CherryPickup_Memo(const MatrixType &grid, const std::size_t r,
                       const int c1, const int c2, MemoType &memo) {
    if (r == grid.size()) {
        return 0;
    }

    if (memo[r][c1][c2] != -1) {
        return memo[r][c1][c2];
    }

    int result = 0;
    const int N = grid.front().size();
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            const auto nc1 = c1 + i;
            const auto nc2 = c2 + j;
            if (nc1 >= 0 and nc1 < N and nc2 >= 0 and nc2 < N) {
                result = std::max(result, CherryPickup_Memo(grid, r + 1, nc1, nc2, memo));
            }
        }
    }
    result += (c1 == c2 ? grid[r][c1] : grid[r][c1] + grid[r][c2]);

    return memo[r][c1][c2] = result;
}

inline auto CherryPickup_Memo(const MatrixType &grid) {
    const auto N = grid.front().size();
    std::vector memo(grid.size(), std::vector(N, std::vector(N, -1)));

    return CherryPickup_Memo(grid, 0, 0, N - 1, memo);
}


auto CherryPickup_DP(const MatrixType &grid) {
    const int M = grid.size();
    const int N = grid[0].size();
    int dp[M][N][N] = {};

    for (int r = M - 1; r >= 0; --r) {
        for (int c1 = 0; c1 < N; ++c1) {
            for (int c2 = 0; c2 < N; ++c2) {
                int result = 0;
                if (r != M - 1) {
                    for (int nc1 = c1 - 1; nc1 <= c1 + 1; ++nc1) {
                        for (int nc2 = c2 - 1; nc2 <= c2 + 1; ++nc2) {
                            if (nc1 >= 0 and nc1 < N and nc2 >= 0 and nc2 < N) {
                                result = std::max(result, dp[r + 1][nc1][nc2]);
                            }
                        }
                    }
                }

                result += grid[r][c1];
                if (c1 != c2) {
                    result += grid[r][c2];
                }

                dp[r][c1][c2] = result;
            }
        }
    }

    return dp[0][0][N - 1];
}

}//namespace


const MatrixType SAMPLE1 = {
    {0, 1, -1},
    {1, 0, -1},
    {1, 1, 1}
};

const MatrixType SAMPLE2 = {
    {1, 1, -1},
    {1, -1, 1},
    {-1, 1, 1}
};

const MatrixType SAMPLE3 = {
    {1, 1, 1, 0, 1},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 0, 1, 1, 1}
};


THE_BENCHMARK(CherryPickRoundTrip, SAMPLE1);

SIMPLE_TEST(CherryPickRoundTrip, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(CherryPickRoundTrip, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(CherryPickRoundTrip, TestSAMPLE3, 8, SAMPLE3);


const MatrixType SAMPLE1C = {
    {3, 1, 1},
    {2, 5, 1},
    {1, 5, 5},
    {2, 1, 1}
};

const MatrixType SAMPLE2C = {
    {1, 0, 0, 0, 0, 0, 1},
    {2, 0, 0, 0, 0, 3, 0},
    {2, 0, 9, 0, 0, 0, 0},
    {0, 3, 0, 5, 4, 0, 0},
    {1, 0, 2, 3, 0, 0, 6}
};


THE_BENCHMARK(CherryPickup_Memo, SAMPLE1C);

SIMPLE_TEST(CherryPickup_Memo, TestSAMPLE1, 24, SAMPLE1C);
SIMPLE_TEST(CherryPickup_Memo, TestSAMPLE2, 28, SAMPLE2C);


THE_BENCHMARK(CherryPickup_DP, SAMPLE1C);

SIMPLE_TEST(CherryPickup_DP, TestSAMPLE1, 24, SAMPLE1C);
SIMPLE_TEST(CherryPickup_DP, TestSAMPLE2, 28, SAMPLE2C);
