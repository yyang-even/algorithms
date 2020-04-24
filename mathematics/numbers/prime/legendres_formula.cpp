#include "common_header.h"

#include "is_prime.h"


namespace {

/** Legendre’s formula (Given p and n, find the largest x such that p^x divides n!)
 *
 * @reference   https://www.geeksforgeeks.org/legendres-formula-highest-power-of-prime-number-that-divides-n/
 */
auto LegendresFormula(const unsigned p, unsigned n) {
    assert(IsPrime_OptimizedSchoolMethod(p));

    unsigned x = 0;

    while (n) {
        n /= p;
        x += n;
    }

    return x;
}

}//namespace


SIMPLE_BENCHMARK(LegendresFormula, 3, 7);

SIMPLE_TEST(LegendresFormula, TestSAMPLE1, 2, 3, 7);
SIMPLE_TEST(LegendresFormula, TestSAMPLE2, 4, 3, 10);
