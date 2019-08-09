#include "common_header.h"


namespace {

/** Find the minimum difference between Shifted tables of two numbers
 *
 * @reference   https://www.geeksforgeeks.org/find-the-difference-between-shifted-tables-of-two-numbers/
 *
 * Given two numbers ‘a’ and ‘b’. Find the minimum difference between any terms in
 * shifted infinite tables of ‘a’ and ‘b’, given shifts ‘x’ and ‘y’, where x, y >= 0.
 */
auto MinDiffBetweenShiftedTablesOfTwoNumbers(const unsigned a, const unsigned b,
        const int x, const int y) {
    const auto g = std::gcd(a, b);
    const auto diff = abs(x - y) % g;
    return std::min(diff, g - diff);
}

}//namespace


SIMPLE_BENCHMARK(MinDiffBetweenShiftedTablesOfTwoNumbers, 20, 52, 5, 7);

SIMPLE_TEST(MinDiffBetweenShiftedTablesOfTwoNumbers, TestSAMPLE1, 2u, 20, 52, 5, 7);
SIMPLE_TEST(MinDiffBetweenShiftedTablesOfTwoNumbers, TestSAMPLE2, 1u, 6, 16, 5, 2);
