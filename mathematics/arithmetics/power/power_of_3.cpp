#include "common_header.h"


namespace {

/** Power of Three
 *
 * @reference   https://leetcode.com/problems/power-of-three/
 *
 * Given an integer n, return true if it is a power of three. Otherwise, return false.
 * An integer n is a power of three, if there exists an integer x such that n == 3^x.
 * Follow up: Could you solve it without loops/recursion?
 */
inline constexpr auto isPowerOfThree_CF(const int32_t n) {
    return n > 0 and 1162261467 % n == 0;
}


inline constexpr auto isPowerOfThree_Log(const int32_t n) {
    if (n <= 0) {
        return false;
    }
    const int x = std::log2(n) / std::log2(3);
    return std::pow(3, x) == n;
}

}//namespace


THE_BENCHMARK(isPowerOfThree_CF, 27);

SIMPLE_TEST(isPowerOfThree_CF, TestSAMPLE1, true, 27);
SIMPLE_TEST(isPowerOfThree_CF, TestSAMPLE2, true, 9);
SIMPLE_TEST(isPowerOfThree_CF, TestSAMPLE3, false, 0);
SIMPLE_TEST(isPowerOfThree_CF, TestSAMPLE4, false, 45);


THE_BENCHMARK(isPowerOfThree_Log, 27);

SIMPLE_TEST(isPowerOfThree_Log, TestSAMPLE1, true, 27);
SIMPLE_TEST(isPowerOfThree_Log, TestSAMPLE2, true, 9);
SIMPLE_TEST(isPowerOfThree_Log, TestSAMPLE3, false, 0);
SIMPLE_TEST(isPowerOfThree_Log, TestSAMPLE4, false, 45);
