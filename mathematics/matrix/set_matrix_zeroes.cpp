#include "common_header.h"

#include "matrix.h"


namespace {

/** Set Matrix Zeroes
 *
 * @reference   73. Set Matrix Zeroes
 *              https://leetcode.com/problems/set-matrix-zeroes/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.7.
 *
 * Given an m x n matrix. If an element is 0, set its entire row and column to 0.
 */
auto SetMatrixZeroes(MatrixType a_matrix) {
    assert(not a_matrix.empty());

    std::vector<bool> zero_rows(a_matrix.size(), 0);
    std::vector<bool> zero_columns(a_matrix.front().size(), 0);

    for (MatrixType::size_type i = 0; i < a_matrix.size(); ++i) {
        for (MatrixType::size_type j = 0; j < a_matrix[i].size(); ++j) {
            if (a_matrix[i][j] == 0) {
                zero_rows[i] = true;
                zero_columns[j] = true;
            }
        }
    }

    for (MatrixType::size_type i = 0; i < a_matrix.size(); ++i) {
        for (MatrixType::size_type j = 0; j < a_matrix[i].size(); ++j) {
            if (zero_rows[i] or zero_columns[j]) {
                a_matrix[i][j] = 0;
            }
        }
    }

    return a_matrix;
}

}//namespace


const MatrixType SAMPLE1 = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
};
const MatrixType EXPECTED1 = {
    {1, 0, 1},
    {0, 0, 0},
    {1, 0, 1}
};

const MatrixType SAMPLE2 = {
    {0, 1, 2, 0},
    {3, 4, 5, 2},
    {1, 3, 1, 5}
};
const MatrixType EXPECTED2 = {
    {0, 0, 0, 0},
    {0, 4, 5, 0},
    {0, 3, 1, 0}
};


THE_BENCHMARK(SetMatrixZeroes, SAMPLE1);

SIMPLE_TEST(SetMatrixZeroes, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SetMatrixZeroes, TestSAMPLE2, EXPECTED2, SAMPLE2);
