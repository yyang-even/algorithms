#include "common_header.h"


namespace {

/** Decode Ways
 *
 * @reference   https://leetcode.com/problems/decode-ways/
 *
 * A message containing letters from A-Z can be encoded into numbers using the following
 * mapping:
 *  'A' -> "1"
 *  'B' -> "2"
 *  ...
 *  'Z' -> "26"
 * To decode an encoded message, all the digits must be grouped then mapped back into
 * letters using the reverse of the mapping above (there may be multiple ways). For
 * example, "11106" can be mapped into:
 *  "AAJF" with the grouping (1 1 10 6)
 *  "KJF" with the grouping (11 10 6)
 * Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F'
 * since "6" is different from "06". Given a string s containing only digits, return
 * the number of ways to decode it. The answer is guaranteed to fit in a 32-bit integer.
 *
 * @note    This problem is a variant of counting ways of climbing stairs.
 */
constexpr auto DecodeWays(const std::string_view encodes) {
    assert(not encodes.empty());

    if (encodes.front() == '0') {
        return 0;
    }

    int dp[encodes.size() + 1] = {1, 1};
    for (std::size_t i = 1; i < encodes.size(); ++i) {
        const auto current = encodes[i];
        const auto prev = encodes[i - 1];

        if (current != '0') {
            dp[i + 1] = dp[i];
        }
        if (prev == '1' or (prev == '2' and current >= '0' and current <= '6')) {
            dp[i + 1] += dp[i - 1];
        }
    }

    return dp[encodes.size()];
}


constexpr auto DecodeWays_O1(const std::string_view encodes) {
    assert(not encodes.empty());

    if (encodes.front() == '0') {
        return 0;
    }

    int curr_dp = 1;
    int prev_dp = 1;
    int result = 1;
    for (std::size_t i = 1; i < encodes.size(); ++i) {
        const auto current = encodes[i];
        const auto prev = encodes[i - 1];

        result = 0;
        if (current != '0') {
            result = curr_dp;
        }
        if (prev == '1' or (prev == '2' and current >= '0' and current <= '6')) {
            result += prev_dp;
        }

        prev_dp = curr_dp;
        curr_dp = result;
    }

    return result;
}


/**
 * @reference   Decode Ways II
 *              https://leetcode.com/problems/decode-ways-ii/
 *
 * In addition to Decode Ways above, an encoded message may contain the '*' character,
 * which can represent any digit from '1' to '9' ('0' is excluded). For example, the
 * encoded message "1*" may represent any of the encoded messages "11", "12", "13",
 * "14", "15", "16", "17", "18", or "19". Decoding "1*" is equivalent to decoding any
 * of the encoded messages it can represent.
 * Given a string s containing digits and the '*' character, return the number of ways
 * to decode it. Since the answer may be very large, return it modulo 10^9 + 7.
 */
constexpr int DecodeWaysWithStar(const std::string_view encodes) {
    assert(not encodes.empty());

    if (encodes.front() == '0') {
        return 0;
    }

    long dp[encodes.size() + 1] = {1, encodes.front() == '*' ? 9 : 1};
    for (std::size_t i = 1; i < encodes.size(); ++i) {
        const auto current = encodes[i];
        const auto prev = encodes[i - 1];

        if (current != '0') {
            dp[i + 1] = (current == '*' ? 9 : 1) * dp[i];
        }

        int factor = 0;
        if (prev == '1') {
            factor = (current == '*' ? 9 : 1);
        } else if (prev == '2') {
            if (current >= '0' and current <= '6') {
                factor = 1;
            } else if (current == '*') {
                factor = 6;
            }
        } else if (prev == '*') {
            if (current >= '0' and current <= '6') {
                factor = 2;
            } else if (current == '*') {
                factor = 15;
            } else {
                factor = 1;
            }
        }
        dp[i + 1] = (dp[i + 1] + factor * dp[i - 1]) % LARGE_PRIME;
    }

    return dp[encodes.size()];
}

}//namespace


THE_BENCHMARK(DecodeWays, "226");

SIMPLE_TEST(DecodeWays, TestSAMPLE1, 0, "0");
SIMPLE_TEST(DecodeWays, TestSAMPLE2, 0, "06");
SIMPLE_TEST(DecodeWays, TestSAMPLE3, 1, "1");
SIMPLE_TEST(DecodeWays, TestSAMPLE4, 1, "9");
SIMPLE_TEST(DecodeWays, TestSAMPLE5, 1, "10");
SIMPLE_TEST(DecodeWays, TestSAMPLE6, 2, "11");
SIMPLE_TEST(DecodeWays, TestSAMPLE7, 2, "12");
SIMPLE_TEST(DecodeWays, TestSAMPLE8, 3, "226");


THE_BENCHMARK(DecodeWays_O1, "226");

SIMPLE_TEST(DecodeWays_O1, TestSAMPLE1, 0, "0");
SIMPLE_TEST(DecodeWays_O1, TestSAMPLE2, 0, "06");
SIMPLE_TEST(DecodeWays_O1, TestSAMPLE3, 1, "1");
SIMPLE_TEST(DecodeWays_O1, TestSAMPLE4, 1, "9");
SIMPLE_TEST(DecodeWays_O1, TestSAMPLE5, 1, "10");
SIMPLE_TEST(DecodeWays_O1, TestSAMPLE6, 2, "11");
SIMPLE_TEST(DecodeWays_O1, TestSAMPLE7, 2, "12");
SIMPLE_TEST(DecodeWays_O1, TestSAMPLE8, 3, "226");


THE_BENCHMARK(DecodeWaysWithStar, "226");

SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE1, 0, "0");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE2, 0, "06");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE3, 1, "1");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE4, 1, "9");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE5, 1, "10");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE6, 2, "11");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE7, 2, "12");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE8, 3, "226");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE9, 9, "*");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE10, 18, "1*");
SIMPLE_TEST(DecodeWaysWithStar, TestSAMPLE11, 15, "2*");
