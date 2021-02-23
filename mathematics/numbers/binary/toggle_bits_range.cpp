#include "common_header.h"

#include "toggle_bits_range.h"


THE_BENCHMARK(ToggleBitsRange, 17, 2, 3);

SIMPLE_TEST(ToggleBitsRange, TestSAMPLE1, 23, 17, 2, 3);
SIMPLE_TEST(ToggleBitsRange, TestSAMPLE2, 44, 50, 2, 5);
