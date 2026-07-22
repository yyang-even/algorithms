#pragma once

#include "set_all_bits_after_most_significant_bit.h"


/**
 * @reference   Toggle all bits after most significant bit
 *              https://www.geeksforgeeks.org/toggle-bits-significant-bit/
 *
 * Given a number, toggle all bits of it after most significant bit including most significant bit.
 *
 * @tags    #bit-tricks
 */
static inline constexpr auto ToggleAllBitsAfterMSB(const unsigned num) {
    return num ^ SetAllBitsAfterMSB(num);
}
