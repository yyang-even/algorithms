#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/**
 * @reference   Score After Flipping Matrix
 *              https://leetcode.com/problems/score-after-flipping-matrix/
 *
 * You are given an m x n binary matrix grid.
 * A move consists of choosing any row or column and toggling each value in that row or column (i.e.,
 * changing all 0's to 1's, and all 1's to 0's).
 * Every row of the matrix is interpreted as a binary number, and the score of the matrix is the sum of
 * these numbers.
 * Return the highest possible score after making any number of moves (including zero moves).
 *
 * @tags    #greedy #matrix
 */
auto ScoreAfterFlipping(const MatrixType &grid) {
    const int M = grid.size();
    const int N = grid.front().size();

    int result = M * (1 << (N - 1));
    for (int j = 1; j < N; ++j) {
        int count = 0;
        for (int i = 0; i < M; ++i) {
            count += (grid[i][j] == grid[i][0]);
        }

        count = std::max(count, M - count);
        result += count * (1 << (N - j - 1));
    }

    return result;
}

} //namespace


// clang-format off
const MatrixType SAMPLE1 = {
    {0, 0, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 0}
};

const MatrixType SAMPLE2 = {{0}};
// clang-format on


THE_BENCHMARK(ScoreAfterFlipping, SAMPLE1);

SIMPLE_TEST(ScoreAfterFlipping, TestSAMPLE1, 39, SAMPLE1);
SIMPLE_TEST(ScoreAfterFlipping, TestSAMPLE2, 1, SAMPLE2);
