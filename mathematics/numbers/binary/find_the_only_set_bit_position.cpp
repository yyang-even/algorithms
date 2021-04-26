#include "common_header.h"

#include "is_power_of_2.h"


namespace {

/** Find position of the only set bit
 *
 * @reference   https://www.geeksforgeeks.org/find-position-of-the-only-set-bit/
 *
 * Given a number having only one '1' and all other '0's in its binary representation,
 * find position of the only set bit.
 */
constexpr inline auto FindPositionOfTheOnlySetBit(const unsigned v) {
    assert(IsPowerOf2(v));

    return static_cast<unsigned>(std::log2(v)) + 1;
}

}//namespace


THE_BENCHMARK(FindPositionOfTheOnlySetBit, 128);

SIMPLE_TEST(FindPositionOfTheOnlySetBit, TestSample1, 1, 1);
SIMPLE_TEST(FindPositionOfTheOnlySetBit, TestSample2, 8, 128);
