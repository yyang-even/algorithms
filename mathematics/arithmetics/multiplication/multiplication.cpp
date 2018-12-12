#include "common_header.h"

#include "multiplication.h"

SIMPLE_BENCHMARK(MultiplyHelper, 3, 4);

SIMPLE_TEST(MultiplyHelper, TestSAMPLE1, -55, 5, -11);
SIMPLE_TEST(MultiplyHelper, TestSAMPLE2, -55, -5, 11);
SIMPLE_TEST(MultiplyHelper, TestSAMPLE3, 55, 5, 11);
SIMPLE_TEST(MultiplyHelper, TestSAMPLE4, 55, -5, -11);
