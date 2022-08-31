#include "common_header.h"

#include "matrix.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Pacific Atlantic Water Flow
 *
 * @reference   https://leetcode.com/problems/pacific-atlantic-water-flow/
 *
 * There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The
 * Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's
 * right and bottom edges.
 * The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights
 * where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).
 * The island receives a lot of rain, and the rain water can flow to neighboring cells directly north,
 * south, east, and west if the neighboring cell's height is less than or equal to the current cell's
 * height. Water can flow from any cell adjacent to an ocean into the ocean.
 * Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can
 * flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
 */
void mark(const MatrixType &heights,
          std::vector<std::vector<bool>> &flag,
          const int i,
          const int j) {
    const int M = heights.size();
    const int N = heights.front().size();

    flag[i][j] = true;

    if (i - 1 >= 0 and not flag[i - 1][j] and heights[i - 1][j] >= heights[i][j]) {
        mark(heights, flag, i - 1, j);
    }
    if (i + 1 < M and not flag[i + 1][j] and heights[i + 1][j] >= heights[i][j]) {
        mark(heights, flag, i + 1, j);
    }
    if (j - 1 >= 0 and not flag[i][j - 1] and heights[i][j - 1] >= heights[i][j]) {
        mark(heights, flag, i, j - 1);
    }
    if (j + 1 < N and not flag[i][j + 1] and heights[i][j + 1] >= heights[i][j]) {
        mark(heights, flag, i, j + 1);
    }
}

auto PacificAtlanticWaterFlow(const MatrixType &heights) {
    const int M = heights.size();
    const int N = heights.front().size();

    std::vector pacific(M, std::vector(N, false));
    for (int i = 0; i < M; ++i) {
        mark(heights, pacific, i, 0);
    }
    for (int j = 1; j < N; ++j) {
        mark(heights, pacific, 0, j);
    }

    std::vector atlantic(M, std::vector(N, false));
    for (int i = 0; i < M; ++i) {
        mark(heights, atlantic, i, N - 1);
    }
    for (int j = 0; j < N - 1; ++j) {
        mark(heights, atlantic, M - 1, j);
    }

    ArrayType result;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (pacific[i][j] and atlantic[i][j]) {
                result.emplace_back(i, j);
            }
        }
    }

    return result;
}

} //namespace


// clang-format off
const MatrixType SAMPLE1 = {
    {1, 2, 2, 3, 5},
    {3, 2, 3, 4, 4},
    {2, 4, 5, 3, 1},
    {6, 7, 1, 4, 5},
    {5, 1, 1, 2, 4}
};
const ArrayType EXPECTED1 = {{0, 4}, {1, 3}, {1, 4}, {2, 2}, {3, 0}, {3, 1}, {4, 0}};

const MatrixType SAMPLE2 = {{1}};
const ArrayType EXPECTED2 = {{0, 0}};
// clang-format on


THE_BENCHMARK(PacificAtlanticWaterFlow, SAMPLE1);

SIMPLE_TEST(PacificAtlanticWaterFlow, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(PacificAtlanticWaterFlow, TestSAMPLE2, EXPECTED2, SAMPLE2);
