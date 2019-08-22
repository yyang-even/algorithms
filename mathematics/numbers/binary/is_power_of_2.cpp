#include "common_header.h"

#include "is_power_of_2.h"


SIMPLE_BENCHMARK(IsPowerOf2, 1);
SIMPLE_BENCHMARK(IsPowerOf2, 0);
SIMPLE_BENCHMARK(IsPowerOf2, std::numeric_limits<int>::min());
SIMPLE_BENCHMARK(IsPowerOf2, std::numeric_limits<unsigned>::max());

SIMPLE_TEST(IsPowerOf2, TestSample1, true, 1);
SIMPLE_TEST(IsPowerOf2, TestSample2, false, 0);
SIMPLE_TEST(IsPowerOf2, TestSample3, true, std::numeric_limits<int>::min());
SIMPLE_TEST(IsPowerOf2, TestSample4, false, std::numeric_limits<int>::max());
SIMPLE_TEST(IsPowerOf2, TestSample5, false, std::numeric_limits<unsigned>::max());
SIMPLE_TEST(IsPowerOf2, TestSample6, true, 1 << 8);
SIMPLE_TEST(IsPowerOf2, TestSample7, false, 118);
SIMPLE_TEST(IsPowerOf2, TestSample8, true, 16);
SIMPLE_TEST(IsPowerOf2, TestSample9, true, 64);
