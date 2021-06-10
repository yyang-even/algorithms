#pragma once


/** Toggle bits in the given range
 *
 * @reference   https://www.geeksforgeeks.org/toggle-bits-given-range/
 *
 * Given a non-negative number n and two values l and r. The problem is to toggle the
 * bits in the range l to r in the binary representation of n, i.e, to toggle bits from
 * the rightmost lth bit to the rightmost rth bit. A toggle operation flips a bit 0 to 1
 * and a bit 1 to 0.
 *
 * Constraint: 1 <= l <= r <= number of bits in the binary representation of n.
 */
static inline constexpr auto
ToggleBitsRange(const unsigned number,
                const unsigned l, const unsigned r) {
    assert(1 <= l);
    assert(l <= r);
    assert(r <= BitsNumber<unsigned>);

    const auto mask = ((1 << r) - 1) ^ ((1 << (l - 1)) - 1);
    return number ^ mask;
}
