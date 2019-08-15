#include "common_header.h"


namespace {

/** Modular Exponentiation (Power in Modular Arithmetic)
 *
 * @reference   https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
 *
 * Given three numbers x, y and p, compute (x^y) % p.
 */
auto ModularExponentiation() {

}

}//namespace


SIMPLE_BENCHMARK(SumOfNaturals, 7);

SIMPLE_TEST(SumOfNaturals, TestSAMPLE1, 6u, 3);
SIMPLE_TEST(SumOfNaturals, TestSAMPLE2, 15u, 5);
