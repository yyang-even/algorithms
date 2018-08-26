#include "common_header.h"

#include "set_all_bits_after_most_significant_bit.h"

using InputType = unsigned;

/** Toggle all bits after most significant bit
 *
 * @reference   https://www.geeksforgeeks.org/toggle-bits-significant-bit/
 *
 * Given a number, toggle all bits of it after most significant bit including most significant bit.
 */
auto ToggleAllBitsAfterMSB(const InputType num) {
    return num ^ SetAllBitsAfterMSB(num);
}


SIMPLE_BENCHMARK(ToggleAllBitsAfterMSB, 0);

SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample1, 0, 0);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample2, 0, 1);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample3, 5, 10);
SIMPLE_TEST(ToggleAllBitsAfterMSB, TestSample4, 2, 5);
