#include "common_header.h"

#include "transpose.h"


const MatrixType SAMPLE1 = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
const MatrixType EXPECTED1 = {
    {1, 4, 7},
    {2, 5, 8},
    {3, 6, 9}
};

const MatrixType SAMPLE2 = {
    {1, 1, 1, 1},
    {2, 2, 2, 2},
    {3, 3, 3, 3},
    {4, 4, 4, 4}
};
const MatrixType EXPECTED2 = {
    {1, 2, 3, 4},
    {1, 2, 3, 4},
    {1, 2, 3, 4},
    {1, 2, 3, 4}
};


THE_BENCHMARK(Transpose, SAMPLE1);

SIMPLE_TEST(Transpose, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(Transpose, TestSAMPLE2, EXPECTED2, SAMPLE2);
