#pragma once

#include "matrix.h"


/** Program to find transpose of a matrix
 *
 * @reference   https://www.geeksforgeeks.org/program-to-find-transpose-of-a-matrix/
 */
static inline auto Transpose(MatrixType square_matrix) {
    const auto N = square_matrix.size();
    for (MatrixType::size_type i = 0; i < N; ++i) {
        for (auto j = i + 1; j < N; ++j) {
            std::swap(square_matrix[i][j], square_matrix[j][i]);
        }
    }

    return square_matrix;
}
