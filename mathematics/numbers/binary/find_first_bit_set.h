#pragma once

#include "clear_all_bits_except_the_last_set_bit.h"


/** Position of rightmost set bit
 *
 * @reference   https://www.geeksforgeeks.org/position-of-rightmost-set-bit/
 *
 * Write a one line C function to return position of first 1 from right to left, in
 * binary representation of an Integer.
 */
static inline constexpr unsigned FindFirstBitSet(const unsigned num) {
    assert(num);

    return std::log2(ClearAllBitsExceptTheLastSetBit(num)) + 1;
}

