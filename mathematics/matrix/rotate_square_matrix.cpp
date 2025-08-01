#include "common_header.h"

#include "reverse_matrix.h"
#include "transpose.h"


namespace {

/**
 * @reference   Turn an image by 90 degree
 *              https://www.geeksforgeeks.org/turn-an-image-by-90-degree/
 * @reference   Inplace rotate square matrix by 90 degrees | Set 1
 *              https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
 *
 * Given a square matrix, turn it by 90 degrees in anti-clockwise direction without using any extra
 * space.
 *
 * @tags    #square-matrix-rotation
 */
void rotateGroup90Degree_AntiClockwise(MatrixType &square_matrix,
                                       const MatrixType::size_type x,
                                       const MatrixType::size_type y) {
    const auto temp = square_matrix[x][y];
    const auto N = square_matrix.size();
    square_matrix[x][y] = square_matrix[y][N - 1 - x];
    square_matrix[y][N - 1 - x] = square_matrix[N - 1 - x][N - 1 - y];
    square_matrix[N - 1 - x][N - 1 - y] = square_matrix[N - 1 - y][x];
    square_matrix[N - 1 - y][x] = temp;
}

template<typename RotateGroupFunc>
constexpr auto Rotate90Degree_Group(MatrixType square_matrix,
                                    const RotateGroupFunc rotate_group) {
    const auto N = square_matrix.size();
    for (MatrixType::size_type x = 0; x < N / 2; ++x) {
        for (auto y = x; y < N - x - 1; ++y) {
            rotate_group(square_matrix, x, y);
        }
    }

    return square_matrix;
}

inline auto Rotate90Degree_AntiClockwise_Group(MatrixType square_matrix) {
    return Rotate90Degree_Group(std::move(square_matrix), rotateGroup90Degree_AntiClockwise);
}


/**
 * @reference   Rotate a matrix by 90 degree without using any extra space | Set 2
 *              https://www.geeksforgeeks.org/rotate-matrix-90-degree-without-using-extra-space-set-2/
 *
 * @tags    #square-matrix-rotation
 */
inline auto Rotate90Degree_AntiClockwise_Transpose(MatrixType square_matrix) {
    return ReverseMatrixColumns(Transpose(std::move(square_matrix)));
}


/**
 * @reference   Rotate Image
 *              https://leetcode.com/problems/rotate-image/
 *
 * You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
 * You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
 * DO NOT allocate another 2D matrix and do the rotation.
 *
 * @tags    #square-matrix-rotation
 */
inline auto Rotate90Degree_Clockwise_Transpose(MatrixType square_matrix) {
    return ReverseMatrixRows(Transpose(std::move(square_matrix)));
}


/**
 * @reference   Rotate a matrix by 90 degree in clockwise direction without using any extra space
 *              https://www.geeksforgeeks.org/rotate-a-matrix-by-90-degree-in-clockwise-direction-without-using-any-extra-space/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.6.
 *
 * @tags    #square-matrix-rotation
 */
void rotateGroup90Degree_Clockwise(MatrixType &square_matrix,
                                   const MatrixType::size_type x,
                                   const MatrixType::size_type y) {
    const auto temp = square_matrix[x][y];
    const auto N = square_matrix.size();
    square_matrix[x][y] = square_matrix[N - 1 - y][x];
    square_matrix[N - 1 - y][x] = square_matrix[N - 1 - x][N - 1 - y];
    square_matrix[N - 1 - x][N - 1 - y] = square_matrix[y][N - 1 - x];
    square_matrix[y][N - 1 - x] = temp;
}

inline auto Rotate90Degree_Clockwise_Group(MatrixType square_matrix) {
    return Rotate90Degree_Group(std::move(square_matrix), rotateGroup90Degree_Clockwise);
}


/**
 * @reference   Determine Whether Matrix Can Be Obtained By Rotation
 *              https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/
 *
 * Given two n x n binary matrices mat and target, return true if it is possible to make mat equal to
 * target by rotating mat in 90-degree increments, or false otherwise.
 *
 * @tags    #square-matrix-rotation
 */
auto areRotation(const MatrixType &one, const MatrixType &target) {
    const auto N = one.size();
    std::vector results(4, true);
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (one[i][j] != target[i][j]) {
                results[0] = false;
            }
            if (one[i][j] != target[N - j - 1][i]) {
                results[1] = false;
            }
            if (one[i][j] != target[N - i - 1][N - j - 1]) {
                results[2] = false;
            }
            if (one[i][j] != target[j][N - i - 1]) {
                results[3] = false;
            }
        }
    }

    return results[0] or results[1] or results[2] or results[3];
}

} //namespace


