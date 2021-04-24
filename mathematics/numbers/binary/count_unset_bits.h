#pragma once

#include "toggle_all_bits_after_most_significant_bit.h"


/** Count unset bits of a number
 *
 * @reference   https://www.geeksforgeeks.org/count-unset-bits-number/
 *
 * Given a number n, count unset bits after MSB (Most Significant Bit).
 */
#ifdef __GNUG__
static constexpr inline auto CountUnsetBits(const unsigned num) {
    return __builtin_popcount(ToggleAllBitsAfterMSB(num));
}
#endif
