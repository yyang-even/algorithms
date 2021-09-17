#include "common_header.h"

#include "matrix.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::vector<std::pair<int, int>>;

/** Spiral Matrix
 *
 * @reference   https://leetcode.com/problems/spiral-matrix/
 *
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 * @reference   Print a given matrix in spiral form
 *              https://www.geeksforgeeks.org/print-a-given-matrix-in-spiral-form/
 */
auto SpiralMatrix(const MatrixType &a_matrix) {
    assert(not a_matrix.empty());

    int row_lower = 0;
    int column_lower = 0;
    int row_upper = a_matrix.size() - 1;
    int column_upper = a_matrix.front().size() - 1;
    ArrayType result;
    while (row_lower <= row_upper and column_lower <= column_upper) {
        for (auto j = column_lower; j <= column_upper; ++j) {
            result.push_back(a_matrix[row_lower][j]);
        }
        ++row_lower;

        for (auto i = row_lower; i <= row_upper; ++i) {
            result.push_back(a_matrix[i][column_upper]);
        }
        --column_upper;

        if (row_lower <= row_upper) {
            for (auto j = column_upper; j >= column_lower; --j) {
                result.push_back(a_matrix[row_upper][j]);
            }
            --row_upper;
        }

        if (column_lower <= column_upper) {
            for (auto i = row_upper; i >= row_lower; --i) {
                result.push_back(a_matrix[i][column_lower]);
            }
            ++column_lower;
        }
    }

    return result;
}


/**
 * @reference   Spiral Matrix II
 *              https://leetcode.com/problems/spiral-matrix-ii/
 *
 * Given a positive integer n, generate an n x n matrix filled with elements from 1 to
 * n^2 in spiral order.
 */
const std::vector<std::pair<int, int>> DIRECTIONS{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

auto GenerateSpiralMatrix(const int n) {
    std::vector result(n, std::vector(n, 0));
    int i = 1;
    int row = 0;
    int column = 0;
    int direction = 0;

    while (i <= n * n) {
        result[row][column] = i++;
        const auto [delta_r, delta_c] = DIRECTIONS[direction];
        const auto r = row + delta_r;
        const auto c = column + delta_c;

        if (r < 0 or c < 0 or r >= n or c >= n or result[r][c]) {
            direction = (direction + 1) % DIRECTIONS.size();
        }

        row += DIRECTIONS[direction].first;
        column += DIRECTIONS[direction].second;
    }

    return result;
}


/**
 * @reference   Spiral Matrix III
 *              https://leetcode.com/problems/spiral-matrix-iii/
 *
 * You start at the cell (rStart, cStart) of an rows x cols grid facing east. The
 * northwest corner is at the first row and column in the grid, and the southeast corner
 * is at the last row and column. You will walk in a clockwise spiral shape to visit
 * every position in this grid. Whenever you move outside the grid's boundary, we
 * continue our walk outside the grid (but may return to the grid boundary later.).
 * Eventually, we reach all rows * cols spaces of the grid. Return an array of
 * coordinates representing the positions of the grid in the order you visited them.
 */
auto SpiralMatrixAnyStart(const int rows, const int columns,
                          const int r_start, const int c_start) {
    OutputType result;
    result.emplace_back(r_start, c_start);
    if (rows * columns == 1) {
        return result;
    }

    auto r = r_start;
    auto c = c_start;
    for (int k = 1; k < 2 * (rows + columns); k += 2) {
        for (int direction = 0; direction < 4; ++direction) {
            const int steps = k + (direction / 2);
            const auto [delta_r, delta_c] = DIRECTIONS[direction];
            for (int j = 0; j < steps; ++j) {
                r += delta_r;
                c += delta_c;
                if (0 <= r and r < rows and 0 <= c and c < columns) {
                    result.emplace_back(r, c);
                    if (result.size() == static_cast<std::size_t>(rows) * columns) {
                        return result;
                    }
                }
            }
        }
    }

    return result;
}

}//namespace


const MatrixType SAMPLE1 = {
    { 1, 2, 3, 4, 5, 6 },
    { 7, 8, 9, 10, 11, 12 },
    { 13, 14, 15, 16, 17, 18 }
};
const ArrayType EXPECTED1 = {1, 2, 3, 4, 5, 6, 12, 18, 17, 16, 15, 14, 13, 7, 8, 9, 10, 11};

const MatrixType SAMPLE2 = {
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 },
    { 13, 14, 15, 16 }
};
const ArrayType EXPECTED2 = {1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10};

const MatrixType SAMPLE3 = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
const ArrayType EXPECTED3 = {1, 2, 3, 6, 9, 8, 7, 4, 5};

const MatrixType SAMPLE4 = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};
const ArrayType EXPECTED4 = {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};

const MatrixType SAMPLE5 = {
    {2, 5, 8},
    {4, 0, -1}
};
const ArrayType EXPECTED5 = {2, 5, 8, -1, 0, 4};


THE_BENCHMARK(SpiralMatrix, SAMPLE1);

SIMPLE_TEST(SpiralMatrix, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SpiralMatrix, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(SpiralMatrix, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(SpiralMatrix, TestSAMPLE4, EXPECTED4, SAMPLE4);
SIMPLE_TEST(SpiralMatrix, TestSAMPLE5, EXPECTED5, SAMPLE5);


const MatrixType EXPECTED1G = {
    {1, 2, 3},
    {8, 9, 4},
    {7, 6, 5}
};
const MatrixType EXPECTED2G = {{1}};


THE_BENCHMARK(GenerateSpiralMatrix, 3);

SIMPLE_TEST(GenerateSpiralMatrix, TestSAMPLE1, EXPECTED1G, 3);
SIMPLE_TEST(GenerateSpiralMatrix, TestSAMPLE2, EXPECTED2G, 1);


const OutputType EXPECTED1P = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
const OutputType EXPECTED2P = {{1, 4}, {1, 5}, {2, 5}, {2, 4}, {2, 3}, {1, 3}, {0, 3}, {0, 4}, {0, 5}, {3, 5}, {3, 4}, {3, 3}, {3, 2}, {2, 2}, {1, 2}, {0, 2}, {4, 5}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}};


THE_BENCHMARK(SpiralMatrixAnyStart, 5, 6, 1, 4);

SIMPLE_TEST(SpiralMatrixAnyStart, TestSAMPLE1, EXPECTED1P, 1, 4, 0, 0);
SIMPLE_TEST(SpiralMatrixAnyStart, TestSAMPLE2, EXPECTED2P, 5, 6, 1, 4);
