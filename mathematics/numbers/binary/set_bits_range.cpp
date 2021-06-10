#include "common_header.h"


namespace {

/** Set all the bits in given range of a number
 *
 * @reference   https://www.geeksforgeeks.org/set-bits-given-range-number/
 *
 * Given a non-negative number n and two values l and r. The problem is to set the bits
 * in the range l to r in the binary representation of n, i.e, to unset bits from the
 * rightmost lth bit to the rightmost r-th bit.
 * Constraint: 1 <= l <= r <= number of bits in the binary representation of n.
 */
inline constexpr auto
SetBitsRange(const unsigned number, const unsigned l, const unsigned r) {
    assert(1 <= l);
    assert(l <= r);
    assert(r <= BitsNumber<unsigned>);

    const auto mask = ((1 << r) - 1) ^ ((1 << (l - 1)) - 1);
    return number | mask;
}

}//namespace


THE_BENCHMARK(SetBitsRange, 17, 2, 3);

SIMPLE_TEST(SetBitsRange, TestSAMPLE1, 23, 17, 2, 3);
SIMPLE_TEST(SetBitsRange, TestSAMPLE2, 62, 50, 2, 5);
