#include "common_header.h"

#include "clear_bits_range.h"


THE_BENCHMARK(ClearBitsRange, 42, 2, 5);

SIMPLE_TEST(ClearBitsRange, TestSAMPLE1, 32, 42, 2, 5);
SIMPLE_TEST(ClearBitsRange, TestSAMPLE2, 48, 63, 1, 4);
