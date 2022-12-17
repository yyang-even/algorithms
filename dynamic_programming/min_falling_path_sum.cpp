#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** Minimum Falling Path Sum
 *
 * @reference   https://leetcode.com/problems/minimum-falling-path-sum/
 *
 * Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
 * A falling path starts at any element in the first row and chooses the element in the next row that is
 * either directly below or diagonally left/right. Specifically, the next element from position (row,
 * col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
 */
auto MinFallingPathSum(MatrixType a_matrix) {
    const int N = a_matrix.size();

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            auto minimum = INT_MAX;
            for (int k = std::max(0, j - 1); k <= std::min(N - 1, j + 1); ++k) {
                minimum = std::min(minimum, a_matrix[i - 1][k]);
            }

            a_matrix[i][j] += minimum;
        }
    }

    return *std::min_element(a_matrix.back().cbegin(), a_matrix.back().cend());
}


/**
 * @reference   Minimum Falling Path Sum II
 *              https://leetcode.com/problems/minimum-falling-path-sum-ii/
 *
 * Given an n x n integer matrix grid, return the minimum sum of a falling path with non-zero shifts.
 * A falling path with non-zero shifts is a choice of exactly one element from each row of grid such
 * that no two elements chosen in adjacent rows are in the same column.
 */
auto MinFallingPathSum_Two(const MatrixType &a_matrix) {
    int first = 0;
    int second = 0;
    auto position_of_first = a_matrix.size();

    for (const auto &row : a_matrix) {
        int new_first = INT_MAX;
        int new_second = INT_MAX;
        auto new_position = a_matrix.size();

        for (std::size_t j = 0; j < row.size(); ++j) {
            const auto mini = (j == position_of_first) ? second : first;
            const auto temp = row[j] + mini;
            if (temp < new_first) {
                new_second = new_first;
                new_first = temp;
                new_position = j;
            } else {
                new_second = std::min(new_second, temp);
            }
        }

        first = new_first;
        second = new_second;
        position_of_first = new_position;
    }

    return first;
}

} //namespace


// clang-format off
const MatrixType SAMPLE1 = {
    {2, 1, 3},
    {6, 5, 4},
    {7, 8, 9}
};

const MatrixType SAMPLE2 = {
    {-19, 57},
    {-40, -5}
};
// clang-format on


THE_BENCHMARK(MinFallingPathSum, SAMPLE1);

SIMPLE_TEST(MinFallingPathSum, TestSAMPLE1, 13, SAMPLE1);
SIMPLE_TEST(MinFallingPathSum, TestSAMPLE2, -59, SAMPLE2);


// clang-format off
const MatrixType SAMPLE1T = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

const MatrixType SAMPLE2T = {{7}};
// clang-format on


THE_BENCHMARK(MinFallingPathSum_Two, SAMPLE1T);

SIMPLE_TEST(MinFallingPathSum_Two, TestSAMPLE1, 13, SAMPLE1T);
SIMPLE_TEST(MinFallingPathSum_Two, TestSAMPLE2, 7, SAMPLE2T);
