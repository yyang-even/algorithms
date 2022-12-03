#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** Image Overlap
 *
 * @reference   https://leetcode.com/problems/image-overlap/
 *
 * You are given two images, img1 and img2, represented as binary, square matrices of size n x n. A
 * binary matrix has only 0s and 1s as values.
 * We translate one image however we choose by sliding all the 1 bits left, right, up, and/or down any
 * number of units. We then place it on top of the other image. We can then calculate the overlap by
 * counting the number of positions that have a 1 in both images.
 * Note also that a translation does not include any kind of rotation. Any 1 bits that are translated
 * outside of the matrix borders are erased.
 * Return the largest possible overlap.
 */
auto nonzeroCells(const MatrixType &a_matrix) {
    std::vector<std::pair<int, int>> result;

    for (std::size_t i = 0; i < a_matrix.size(); ++i) {
        for (std::size_t j = 0; j < a_matrix.front().size(); ++j) {
            if (a_matrix[i][j] == 1) {
                result.emplace_back(i, j);
            }
        }
    }

    return result;
}

auto ImageOverlap_Vector(const MatrixType &image1, const MatrixType &image2) {
    const auto image_one_ones = nonzeroCells(image1);
    const auto image_two_ones = nonzeroCells(image2);

    std::map<std::pair<int, int>, int> group_count;
    for (const auto &[i, j] : image_one_ones) {
        for (const auto &[m, n] : image_two_ones) {
            const auto x = m - i;
            const auto y = n - j;

            const auto [iter, inserted] = group_count.emplace(std::pair(x, y), 1);
            if (not inserted) {
                ++(iter->second);
            }
        }
    }

    int result = 0;
    for (const auto &[_, c] : group_count) {
        result = std::max(result, c);
    }

    return result;
}


auto convolute(const MatrixType &a_matrix, const MatrixType &kernel, const int x, const int y) {
    int result = 0;
    for (std::size_t r = 0; r < a_matrix.size(); ++r) {
        for (std::size_t c = 0; c < a_matrix.size(); ++c) {
            result += a_matrix[r][c] * kernel[r + y][c + x];
        }
    }

    return result;
}

auto ImageOverlap_Convolution(const MatrixType &image1, const MatrixType &image2) {
    const int N = image1.size();
    std::vector padded_image2(3 * N - 2, std::vector(3 * N - 2, 0));
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            padded_image2[r + N - 1][c + N - 1] = image2[r][c];
        }
    }

    int result = 0;
    for (int x = 0; x < 2 * N - 1; ++x) {
        for (int y = 0; y < 2 * N - 1; ++y) {
            result = std::max(result, convolute(image1, padded_image2, x, y));
        }
    }

    return result;
}

} //namespace


const MatrixType SAMPLE1L = {{1, 1, 0}, {0, 1, 0}, {0, 1, 0}};
const MatrixType SAMPLE1R = {{0, 0, 0}, {0, 1, 1}, {0, 0, 1}};

const MatrixType SAMPLE2 = {{1}};
const MatrixType SAMPLE3 = {{0}};


THE_BENCHMARK(ImageOverlap_Vector, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(ImageOverlap_Vector, TestSAMPLE1, 3, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(ImageOverlap_Vector, TestSAMPLE2, 1, SAMPLE2, SAMPLE2);
SIMPLE_TEST(ImageOverlap_Vector, TestSAMPLE3, 0, SAMPLE3, SAMPLE3);


THE_BENCHMARK(ImageOverlap_Convolution, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(ImageOverlap_Convolution, TestSAMPLE1, 3, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(ImageOverlap_Convolution, TestSAMPLE2, 1, SAMPLE2, SAMPLE2);
SIMPLE_TEST(ImageOverlap_Convolution, TestSAMPLE3, 0, SAMPLE3, SAMPLE3);
