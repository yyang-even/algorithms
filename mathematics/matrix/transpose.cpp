#include "common_header.h"

#include "transpose.h"


namespace {

/**
 * @reference   Transpose Matrix
 *              https://leetcode.com/problems/transpose-matrix/
 *
 * Given a 2D integer array matrix, return the transpose of matrix. The transpose of a
 * matrix is the matrix flipped over its main diagonal, switching the matrix's row and
 * column indices.
 */
auto MatrixTranspose(const MatrixType &matrix) {
    assert(matrix.size() and matrix.front().size());

    std::vector result(matrix.front().size(), std::vector(matrix.size(), 0));

    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix.front().size(); ++j) {
            result[j][i] = matrix[i][j];
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
    {1, 4, 7},
    {2, 5, 8},
    {3, 6, 9}
};

const MatrixType SAMPLE2 = {
    {1, 1, 1, 1},
    {2, 2, 2, 2},
    {3, 3, 3, 3},
    {4, 4, 4, 4}
};
const MatrixType EXPECTED2 = {
    {1, 2, 3, 4},
    {1, 2, 3, 4},
    {1, 2, 3, 4},
    {1, 2, 3, 4}
};

const MatrixType SAMPLE3 = {
    {1, 2, 3},
    {4, 5, 6},
};
const MatrixType EXPECTED3 = {
    {1, 4},
    {2, 5},
    {3, 6}
};


THE_BENCHMARK(Transpose, SAMPLE1);

SIMPLE_TEST(Transpose, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(Transpose, TestSAMPLE2, EXPECTED2, SAMPLE2);


THE_BENCHMARK(MatrixTranspose, SAMPLE1);

SIMPLE_TEST(MatrixTranspose, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(MatrixTranspose, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(MatrixTranspose, TestSAMPLE3, EXPECTED3, SAMPLE3);
