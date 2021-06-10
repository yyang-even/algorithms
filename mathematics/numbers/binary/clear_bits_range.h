#pragma once

#include "toggle_bits_range.h"


/** Unset bits in the given range
 *
 * @reference   https://www.geeksforgeeks.org/unset-bits-given-range/
 *
 * Given a non-negative number n and two values l and r. The problem is to unset the bits
 * in the range l to r in the binary representation of n, i.e, to unset bits from the
 * rightmost lth bit to the rightmost rth bit.
 *
 * Constraint: 1 <= l <= r <= number of bits in the binary representation of n.
 */
static inline constexpr auto
ClearBitsRange(const unsigned number, const unsigned l, const unsigned r) {
    assert(1 <= l);
    assert(l <= r);
    assert(r <= BitsNumber<unsigned>);

    const auto mask = ToggleBitsRange(-1, l, r);
    return number & mask;
}
