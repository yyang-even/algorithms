#include "common_header.h"

#include "matrix.h"


namespace {

/** Toeplitz Matrix
 *
 * @reference   https://leetcode.com/problems/toeplitz-matrix/
 *
 * Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise, return false.
 * A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same
 * elements.
 * Follow up: What if the matrix is stored on disk, and the memory is limited such that
 * you can only load at most one row of the matrix into the memory at once? What if the
 * matrix is so large that you can only load up a partial row into the memory at once?
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

}//namespace


const MatrixType SAMPLE1 = {
    {1, 2, 3, 4},
    {5, 1, 2, 3},
    {9, 5, 1, 2}
};

const MatrixType SAMPLE2 = {
    {1, 2},
    {2, 2}
};


THE_BENCHMARK(Toeplitz_Group, SAMPLE1);

SIMPLE_TEST(Toeplitz_Group, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(Toeplitz_Group, TestSAMPLE2, false, SAMPLE2);


THE_BENCHMARK(Toeplitz_Neighbor, SAMPLE1);

SIMPLE_TEST(Toeplitz_Neighbor, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(Toeplitz_Neighbor, TestSAMPLE2, false, SAMPLE2);
