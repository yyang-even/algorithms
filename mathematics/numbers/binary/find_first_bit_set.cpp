#include "common_header.h"

#include "clear_bit.h"
#include "find_first_bit_set.h"


namespace {

/** Position of rightmost different bit
 *
 * @reference   https://www.geeksforgeeks.org/position-rightmost-different-bit/
 */
inline auto
PositionOfRightmostDifferentBit(const unsigned lhs, const unsigned rhs) {
    return ffs((lhs ^ rhs));
}


/** Number formed by the rightmost set bit in N
 *
 * @reference   https://www.geeksforgeeks.org/number-formed-by-the-rightmost-set-bit-in-n/
 */
inline constexpr auto NumberFormedByRightmostBit(const unsigned N) {
    return N ^ ClearRightmostBit(N);
}

}//namespace


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


THE_BENCHMARK(FindFirstBitSet, 4);

SIMPLE_TEST(FindFirstBitSet, TestLOWER, 1, LOWER);
SIMPLE_TEST(FindFirstBitSet, TestSample1, 1, 0b101);
SIMPLE_TEST(FindFirstBitSet, TestSample2, 2, 18);
SIMPLE_TEST(FindFirstBitSet, TestSample3, 1, 19);
SIMPLE_TEST(FindFirstBitSet, TestSample4, 3, 12);
SIMPLE_TEST(FindFirstBitSet, TestUPPER, 1, UPPER);

MUTUAL_RANDOM_TEST(FindFirstBitSet, ffs, LOWER, UPPER);


THE_BENCHMARK(PositionOfRightmostDifferentBit, 11, 9);

SIMPLE_TEST(PositionOfRightmostDifferentBit, TestSample1, 2, 11, 9);
SIMPLE_TEST(PositionOfRightmostDifferentBit, TestSample2, 5, 52, 4);


THE_BENCHMARK(NumberFormedByRightmostBit, 4);

SIMPLE_TEST(NumberFormedByRightmostBit, TestSample1, 1, 7);
SIMPLE_TEST(NumberFormedByRightmostBit, TestSample2, 2, 10);
SIMPLE_TEST(NumberFormedByRightmostBit, TestSample3, 16, 16);
