#include "common_header.h"

#include <string.h>

using InputType = unsigned;

/** Position of rightmost set bit
 *
 * @reference   https://www.geeksforgeeks.org/position-of-rightmost-set-bit/
 *
 * Write a one line C function to return position of first 1 from right to left,
 * in binary representation of an Integer.
 */
InputType FindFirstBitSet(const InputType num) {
    assert(num);

    return log2(num & (-num)) + 1;
}


constexpr auto LOWER = 1;
constexpr auto UPPER = std::numeric_limits<unsigned>::max();

SIMPLE_BENCHMARK(FindFirstBitSet, 4);

SIMPLE_TEST(FindFirstBitSet, TestLOWER, 1, LOWER);
SIMPLE_TEST(FindFirstBitSet, TestSample1, 1, 0b101);
SIMPLE_TEST(FindFirstBitSet, TestSample2, 2, 18);
SIMPLE_TEST(FindFirstBitSet, TestSample3, 1, 19);
SIMPLE_TEST(FindFirstBitSet, TestSample4, 3, 12);
SIMPLE_TEST(FindFirstBitSet, TestUPPER, 1, UPPER);

MUTUAL_RANDOM_TEST(FindFirstBitSet, ffs, LOWER, UPPER);
