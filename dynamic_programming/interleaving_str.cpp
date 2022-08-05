#include "common_header.h"


namespace {

using MemoType = std::vector<std::vector<int>>;

/** Interleaving String
 *
 * @reference   https://leetcode.com/problems/interleaving-string/
 *
 * Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
 * An interleaving of two strings s and t is a configuration where they are divided into non-empty
 * substrings such that:
 *  s = s1 + s2 + ... + sn
 *  t = t1 + t2 + ... + tm
 *  |n - m| <= 1
 *  The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
 * Note: a + b is the concatenation of strings a and b.
 * Follow up: Could you solve it using only O(s2.length) additional memory space?
 */
bool InterleavingStr_Memo(const std::string_view s1,
                          const std::size_t i,
                          const std::string_view s2,
                          const std::size_t j,
                          const std::string_view s3,
                          MemoType &memo) {
    const auto k = i + j;
    if (i == s1.size()) {
        return std::equal(s2.cbegin() + j, s2.cend(), s3.cbegin() + k);
    }

    if (j == s2.size()) {
        return std::equal(s1.cbegin() + i, s1.cend(), s3.cbegin() + k);
    }

    if (memo[i][j] >= 0) {
        return memo[i][j];
    }

    return (memo[i][j] = (s3[k] == s1[i] and InterleavingStr_Memo(s1, i + 1, s2, j, s3, memo)) or
                         (s3[k] == s2[j] and InterleavingStr_Memo(s1, i, s2, j + 1, s3, memo)));
}

inline auto InterleavingStr_Memo(const std::string_view s1,
                                 const std::string_view s2,
                                 const std::string_view s3) {
    if (s1.size() + s2.size() != s3.size()) {
        return false;
    }

    MemoType memo(s1.size(), std::vector(s2.size(), -1));
    return InterleavingStr_Memo(s1, 0, s2, 0, s3, memo);
}


auto InterleavingStr_DP(const std::string_view s1,
                        const std::string_view s2,
                        const std::string_view s3) {
    if (s1.size() + s2.size() != s3.size()) {
        return false;
    }

    bool dp[s2.size() + 1] = {};
    for (std::size_t i = 0; i <= s1.size(); ++i) {
        for (std::size_t j = 0; j <= s2.size(); ++j) {
            if (i == 0 and j == 0) {
                dp[j] = true;
            } else if (i == 0) {
                dp[j] = dp[j - 1] and s2[j - 1] == s3[i + j - 1];
            } else if (j == 0) {
                dp[j] = dp[j] and s1[i - 1] == s3[i + j - 1];
            } else {
                dp[j] = (dp[j] and s1[i - 1] == s3[i + j - 1]) or
                        (dp[j - 1] and s2[j - 1] == s3[i + j - 1]);
            }
        }
    }

    return dp[s2.size()];
}

} //namespace


THE_BENCHMARK(InterleavingStr_Memo, "aabcc", "dbbca", "aadbbcbcac");

SIMPLE_TEST(InterleavingStr_Memo, TestSAMPLE1, true, "aabcc", "dbbca", "aadbbcbcac");
SIMPLE_TEST(InterleavingStr_Memo, TestSAMPLE2, false, "aabcc", "dbbca", "aadbbbaccc");
SIMPLE_TEST(InterleavingStr_Memo, TestSAMPLE3, true, "", "", "");


THE_BENCHMARK(InterleavingStr_DP, "aabcc", "dbbca", "aadbbcbcac");

SIMPLE_TEST(InterleavingStr_DP, TestSAMPLE1, true, "aabcc", "dbbca", "aadbbcbcac");
SIMPLE_TEST(InterleavingStr_DP, TestSAMPLE2, false, "aabcc", "dbbca", "aadbbbaccc");
SIMPLE_TEST(InterleavingStr_DP, TestSAMPLE3, true, "", "", "");
