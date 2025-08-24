#include "common_header.h"

#include "matrix.h"


namespace {

/**
 * @reference   Matrix Diagonal Sum
 *              https://leetcode.com/problems/matrix-diagonal-sum/
 *
 * Given a square matrix mat, return the sum of the matrix diagonals.
 * Only include the sum of all the elements on the primary diagonal and all the elements on the
 * secondary diagonal that are not part of the primary diagonal.
 * n == mat.length == mat[i].length
 *
 * @tags    #matrix
 */
auto DiagonalSum(const MatrixType &matrix) {
    int result = 0;
    const int N = matrix.size();
    for (int i = 0; i < N; ++i) {
        result += matrix[i][i] + matrix[N - 1 - i][i];
    }
    if (N % 2) {
        result -= matrix[N / 2][N / 2];
    }

    return result;
}


/**
 * @reference   Check if Matrix Is X-Matrix
 *              https://leetcode.com/problems/check-if-matrix-is-x-matrix/
 *
 * A square matrix is said to be an X-Matrix if both of the following conditions hold:
 *  All the elements in the diagonals of the matrix are non-zero.
 *  All other elements are 0.
 * Given a 2D integer array grid of size n x n representing a square matrix, return true if grid is an
 * X-Matrix. Otherwise, return false.
 *
 * @hint    An element is in the diagonals if and only if x == y or x + y == N - 1.
 *
 * @tags    #matrix
 */

} //namespace


// clang-format off
const MatrixType SAMPLE1 = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

const MatrixType SAMPLE2 = {
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {1, 1, 1, 1}
};
// clang-format on

const MatrixType SAMPLE3 = {{5}};


THE_BENCHMARK(DiagonalSum, SAMPLE1);

SIMPLE_TEST(DiagonalSum, TestSAMPLE1, 25, SAMPLE1);
SIMPLE_TEST(DiagonalSum, TestSAMPLE2, 8, SAMPLE2);
SIMPLE_TEST(DiagonalSum, TestSAMPLE3, 5, SAMPLE3);
