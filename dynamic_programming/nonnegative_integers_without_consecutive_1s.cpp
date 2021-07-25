#include "common_header.h"


namespace {

/** Non-negative Integers without Consecutive Ones
 *
 * @reference   https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/
 *
 * Given a positive integer n, return the number of the integers in the range [0, n]
 * whose binary representations do not contain consecutive ones.
 */
constexpr auto
CountIntegersWithoutConsecutive1s(const unsigned i, const unsigned suffix,
                                  const unsigned n, const bool prev_is_1) {
    if (suffix > n) {
        return 0;
    }

    if (1u << i > n) {
        return 1;
    }

    if (prev_is_1) {
        return CountIntegersWithoutConsecutive1s(i + 1, suffix, n, false);
    }
    return CountIntegersWithoutConsecutive1s(i + 1, suffix, n, false) +
           CountIntegersWithoutConsecutive1s(i + 1, suffix + (1 << i), n, true);
}

inline constexpr auto CountIntegersWithoutConsecutive1s(const unsigned n) {
    return CountIntegersWithoutConsecutive1s(0, 0, n, false);
}


inline constexpr auto CountIntegersWithoutConsecutive1s_DP(const unsigned n) {
    int dp[32] = {1, 2};

    for (int i = 2; i < 32; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    int sum = 1, prev_bit = 0;
    for (int i = 31; i >= 0; --i) {
        if ((n & (1 << i)) != 0) {
            sum += dp[i];
            if (prev_bit == 1) {
                --sum;
                break;
            }
            prev_bit = 1;
        } else {
            prev_bit = 0;
        }
    }

    return sum;
}

}//namespace


THE_BENCHMARK(CountIntegersWithoutConsecutive1s, 5);

SIMPLE_TEST(CountIntegersWithoutConsecutive1s, TestSAMPLE1, 5, 5);
SIMPLE_TEST(CountIntegersWithoutConsecutive1s, TestSAMPLE2, 2, 1);
SIMPLE_TEST(CountIntegersWithoutConsecutive1s, TestSAMPLE3, 3, 2);


THE_BENCHMARK(CountIntegersWithoutConsecutive1s_DP, 5);

SIMPLE_TEST(CountIntegersWithoutConsecutive1s_DP, TestSAMPLE1, 5, 5);
SIMPLE_TEST(CountIntegersWithoutConsecutive1s_DP, TestSAMPLE2, 2, 1);
SIMPLE_TEST(CountIntegersWithoutConsecutive1s_DP, TestSAMPLE3, 3, 2);
