#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using MemoType = MatrixType;

/** Distinct Subsequences
 *
 * @reference   https://leetcode.com/problems/distinct-subsequences/
 * @reference   https://medium.com/@vivek_ranjan/distinct-subsequences-adde0692e19c
 *
 * Given two strings s and t, return the number of distinct subsequences of s which
 * equals t. A string's subsequence is a new string formed from the original string by
 * deleting some (can be none) of the characters without disturbing the remaining
 * characters' relative positions. (i.e., "ACE" is a subsequence of "ABCDE" while "AEC"
 * is not). It is guaranteed the answer fits on a 32-bit signed integer.
 */
auto
DistinctSubsequences_Memo(const std::string_view s, const std::size_t i,
                          const std::string_view t, const std::size_t j, MemoType &memo) {
    if (j == 0) {
        return 1;
    }
    if (i == 0) {
        return 0;
    }

    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    return memo[i][j] = DistinctSubsequences_Memo(s, i - 1, t, j, memo) +
                        (s[i - 1] == t[j - 1] ? DistinctSubsequences_Memo(s, i - 1, t, j - 1, memo) : 0);
}

inline auto
DistinctSubsequences_Memo(const std::string_view s, const std::string_view t) {
    std::vector memo(s.size() + 1, std::vector(t.size() + 1, -1));
    return DistinctSubsequences_Memo(s, s.size(), t, t.size(), memo);
}


constexpr auto
DistinctSubsequences_DP(const std::string_view s, const std::string_view t) {
    unsigned long dp[t.size() + 1][s.size() + 1] = {};

    for (auto &i : dp[0]) {
        i = 1;
    }

    for (std::size_t i = 1; i <= t.size(); ++i) {
        for (std::size_t j = 1; j <= s.size(); ++j) {
            dp[i][j] = dp[i][j - 1] + (t[i - 1] == s[j - 1] ? dp[i - 1][j - 1] : 0);
        }
    }
    return dp[t.size()][s.size()];
}


constexpr auto
DistinctSubsequences_DP_1D(const std::string_view s, const std::string_view t) {
    int dp[t.size() + 1] = {1};

    for (std::size_t i = 1; i <= s.size(); ++i) {
        for (int j = t.size(); j > 0; --j) {
            if (s[i - 1] == t[j - 1]) {
                dp[j] += dp[j - 1];
            }
        }
    }

    return dp[t.size()];
}


/**
 * @reference   Distinct Subsequences II
 *              https://leetcode.com/problems/distinct-subsequences-ii/
 *
 * Given a string s, return the number of distinct non-empty subsequences of s. Since the
 * answer may be very large, return it modulo 10^9 + 7. A subsequence of a string is a
 * new string that is formed from the original string by deleting some (can be none) of
 * the characters without disturbing the relative positions of the remaining characters.
 * (i.e., "ace" is a subsequence of "abcde" while "aec" is not.
 */
auto CountDistinctSubsequences_DP(const std::string_view S) {
    int dp[S.size() + 1] = {1};

    std::vector last(26, -1);

    for (std::size_t i = 0; i < S.size(); ++i) {
        const auto index = S[i] - 'a';
        dp[i + 1] = dp[i] * 2 % LARGE_PRIME;
        if (last[index] >= 0) {
            dp[i + 1] -= dp[last[index]];
        }
        dp[i + 1] %= LARGE_PRIME;
        last[index] = i;
    }

    if (--dp[S.size()] < 0) {
        dp[S.size()] += LARGE_PRIME;
    }
    return dp[S.size()];
}


auto CountDistinctSubsequences_DP_O1(const std::string_view S) {
    int prev = 1;
    int cur = 1;
    int last_count[26] = {};
    for (std::size_t i = 0; i < S.size(); ++i) {
        const auto index = S[i] - 'a';
        cur = prev * 2 % LARGE_PRIME;
        cur -= last_count[index];
        cur = cur >= 0 ?  cur % LARGE_PRIME : cur + LARGE_PRIME;
        last_count[index] = prev;
        prev = cur;
    }
    --cur;

    return cur;
}

}//namespace


THE_BENCHMARK(DistinctSubsequences_DP, "rabbbit", "rabbit");

SIMPLE_TEST(DistinctSubsequences_DP, TestSAMPLE1, 3, "rabbbit", "rabbit");
SIMPLE_TEST(DistinctSubsequences_DP, TestSAMPLE2, 5, "babgbag", "bag");


THE_BENCHMARK(DistinctSubsequences_Memo, "rabbbit", "rabbit");

SIMPLE_TEST(DistinctSubsequences_Memo, TestSAMPLE1, 3, "rabbbit", "rabbit");
SIMPLE_TEST(DistinctSubsequences_Memo, TestSAMPLE2, 5, "babgbag", "bag");


THE_BENCHMARK(DistinctSubsequences_DP_1D, "rabbbit", "rabbit");

SIMPLE_TEST(DistinctSubsequences_DP_1D, TestSAMPLE1, 3, "rabbbit", "rabbit");
SIMPLE_TEST(DistinctSubsequences_DP_1D, TestSAMPLE2, 5, "babgbag", "bag");


THE_BENCHMARK(CountDistinctSubsequences_DP, "abc");

SIMPLE_TEST(CountDistinctSubsequences_DP, TestSAMPLE1, 7, "abc");
SIMPLE_TEST(CountDistinctSubsequences_DP, TestSAMPLE2, 6, "aba");
SIMPLE_TEST(CountDistinctSubsequences_DP, TestSAMPLE3, 3, "aaa");


THE_BENCHMARK(CountDistinctSubsequences_DP_O1, "abc");

SIMPLE_TEST(CountDistinctSubsequences_DP_O1, TestSAMPLE1, 7, "abc");
SIMPLE_TEST(CountDistinctSubsequences_DP_O1, TestSAMPLE2, 6, "aba");
SIMPLE_TEST(CountDistinctSubsequences_DP_O1, TestSAMPLE3, 3, "aaa");
