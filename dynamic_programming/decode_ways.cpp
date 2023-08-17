#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

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


/**
 * @reference   Check if There is a Valid Partition For The Array
 *              https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/
 *
 * You are given a 0-indexed integer array nums. You have to partition the array into one or more
 * contiguous subarrays.
 * We call a partition of the array valid if each of the obtained subarrays satisfies one of the
 * following conditions:
 *  The subarray consists of exactly 2 equal elements. For example, the subarray [2,2] is good.
 *  The subarray consists of exactly 3 equal elements. For example, the subarray [4,4,4] is good.
 *  The subarray consists of exactly 3 consecutive increasing elements, that is, the difference between
 *  adjacent elements is 1. For example, the subarray [3,4,5] is good, but the subarray [1,3,5] is not.
 * Return true if the array has at least one valid partition. Otherwise, return false.
 */
bool ValidPartition(const ArrayType &nums) {
    const int N = nums.size();

    int dp[] = {0, 0, 0, 1};
    for (int i = 0; i < N; ++i) {
        dp[i % 4] = 0;

        if (i - 1 >= 0 and nums[i] == nums[i - 1]) {
            dp[i % 4] |= dp[(i + 2) % 4];
        }

        if (i - 2 >= 0 and nums[i] == nums[i - 1] and nums[i - 1] == nums[i - 2]) {
            dp[i % 4] |= dp[(i + 1) % 4];
        }

        if (i - 2 >= 0 and nums[i] - 1 == nums[i - 1] and nums[i - 1] == nums[i - 2] + 1) {
            dp[i % 4] |= dp[(i + 1) % 4];
        }
    }

    return dp[(N - 1) % 4];
}

} //namespace


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


const ArrayType SAMPLE1 = {4, 4, 4, 5, 6};
const ArrayType SAMPLE2 = {1, 1, 1, 2};


THE_BENCHMARK(ValidPartition, SAMPLE1);

SIMPLE_TEST(ValidPartition, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(ValidPartition, TestSAMPLE2, false, SAMPLE2);
