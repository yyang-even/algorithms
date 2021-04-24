#include "common_header.h"

#include "is_bit_set.h"


THE_BENCHMARK(IsBitSet, 0, 4);

SIMPLE_TEST(IsBitSet, TestSample1, true, 0b101, 0);
SIMPLE_TEST(IsBitSet, TestSample2, false, 0, 0);
SIMPLE_TEST(IsBitSet, TestSample3, false, 0, 1);
SIMPLE_TEST(IsBitSet, TestSample4, false, 13, 1);
SIMPLE_TEST(IsBitSet, TestSample5, true, 14, 2);
SIMPLE_TEST(IsBitSet, TestSample6, true, 10, 1);
SIMPLE_TEST(IsBitSet, TestSample7, false, 21, 3);
