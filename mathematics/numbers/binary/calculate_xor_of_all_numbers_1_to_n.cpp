#include "common_header.h"

#include "calculate_xor_of_all_numbers_1_to_n.h"


THE_BENCHMARK(XorOfAllFrom1toN, 4);

SIMPLE_TEST(XorOfAllFrom1toN, TestLOWER, 0, 0);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample1, 1, 1);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample2, 3, 2);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample3, 3, 2);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample4, 0, 3);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample5, 1, 5);
