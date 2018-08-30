#include "common_header.h"

#include "are_all_bits_set.h"

using InputType = unsigned;

/** Check if a number has bits in alternate pattern
 *
 * @reference   Check if a number has bits in alternate pattern | Set 1
 *              https://www.geeksforgeeks.org/check-if-a-number-has-bits-in-alternate-pattern/
 * @reference   Check if a number has bits in alternate pattern | Set-2 O(1) Approach
 *              https://www.geeksforgeeks.org/check-number-bits-alternate-pattern-set-2-o1-approach/
 *
 * Given an integer n > 0, the task is to find whether this integer has an alternate
 * pattern in its bits representation. For example- 5 has an alternate pattern i.e. 101.
 * Print “Yes” if it has an alternate pattern otherwise “No”. Here alternate pattern
 * can be like 0101 or 1010.
 */
INT_BOOL CheckForBitsAlternatePatternSimple(InputType num) {
    assert(num);

    auto previous = num & 1u;
    while (num >>= 1u) {
        auto current = num & 1u;
        if (current == previous) {
            return false;
        }

        previous = current;
    }

    return true;
}


auto CheckForBitsAlternatePattern(const InputType num) {
    return AreAllBitsSet(num ^ (num >> 1u));
}


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(CheckForBitsAlternatePatternSimple, 1);

SIMPLE_TEST(CheckForBitsAlternatePatternSimple, TestSample1, FALSE, 15);
SIMPLE_TEST(CheckForBitsAlternatePatternSimple, TestSample2, FALSE, 12);
SIMPLE_TEST(CheckForBitsAlternatePatternSimple, TestSample3, TRUE, 10);
SIMPLE_TEST(CheckForBitsAlternatePatternSimple, TestSample4, TRUE, 5);
SIMPLE_TEST(CheckForBitsAlternatePatternSimple, TestLOWER, TRUE, LOWER);
SIMPLE_TEST(CheckForBitsAlternatePatternSimple, TestUPPER, FALSE, UPPER);


SIMPLE_BENCHMARK(CheckForBitsAlternatePattern, 1);

SIMPLE_TEST(CheckForBitsAlternatePattern, TestSample1, FALSE, 15);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestSample2, FALSE, 12);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestSample3, TRUE, 10);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestSample4, TRUE, 5);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestLOWER, TRUE, LOWER);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestUPPER, FALSE, UPPER);

MUTUAL_RANDOM_TEST(CheckForBitsAlternatePatternSimple, CheckForBitsAlternatePattern, LOWER, UPPER);
