#include "common_header.h"

#include "matrix.h"


namespace {

/** Island Perimeter
 *
 * @reference   https://leetcode.com/problems/island-perimeter/
 *
 * You are given row x col grid representing a map where grid[i][j] = 1 represents land
 * and grid[i][j] = 0 represents water. Grid cells are connected horizontally/vertically
 * (not diagonally). The grid is completely surrounded by water, and there is exactly
 * one island (i.e., one or more connected land cells). The island doesn't have "lakes",
 * meaning the water inside isn't connected to the water around the island. One cell is
 * a square with side length 1. The grid is rectangular, width and height don't exceed
 * 100. Determine the perimeter of the island.
 */
auto IslandPerimeter_2Directions(const MatrixType &grid) {
    int island_count = 0 ;
    int overlapped_edges = 0 ;
    for (std::size_t i = 0 ; i < grid.size(); ++i) {
        for (std::size_t j = 0 ; j < grid.front().size(); ++j) {
            if (grid[i][j] == 1) {
                ++island_count;
                if (i != 0 and grid[i - 1][j] == 1) {
                    ++overlapped_edges;
                }
                if (j != 0 and grid[i][j - 1] == 1) {
                    ++overlapped_edges;
                }
            }
        }
    }

    return 4 * island_count - 2 * overlapped_edges ;
}


auto IslandPerimeter_4Directions(const MatrixType &grid) {
    const int M = grid.size();
    const int N = grid.front().size();

    int result = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 1) {
                result += 4;
                if (i > 0 and grid[i - 1][j]) {
                    --result;
                }
                if (j > 0 and grid[i][j - 1]) {
                    --result;
                }
                if (i < M - 1 and grid[i + 1][j]) {
                    --result;
                }
                if (j < N - 1 and grid[i][j + 1]) {
                    --result;
                }
            }
        }
    }

    return result;
}

}//namespace


const MatrixType SAMPLE1 = {
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0}
};

const MatrixType SAMPLE2 = {
    {1}
};

const MatrixType SAMPLE3 = {
    {1, 0}
};


THE_BENCHMARK(IslandPerimeter_2Directions, SAMPLE1);

SIMPLE_TEST(IslandPerimeter_2Directions, TestSAMPLE1, 16, SAMPLE1);
SIMPLE_TEST(IslandPerimeter_2Directions, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(IslandPerimeter_2Directions, TestSAMPLE3, 4, SAMPLE3);


THE_BENCHMARK(IslandPerimeter_4Directions, SAMPLE1);

SIMPLE_TEST(IslandPerimeter_4Directions, TestSAMPLE1, 16, SAMPLE1);
SIMPLE_TEST(IslandPerimeter_4Directions, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(IslandPerimeter_4Directions, TestSAMPLE3, 4, SAMPLE3);
