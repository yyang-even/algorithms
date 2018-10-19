#include "common_header.h"

#include "gcd.h"

SIMPLE_BENCHMARK(gcd, 12, 18);
SIMPLE_BENCHMARK(gcd, 18, 12);
SIMPLE_TEST(gcd, Test1, 6, 12, 18);
SIMPLE_TEST(gcd, Test2, 6, 18, 12);
