#include "common_header.h"

#include "matrix.h"


namespace {

/** Shift 2D Grid
 *
 * @reference   https://leetcode.com/problems/shift-2d-grid/
 *
 * Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.
 * In one shift operation:
 *  Element at grid[i][j] moves to grid[i][j + 1].
 *  Element at grid[i][n - 1] moves to grid[i + 1][0].
 *  Element at grid[m - 1][n - 1] moves to grid[0][0].
 * Return the 2D grid after applying shift operation k times.
 */
auto Shift2dGrid(const MatrixType &grid, const int k) {
    const auto M = grid.size();
    const auto N = grid.front().size();

    std::vector result(M, std::vector(N, 0));
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            const auto new_i = (i + (j + k) / N) % M;
            const auto new_j = (j + k) % N;

            result[new_i][new_j] = grid[i][j];
        }
    }

    return result;
}

}//namespace


const MatrixType SAMPLE1 = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
const MatrixType EXPECTED1 = {
    {9, 1, 2},
    {3, 4, 5},
    {6, 7, 8}
};

const MatrixType SAMPLE2 = {
    {3, 8, 1, 9},
    {19, 7, 2, 5},
    {4, 6, 11, 10},
    {12, 0, 21, 13}
};
const MatrixType EXPECTED2 = {
    {12, 0, 21, 13},
    {3, 8, 1, 9},
    {19, 7, 2, 5},
    {4, 6, 11, 10}
};


THE_BENCHMARK(Shift2dGrid, SAMPLE1, 1);

SIMPLE_TEST(Shift2dGrid, TestSAMPLE1, EXPECTED1, SAMPLE1, 1);
SIMPLE_TEST(Shift2dGrid, TestSAMPLE2, EXPECTED2, SAMPLE2, 4);
SIMPLE_TEST(Shift2dGrid, TestSAMPLE3, SAMPLE1, SAMPLE1, 3 * 3);
