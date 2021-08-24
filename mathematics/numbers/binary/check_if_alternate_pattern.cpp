#include "common_header.h"

#include "are_all_bits_set.h"


namespace {

/** Check if a number has bits in alternate pattern
 *
 * @reference   Check if a number has bits in alternate pattern | Set 1
 *              https://www.geeksforgeeks.org/check-if-a-number-has-bits-in-alternate-pattern/
 * @reference   Check if a number has bits in alternate pattern | Set-2 O(1) Approach
 *              https://www.geeksforgeeks.org/check-number-bits-alternate-pattern-set-2-o1-approach/
 *
 * Given an integer n > 0, the task is to find whether this integer has an alternate
 * pattern in its bits representation. For example- 5 has an alternate pattern i.e. 101.
 * Print “Yes” if it has an alternate pattern otherwise "No". Here alternate pattern
 * can be like 0101 or 1010.
 *
 * @reference   Binary Number with Alternating Bits
 *              https://leetcode.com/problems/binary-number-with-alternating-bits/
 */
constexpr auto CheckForBitsAlternatePattern_Simple(unsigned num) {
    assert(num);

    auto previous = num & 1;
    while (num >>= 1) {
        auto current = num & 1;
        if (current == previous) {
            return false;
        }

        previous = current;
    }

    return true;
}


inline constexpr auto CheckForBitsAlternatePattern(const unsigned num) {
    return AreAllBitsSet(num ^ (num >> 1));
}

}//namespace


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


THE_BENCHMARK(CheckForBitsAlternatePattern_Simple, 1);

SIMPLE_TEST(CheckForBitsAlternatePattern_Simple, TestSample1, false, 15);
SIMPLE_TEST(CheckForBitsAlternatePattern_Simple, TestSample2, false, 12);
SIMPLE_TEST(CheckForBitsAlternatePattern_Simple, TestSample3, true, 10);
SIMPLE_TEST(CheckForBitsAlternatePattern_Simple, TestSample4, true, 5);
SIMPLE_TEST(CheckForBitsAlternatePattern_Simple, TestLOWER, true, LOWER);
SIMPLE_TEST(CheckForBitsAlternatePattern_Simple, TestUPPER, false, UPPER);


THE_BENCHMARK(CheckForBitsAlternatePattern, 1);

SIMPLE_TEST(CheckForBitsAlternatePattern, TestSample1, false, 15);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestSample2, false, 12);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestSample3, true, 10);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestSample4, true, 5);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestLOWER, true, LOWER);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestUPPER, false, UPPER);
SIMPLE_TEST(CheckForBitsAlternatePattern, TestSample5, false, 4);

MUTUAL_RANDOM_TEST(CheckForBitsAlternatePattern_Simple, CheckForBitsAlternatePattern,
                   LOWER, UPPER);
