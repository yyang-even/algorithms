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


SIMPLE_BENCHMARK(Absolute, -1);
SIMPLE_BENCHMARK(Absolute, 0);
SIMPLE_BENCHMARK(Absolute, INT_MIN);
SIMPLE_BENCHMARK(Absolute, INT_MAX);

SIMPLE_TEST(Absolute, TestSample1, 1, -1);
SIMPLE_TEST(Absolute, TestSample2, 1, -1);
SIMPLE_TEST(Absolute, TestSample3, 0, 0);
SIMPLE_TEST(Absolute, TestSample4, static_cast<unsigned>(INT_MAX) + 1 , INT_MIN);
SIMPLE_TEST(Absolute, TestSample5, INT_MAX, INT_MAX);

SIMPLE_BENCHMARK(AbsPatented, -1);
SIMPLE_BENCHMARK(AbsPatented, 0);
SIMPLE_BENCHMARK(AbsPatented, INT_MIN);
SIMPLE_BENCHMARK(AbsPatented, INT_MAX);

SIMPLE_TEST(AbsPatented, TestSample1, 1, -1);
SIMPLE_TEST(AbsPatented, TestSample2, 1, -1);
SIMPLE_TEST(AbsPatented, TestSample3, 0, 0);
SIMPLE_TEST(AbsPatented, TestSample4, static_cast<unsigned>(INT_MAX) + 1 , INT_MIN);
SIMPLE_TEST(AbsPatented, TestSample5, INT_MAX, INT_MAX);

MUTUAL_RANDOM_TEST(Absolute, AbsPatented, INT_MIN, INT_MAX);
