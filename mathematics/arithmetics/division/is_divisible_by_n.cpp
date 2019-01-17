#include "common_header.h"

#include "is_divisible_by_n.h"

const std::vector<unsigned> SAMPLE1 = {1, 0, 1, 0, 1};
const std::vector<bool> EXPECTED1 = {false, false, false, false, true};

SIMPLE_BENCHMARK(isDivisibleByNDFA, SAMPLE1, 3);

SIMPLE_TEST(isDivisibleByNDFA, TestSAMPLE1, EXPECTED1, SAMPLE1, 3);
