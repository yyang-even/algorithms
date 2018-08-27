#include "common_header.h"

#include "find_first_bit_set.h"

using InputType = unsigned;


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(FindFirstBitSet, 4);

SIMPLE_TEST(FindFirstBitSet, TestLOWER, 1, LOWER);
SIMPLE_TEST(FindFirstBitSet, TestSample1, 1, 0b101);
SIMPLE_TEST(FindFirstBitSet, TestSample2, 2, 18);
SIMPLE_TEST(FindFirstBitSet, TestSample3, 1, 19);
SIMPLE_TEST(FindFirstBitSet, TestSample4, 3, 12);
SIMPLE_TEST(FindFirstBitSet, TestUPPER, 1, UPPER);

MUTUAL_RANDOM_TEST(FindFirstBitSet, ffs, LOWER, UPPER);
