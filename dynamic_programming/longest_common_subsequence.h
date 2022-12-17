#pragma once


/** Longest Common Subsequence
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 15.4.
 * @reference   Longest Common Subsequence | DP-4
 *              https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
 * @reference   C++ Program for Longest Common Subsequence
 *              https://www.geeksforgeeks.org/cpp-program-for-longest-common-subsequence/
 *
 * LCS Problem Statement: Given two sequences, find the length of longest subsequence present in both of
 * them. A subsequence is a sequence that appears in the same relative order, but not necessarily
 * contiguous. For example, "abc", "abg", "bdf", "aeg", "acefg", .. etc are subsequences of "abcdefg".
 * It is a classic computer science problem, the basis of diff (a file comparison program that outputs
 * the differences between two files), and has applications in bioinformatics.
 *
 * @reference   Longest Common Subsequence
 *              https://leetcode.com/problems/longest-common-subsequence/
 *
 * Given two strings text1 and text2, return the length of their longest common subsequence. If there is
 * no common subsequence, return 0.
 * A subsequence of a string is a new string generated from the original string with some characters
 * (can be none) deleted without changing the relative order of the remaining characters.
 *  For example, "ace" is a subsequence of "abcde".
 * A common subsequence of two strings is a subsequence that is common to both strings.
 */
template<typename ArrayType>
static inline constexpr auto LongestCommonSubsequence(const ArrayType &X,
                                                      const ArrayType &Y,
                                                      ArrayType *const the_lcs = nullptr) {
    unsigned LCS_table[X.size() + 1][Y.size() + 1] = {};

    for (typename ArrayType::size_type i = 1; i <= X.size(); ++i) {
        for (typename ArrayType::size_type j = 1; j <= Y.size(); ++j) {
            if (X[i - 1] == Y[j - 1]) {
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            } else {
                LCS_table[i][j] = std::max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
            }
        }
    }

    if (the_lcs) {
        auto i = X.size();
        auto j = Y.size();
        auto lcs_length = LCS_table[i][j];
        the_lcs->resize(lcs_length);

        while (i and j) {
            if (X[i - 1] == Y[j - 1]) {
                (*the_lcs)[--lcs_length] = X[--i];
                --j;
            } else if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
                --i;
            } else {
                --j;
            }
        }
    }

    return LCS_table[X.size()][Y.size()];
}
