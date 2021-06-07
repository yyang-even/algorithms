#pragma once


#include "is_prime.h"


/** Legendre’s formula (Given p and n, find the largest x such that p^x divides n!)
 *
 * @reference   https://www.geeksforgeeks.org/legendres-formula-highest-power-of-prime-number-that-divides-n/
 */
static constexpr inline auto
LegendresFormula(const unsigned p, unsigned n) {
    assert(IsPrime_OptimizedSchoolMethod(p));

    unsigned x = 0;

    while (n) {
        n /= p;
        x += n;
    }

    return x;
}


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
    assert(IsPrime_OptimizedSchoolMethod(p));

    unsigned power = 0;
    //Use ULL to prevent overflow
    for (unsigned long long i = p; i <= n; i *= p) {
        power += (n / i);
    }
    return power;
}
