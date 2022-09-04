#include "common_header.h"

#include "matrix.h"


namespace {

/** Toeplitz Matrix
 *
 * @reference   https://leetcode.com/problems/toeplitz-matrix/
 *
 * Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise, return false.
 * A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same elements.
 * Follow up: What if the matrix is stored on disk, and the memory is limited such that you can only
 * load at most one row of the matrix into the memory at once? What if the matrix is so large that you
 * can only load up a partial row into the memory at once?
 */
auto Toeplitz_Group(const MatrixType &a_matrix) {
    const int M = a_matrix.size();
    const int N = a_matrix.front().size();

    std::unordered_map<int, int> groups;
    for (int r = 0; r < M; ++r) {
        for (int c = 0; c < N; ++c) {
            const auto [iter, inserted] = groups.emplace(r - c, a_matrix[r][c]);
            if (not inserted and iter->second != a_matrix[r][c]) {
                return false;
            }
        }
    }

    return true;
}


auto Toeplitz_Neighbor(const MatrixType &a_matrix) {
    for (std::size_t r = 1; r < a_matrix.size(); ++r) {
        for (std::size_t c = 1; c < a_matrix.front().size(); ++c) {
            if (a_matrix[r - 1][c - 1] != a_matrix[r][c]) {
                return false;
            }
        }
    }

    return true;
}


/**
 * @reference   Sort the Matrix Diagonally
 *              https://leetcode.com/problems/sort-the-matrix-diagonally/
 *
 * A matrix diagonal is a diagonal line of cells starting from some cell in either the topmost row or
 * leftmost column and going in the bottom-right direction until reaching the matrix's end. For example,
 * the matrix diagonal starting from mat[2][0], where mat is a 6 x 3 matrix, includes cells mat[2][0],
 * mat[3][1], and mat[4][2].
 * Given an m x n matrix mat of integers, sort each matrix diagonal in ascending order and return the
 * resulting matrix.
 */
auto SortMatrixDiagonally(MatrixType a_matrix) {
    const auto M = a_matrix.size();
    const auto N = a_matrix.front().size();

    std::unordered_map<int, std::vector<int>> diagonals;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            diagonals[i - j].push_back(a_matrix[i][j]);
        }
    }

    std::unordered_map<int, int> indices;
    for (auto &[k, d] : diagonals) {
        std::sort(d.begin(), d.end());
        indices[k] = 0;
    }

    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            a_matrix[i][j] = diagonals[i - j][indices[i - j]++];
        }
    }

    return a_matrix;
}

} //namespace


// clang-format off
const MatrixType SAMPLE1 = {
    {1, 2, 3, 4},
    {5, 1, 2, 3},
    {9, 5, 1, 2}
};

const MatrixType SAMPLE2 = {
    {1, 2},
    {2, 2}
};
// clang-format on


THE_BENCHMARK(Toeplitz_Group, SAMPLE1);

SIMPLE_TEST(Toeplitz_Group, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(Toeplitz_Group, TestSAMPLE2, false, SAMPLE2);


THE_BENCHMARK(Toeplitz_Neighbor, SAMPLE1);

SIMPLE_TEST(Toeplitz_Neighbor, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(Toeplitz_Neighbor, TestSAMPLE2, false, SAMPLE2);


// clang-format off
const MatrixType SAMPLE3 = {
    {3, 3, 1, 1},
    {2, 2, 1, 2},
    {1, 1, 1, 2}
};
const MatrixType EXPECTED3 = {
    {1, 1, 1, 1},
    {1, 2, 2, 2},
    {1, 2, 3, 3}
};

const MatrixType SAMPLE4 = {
    {11, 25, 66, 1, 69, 7},
    {23, 55, 17, 45, 15, 52},
    {75, 31, 36, 44, 58, 8},
    {22, 27, 33, 25, 68, 4},
    {84, 28, 14, 11, 5, 50}
};
const MatrixType EXPECTED4 = {
    {5, 17, 4, 1, 52, 7},
    {11, 11, 25, 45, 8, 69},
    {14, 23, 25, 44, 58, 15},
    {22, 27, 31, 36, 50, 66},
    {84, 28, 75, 33, 55, 68}
};
// clang-format on


THE_BENCHMARK(SortMatrixDiagonally, SAMPLE1);

SIMPLE_TEST(SortMatrixDiagonally, TestSAMPLE1, SAMPLE1, SAMPLE1);
SIMPLE_TEST(SortMatrixDiagonally, TestSAMPLE2, SAMPLE2, SAMPLE2);
SIMPLE_TEST(SortMatrixDiagonally, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(SortMatrixDiagonally, TestSAMPLE4, EXPECTED4, SAMPLE4);
