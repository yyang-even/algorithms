#include "common_header.h"

#include "sum_of_factors_of_a_number.h"


SIMPLE_BENCHMARK(SumOfFactorsOfN, 1100);

SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE1, 28, 12);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE2, 168, 60);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE3, 2604, 1100);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE4, 72, 30);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE5, 24, 15);
SIMPLE_TEST(SumOfFactorsOfN, TestSAMPLE6, 14, 13);
