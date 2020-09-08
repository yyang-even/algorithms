#include "common_header.h"

#include "modulo.h"


typedef int InputType;


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(Mod10, Sample1, LOWER);
SIMPLE_BENCHMARK(Mod10, Sample2, UPPER);

SIMPLE_TEST(Mod10, TestLOWER, LOWER % 10, LOWER);
SIMPLE_TEST(Mod10, TestUPPER, UPPER % 10, UPPER);
SIMPLE_TEST(Mod10, TestSAMPLE1, 3, 203);
SIMPLE_TEST(Mod10, TestSAMPLE2, 0, 70);
SIMPLE_TEST(Mod10, TestSAMPLE3, 0, 0);
SIMPLE_TEST(Mod10, TestSAMPLE4, -3, -203);
SIMPLE_TEST(Mod10, TestSAMPLE5, 0, -200);
SIMPLE_TEST(Mod10, TestSAMPLE6, -5, -1082066345);


SIMPLE_BENCHMARK(Mod10_Float, Sample1, LOWER);
SIMPLE_BENCHMARK(Mod10_Float, Sample2, UPPER);

SIMPLE_TEST(Mod10_Float, TestLOWER, LOWER % 10, LOWER);
SIMPLE_TEST(Mod10_Float, TestUPPER, UPPER % 10, UPPER);
SIMPLE_TEST(Mod10_Float, TestSAMPLE1, 3, 203);
SIMPLE_TEST(Mod10_Float, TestSAMPLE2, 0, 70);
SIMPLE_TEST(Mod10_Float, TestSAMPLE3, 0, 0);
SIMPLE_TEST(Mod10_Float, TestSAMPLE4, -3, -203);
SIMPLE_TEST(Mod10_Float, TestSAMPLE5, 0, -200);
SIMPLE_TEST(Mod10_Float, TestSAMPLE6, -5, -1082066345);

MUTUAL_RANDOM_TEST(Mod10, Mod10_Float, LOWER, UPPER);
