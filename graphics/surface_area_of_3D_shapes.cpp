#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** Surface Area of 3D Shapes
 *
 * @reference   https://leetcode.com/problems/surface-area-of-3d-shapes/
 *
 * You are given an n x n grid where you have placed some 1 x 1 x 1 cubes. Each value
 * v = grid[i][j] represents a tower of v cubes placed on top of cell (i, j). After
 * placing these cubes, you have decided to glue any directly adjacent cubes to each
 * other, forming several irregular 3D shapes. Return the total surface area of the
 * resulting shapes. Note: The bottom face of each shape counts toward its surface area.
 */
auto SurfaceArea(const MatrixType &grid) {
    assert(grid.size() == grid.front().size());

    int result = 0;
    for (std::size_t i = 0; i < grid.size(); ++i) {
        for (std::size_t j = 0; j < grid.size(); ++j) {
            if (grid[i][j]) {
                result += grid[i][j] * 4 + 2;
            }
            if (i) {
                result -= std::min(grid[i][j], grid[i - 1][j]) * 2;
            }
            if (j) {
                result -= std::min(grid[i][j], grid[i][j - 1]) * 2;
            }
        }
    }

    return result;
}

}//namespace


const MatrixType SAMPLE1 = {{2}};
const MatrixType SAMPLE2 = {
    {1, 2},
    {3, 4}
};
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


THE_BENCHMARK(SurfaceArea, SAMPLE1);

SIMPLE_TEST(SurfaceArea, TestSAMPLE1, 10, SAMPLE1);
SIMPLE_TEST(SurfaceArea, TestSAMPLE2, 34, SAMPLE2);
SIMPLE_TEST(SurfaceArea, TestSAMPLE3, 16, SAMPLE3);
SIMPLE_TEST(SurfaceArea, TestSAMPLE4, 32, SAMPLE4);
SIMPLE_TEST(SurfaceArea, TestSAMPLE5, 46, SAMPLE5);
