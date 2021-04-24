#include "common_header.h"

#include "toggle_all_bits_after_most_significant_bit.h"


THE_BENCHMARK(ToggleAllBitsAfterMSB, 0);

SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample1, 0, 0);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample2, 0, 1);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample3, 5, 10);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample4, 2, 5);
