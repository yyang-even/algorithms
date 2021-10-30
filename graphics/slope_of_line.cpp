#include "common_header.h"

#include "line.h"


constexpr Point SAMPLE_P1 = {4, 2};
constexpr Point SAMPLE_P2 = {2, 5};


THE_BENCHMARK(Slope, SAMPLE_P1, SAMPLE_P2);

SIMPLE_DOUBLE_TEST(Slope, TestSAMPLE1, -1.5, SAMPLE_P1, SAMPLE_P2);
