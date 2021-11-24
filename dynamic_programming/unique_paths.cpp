#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<int>;

/** Unique Paths
 *
 * @reference   https://leetcode.com/problems/unique-paths/
 *
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the
 * diagram below). The robot can only move either down or right at any point in time.
 * The robot is trying to reach the bottom-right corner of the grid (marked 'Finish'
 * in the diagram below). How many possible unique paths are there?
 *
 * (m+n)! / (m! * n!)
 */
constexpr int combine(const int m, const int n) {
    assert(m >= n);

    long result = 1;
    int j = 1;
    for (int i = m + 1; i <= m + n; ++i, ++j) {
        result *= i;
        result /= j;
    }

    return result;
}

constexpr auto UniquePaths(const int m, const int n) {
    if (m == 1 or n == 1) {
        return 1;
    }

    if (m < n) {
        return combine(n - 1, m - 1);
    }
    return combine(m - 1, n - 1);
}


/**
 * @reference   Unique Paths II
 *              https://leetcode.com/problems/unique-paths-ii/
 *
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the
 * diagram below). The robot can only move either down or right at any point in time.
 * The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in
 * the diagram below). Now consider if some obstacles are added to the grids. How many
 * unique paths would there be? An obstacle and space is marked as 1 and 0 respectively
 * in the grid.
 */
auto UniquePathsWithObstacles(const MatrixType &grid) {
    const auto M = grid.size();
    const auto N = grid.front().size();

    int dp[N] = {1};
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j]) {
                dp[j] = 0;
            } else if (j > 0) {
                dp[j] += dp[j - 1];
            }
        }
    }

    return dp[N - 1];
}


/**
 * @reference   Unique Paths III
 *              https://leetcode.com/problems/unique-paths-iii/
 *
 * You are given an m x n integer array grid where grid[i][j] could be:
 *  1 representing the starting square. There is exactly one starting square.
 *  2 representing the ending square. There is exactly one ending square.
 *  0 representing empty squares we can walk over.
 *  -1 representing obstacles that we cannot walk over.
 * Return the number of 4-directional walks from the starting square to the ending square,
 * that walk over every non-obstacle square exactly once.
 */
void UniquePaths3(MatrixType &grid, const int x, const int y,
                  const int to_visit, int &result) {
    const int M = grid.size();
    const int N = grid.front().size();

    if (x < 0 or x >= M or y < 0 or y >= N or grid[x][y] == -1) {
        return;
    }

    if (grid[x][y] == 2) {
        if (0 == to_visit) {
            ++result;
        }
        return;
    }

    grid[x][y] = -1;

    UniquePaths3(grid, x + 1, y, to_visit - 1, result);
    UniquePaths3(grid, x - 1, y, to_visit - 1, result);
    UniquePaths3(grid, x, y + 1, to_visit - 1, result);
    UniquePaths3(grid, x, y - 1, to_visit - 1, result);

    grid[x][y] = 0;
}

auto UniquePaths3(MatrixType grid) {
    const int M = grid.size();
    const int N = grid.front().size();

    int empty_square = 1;
    int start_i = 0;
    int start_j = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 1) {
                start_i = i;
                start_j = j;
            } else if (grid[i][j] == 0) {
                ++empty_square;
            }
        }
    }

    int result = 0;
    UniquePaths3(grid, start_i, start_j, empty_square, result);

    return result;
}

}//namespace


THE_BENCHMARK(UniquePaths, 3, 7);

SIMPLE_TEST(UniquePaths, TestSAMPLE1, 28, 3, 7);
SIMPLE_TEST(UniquePaths, TestSAMPLE2, 3, 3, 2);
SIMPLE_TEST(UniquePaths, TestSAMPLE3, 28, 7, 3);
SIMPLE_TEST(UniquePaths, TestSAMPLE4, 6, 3, 3);


const MatrixType SAMPLE1 = {
    {0, 0, 0},
    {0, 1, 0},
    {0, 0, 0}
};

const MatrixType SAMPLE2 = {
    {0, 1},
    {0, 0}
};


THE_BENCHMARK(UniquePathsWithObstacles, SAMPLE1);

SIMPLE_TEST(UniquePathsWithObstacles, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(UniquePathsWithObstacles, TestSAMPLE2, 1, SAMPLE2);


const MatrixType SAMPLE1T = {
    {1, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 2, -1}
};

const MatrixType SAMPLE2T = {
    {1, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 2}
};

const MatrixType SAMPLE3T = {
    {0, 1},
    {2, 0}
};


THE_BENCHMARK(UniquePaths3, SAMPLE1T);

SIMPLE_TEST(UniquePaths3, TestSAMPLE1, 2, SAMPLE1T);
SIMPLE_TEST(UniquePaths3, TestSAMPLE2, 4, SAMPLE2T);
SIMPLE_TEST(UniquePaths3, TestSAMPLE3, 0, SAMPLE3T);
