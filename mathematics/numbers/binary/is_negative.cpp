#include "common_header.h"

typedef int InputType;

/** Compute the sign of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the sign of an integer
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
INT_BOOL IsNegativePortable(const InputType num) {
    return 1 & ((unsigned InputType)num >> (sizeof(InputType) * CHAR_BIT - 1));
}

INT_BOOL IsNegative(const InputType num) {
    return num < 0 ? TRUE : FALSE;
}

SIMPLE_BENCHMARK(IsNegativePortable, -1);
SIMPLE_BENCHMARK(IsNegativePortable, 0);
SIMPLE_BENCHMARK(IsNegativePortable, INT_MIN);
SIMPLE_BENCHMARK(IsNegativePortable, INT_MAX);

SIMPLE_TEST(IsNegativePortable, TestSample1, TRUE, -1);
SIMPLE_TEST(IsNegativePortable, TestSample2, FALSE, 0);
SIMPLE_TEST(IsNegativePortable, TestSample3, TRUE, INT_MIN);
SIMPLE_TEST(IsNegativePortable, TestSample4, FALSE, INT_MAX);
MUTUAL_RANDOM_TEST(IsNegativePortable, IsNegative, INT_MIN, INT_MAX);
