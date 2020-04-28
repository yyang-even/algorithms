#pragma once

#include "is_prime.h"


/** Legendre’s formula (Given p and n, find the largest x such that p^x divides n!)
 *
 * @reference   https://www.geeksforgeeks.org/legendres-formula-highest-power-of-prime-number-that-divides-n/
 */
static inline auto LegendresFormula(const unsigned p, unsigned n) {
    assert(IsPrime_OptimizedSchoolMethod(p));

    unsigned x = 0;

    while (n) {
        n /= p;
        x += n;
    }

    return x;
}
