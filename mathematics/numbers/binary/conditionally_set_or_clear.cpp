#include "common_header.h"

#include "conditionally_set_or_clear.h"


namespace {

/** Modify a bit at a given position
 *
 * @reference   https://www.geeksforgeeks.org/modify-bit-given-position/
 *
 * Given a number n, a position p and a binary value b, we need to change the bit at position p in n to value b.
 */
auto SetOrClearOneBit(const unsigned n, const unsigned p, const bool is_set) {
    return SetOrClear(is_set, 1 << p, n);
}

}//namespace


SIMPLE_BENCHMARK(SetOrClear, true, 0b0110, 0b1101);
SIMPLE_BENCHMARK(SetOrClear, false, 0b0110, 0b1101);

SIMPLE_TEST(SetOrClear, TestSample1, 0b1111u, true, 0b0110, 0b1101);
SIMPLE_TEST(SetOrClear, TestSample2, 0b1001u, false, 0b0110, 0b1101);


SIMPLE_BENCHMARK(SetOrClear_Superscalar, true, 0b0110, 0b1101);
SIMPLE_BENCHMARK(SetOrClear_Superscalar, false, 0b0110, 0b1101);

SIMPLE_TEST(SetOrClear_Superscalar, TestSample1, 0b1111u, true, 0b0110, 0b1101);
SIMPLE_TEST(SetOrClear_Superscalar, TestSample2, 0b1001u, false, 0b0110, 0b1101);


SIMPLE_BENCHMARK(SetOrClearOneBit, 7, 2, 0);

SIMPLE_TEST(SetOrClearOneBit, TestSample1, 3u, 7, 2, 0);
SIMPLE_TEST(SetOrClearOneBit, TestSample2, 15u, 7, 3, 1);
