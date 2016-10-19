#include "common_header.h"

typedef int InputType;

InputType Mod10(const InputType num) {
    return num - (num / 10 * 10);
}

InputType Mod10Float(const InputType num) {
    //Use static_cast<InputType> instead of std::floor() to avoid float accuracy issue
    return num - (static_cast<InputType>(static_cast<double>(num) * 0.1) * 10);
}


const InputType LOWER = INT_MIN;
const InputType UPPER = INT_MAX;

SIMPLE_BENCHMARK(Mod10, LOWER);
SIMPLE_BENCHMARK(Mod10, UPPER);
RANDOM_BENCHMARK(Mod10, LOWER, UPPER);

SIMPLE_TEST(Mod10, TestLOWER, LOWER % 10, LOWER);
SIMPLE_TEST(Mod10, TestUPPER, UPPER % 10, UPPER);
SIMPLE_TEST(Mod10, TestSAMPLE1, 3, 203);
SIMPLE_TEST(Mod10, TestSAMPLE2, 0, 70);
SIMPLE_TEST(Mod10, TestSAMPLE3, 0, 0);
SIMPLE_TEST(Mod10, TestSAMPLE4, -3, -203);
SIMPLE_TEST(Mod10, TestSAMPLE5, 0, -200);
SIMPLE_TEST(Mod10, TestSAMPLE6, -5, -1082066345);

SIMPLE_BENCHMARK(Mod10Float, LOWER);
SIMPLE_BENCHMARK(Mod10Float, UPPER);
RANDOM_BENCHMARK(Mod10Float, LOWER, UPPER);

SIMPLE_TEST(Mod10Float, TestLOWER, LOWER % 10, LOWER);
SIMPLE_TEST(Mod10Float, TestUPPER, UPPER % 10, UPPER);
SIMPLE_TEST(Mod10Float, TestSAMPLE1, 3, 203);
SIMPLE_TEST(Mod10Float, TestSAMPLE2, 0, 70);
SIMPLE_TEST(Mod10Float, TestSAMPLE3, 0, 0);
SIMPLE_TEST(Mod10Float, TestSAMPLE4, -3, -203);
SIMPLE_TEST(Mod10Float, TestSAMPLE5, 0, -200);
SIMPLE_TEST(Mod10Float, TestSAMPLE6, -5, -1082066345);

MUTUAL_RANDOM_TEST(Mod10, Mod10Float, LOWER, UPPER);
