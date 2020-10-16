#include "common_header.h"

#include "longest_common_subsequence.h"


namespace {

using TwoDimensionalArrayType =
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, unsigned>>;

using ThreeDimensionalArrayType =
    std::unordered_map<std::size_t,
    std::unordered_map<std::size_t,
    std::unordered_map<std::size_t, unsigned>>>;


auto LongestCommonSubsequence_DP(const std::string &X, const std::string &Y) {
    return LongestCommonSubsequence(X, Y);
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.4-4.
 * @reference   A Space Optimized Solution of LCS
 *              https://www.geeksforgeeks.org/space-optimized-solution-lcs/
 */
auto LongestCommonSubsequence_SpaceOptimized(const std::string &X,
                                             const std::string &Y) {
    auto row_size = 2;  //work around a GCC bug.
    unsigned LCS_table[row_size][Y.size() + 1] = {};

    for (std::string::size_type i = 1; i <= X.size(); ++i) {
        const auto current_row = i & 1;
        for (std::string::size_type j = 1; j <= Y.size(); ++j) {
            if (X[i - 1] == Y[j - 1]) {
                LCS_table[current_row][j] = LCS_table[1 - current_row][j - 1] + 1;
            } else {
                LCS_table[current_row][j] =
                    std::max(LCS_table[1 - current_row][j], LCS_table[current_row][j - 1]);
            }
        }
    }

    return LCS_table[X.size() & 1][Y.size()];
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.4-3.
 * @reference   Longest Common Subsequence | DP using Memoization
 *              https://www.geeksforgeeks.org/longest-common-subsequence-dp-using-memoization/
 */
unsigned LongestCommonSubsequence_Memoization(
    const std::string &X, const std::string::size_type x_i,
    const std::string &Y, const std::string::size_type y_i,
    TwoDimensionalArrayType &LCS_table) {
    if (x_i == 0 or y_i == 0) {
        return 0;
    }

    if (LCS_table[x_i - 1].find(y_i - 1) == LCS_table[x_i - 1].cend()) {
        if (X[x_i - 1] == Y[y_i - 1]) {
            LCS_table[x_i - 1][y_i - 1] =
                1 + LongestCommonSubsequence_Memoization(X, x_i - 1, Y, y_i - 1, LCS_table);
        } else
            LCS_table[x_i - 1][y_i - 1] =
                std::max(LongestCommonSubsequence_Memoization(X, x_i, Y, y_i - 1, LCS_table),
                         LongestCommonSubsequence_Memoization(X, x_i - 1, Y, y_i, LCS_table));
    }

    return LCS_table[x_i - 1][y_i - 1];
}

auto LongestCommonSubsequence_Memoization(const std::string &X, const std::string &Y) {
    TwoDimensionalArrayType LCS_table;
    return LongestCommonSubsequence_Memoization(X, X.size(), Y, Y.size(), LCS_table);
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.4-2.
 * @reference   Printing Longest Common Subsequence
 *              https://www.geeksforgeeks.org/printing-longest-common-subsequence/
 */
auto LongestCommonSubsequenceString(const std::string &X, const std::string &Y) {
    std::string the_lcs;
    LongestCommonSubsequence(X, Y, &the_lcs);
    return the_lcs;
}


/**
 * @reference   Printing Longest Common Subsequence | Set 2 (Printing All)
 *              https://www.geeksforgeeks.org/printing-longest-common-subsequence-set-2-printing/
 */
auto AllLongestCommonSubsequenceStrings(const std::string &X,
                                        const std::string::size_type x_i,
                                        const std::string &Y,
                                        const std::string::size_type y_i,
                                        TwoDimensionalArrayType &LCS_table) {
    if (x_i == 0 or y_i == 0)
        return std::unordered_set<std::string> {""};

    std::unordered_set<std::string> all_lcs;
    if (X[x_i - 1] == Y[y_i - 1]) {
        const auto all_sub_lcs =
            AllLongestCommonSubsequenceStrings(X, x_i - 1, Y, y_i - 1, LCS_table);
        for (const auto &one_sub_lcs : all_sub_lcs) {
            all_lcs.emplace(one_sub_lcs + X[x_i - 1]);
        }
    } else {
        if (LCS_table[x_i - 1][y_i] >= LCS_table[x_i][y_i - 1]) {
            all_lcs = AllLongestCommonSubsequenceStrings(X, x_i - 1, Y, y_i, LCS_table);
        }
        if (LCS_table[x_i - 1][y_i] <= LCS_table[x_i][y_i - 1]) {
            all_lcs.merge(AllLongestCommonSubsequenceStrings(X, x_i, Y, y_i - 1, LCS_table));
        }
    }
    return all_lcs;
}

auto AllLongestCommonSubsequenceStrings(const std::string &X, const std::string &Y) {
    TwoDimensionalArrayType LCS_table = {};

    for (std::string::size_type i = 1; i <= X.size(); ++i) {
        for (std::string::size_type j = 1; j <= Y.size(); ++j) {
            if (X[i - 1] == Y[j - 1]) {
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            } else {
                LCS_table[i][j] = std::max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
            }
        }
    }

    return AllLongestCommonSubsequenceStrings(X, X.size(), Y, Y.size(), LCS_table);
}


/**
 * @reference   LCS (Longest Common Subsequence) of three strings
 *              https://www.geeksforgeeks.org/lcs-longest-common-subsequence-three-strings/
 */
auto LongestCommonSubsequenceOfThree(const std::string &X,
                                     const std::string &Y, const std::string &Z) {
    unsigned LCS_table[X.size() + 1][Y.size() + 1][Z.size() + 1] = {};

    for (std::string::size_type i = 1; i <= X.size(); ++i) {
        for (std::string::size_type j = 1; j <= Y.size(); ++j) {
            for (std::string::size_type k = 1; k <= Z.size(); ++k) {
                if (X[i - 1] == Y[j - 1] and Y[j - 1] == Z[k - 1]) {
                    LCS_table[i][j][k] = LCS_table[i - 1][j - 1][k - 1] + 1;
                } else
                    LCS_table[i][j][k] = std::max(std::max(LCS_table[i - 1][j][k],
                                                           LCS_table[i][j - 1][k]),
                                                  LCS_table[i][j][k - 1]);
            }
        }
    }

    return LCS_table[X.size()][Y.size()][Z.size()];
}


/**
 * @reference   Memoization (1D, 2D and 3D)
 *              https://www.geeksforgeeks.org/memoization-1d-2d-and-3d/
 */
unsigned LongestCommonSubsequenceOfThree_Memoization(
    const std::string &X, const std::string::size_type x_i,
    const std::string &Y, const std::string::size_type y_i,
    const std::string &Z, const std::string::size_type z_i,
    ThreeDimensionalArrayType &LCS_table) {
    if (x_i == 0 or y_i == 0 or z_i == 0) {
        return 0;
    }

    if (LCS_table[x_i - 1][y_i - 1].find(z_i - 1) == LCS_table[x_i - 1][y_i - 1].cend()) {
        if (X[x_i - 1] == Y[y_i - 1] and Y[y_i - 1] == Z[z_i - 1]) {
            LCS_table[x_i - 1][y_i - 1][z_i - 1] = 1 +
                                                   LongestCommonSubsequenceOfThree_Memoization(
                                                       X, x_i - 1, Y, y_i - 1, Z, z_i - 1, LCS_table);
        } else
            LCS_table[x_i - 1][y_i - 1][z_i - 1] =
                std::max(
                    std::max(
                        LongestCommonSubsequenceOfThree_Memoization(X, x_i, Y, y_i - 1, Z, z_i, LCS_table),
                        LongestCommonSubsequenceOfThree_Memoization(X, x_i - 1, Y, y_i, Z, z_i, LCS_table)),
                    LongestCommonSubsequenceOfThree_Memoization(X, x_i, Y, y_i, Z, z_i - 1, LCS_table));
    }

    return LCS_table[x_i - 1][y_i - 1][z_i - 1];
}

auto LongestCommonSubsequenceOfThree_Memoization(const std::string &X,
                                                 const std::string &Y, const std::string &Z) {
    ThreeDimensionalArrayType LCS_table;
    return LongestCommonSubsequenceOfThree_Memoization(
               X, X.size(), Y, Y.size(), Z, Z.size(), LCS_table);
}

}//namespace


const auto SAMPLE1_X = "ABCDGH";
const auto SAMPLE1_Y = "AEDFHR";
const std::string EXPECTED1 = "ADH";

const auto SAMPLE2_X = "AGGTAB";
const auto SAMPLE2_Y = "GXTXAYB";
const std::string EXPECTED2 = "GTAB";

const auto SAMPLE3_X = "10010101";
const auto SAMPLE3_Y = "010110110";
const std::string EXPECTED3 = "010101";


SIMPLE_BENCHMARK(LongestCommonSubsequence_DP, Sample1, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubsequence_DP, TestSAMPLE1, EXPECTED1.size(),
            SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubsequence_DP, TestSAMPLE2, EXPECTED2.size(),
            SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubsequence_DP, TestSAMPLE3, EXPECTED3.size(),
            SAMPLE3_X, SAMPLE3_Y);


SIMPLE_BENCHMARK(LongestCommonSubsequence_SpaceOptimized, Sample1,
                 SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubsequence_SpaceOptimized, TestSAMPLE1, EXPECTED1.size(),
            SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubsequence_SpaceOptimized, TestSAMPLE2, EXPECTED2.size(),
            SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubsequence_SpaceOptimized, TestSAMPLE3, EXPECTED3.size(),
            SAMPLE3_X, SAMPLE3_Y);


SIMPLE_BENCHMARK(LongestCommonSubsequence_Memoization, Sample1, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubsequence_Memoization, TestSAMPLE1, EXPECTED1.size(),
            SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubsequence_Memoization, TestSAMPLE2, EXPECTED2.size(),
            SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubsequence_Memoization, TestSAMPLE3, EXPECTED3.size(),
            SAMPLE3_X, SAMPLE3_Y);


SIMPLE_BENCHMARK(LongestCommonSubsequenceString, Sample1, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubsequenceString, TestSAMPLE1, EXPECTED1,
            SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubsequenceString, TestSAMPLE2, EXPECTED2,
            SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubsequenceString, TestSAMPLE3, EXPECTED3,
            SAMPLE3_X, SAMPLE3_Y);


const auto SAMPLE4_X = "AGTGATG";
const auto SAMPLE4_Y = "GTTAG";
const std::unordered_set<std::string> EXPECTED4 = {"GTAG", "GTTG"};

const auto SAMPLE5_X = "AATCC";
const auto SAMPLE5_Y = "ACACG";
const std::unordered_set<std::string> EXPECTED5 = {"ACC", "AAC"};

const auto SAMPLE6_X = "ABCBDAB";
const auto SAMPLE6_Y = "BDCABA";
const std::unordered_set<std::string> EXPECTED6 = {"BCAB", "BCBA", "BDAB"};


SIMPLE_BENCHMARK(AllLongestCommonSubsequenceStrings, Sample1, SAMPLE4_X, SAMPLE4_Y);

SIMPLE_TEST(AllLongestCommonSubsequenceStrings, TestSAMPLE4, EXPECTED4,
            SAMPLE4_X, SAMPLE4_Y);
SIMPLE_TEST(AllLongestCommonSubsequenceStrings, TestSAMPLE5, EXPECTED5,
            SAMPLE5_X, SAMPLE5_Y);
SIMPLE_TEST(AllLongestCommonSubsequenceStrings, TestSAMPLE6, EXPECTED6,
            SAMPLE6_X, SAMPLE6_Y);


const std::string SAMPLE7_X = "geeks";
const auto SAMPLE7_Y = "geeksfor";
const auto SAMPLE7_Z = "geeksforgeeks";

const auto SAMPLE8_X = "abcd1e2";
const auto SAMPLE8_Y = "bc12ea";
const auto SAMPLE8_Z = "bd1ea";
const std::string EXPECTED8 = "b1e";


SIMPLE_BENCHMARK(LongestCommonSubsequenceOfThree, Sample1,
                 SAMPLE7_X, SAMPLE7_Y, SAMPLE7_Z);

SIMPLE_TEST(LongestCommonSubsequenceOfThree, TestSAMPLE7, SAMPLE7_X.size(),
            SAMPLE7_X, SAMPLE7_Y, SAMPLE7_Z);
SIMPLE_TEST(LongestCommonSubsequenceOfThree, TestSAMPLE8, EXPECTED8.size(),
            SAMPLE8_X, SAMPLE8_Y, SAMPLE8_Z);


SIMPLE_BENCHMARK(LongestCommonSubsequenceOfThree_Memoization, Sample1,
                 SAMPLE7_X, SAMPLE7_Y, SAMPLE7_Z);

SIMPLE_TEST(LongestCommonSubsequenceOfThree_Memoization, TestSAMPLE7, SAMPLE7_X.size(),
            SAMPLE7_X, SAMPLE7_Y, SAMPLE7_Z);
SIMPLE_TEST(LongestCommonSubsequenceOfThree_Memoization, TestSAMPLE8, EXPECTED8.size(),
            SAMPLE8_X, SAMPLE8_Y, SAMPLE8_Z);
