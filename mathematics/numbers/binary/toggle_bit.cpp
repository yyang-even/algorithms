#include "common_header.h"

using InputType = unsigned;

/** Toggling a bit at nth position
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 */
auto ToggleBit(const InputType num, const InputType position) {
    return num ^ (1 << position);
}


SIMPLE_BENCHMARK(ToggleBit, 0, 4);

SIMPLE_TEST(ToggleBit, TestSample1, 0b110, 0b100, 1);
SIMPLE_TEST(ToggleBit, TestSample2, 1, 0, 0);
SIMPLE_TEST(ToggleBit, TestSample3, 0b10, 0, 1);
