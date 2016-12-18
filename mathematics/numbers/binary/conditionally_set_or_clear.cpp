#include "common_header.h"

/** Conditionally set or clear bits without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Conditionally set or clear bits without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
//if (is_set) bits |= mask; else bits &= ~mask;
unsigned SetOrClear(const bool is_set, const unsigned mask, const unsigned bits) {
    return bits ^ ((-is_set ^ bits) & mask);
}

unsigned SetOrClearSuperscalar(const bool is_set, const unsigned mask, const unsigned bits) {
    return (bits & ~mask) | (-is_set & mask);
}


SIMPLE_BENCHMARK(SetOrClear, true, 0b0110, 0b1101);
SIMPLE_BENCHMARK(SetOrClear, false, 0b0110, 0b1101);

SIMPLE_TEST(SetOrClear, TestSample1, 0b1111, true, 0b0110, 0b1101);
SIMPLE_TEST(SetOrClear, TestSample2, 0b1001, false, 0b0110, 0b1101);

SIMPLE_BENCHMARK(SetOrClearSuperscalar, true, 0b0110, 0b1101);
SIMPLE_BENCHMARK(SetOrClearSuperscalar, false, 0b0110, 0b1101);

SIMPLE_TEST(SetOrClearSuperscalar, TestSample1, 0b1111, true, 0b0110, 0b1101);
SIMPLE_TEST(SetOrClearSuperscalar, TestSample2, 0b1001, false, 0b0110, 0b1101);
