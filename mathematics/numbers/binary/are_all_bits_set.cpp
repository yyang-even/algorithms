#include "common_header.h"

#include "are_all_bits_set.h"

SIMPLE_BENCHMARK(AreAllBitsSet, 7);

SIMPLE_TEST(AreAllBitsSet, TestSample1, TRUE, 0b111);
SIMPLE_TEST(AreAllBitsSet, TestSample2, FALSE, 0);
SIMPLE_TEST(AreAllBitsSet, TestSample3, FALSE, 0b101);
