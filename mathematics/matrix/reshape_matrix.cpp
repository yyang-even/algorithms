#include "common_header.h"

#include "matrix.h"


namespace {

/** Reshape the Matrix
 *
 * @reference   https://leetcode.com/problems/reshape-the-matrix/
 *
 * In MATLAB, there is a handy function called reshape which can reshape an m x n matrix
 * into a new one with a different size r x c keeping its original data. You are given
 * an m x n matrix mat and two integers r and c representing the row number and column
 * number of the wanted reshaped matrix. The reshaped matrix should be filled with all
 * the elements of the original matrix in the same row-traversing order as they were.
 * If the reshape operation with given parameters is possible and legal, output the new
 * reshaped matrix; Otherwise, output the original matrix.
 */
auto ReshapeMatrix(const MatrixType &original,
                   const std::size_t r, const std::size_t c) {
    if (original.empty() or r * c != original.size() * original.front().size()) {
        return original;
    }

    std::size_t i = 0;
    std::size_t j = 0;
    auto results = std::vector(r, MatrixType::value_type(c, 0));
    for (std::size_t x = 0; x < original.size(); ++x) {
        for (std::size_t y = 0; y < original.front().size(); ++y) {
            results[i][j++] = original[x][y];
            if (j == c) {
                j = 0;
                ++i;
            }
        }
    }

    return results;
}


/**
 * @reference   Convert 1D Array Into 2D Array
 *              https://leetcode.com/problems/convert-1d-array-into-2d-array/
 *
 * You are given a 0-indexed 1-dimensional (1D) integer array original, and two integers,
 * m and n. You are tasked with creating a 2-dimensional (2D) array with m rows and n
 * columns using all the elements from original.
 * The elements from indices 0 to n - 1 (inclusive) of original should form the first row
 * of the constructed 2D array, the elements from indices n to 2 * n - 1 (inclusive) should
 * form the second row of the constructed 2D array, and so on.
 * Return an m x n 2D array constructed according to the above procedure, or an empty 2D
 * array if it is impossible.
 */

}//namespace


const MatrixType SAMPLE1 = {
    {1, 2},
    {3, 4}
};
const MatrixType EXPECTED1 = {
    {1, 2, 3, 4}
};


THE_BENCHMARK(ReshapeMatrix, SAMPLE1, 1, 4);

SIMPLE_TEST(ReshapeMatrix, TestSAMPLE1, EXPECTED1, SAMPLE1, 1, 4);
SIMPLE_TEST(ReshapeMatrix, TestSAMPLE2, SAMPLE1, SAMPLE1, 2, 4);
