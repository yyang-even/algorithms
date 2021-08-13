#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<std::string_view>;
using OutputType = std::vector<ArrayType>;
using MemoType = MatrixTypeTemplate<bool>;

/** Palindrome Partitioning
 *
 * @reference   https://leetcode.com/problems/palindrome-partitioning/
 *
 * Given a string s, partition s such that every substring of the partition is a
 * palindrome. Return all possible palindrome partitioning of s. A palindrome string is
 * a string that reads the same backward as forward.
 */
void AllPalindromePartitioning(const std::string_view text, const std::size_t start,
                               ArrayType &current, MemoType &memo, OutputType &results) {
    if (start >= text.size()) {
        results.push_back(current);
    }

    for (auto end = start; end < text.size(); ++end) {
        if (text[start] == text[end] and (end - start <= 2 or memo[start + 1][end - 1])) {
            memo[start][end] = true;
            current.push_back(text.substr(start, end - start + 1));
            AllPalindromePartitioning(text, end + 1, current, memo, results);
            current.pop_back();
        }
    }
}

inline auto AllPalindromePartitioning(const std::string_view text) {
    MemoType memo = std::vector(text.size(), std::vector(text.size(), false));
    OutputType results;
    ArrayType current;
    AllPalindromePartitioning(text, 0, current, memo, results);

    return results;
}


/**
 * @reference   Palindrome Partitioning | DP-17
 *              https://www.geeksforgeeks.org/palindrome-partitioning-dp-17/
 *
 * @reference   Palindrome Partitioning II
 *              https://leetcode.com/problems/palindrome-partitioning-ii/
 *
 * Given a string s, partition s such that every substring of the partition is a
 * palindrome. Return the minimum cuts needed for a palindrome partitioning of s.
 *
 * @note    This problem is a variation of Matrix Chain Multiplication problem.
 */
constexpr auto
MinPalindromePartitioning_DP(const std::string_view text) {
    int dp[text.size()][text.size()] = {};
    bool is_palindrome[text.size()][text.size()] = {};

    for (std::size_t i = 0; i < text.size(); ++i) {
        is_palindrome[i][i] = true;
    }

    for (std::size_t length = 2; length <= text.size(); ++length) {
        for (std::size_t i = 0; i < text.size() - length + 1; ++i) {
            const auto j = i + length - 1;

            if (length == 2) {
                is_palindrome[i][j] = (text[i] == text[j]);
            } else {
                is_palindrome[i][j] = (text[i] == text[j]) and is_palindrome[i + 1][j - 1];
            }

            if (not is_palindrome[i][j]) {
                dp[i][j] = INT_MAX;
                for (auto k = i; k < j; ++k) {
                    dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j] + 1);
                }
            }
        }
    }

    return dp[0][text.size() - 1];
}


constexpr auto
MinPalindromePartitioning_DP_SpaceOptimized(const std::string_view text) {
    int dp[text.size()] = {};
    bool is_palindrome[text.size()][text.size()] = {};

    for (std::size_t last = 0; last < text.size(); ++last) {
        int min_cut = last;
        for (std::size_t start = 0; start <= last; ++start) {
            if (text[last] == text[start] and
                (last - start < 2 or is_palindrome[start + 1][last - 1])) {
                is_palindrome[start][last] = true;
                min_cut = std::min(min_cut, start == 0 ? 0 : (dp[start - 1] + 1));
            }
        }
        dp[last] = min_cut;
    }

    return dp[text.size() - 1];
}


auto MinPalindromePartitioning_DP_EvenOdd(const std::string_view text) {
    if (text.empty()) {
        return 0;
    }

    const int N = text.size();
    std::vector dp(N + 1, INT_MAX);
    dp[0] = -1;
    for (int i = 0; i < N; ++i) {
        for (int length = 0;
             i - length >= 0 and i + length < N and text[i - length] == text[i + length];
             ++length) {
            dp[i + length + 1] = std::min(dp[i + length + 1], 1 + dp[i - length]);
        }
        for (int length = 0;
             i - length >= 0 and i + length + 1 < N and text[i - length] == text[i + length + 1];
             ++length) {
            dp[i + length + 2] = std::min(dp[i + length + 2], 1 + dp[i - length]);
        }
    }

    return dp[N];
}


/**
 * @reference   Palindrome Partitioning III
 *              https://leetcode.com/problems/palindrome-partitioning-iii/
 * @reference   https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-1278-palindrome-partitioning-iii/
 *
 * You are given a string s containing lowercase letters and an integer k. You need to:
 *  First, change some characters of s to other lowercase English letters.
 *  Then divide s into k non-empty disjoint substrings such that each substring is a
 *  palindrome.
 * Return the minimal number of characters that you need to change to divide the string.
 */
auto MinChangesPalindromePartitioning_DP(const std::string_view text, const int K) {
    const int n = text.length();
    int cost[text.size()][text.size()] = {};
    for (std::size_t length = 2; length <= text.size(); ++length) {
        for (std::size_t i = 0, j = length - 1; j < text.size(); ++i, ++j) {
            cost[i][j] = (text[i] != text[j]) + cost[i + 1][j - 1];
        }
    }

    std::vector dp(text.size(), std::vector(K + 1, INT_MAX / 2));
    for (std::size_t i = 0; i < text.size(); ++i) {
        dp[i][1] = cost[0][i];
        for (int k = 2; k <= K; ++k) {
            for (std::size_t j = 0; j < i; ++j) {
                dp[i][k] = std::min(dp[i][k], dp[j][k - 1] + cost[j + 1][i]);
            }
        }
    }

    return dp[n - 1][K];
}


