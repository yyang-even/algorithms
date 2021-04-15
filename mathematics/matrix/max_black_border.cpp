#include "common_header.h"

#include "matrix.h"


namespace {

/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.11.
 *
 * Imagine there is a square matrix with n x n cells. Each cell is either filled with a
 * black pixel or a white pixel. Design an algorithm to find the maximum subsquare such
 * that all four borders are filled with black pixels.
 */
auto MaxBlackBorderPreprocess(const MatrixType &a_matrix) {
    assert(not a_matrix.empty());
    assert(a_matrix.size() == a_matrix.front().size());

    auto processed_matrix =
        std::vector(a_matrix.size(), std::vector(a_matrix.front().size(), std::pair(0, 0)));

    for (int row = a_matrix.size() - 1; row >= 0; --row) {
        for (int column = a_matrix.front().size() - 1; column >= 0; --column) {
            auto &[right_zeros, below_zeros] = processed_matrix[row][column];

            if (a_matrix[row][column] == 0) {
                ++right_zeros;
                ++below_zeros;

                if (const std::size_t next_column = column + 1; next_column < a_matrix.front().size()) {
                    right_zeros += processed_matrix[row][next_column].first;
                }

                if (const std::size_t next_row = row + 1; next_row < a_matrix.size()) {
                    below_zeros += processed_matrix[next_row][column].second;
                }
            }
        }
    }

    return processed_matrix;
}

unsigned MaxBlackBorder(const MatrixType &a_matrix) {
    const auto processed_matrix = MaxBlackBorderPreprocess(a_matrix);

    for (int size = a_matrix.size(); size > 0; --size) {
        const auto count = a_matrix.size() - size + 1;
        for (std::size_t row = 0; row < count; ++row) {
            for (std::size_t column = 0; column < count; ++column) {
                const auto [zeros_right_to_top_left, zeros_below_top_left] =
                    processed_matrix[row][column];
                const auto zeros_below_top_right = processed_matrix[row][column + size - 1].second;
                const auto zeros_right_to_bottom_left = processed_matrix[row + size - 1][column].first;
                if (not(zeros_right_to_top_left < size or
                        zeros_below_top_left < size or
                        zeros_below_top_right < size or
                        zeros_right_to_bottom_left < size)) {
                    return size;
                }
            }
        }
    }

    return 0;
}

}//namespace


const MatrixType SAMPLE1 = {
    {1, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
};

const MatrixType SAMPLE2 = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1},
};

const MatrixType SAMPLE3 = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 0},
};

const MatrixType SAMPLE4 = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};


THE_BENCHMARK(MaxBlackBorder, SAMPLE1);

SIMPLE_TEST(MaxBlackBorder, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MaxBlackBorder, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(MaxBlackBorder, TestSAMPLE3, 1, SAMPLE3);
SIMPLE_TEST(MaxBlackBorder, TestSAMPLE4, 3, SAMPLE4);
