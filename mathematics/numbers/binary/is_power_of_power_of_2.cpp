#include "common_header.h"

#include "count_trailing_zeros.h"
#include "is_power_of_2.h"


namespace {

/**
 * @reference   Check if given number is a power of d where d is a power of 2
 *              https://www.geeksforgeeks.org/check-given-number-power-d-d-power-2/
 *
 * Given an integer n, find whether it is a power of d or not, where d is itself a power of 2.
 *
 * @tags    #bit-tricks
 */
inline constexpr auto IsPowerOfPowerOf2(const unsigned n, const unsigned d) {
    return IsPowerOf2(n) and (CountTrailingZeros_Linear(n) % static_cast<unsigned>(log2(d))) == 0;
}


/**
 * @reference   Find whether a given number is a power of 4 or not
 *              https://www.geeksforgeeks.org/find-whether-a-given-number-is-a-power-of-4-or-not/
 *
 * Given an integer n, find whether it is a power of 4 or not.
 *
 * @reference   Power of Four
 *              https://leetcode.com/problems/power-of-four/
 *
 * Given an integer n, return true if it is a power of four. Otherwise, return false.
 * An integer n is a power of four, if there exists an integer x such that n == 4^x.
 * Follow up: Could you solve it without loops/recursion?
 *
 * @reference   Nim Game
 *              https://leetcode.com/problems/nim-game/
 *
 * You are playing the following Nim Game with your friend:
 *  Initially, there is a heap of stones on the table.
 *  You and your friend will alternate taking turns, and you go first.
 *  On each turn, the person whose turn it is will remove 1 to 3 stones from the heap.
 *  The one who removes the last stone is the winner.
 * Given n, the number of stones in the heap, return true if you can win the game assuming both you and
 * your friend play optimally, otherwise return false.
 *
 * @tags    #bit-tricks
 */
inline constexpr auto IsPowerOf4(const unsigned num) {
    return IsPowerOfPowerOf2(num, 4);
}


inline constexpr auto IsPowerOf4_Const(const unsigned num) {
    return IsPowerOf2(num) and (num & 0x55555555);
}


/**
 * @reference   Check if a number is power of 8 or not
 *              https://www.geeksforgeeks.org/check-number-power-8-not/
 *
 * Given a number check whether it is power of 8 or not.
 *
 * @tags    #bit-tricks
 */
inline constexpr auto IsPowerOf8(const unsigned num) {
    return IsPowerOfPowerOf2(num, 8);
}


inline constexpr auto IsPowerOf8_Const(const unsigned num) {
    return IsPowerOf2(num) and not(num & 0xB6DB6DB6);
}

} //namespace


SIMPLE_BENCHMARK(IsPowerOf4, Sample1, 1);
SIMPLE_BENCHMARK(IsPowerOf4, Sample2, 0);

SIMPLE_TEST(IsPowerOf4, TestSample1, true, 1);
SIMPLE_TEST(IsPowerOf4, TestSample2, false, 0);
SIMPLE_TEST(IsPowerOf4, TestSample3, false, std::numeric_limits<int>::max());
SIMPLE_TEST(IsPowerOf4, TestSample4, false, 20);
SIMPLE_TEST(IsPowerOf4, TestSample5, true, 16);
SIMPLE_TEST(IsPowerOf4, TestSample6, true, 64);


SIMPLE_BENCHMARK(IsPowerOf4_Const, Sample2, 0);

SIMPLE_TEST(IsPowerOf4_Const, TestSample1, true, 1);
SIMPLE_TEST(IsPowerOf4_Const, TestSample2, false, 0);
SIMPLE_TEST(IsPowerOf4_Const, TestSample3, false, std::numeric_limits<int>::max());
SIMPLE_TEST(IsPowerOf4_Const, TestSample4, false, 20);
SIMPLE_TEST(IsPowerOf4_Const, TestSample5, true, 16);
SIMPLE_TEST(IsPowerOf4_Const, TestSample6, true, 64);


THE_BENCHMARK(IsPowerOfPowerOf2, 8, 2);

SIMPLE_TEST(IsPowerOfPowerOf2, TestSample1, false, 0, 2);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample2, true, 8, 2);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample3, false, 14, 8);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample4, false, 32, 16);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample5, true, 256, 16);
SIMPLE_TEST(IsPowerOfPowerOf2, TestSample6, true, 64, 8);


THE_BENCHMARK(IsPowerOf8, 8);

SIMPLE_TEST(IsPowerOf8, TestSample1, true, 64);
SIMPLE_TEST(IsPowerOf8, TestSample2, false, 75);
SIMPLE_TEST(IsPowerOf8, TestSample3, false, 14);
SIMPLE_TEST(IsPowerOf8, TestSample4, false, 65);


THE_BENCHMARK(IsPowerOf8_Const, 8);

SIMPLE_TEST(IsPowerOf8_Const, TestSample1, true, 64);
SIMPLE_TEST(IsPowerOf8_Const, TestSample2, false, 75);
SIMPLE_TEST(IsPowerOf8_Const, TestSample3, false, 14);
SIMPLE_TEST(IsPowerOf8_Const, TestSample4, false, 65);
