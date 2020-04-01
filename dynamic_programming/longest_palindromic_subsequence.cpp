#include "common_header.h"


namespace {

/** Longest Palindromic Subsequence
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 15-2.
 * @reference   Longest Palindromic Subsequence | DP-12
 *              https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/
 */
auto LongestPalindromicSubsequence(const std::string &elements) {
    std::string::size_type LPSs[elements.size()][elements.size()] = {};

    for (std::string::size_type i = 0; i < elements.size(); ++i) {
        LPSs[i][i] = 1;
    }

    for (std::string::size_type length = 2; length <= elements.size(); ++length) {
        for (std::string::size_type i = 0; i <= elements.size() - i; ++i) {
            const auto j = i + length - 1;
            if (elements[i] == elements[j]) {
                if (length == 2) {
                    LPSs[i][j] = 2;
                } else {
                    LPSs[i][j] = LPSs[i + 1][j - 1] + 2;
                }
            } else {
                LPSs[i][j] = std::max(LPSs[i][j - 1], LPSs[i + 1][j]);
            }
        }
    }

    return LPSs[0][elements.size() - 1];
}

}//namespace


const auto SAMPLE1 = "BBABCBCAB";
const std::string EXPECTED1 = "BABCBAB";


SIMPLE_BENCHMARK(LongestPalindromicSubsequence, SAMPLE1);

SIMPLE_TEST(LongestPalindromicSubsequence, TestSAMPLE1, EXPECTED1.size(), SAMPLE1);
