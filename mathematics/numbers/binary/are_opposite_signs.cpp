#include "common_header.h"


namespace {

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
auto AreOppositeSigns(const int x, const int y) {
    return (x ^ y) < 0;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<int>::min();
constexpr auto UPPER = std::numeric_limits<int>::max();

SIMPLE_BENCHMARK(AreOppositeSigns, -1, 0);
SIMPLE_BENCHMARK(AreOppositeSigns, -1, 1);
SIMPLE_BENCHMARK(AreOppositeSigns, LOWER, UPPER);

SIMPLE_TEST(AreOppositeSigns, TestSample1, true, -1, 0);
SIMPLE_TEST(AreOppositeSigns, TestSample2, false, -1, -1);
SIMPLE_TEST(AreOppositeSigns, TestSample3, false, 0, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample4, false, 1, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample5, true, -1, 1);
SIMPLE_TEST(AreOppositeSigns, TestSample6, false, 0, 0);
SIMPLE_TEST(AreOppositeSigns, TestSample7, true, LOWER, UPPER);
SIMPLE_TEST(AreOppositeSigns, TestSample8, false, LOWER, LOWER);
