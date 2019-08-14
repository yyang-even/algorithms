#include "common_header.h"

#include "conditionally_set_or_clear.h"


SIMPLE_BENCHMARK(SetOrClear, true, 0b0110, 0b1101);
SIMPLE_BENCHMARK(SetOrClear, false, 0b0110, 0b1101);

SIMPLE_TEST(SetOrClear, TestSample1, 0b1111u, true, 0b0110, 0b1101);
SIMPLE_TEST(SetOrClear, TestSample2, 0b1001u, false, 0b0110, 0b1101);


SIMPLE_BENCHMARK(SetOrClear_Superscalar, true, 0b0110, 0b1101);
SIMPLE_BENCHMARK(SetOrClear_Superscalar, false, 0b0110, 0b1101);

SIMPLE_TEST(SetOrClear_Superscalar, TestSample1, 0b1111u, true, 0b0110, 0b1101);
SIMPLE_TEST(SetOrClear_Superscalar, TestSample2, 0b1001u, false, 0b0110, 0b1101);
