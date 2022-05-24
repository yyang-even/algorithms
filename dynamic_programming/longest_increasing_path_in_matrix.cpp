#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** Longest Increasing Path in a Matrix
 *
 * @reference   https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
 *
 * Given an m x n integers matrix, return the length of the longest increasing path in matrix.
 * From each cell, you can either move in four directions: left, right, up, or down. You may not
 * move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
 */
int LongestIncreasingPath(
    const MatrixType &grid, const int i, const int j, const int prev, MatrixType &memo) {
    const int M = grid.size();
    const int N = grid.front().size();

    if (i < 0 or j < 0 or i >= M or j >= N or grid[i][j] <= prev) {
        return 0;
    }

    if (memo[i][j]) {
        return memo[i][j];
    }

    return memo[i][j] = 1 + std::max({LongestIncreasingPath(grid, i + 1, j, grid[i][j], memo),
                                      LongestIncreasingPath(grid, i - 1, j, grid[i][j], memo),
                                      LongestIncreasingPath(grid, i, j + 1, grid[i][j], memo),
                                      LongestIncreasingPath(grid, i, j - 1, grid[i][j], memo)});
}

auto LongestIncreasingPath(const MatrixType &grid) {
    int result = 0;
    std::vector memo(grid.size(), std::vector(grid.front().size(), 0));

    for (std::size_t i = 0; i < grid.size(); ++i) {
        for (std::size_t j = 0; j < grid.front().size(); ++j) {
            result = std::max(result, LongestIncreasingPath(grid, i, j, -1, memo));
        }
    }

    return result;
}

} //namespace


// clang-format off
const MatrixType SAMPLE1 = {
    {9,9,4},
    {6,6,8},
    {2,1,1}
};

const MatrixType SAMPLE2 = {
    {3,4,5},
    {3,2,6},
    {2,2,1}
};
// clang-format on

const MatrixType SAMPLE3 = {{1}};


THE_BENCHMARK(LongestIncreasingPath, SAMPLE1);

SIMPLE_TEST(LongestIncreasingPath, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(LongestIncreasingPath, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(LongestIncreasingPath, TestSAMPLE3, 1, SAMPLE3);
