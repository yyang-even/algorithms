#include "common_header.h"

#include "modular_multiplicative_inverse.h"


namespace {

/** Modular Division
 *
 * @reference   https://www.geeksforgeeks.org/modular-division/
 *
 * Given three positive numbers a, b and m. Compute a/b under modulo m.
 * The task is basically to find a number c such that (b * c) % m = a % m.
 */
unsigned ModularDivision(unsigned a, const unsigned b, const unsigned m) {
    assert(m);
    a %= m;
    const auto modular_inverse = ModularMultiplicativeInverse(b, m);
    return modular_inverse ? (modular_inverse * a) % m : modular_inverse;
}

}//namespace


SIMPLE_BENCHMARK(ModularDivision, 8, 4, 5);

SIMPLE_TEST(ModularDivision, TestSample1, 2u, 8, 4, 5);
SIMPLE_TEST(ModularDivision, TestSample2, 1u, 8, 3, 5);
SIMPLE_TEST(ModularDivision, TestSample3, 4u, 11, 4, 5);
SIMPLE_TEST(ModularDivision, TestSample4, 0u, 4, 12, 6);
SIMPLE_TEST(ModularDivision, TestSample5, 0u, 8, 0, 5);
