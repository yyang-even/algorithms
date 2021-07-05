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
