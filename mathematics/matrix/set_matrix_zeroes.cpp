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
 * Given an m x n integer matrix matrix, if an element is 0, set its entire row and
 * column to 0's, and return the matrix. You must do it in place.
 */
auto SetMatrixZeroes(MatrixType a_matrix) {
    assert(not a_matrix.empty());

    const auto M = a_matrix.size();
    const auto N = a_matrix.front().size();

    std::vector<bool> zero_rows(M, 0);
    std::vector<bool> zero_columns(N, 0);

    for (MatrixType::size_type i = 0; i < M; ++i) {
        for (MatrixType::size_type j = 0; j < N; ++j) {
            if (a_matrix[i][j] == 0) {
                zero_rows[i] = true;
                zero_columns[j] = true;
            }
        }
    }

    for (MatrixType::size_type i = 0; i < M; ++i) {
        for (MatrixType::size_type j = 0; j < N; ++j) {
            if (zero_rows[i] or zero_columns[j]) {
                a_matrix[i][j] = 0;
            }
        }
    }

    return a_matrix;
}


auto SetMatrixZeroes_O1(MatrixType a_matrix) {
    assert(not a_matrix.empty());

    const auto M = a_matrix.size();
    const auto N = a_matrix.front().size();
    bool is_first_column_zero = false;

    for (std::size_t i = 0; i < M; ++i) {
        if (a_matrix[i][0] == 0) {
            is_first_column_zero = true;
        }

        for (std::size_t j = 1; j < N; ++j) {
            if (a_matrix[i][j] == 0) {
                a_matrix[0][j] = 0;
                a_matrix[i][0] = 0;
            }
        }
    }

    for (std::size_t i = 1; i < M; ++i) {
        for (std::size_t j = 1; j < N; ++j) {
            if (a_matrix[i][0] == 0 or a_matrix[0][j] == 0) {
                a_matrix[i][j] = 0;
            }
        }
    }

    if (a_matrix[0][0] == 0) {
        for (std::size_t j = 0; j < N; ++j) {
            a_matrix[0][j] = 0;
        }
    }

    if (is_first_column_zero) {
        for (std::size_t i = 0; i < M; ++i) {
            a_matrix[i][0] = 0;
        }
    }

    return a_matrix;
}


/**
 * @reference   Lucky Numbers in a Matrix
 *              https://leetcode.com/problems/lucky-numbers-in-a-matrix/
 *
 * Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in
 * any order. A lucky number is an element of the matrix such that it is the minimum
 * element in its row and maximum in its column.
 * 1 <= matrix[i][j] <= 10^5.
 */


/**
 * @reference   Special Positions in a Binary Matrix
 *              https://leetcode.com/problems/special-positions-in-a-binary-matrix/
 *
 * Given an m x n binary matrix mat, return the number of special positions in mat.
 * A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i
 * and column j are 0 (rows and columns are 0-indexed).
 */
auto NumberSpecials(const MatrixType &mat) {
    std::vector rows(mat.size(), 0);
    std::vector columns(mat.front().size(), 0);

    for (std::size_t i = 0; i < mat.size(); ++i) {
        for (std::size_t j = 0; j < mat.front().size(); ++j) {
            if (mat[i][j]) {
                ++rows[i];
                ++columns[j];
            }
        }
    }

    int result = 0;
    for (std::size_t i = 0; i < mat.size(); ++i) {
        for (std::size_t j = 0; j < mat.front().size(); ++j) {
            if (mat[i][j] and rows[i] == 1 and columns[j] == 1) {
                ++result;
            }
        }
    }

    return result;
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


THE_BENCHMARK(SetMatrixZeroes_O1, SAMPLE1);

SIMPLE_TEST(SetMatrixZeroes_O1, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SetMatrixZeroes_O1, TestSAMPLE2, EXPECTED2, SAMPLE2);


const MatrixType SAMPLE1S = {
    {1, 0, 0},
    {0, 0, 1},
    {1, 0, 0}
};

const MatrixType SAMPLE2S = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};


THE_BENCHMARK(NumberSpecials, SAMPLE1S);

SIMPLE_TEST(NumberSpecials, TestSAMPLE1, 1, SAMPLE1S);
SIMPLE_TEST(NumberSpecials, TestSAMPLE2, 3, SAMPLE2S);
