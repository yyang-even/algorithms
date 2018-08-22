#include "common_header.h"

#include "conditionally_set_or_clear.h"

SIMPLE_BENCHMARK(SetOrClear, true, 0b0110, 0b1101);
SIMPLE_BENCHMARK(SetOrClear, false, 0b0110, 0b1101);

SIMPLE_TEST(SetOrClear, TestSample1, 0b1111, true, 0b0110, 0b1101);
SIMPLE_TEST(SetOrClear, TestSample2, 0b1001, false, 0b0110, 0b1101);

SIMPLE_BENCHMARK(SetOrClearSuperscalar, true, 0b0110, 0b1101);
SIMPLE_BENCHMARK(SetOrClearSuperscalar, false, 0b0110, 0b1101);

SIMPLE_TEST(SetOrClearSuperscalar, TestSample1, 0b1111, true, 0b0110, 0b1101);
SIMPLE_TEST(SetOrClearSuperscalar, TestSample2, 0b1001, false, 0b0110, 0b1101);
