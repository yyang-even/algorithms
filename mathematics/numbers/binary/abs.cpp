#include "common_header.h"

typedef int InputType;

/** Compute the integer absolute value (abs) without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the integer absolute value (abs) without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
unsigned Absolute(const InputType num) {
    const int mask = num >> sizeof(InputType) * CHAR_BIT - 1;
    return (num + mask) ^ mask;
}
unsigned AbsPatented(const InputType num) {
    const int mask = num >> sizeof(InputType) * CHAR_BIT - 1;
    return (num ^ mask) - mask;
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(Absolute, -1);
SIMPLE_BENCHMARK(Absolute, 0);
SIMPLE_BENCHMARK(Absolute, LOWER);
SIMPLE_BENCHMARK(Absolute, UPPER);

SIMPLE_TEST(Absolute, TestSample1, 1, -1);
SIMPLE_TEST(Absolute, TestSample2, 1, -1);
SIMPLE_TEST(Absolute, TestSample3, 0, 0);
SIMPLE_TEST(Absolute, TestSample4, static_cast<unsigned>(UPPER) + 1 , LOWER);
SIMPLE_TEST(Absolute, TestSample5, UPPER, UPPER);

SIMPLE_BENCHMARK(AbsPatented, -1);
SIMPLE_BENCHMARK(AbsPatented, 0);
SIMPLE_BENCHMARK(AbsPatented, LOWER);
SIMPLE_BENCHMARK(AbsPatented, UPPER);

SIMPLE_TEST(AbsPatented, TestSample1, 1, -1);
SIMPLE_TEST(AbsPatented, TestSample2, 1, -1);
SIMPLE_TEST(AbsPatented, TestSample3, 0, 0);
SIMPLE_TEST(AbsPatented, TestSample4, static_cast<unsigned>(UPPER) + 1 , LOWER);
SIMPLE_TEST(AbsPatented, TestSample5, UPPER, UPPER);

MUTUAL_RANDOM_TEST(Absolute, AbsPatented, LOWER, UPPER);
