#include "common_header.h"

/** Detect if two integers have opposite signs
 *
 * @reference   Detect if two integers have opposite signs
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
INT_BOOL AreOppositeSigns(const int x, const int y) {
    return ((x ^ y) < 0) ? TRUE : FALSE;
}


SIMPLE_BENCHMARK(AreOppositeSigns, -1, 0);
SIMPLE_BENCHMARK(AreOppositeSigns, -1, 1);
SIMPLE_BENCHMARK(AreOppositeSigns, INT_MIN, INT_MAX);

SIMPLE_TEST(AreOppositeSigns, TestSample1, TRUE, -1, 0);
SIMPLE_TEST(AreOppositeSigns, TestSample2, FALSE, -1, -1);
SIMPLE_TEST(AreOppositeSigns, TestSample3, FALSE, 0, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample4, FALSE, 1, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample5, TRUE, -1, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample6, FALSE, 0, 0);
SIMPLE_TEST(AreOppositeSigns, TestSample7, TRUE, INT_MIN, INT_MAX);
SIMPLE_TEST(AreOppositeSigns, TestSample8, FALSE, INT_MIN, INT_MIN);
