#include "common_header.h"

using InputType = int;

/** Detect if two integers have opposite signs
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Detect if two integers have opposite signs
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Detect if two integers have opposite signs
 *              https://www.geeksforgeeks.org/detect-if-two-integers-have-opposite-signs/
 *
 * Given two signed integers, write a function that returns true if the signs of given
 * integers are different, otherwise false. For example, the function should return
 * true -1 and +100, and should return false for -100 and -200. The function should
 * not use any of the arithmetic operators.
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
