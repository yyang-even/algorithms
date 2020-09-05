#include "common_header.h"

#include "toggle_all_bits_after_most_significant_bit.h"


SIMPLE_BENCHMARK(ToggleAllBitsAfterMSB, Sample1, 0);

SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample1, 0u, 0);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample2, 0u, 1);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample3, 5u, 10);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample4, 2u, 5);
