#include "common_header.h"

using InputType = int;

/** Detect if two integers have opposite signs
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Detect if two integers have opposite signs
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
INT_BOOL AreOppositeSigns(const InputType x, const InputType y) {
    return ((x ^ y) < 0) ? TRUE : FALSE;
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(AreOppositeSigns, -1, 0);
SIMPLE_BENCHMARK(AreOppositeSigns, -1, 1);
SIMPLE_BENCHMARK(AreOppositeSigns, LOWER, UPPER);

SIMPLE_TEST(AreOppositeSigns, TestSample1, TRUE, -1, 0);
SIMPLE_TEST(AreOppositeSigns, TestSample2, FALSE, -1, -1);
SIMPLE_TEST(AreOppositeSigns, TestSample3, FALSE, 0, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample4, FALSE, 1, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample5, TRUE, -1, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample6, FALSE, 0, 0);
SIMPLE_TEST(AreOppositeSigns, TestSample7, TRUE, LOWER, UPPER);
SIMPLE_TEST(AreOppositeSigns, TestSample8, FALSE, LOWER, LOWER);
