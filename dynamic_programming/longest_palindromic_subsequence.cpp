#include "common_header.h"

#include "longest_common_subsequence.h"


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


/**
 * @reference   Print Longest Palindromic Subsequence
 *              https://www.geeksforgeeks.org/print-longest-palindromic-subsequence/
 */
auto LongestPalindromicSubsequenceString_LCS(const std::string &elements) {
    auto reversed = elements;
    std::reverse(reversed.begin(), reversed.end());

    std::string the_lps;
    LongestCommonSubsequence(elements, reversed, &the_lps);

    return the_lps;
}


/**
 * @reference   Longest palindrome subsequence with O(n) space
 *              https://www.geeksforgeeks.org/longest-palindrome-subsequence-space/
 */
auto LongestPalindromicSubsequence_SpaceOptimized(const std::string &elements) {
    unsigned LPSs[elements.size()] = {};
    for (int i = elements.size() - 1; i >= 0; --i) {
        unsigned back_up = 0;
        for (std::string::size_type j = i; j < elements.size(); ++j) {
            if (static_cast<decltype(j)>(i) == j) {
                LPSs[j] = 1;
            } else if (elements[i] == elements[j]) {
                std::swap(LPSs[j], back_up);
                LPSs[j] += 2;
            } else {
                back_up = LPSs[j];
                LPSs[j] = std::max(LPSs[j - 1], LPSs[j]);
            }
        }
    }

    return LPSs[elements.size() - 1];
}

}//namespace


const auto SAMPLE1 = "BBABCBCAB";
const std::string EXPECTED1 = "BACBCAB";

const auto SAMPLE2 = "GEEKSFORGEEKS";
const std::string EXPECTED2 = "EEGEE";


SIMPLE_BENCHMARK(LongestPalindromicSubsequence, Sample1, SAMPLE1);

SIMPLE_TEST(LongestPalindromicSubsequence, TestSAMPLE1, EXPECTED1.size(), SAMPLE1);
SIMPLE_TEST(LongestPalindromicSubsequence, TestSAMPLE2, EXPECTED2.size(), SAMPLE2);


SIMPLE_BENCHMARK(LongestPalindromicSubsequenceString_LCS, Sample1, SAMPLE1);

SIMPLE_TEST(LongestPalindromicSubsequenceString_LCS, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(LongestPalindromicSubsequenceString_LCS, TestSAMPLE2, EXPECTED2, SAMPLE2);


SIMPLE_BENCHMARK(LongestPalindromicSubsequence_SpaceOptimized, Sample1, SAMPLE1);

SIMPLE_TEST(LongestPalindromicSubsequence_SpaceOptimized, TestSAMPLE1, EXPECTED1.size(), SAMPLE1);
SIMPLE_TEST(LongestPalindromicSubsequence_SpaceOptimized, TestSAMPLE2, EXPECTED2.size(), SAMPLE2);
