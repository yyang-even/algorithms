#include "common_header.h"

#include "find_first_bit_set.h"


namespace {

using InputType = unsigned;

/** Position of rightmost different bit
 *
 * @reference   https://www.geeksforgeeks.org/position-rightmost-different-bit/
 */
auto PositionOfRightmostDifferentBit(const InputType lhs, const InputType rhs) {
    return ffs((lhs ^ rhs));
}

}//namespace


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(FindFirstBitSet, 4);

SIMPLE_TEST(FindFirstBitSet, TestLOWER, 1u, LOWER);
SIMPLE_TEST(FindFirstBitSet, TestSample1, 1u, 0b101);
SIMPLE_TEST(FindFirstBitSet, TestSample2, 2u, 18);
SIMPLE_TEST(FindFirstBitSet, TestSample3, 1u, 19);
SIMPLE_TEST(FindFirstBitSet, TestSample4, 3u, 12);
SIMPLE_TEST(FindFirstBitSet, TestUPPER, 1u, UPPER);

MUTUAL_RANDOM_TEST(FindFirstBitSet, ffs, LOWER, UPPER);


SIMPLE_BENCHMARK(PositionOfRightmostDifferentBit, 11, 9);

SIMPLE_TEST(PositionOfRightmostDifferentBit, TestSample1, 2, 11, 9);
SIMPLE_TEST(PositionOfRightmostDifferentBit, TestSample2, 5, 52, 4);
