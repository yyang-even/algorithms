#pragma once

#include "matrix.h"


/** Program to reverse the rows in a 2d Array
 *
 * @reference   https://www.geeksforgeeks.org/program-to-reverse-the-rows-in-a-2d-array/
 */
static inline auto ReverseMatrixRows(MatrixType a_matrix) {
    for (auto &row : a_matrix) {
        std::reverse(row.begin(), row.end());
    }

    return a_matrix;
}


static inline auto ReverseMatrixColumns(MatrixType a_matrix) {
    std::reverse(a_matrix.begin(), a_matrix.end());
    return a_matrix;
}
