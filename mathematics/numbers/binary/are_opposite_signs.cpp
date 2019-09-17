#include "common_header.h"

#include "are_opposite_signs.h"


constexpr auto LOWER = std::numeric_limits<int>::min();
constexpr auto UPPER = std::numeric_limits<int>::max();


SIMPLE_BENCHMARK(AreOppositeSigns, -1, 0);
SIMPLE_BENCHMARK(AreOppositeSigns, -1, 1);
SIMPLE_BENCHMARK(AreOppositeSigns, LOWER, UPPER);

SIMPLE_TEST(AreOppositeSigns, TestSample1, true, -1, 0);
SIMPLE_TEST(AreOppositeSigns, TestSample2, false, -1, -1);
SIMPLE_TEST(AreOppositeSigns, TestSample3, false, 0, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample4, false, 1, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample5, true, -1, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample6, false, 0, 0);
SIMPLE_TEST(AreOppositeSigns, TestSample7, true, LOWER, UPPER);
SIMPLE_TEST(AreOppositeSigns, TestSample8, false, LOWER, LOWER);
