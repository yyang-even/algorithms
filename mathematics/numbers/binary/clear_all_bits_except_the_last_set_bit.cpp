#include "common_header.h"

#include "clear_all_bits_except_the_last_set_bit.h"

SIMPLE_BENCHMARK(ClearAllBitsExceptTheLastSetBit, 1);

SIMPLE_TEST(ClearAllBitsExceptTheLastSetBit, TestSample1, 0b00000100u, 0b00101100);
