#include "common_header.h"

#include "matrix.h"


namespace {

using ArrayType = std::vector<int>;

/** Rotting Oranges
 *
 * @reference   https://leetcode.com/problems/rotting-oranges/
 *
 * You are given an m x n grid where each cell can have one of three values:
 *  0 representing an empty cell,
 *  1 representing a fresh orange, or
 *  2 representing a rotten orange.
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange
 * becomes rotten. Return the minimum number of minutes that must elapse until no cell
 * has a fresh orange. If this is impossible, return -1.
 */
auto RottingOranges(MatrixType grid) {
    const auto M = grid.size();
    const auto N = grid.front().size();

    std::queue<std::pair<std::size_t, std::size_t>> q;
    int fresh = 0;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == 2) {
                q.emplace(i, j);
            } else if (grid[i][j] == 1) {
                ++fresh;
            }
        }
    }

    int result = q.empty() ? 0 : -1;
    while (not q.empty()) {
        ++result;
        for (int size = q.size(); size--;) {
            const auto [i, j] = q.front();
            q.pop();
            if (i > 0 and grid[i - 1][j] == 1) {
                grid[i - 1][j] = 2;
                q.emplace(i - 1, j);
                --fresh;
            }

            if (i < M - 1 and grid[i + 1][j] == 1) {
                grid[i + 1][j] = 2;
                q.emplace(i + 1, j);
                --fresh;
            }

            if (j > 0 and grid[i][j - 1] == 1) {
                grid[i][j - 1] = 2;
                q.emplace(i, j - 1);
                --fresh;
            }

            if (j < N - 1 and grid[i][j + 1] == 1) {
                grid[i][j + 1] = 2;
                q.emplace(i, j + 1);
                --fresh;
            }
        }
    }

    if (fresh > 0) {
        return -1;
    }
    if (result == -1) {
        return 0;
    }
    return result;
}

}//namespace


const MatrixType SAMPLE1 = {
    {2, 1, 1},
    {1, 1, 0},
    {0, 1, 1}
};

const MatrixType SAMPLE2 = {
    {0}
};

const MatrixType SAMPLE3 = {
    {2, 1, 1},
    {0, 1, 1},
    {1, 0, 1}
};

const MatrixType SAMPLE4 = {
    {0, 2}
};


THE_BENCHMARK(RottingOranges, SAMPLE1);

SIMPLE_TEST(RottingOranges, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(RottingOranges, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(RottingOranges, TestSAMPLE3, -1, SAMPLE3);
SIMPLE_TEST(RottingOranges, TestSAMPLE4, 0, SAMPLE4);
