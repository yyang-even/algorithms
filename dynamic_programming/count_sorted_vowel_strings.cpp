#include "common_header.h"


namespace {

/** Count Sorted Vowel Strings
 *
 * @reference   https://leetcode.com/problems/count-sorted-vowel-strings/
 *
 * Given an integer n, return the number of strings of length n that consist only of vowels
 * (a, e, i, o, u) and are lexicographically sorted.
 * A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before
 * s[i+1] in the alphabet.
 */
constexpr auto CountSortedVowelStrs_DP(const int n) {
    int dp[] = {0, 1, 1, 1, 1, 1};

    for (int i = 1; i <= n; ++i) {
        for (int k = 1; k <= 5; ++k) {
            dp[k] += dp[k - 1];
        }
    }

    return dp[5];
}


constexpr auto CountSortedVowelStrs_Pentatope(const int n) {
    return (n + 1) * (n + 2) * (n + 3) * (n + 4) / (1 * 2 * 3 * 4);
}

} //namespace


THE_BENCHMARK(CountSortedVowelStrs_DP, 33);

SIMPLE_TEST(CountSortedVowelStrs_DP, TestSAMPLE1, 5, 1);
SIMPLE_TEST(CountSortedVowelStrs_DP, TestSAMPLE2, 15, 2);
SIMPLE_TEST(CountSortedVowelStrs_DP, TestSAMPLE3, 66045, 33);


THE_BENCHMARK(CountSortedVowelStrs_Pentatope, 33);

SIMPLE_TEST(CountSortedVowelStrs_Pentatope, TestSAMPLE1, 5, 1);
SIMPLE_TEST(CountSortedVowelStrs_Pentatope, TestSAMPLE2, 15, 2);
SIMPLE_TEST(CountSortedVowelStrs_Pentatope, TestSAMPLE3, 66045, 33);
