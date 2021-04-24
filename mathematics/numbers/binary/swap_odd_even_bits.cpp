#include "common_header.h"

#include "swap_odd_even_bits.h"


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


THE_BENCHMARK(SwapOddAndEvenBits, UPPER);

SIMPLE_TEST(SwapOddAndEvenBits, TestLOWER, LOWER, LOWER);
SIMPLE_TEST(SwapOddAndEvenBits, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(SwapOddAndEvenBits, TestSAMPLE1, 0b00101011, 0b00010111);
