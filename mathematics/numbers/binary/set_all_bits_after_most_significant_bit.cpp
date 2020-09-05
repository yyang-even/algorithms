#include "common_header.h"

#include "set_all_bits_after_most_significant_bit.h"


SIMPLE_BENCHMARK(SetAllBitsAfterMSB, Sample1, 0);

SIMPLE_TEST(SetAllBitsAfterMSB, TestSample1, 0u, 0);
SIMPLE_TEST(SetAllBitsAfterMSB, TestSample2, 1u, 1);
SIMPLE_TEST(SetAllBitsAfterMSB, TestSample3, 0b1111u, 0b1010);
SIMPLE_TEST(SetAllBitsAfterMSB, TestSample4, 0b111u, 0b101);
