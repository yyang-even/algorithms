#include "common_header.h"

#include "reverse_matrix.h"


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
