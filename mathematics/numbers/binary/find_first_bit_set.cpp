#include "common_header.h"

#include "clear_bit.h"
#include "find_first_bit_set.h"


namespace {

/** Position of rightmost different bit
 *
 * @reference   https://www.geeksforgeeks.org/position-rightmost-different-bit/
 */
auto PositionOfRightmostDifferentBit(const unsigned lhs, const unsigned rhs) {
    return ffs((lhs ^ rhs));
}


/** Number formed by the rightmost set bit in N
 *
 * @reference   https://www.geeksforgeeks.org/number-formed-by-the-rightmost-set-bit-in-n/
 */
auto NumberFormedByRightmostBit(const unsigned N) {
    return N ^ ClearRightmostBit(N);
}

}//namespace


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


SIMPLE_BENCHMARK(FindFirstBitSet, Sample1, 4);

SIMPLE_TEST(FindFirstBitSet, TestLOWER, 1u, LOWER);
SIMPLE_TEST(FindFirstBitSet, TestSample1, 1u, 0b101);
SIMPLE_TEST(FindFirstBitSet, TestSample2, 2u, 18);
SIMPLE_TEST(FindFirstBitSet, TestSample3, 1u, 19);
SIMPLE_TEST(FindFirstBitSet, TestSample4, 3u, 12);
SIMPLE_TEST(FindFirstBitSet, TestUPPER, 1u, UPPER);

MUTUAL_RANDOM_TEST(FindFirstBitSet, ffs, LOWER, UPPER);


SIMPLE_BENCHMARK(PositionOfRightmostDifferentBit, Sample1, 11, 9);

SIMPLE_TEST(PositionOfRightmostDifferentBit, TestSample1, 2, 11, 9);
SIMPLE_TEST(PositionOfRightmostDifferentBit, TestSample2, 5, 52, 4);


SIMPLE_BENCHMARK(NumberFormedByRightmostBit, Sample1, 4);

SIMPLE_TEST(NumberFormedByRightmostBit, TestSample1, 1u, 7);
SIMPLE_TEST(NumberFormedByRightmostBit, TestSample2, 2u, 10);
SIMPLE_TEST(NumberFormedByRightmostBit, TestSample3, 16u, 16);
