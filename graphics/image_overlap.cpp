#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/**
 * @reference   Image Overlap
 *              https://leetcode.com/problems/image-overlap/
 *
 * You are given two images, img1 and img2, represented as binary, square matrices of size n x n. A
 * binary matrix has only 0s and 1s as values.
 * We translate one image however we choose by sliding all the 1 bits left, right, up, and/or down any
 * number of units. We then place it on top of the other image. We can then calculate the overlap by
 * counting the number of positions that have a 1 in both images.
 * Note also that a translation does not include any kind of rotation. Any 1 bits that are translated
 * outside of the matrix borders are erased.
 * Return the largest possible overlap.
 *
 * @tags    #matrix #enumeration #hash-table #min-max-element
 */
auto ImageOverlap_Vector(const MatrixType &img1, const MatrixType &img2) {
    const int N = img1.size();

    std::vector<std::pair<int, int>> ones1;
    std::vector<std::pair<int, int>> ones2;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (img1[i][j]) {
                ones1.emplace_back(i, j);
            }
            if (img2[i][j]) {
                ones2.emplace_back(i, j);
            }
        }
    }

    int result = 0;
    std::vector delta_counts(2 * N, std::vector(2 * N, 0));
    for (const auto &[i, j] : ones1) {
        for (const auto &[x, y] : ones2) {
            const auto dx = x - i + N;
            const auto dy = y - j + N;
            result = std::max(result, ++delta_counts[dx][dy]);
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
