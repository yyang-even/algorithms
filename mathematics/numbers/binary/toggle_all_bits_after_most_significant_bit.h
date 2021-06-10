#pragma once

#include "set_all_bits_after_most_significant_bit.h"


/** Toggle all bits after most significant bit
 *
 * @reference   https://www.geeksforgeeks.org/toggle-bits-significant-bit/
 *
 * Given a number, toggle all bits of it after most significant bit including most
 * significant bit.
 */
static inline constexpr auto ToggleAllBitsAfterMSB(const unsigned num) {
    return num ^ SetAllBitsAfterMSB(num);
}