// clang-format off
const MatrixType SAMPLE1 = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};

const MatrixType EXPECTED_A1 = {
    {4, 8, 12, 16},
    {3, 7, 11, 15},
    {2, 6, 10, 14},
    {1, 5, 9, 13}
};

const MatrixType EXPECTED_C1 = {
    {13, 9, 5, 1},
    {14, 10, 6, 2},
    {15, 11, 7, 3},
    {16, 12, 8, 4},
};


const MatrixType SAMPLE2 = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

const MatrixType EXPECTED_A2 = {
    {3, 6, 9},
    {2, 5, 8},
    {1, 4, 7}
};

const MatrixType EXPECTED_C2 = {
    {7, 4, 1},
    {8, 5, 2},
    {9, 6, 3},
};

const MatrixType EXPECTED_T2 = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}
};

const MatrixType SAMPLE3 = {{1}};
// clang-format on


THE_BENCHMARK(Rotate90Degree_AntiClockwise_Group, SAMPLE1);

SIMPLE_TEST(Rotate90Degree_AntiClockwise_Group, TestSAMPLE1, EXPECTED_A1, SAMPLE1);
SIMPLE_TEST(Rotate90Degree_AntiClockwise_Group, TestSAMPLE2, EXPECTED_A2, SAMPLE2);
SIMPLE_TEST(Rotate90Degree_AntiClockwise_Group, TestSAMPLE3, SAMPLE3, SAMPLE3);


THE_BENCHMARK(Rotate90Degree_AntiClockwise_Transpose, SAMPLE1);

SIMPLE_TEST(Rotate90Degree_AntiClockwise_Transpose, TestSAMPLE1, EXPECTED_A1, SAMPLE1);
SIMPLE_TEST(Rotate90Degree_AntiClockwise_Transpose, TestSAMPLE2, EXPECTED_A2, SAMPLE2);
SIMPLE_TEST(Rotate90Degree_AntiClockwise_Transpose, TestSAMPLE3, SAMPLE3, SAMPLE3);


THE_BENCHMARK(Rotate90Degree_Clockwise_Group, SAMPLE1);

SIMPLE_TEST(Rotate90Degree_Clockwise_Group, TestSAMPLE1, EXPECTED_C1, SAMPLE1);
SIMPLE_TEST(Rotate90Degree_Clockwise_Group, TestSAMPLE2, EXPECTED_C2, SAMPLE2);
SIMPLE_TEST(Rotate90Degree_Clockwise_Group, TestSAMPLE3, SAMPLE3, SAMPLE3);


THE_BENCHMARK(Rotate90Degree_Clockwise_Transpose, SAMPLE1);

SIMPLE_TEST(Rotate90Degree_Clockwise_Transpose, TestSAMPLE1, EXPECTED_C1, SAMPLE1);
SIMPLE_TEST(Rotate90Degree_Clockwise_Transpose, TestSAMPLE2, EXPECTED_C2, SAMPLE2);
SIMPLE_TEST(Rotate90Degree_Clockwise_Transpose, TestSAMPLE3, SAMPLE3, SAMPLE3);


THE_BENCHMARK(areRotation, SAMPLE1, EXPECTED_A1);

SIMPLE_TEST(areRotation, TestSAMPLE1, true, EXPECTED_A1, SAMPLE1);
SIMPLE_TEST(areRotation, TestSAMPLE2, true, EXPECTED_C2, SAMPLE2);
SIMPLE_TEST(areRotation, TestSAMPLE3, true, SAMPLE3, SAMPLE3);
SIMPLE_TEST(areRotation, TestSAMPLE4, true, EXPECTED_T2, SAMPLE2);
