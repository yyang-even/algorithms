#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** Projection Area of 3D Shapes
 *
 * @reference   https://leetcode.com/problems/projection-area-of-3d-shapes/
 *
 * You are given an n x n grid where we place some 1 x 1 x 1 cubes that are axis-aligned
 * with the x, y, and z axes. Each value v = grid[i][j] represents a tower of v cubes
 * placed on top of the cell (i, j). We view the projection of these cubes onto the xy,
 * yz, and zx planes. A projection is like a shadow, that maps our 3-dimensional figure
 * to a 2-dimensional plane. We are viewing the "shadow" when looking at the cubes from
 * the top, the front, and the side. Return the total area of all three projections.
 */
auto ProjectionArea3D(const MatrixType &grid) {
    assert(grid.size() == grid.front().size());

    int result = 0;
    for (std::size_t i = 0; i < grid.size();  ++i) {
        int highest_row = 0;
        int highest_column = 0;
        for (std::size_t j = 0; j < grid.size(); ++j) {
            if (grid[i][j] > 0) {
                ++result;
            }
            highest_row = std::max(highest_row, grid[i][j]);
            highest_column = std::max(highest_column, grid[j][i]);
        }
        result += highest_row + highest_column;
    }

    return result;
}

}//namespace


const MatrixType SAMPLE1 = {
    {1, 2},
    {3, 4}
};
const MatrixType SAMPLE2 = {{2}};
const MatrixType SAMPLE3 = {
    {1, 0},
    {0, 2}
};
const MatrixType SAMPLE4 = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
};
const MatrixType SAMPLE5 = {
    {2, 2, 2},
    {2, 1, 2},
    {2, 2, 2}
};


THE_BENCHMARK(ProjectionArea3D, SAMPLE4);

SIMPLE_TEST(ProjectionArea3D, TestSAMPLE1, 17, SAMPLE1);
SIMPLE_TEST(ProjectionArea3D, TestSAMPLE2, 5, SAMPLE2);
SIMPLE_TEST(ProjectionArea3D, TestSAMPLE3, 8, SAMPLE3);
SIMPLE_TEST(ProjectionArea3D, TestSAMPLE4, 14, SAMPLE4);
SIMPLE_TEST(ProjectionArea3D, TestSAMPLE5, 21, SAMPLE5);
