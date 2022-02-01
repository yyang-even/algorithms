#include "common_header.h"

#include "matrix.h"


namespace {

/** Matrix Diagonal Sum
 *
 * @reference   https://leetcode.com/problems/matrix-diagonal-sum/
 *
 * Given a square matrix mat, return the sum of the matrix diagonals.
 * Only include the sum of all the elements on the primary diagonal and all the elements
 * on the secondary diagonal that are not part of the primary diagonal.
 * n == mat.length == mat[i].length
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

}//namespace


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

const MatrixType SAMPLE3 = {{5}};


THE_BENCHMARK(DiagonalSum, SAMPLE1);

SIMPLE_TEST(DiagonalSum, TestSAMPLE1, 25, SAMPLE1);
SIMPLE_TEST(DiagonalSum, TestSAMPLE2, 8, SAMPLE2);
SIMPLE_TEST(DiagonalSum, TestSAMPLE3, 5, SAMPLE3);
