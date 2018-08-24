#include "common_header.h"

using InputType = unsigned;

/** Toggling a bit at nth position
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 * @reference   Toggling k-th bit of a number
 *              https://www.geeksforgeeks.org/toggling-k-th-bit-number/
 */
auto ToggleBit(const InputType num, const InputType position) {
    return num ^ (1 << position);
}


/** Toggle all the bits of a number except k-th bit.
 *
 * @reference   https://www.geeksforgeeks.org/toggle-bits-number-except-k-th-bit/
 */
auto ToggleAllBitsExceptKth(const InputType num, const InputType position) {
    return ~(num ^ (1 << position));
}


SIMPLE_BENCHMARK(ToggleBit, 0, 4);

SIMPLE_TEST(ToggleBit, TestSample1, 0b110, 0b100, 1);
SIMPLE_TEST(ToggleBit, TestSample2, 1, 0, 0);
SIMPLE_TEST(ToggleBit, TestSample3, 0b10, 0, 1);


SIMPLE_BENCHMARK(ToggleAllBitsExceptKth, 0, 4);

SIMPLE_TEST(ToggleAllBitsExceptKth, TestSample1, 1, std::numeric_limits<InputType>::max(), 0);
