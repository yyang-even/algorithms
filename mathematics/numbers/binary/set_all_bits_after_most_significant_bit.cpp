#include "common_header.h"

#include "set_all_bits_after_most_significant_bit.h"


THE_BENCHMARK(SetAllBitsAfterMSB, 0);

SIMPLE_TEST(SetAllBitsAfterMSB, TestSample1, 0, 0);
SIMPLE_TEST(SetAllBitsAfterMSB, TestSample2, 1, 1);
SIMPLE_TEST(SetAllBitsAfterMSB, TestSample3, 0b1111, 0b1010);
SIMPLE_TEST(SetAllBitsAfterMSB, TestSample4, 0b111, 0b101);
