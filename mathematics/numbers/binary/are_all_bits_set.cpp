#include "common_header.h"

#include "are_all_bits_set.h"


THE_BENCHMARK(AreAllBitsSet, 7);

SIMPLE_TEST(AreAllBitsSet, TestSample1, true, 0b111);
SIMPLE_TEST(AreAllBitsSet, TestSample2, false, 0);
SIMPLE_TEST(AreAllBitsSet, TestSample3, false, 0b101);