/**
 * @reference   Palindrome Partitioning IV
 *              https://leetcode.com/problems/palindrome-partitioning-iv/
 * @reference   https://frankkkkk.com/2021/01/31/1745-Palindrome-Partitioning-IV/
 *
 * Given a string s, return true if it is possible to split the string s into three
 * non-empty palindromic substrings. Otherwise, return false. A string is said to be
 * palindrome if it the same string when reversed.
 */
auto PalindromePartitioning3(const std::string_view text) {
    bool is_palindrome[text.size()][text.size()] = {};
    const int N = text.size();
    for (int j = 0; j < N; ++j) {
        for (int i = j; i >= 0; --i) {
            if (text[i] == text[j]) {
                is_palindrome[i][j] = (i + 1 <= j - 1) ? is_palindrome[i + 1][j - 1] : true;
            }
        }
    }

    for (int i = 1; i < N - 1; ++i) {
        for (auto j = i; j < N - 1; ++j) {
            if (is_palindrome[0][i - 1] and is_palindrome[i][j] and is_palindrome[j + 1][N - 1]) {
                return true;
            }
        }
    }

    return false;
}

}//namespace


const OutputType EXPECTED1 = {{"a", "a", "b"}, {"aa", "b"}};
const OutputType EXPECTED2 = {{"a"}};


THE_BENCHMARK(AllPalindromePartitioning, "aab");

SIMPLE_TEST(AllPalindromePartitioning, TestSAMPLE1, EXPECTED1, "aab");
SIMPLE_TEST(AllPalindromePartitioning, TestSAMPLE2, EXPECTED2, "a");


THE_BENCHMARK(MinPalindromePartitioning_DP_SpaceOptimized, "aab");

SIMPLE_TEST(MinPalindromePartitioning_DP_SpaceOptimized, TestSAMPLE1, 1, "aab");
SIMPLE_TEST(MinPalindromePartitioning_DP_SpaceOptimized, TestSAMPLE2, 0, "a");
SIMPLE_TEST(MinPalindromePartitioning_DP_SpaceOptimized, TestSAMPLE3, 1, "ab");
SIMPLE_TEST(MinPalindromePartitioning_DP_SpaceOptimized, TestSAMPLE4, 2, "geek");
SIMPLE_TEST(MinPalindromePartitioning_DP_SpaceOptimized, TestSAMPLE5, 0, "aaaa");
SIMPLE_TEST(MinPalindromePartitioning_DP_SpaceOptimized, TestSAMPLE6, 1, "abbac");


THE_BENCHMARK(MinPalindromePartitioning_DP, "aab");

SIMPLE_TEST(MinPalindromePartitioning_DP, TestSAMPLE1, 1, "aab");
SIMPLE_TEST(MinPalindromePartitioning_DP, TestSAMPLE2, 0, "a");
SIMPLE_TEST(MinPalindromePartitioning_DP, TestSAMPLE3, 1, "ab");
SIMPLE_TEST(MinPalindromePartitioning_DP, TestSAMPLE4, 2, "geek");
SIMPLE_TEST(MinPalindromePartitioning_DP, TestSAMPLE5, 0, "aaaa");
SIMPLE_TEST(MinPalindromePartitioning_DP, TestSAMPLE6, 1, "abbac");


THE_BENCHMARK(MinPalindromePartitioning_DP_EvenOdd, "aab");

SIMPLE_TEST(MinPalindromePartitioning_DP_EvenOdd, TestSAMPLE1, 1, "aab");
SIMPLE_TEST(MinPalindromePartitioning_DP_EvenOdd, TestSAMPLE2, 0, "a");
SIMPLE_TEST(MinPalindromePartitioning_DP_EvenOdd, TestSAMPLE3, 1, "ab");
SIMPLE_TEST(MinPalindromePartitioning_DP_EvenOdd, TestSAMPLE4, 2, "geek");
SIMPLE_TEST(MinPalindromePartitioning_DP_EvenOdd, TestSAMPLE5, 0, "aaaa");
SIMPLE_TEST(MinPalindromePartitioning_DP_EvenOdd, TestSAMPLE6, 1, "abbac");


THE_BENCHMARK(MinChangesPalindromePartitioning_DP, "abc", 2);

SIMPLE_TEST(MinChangesPalindromePartitioning_DP, TestSAMPLE1, 1, "abc", 2);
SIMPLE_TEST(MinChangesPalindromePartitioning_DP, TestSAMPLE2, 0, "aabbc", 3);
SIMPLE_TEST(MinChangesPalindromePartitioning_DP, TestSAMPLE3, 0, "leetcode", 8);


THE_BENCHMARK(PalindromePartitioning3, "abcbdd");

SIMPLE_TEST(PalindromePartitioning3, TestSAMPLE1, true, "abcbdd");
SIMPLE_TEST(PalindromePartitioning3, TestSAMPLE2, false, "bcbddxy");
