#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Perfect Squares
 *
 * @reference   https://leetcode.com/problems/perfect-squares/
 *
 * Given an integer n, return the least number of perfect square numbers that sum to n.
 * A perfect square is an integer that is the square of an integer; in other words, it is the product of
 * some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.
 */
auto NumberPerfectSquaresSumAsN_DP(const int n) {
    std::vector dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i * i <= n; ++i) {
        const auto square = i * i;
        for (auto j = square; j <= n; ++j) {
            dp[j] = std::min(dp[j - square] + 1, dp[j]);
        }
    }

    return dp[n];
}


constexpr auto NumberPerfectSquaresSumAsN_AnotherDP(const int n) {
    if (n <= 1) {
        return n;
    }

    int dp[n + 1] = {};
    for (int i = 1; i <= n; ++i) {
        int count = INT_MAX;
        for (int j = 1; j * j <= i; ++j) {
            count = std::min(count, dp[i - j * j] + 1);
        }

        dp[i] = count;
    }

    return dp[n];
}


auto NumberPerfectSquaresSumAsN_Memo(const int n, ArrayType &memo) {
    if (memo[n]) {
        return memo[n];
    }

    int count = n;
    for (int i = 1; i * i <= n; ++i) {
        count = std::min(count, NumberPerfectSquaresSumAsN_Memo(n - i * i, memo) + 1);
    }

    return memo[n] = count;
}

auto NumberPerfectSquaresSumAsN_Memo(const int n) {
    ArrayType memo(n + 1);
    for (int i = 1; i * i <= n; ++i) {
        memo[i * i] = 1;
    }

    return NumberPerfectSquaresSumAsN_Memo(n, memo);
}

} //namespace


THE_BENCHMARK(NumberPerfectSquaresSumAsN_DP, 12);

SIMPLE_TEST(NumberPerfectSquaresSumAsN_DP, TestSAMPLE1, 3, 12);
SIMPLE_TEST(NumberPerfectSquaresSumAsN_DP, TestSAMPLE2, 2, 13);


THE_BENCHMARK(NumberPerfectSquaresSumAsN_AnotherDP, 12);

SIMPLE_TEST(NumberPerfectSquaresSumAsN_AnotherDP, TestSAMPLE1, 3, 12);
SIMPLE_TEST(NumberPerfectSquaresSumAsN_AnotherDP, TestSAMPLE2, 2, 13);


THE_BENCHMARK(NumberPerfectSquaresSumAsN_Memo, 12);

SIMPLE_TEST(NumberPerfectSquaresSumAsN_Memo, TestSAMPLE1, 3, 12);
SIMPLE_TEST(NumberPerfectSquaresSumAsN_Memo, TestSAMPLE2, 2, 13);
