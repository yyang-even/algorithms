#include "common_header.h"

#include "gcd.h"


SIMPLE_BENCHMARK(gcd, 12, 18);
SIMPLE_BENCHMARK(gcd, 18, 12);

SIMPLE_TEST(gcd, Test1, 6, 12, 18);
SIMPLE_TEST(gcd, Test2, 6, 18, 12);
SIMPLE_TEST(gcd, Test3, 5, 10, 15);
SIMPLE_TEST(gcd, Test4, 5, 35, 10);
SIMPLE_TEST(gcd, Test5, 1, 31, 2);


const auto EXPECTED1 = std::make_tuple(10, 1, -1);
const auto EXPECTED2 = std::make_tuple(5, 1, -2);

SIMPLE_BENCHMARK(gcdExtended, 18, 12);

SIMPLE_TEST(gcdExtended, TestSample1, EXPECTED1, 30, 20);
SIMPLE_TEST(gcdExtended, TestSample2, EXPECTED2, 35, 15);
