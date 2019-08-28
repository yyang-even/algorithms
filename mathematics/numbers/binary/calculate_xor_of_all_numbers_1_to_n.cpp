#include "common_header.h"

#include "calculate_xor_of_all_numbers_1_to_n.h"


SIMPLE_BENCHMARK(XorOfAllFrom1toN, 4);

SIMPLE_TEST(XorOfAllFrom1toN, TestLOWER, 0u, 0);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample1, 1u, 1);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample2, 3u, 2);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample3, 3u, 2);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample4, 0u, 3);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample5, 1u, 5);
