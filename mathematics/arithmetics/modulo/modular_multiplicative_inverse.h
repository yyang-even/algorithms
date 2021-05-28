#pragma once

#include "mathematics/numbers/gcd/gcd.h"


/** Modular multiplicative inverse
 *
 * @reference   https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
 *
 * Given two integers 'a' and 'm', find modular multiplicative inverse of 'a' under
 * modulo 'm'.
 *  The modular multiplicative inverse is an integer 'x' such that.
 *      a x ≡ 1 (mod m)
 *  The value of x should be in {0, 1, 2, ... m-1}, i.e., in the ring of integer modulo
 *  m. The multiplicative inverse of "a modulo m" exists if and only if a and m are
 *  relatively prime (i.e., if gcd(a, m) = 1).
 */
static constexpr inline auto
ModularMultiplicativeInverse(const int a, const int m) {
    const auto results = gcd_Extended(a, m);
    return (std::get<0>(results) == 1) ? ((std::get<1>(results) % m + m) % m) : 0;
}
