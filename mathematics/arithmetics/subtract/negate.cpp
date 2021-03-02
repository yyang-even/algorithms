#include "common_header.h"

#include "negate.h"


THE_BENCHMARK(Negate, 1);

SIMPLE_TEST(Negate, TestSAMPLE1, -1, 1);
SIMPLE_TEST(Negate, TestSAMPLE2, 1, -1);
SIMPLE_TEST(Negate, TestSAMPLE3, 0, 0);
