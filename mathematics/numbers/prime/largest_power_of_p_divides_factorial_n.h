#pragma once


/**The largest power of p that divides n!
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 4.4.
 *
 * We'd like to determine, for any given prime p, the largest power of p that divides
 * n!; that is, we want the exponent of p in n!'s unique factorization.
 *
 * @bug It will fall into infinite loop for large n or p, as which may cause i *= p to
 * overflow
 */
static constexpr inline auto
LargestPowerOfPDividesFactorialN(const unsigned p, const unsigned n) {
    unsigned power = 0;
    //Use ULL to prevent overflow
    for (unsigned long long i = p; i <= n; i *= p) {
        power += (n / i);
    }
    return power;
}
