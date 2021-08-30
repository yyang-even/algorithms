#include "common_header.h"

#include "reverse_matrix.h"


namespace {

/**
 * @reference   Flipping an Image
 *              https://leetcode.com/problems/flipping-an-image/
 *
 * Given an n x n binary matrix image, flip the image horizontally, then invert it, and
 * return the resulting image.
 * To flip an image horizontally means that each row of the image is reversed.
 *  For example, flipping [1,1,0] horizontally results in [0,1,1].
 * To invert an image means that each 0 is replaced by 1, and each 1 is replaced by 0.
 *  For example, inverting [0,1,1] results in [1,0,0].
 */

}//namespace

const MatrixType SAMPLE1 = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
};
const MatrixType EXPECTED_R1 = {
    {3, 2, 1},
    {6, 5, 4},
    {9, 8, 7}
};
const MatrixType EXPECTED_C1 = {
    {7, 8, 9},
    {4, 5, 6},
    {1, 2, 3},
};

const MatrixType SAMPLE2 = {
    {1, 2},
    {4, 5},
    {7, 8},
    {9, 10},
};
const MatrixType EXPECTED_R2 = {
    {2, 1},
    {5, 4},
    {8, 7},
    {10, 9}
};
const MatrixType EXPECTED_C2 = {
    {9, 10},
    {7, 8},
    {4, 5},
    {1, 2},
};


THE_BENCHMARK(ReverseMatrixRows, SAMPLE1);

SIMPLE_TEST(ReverseMatrixRows, TestSAMPLE1, EXPECTED_R1, SAMPLE1);
SIMPLE_TEST(ReverseMatrixRows, TestSAMPLE2, EXPECTED_R2, SAMPLE2);


THE_BENCHMARK(ReverseMatrixColumns, SAMPLE1);

SIMPLE_TEST(ReverseMatrixColumns, TestSAMPLE1, EXPECTED_C1, SAMPLE1);
SIMPLE_TEST(ReverseMatrixColumns, TestSAMPLE2, EXPECTED_C2, SAMPLE2);
