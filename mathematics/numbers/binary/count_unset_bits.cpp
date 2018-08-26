#include "common_header.h"

#include "toggle_all_bits_after_most_significant_bit.h"

using InputType = unsigned;

/** Count unset bits of a number
 *
 * @reference   https://www.geeksforgeeks.org/count-unset-bits-number/
 *
 * Given a number n, count unset bits after MSB (Most Significant Bit).
 */
#ifdef __GNUG__
auto CountUnsetBits(const InputType num) {
    return __builtin_popcount(ToggleAllBitsAfterMSB(num));
}


SIMPLE_BENCHMARK(CountUnsetBits, 0);

SIMPLE_TEST(CountUnsetBits, TestSample1, 0, 0);
SIMPLE_TEST(CountUnsetBits, TestSample2, 3, 17);
SIMPLE_TEST(CountUnsetBits, TestSample3, 0, 7);
#endif
