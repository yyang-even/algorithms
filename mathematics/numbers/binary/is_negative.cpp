#include "common_header.h"

typedef int InputType;

/** Compute the sign of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the sign of an integer
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
INT_BOOL IsNegativePortable(const InputType num) {
    return 1 & ((unsigned InputType)num >> (Bits_Number<decltype(num)>() - 1));
}

INT_BOOL IsNegative(const InputType num) {
    return num < 0 ? TRUE : FALSE;
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(IsNegativePortable, -1);
SIMPLE_BENCHMARK(IsNegativePortable, 0);
SIMPLE_BENCHMARK(IsNegativePortable, LOWER);
SIMPLE_BENCHMARK(IsNegativePortable, UPPER);

SIMPLE_TEST(IsNegativePortable, TestSample1, TRUE, -1);
SIMPLE_TEST(IsNegativePortable, TestSample2, FALSE, 0);
SIMPLE_TEST(IsNegativePortable, TestSample3, TRUE, LOWER);
SIMPLE_TEST(IsNegativePortable, TestSample4, FALSE, UPPER);
MUTUAL_RANDOM_TEST(IsNegativePortable, IsNegative, LOWER, UPPER);
