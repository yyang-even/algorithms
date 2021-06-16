#include "common_header.h"

#include "rectangle.h"


constexpr Rectangle SAMPLE_R1 = {0, 10, 8, 0};
constexpr Point SAMPLE_P1 = {1, 5};
constexpr Rectangle SAMPLE_R2 = {4, 2, 3, -1};
constexpr Point SAMPLE_P2 = {0, 4};


THE_BENCHMARK(Contains, SAMPLE_R1, SAMPLE_P1);

SIMPLE_TEST(Contains, TestSAMPLE1, true, SAMPLE_R1, SAMPLE_P1);
SIMPLE_TEST(Contains, TestSAMPLE2, false, SAMPLE_R2, SAMPLE_P2);
