#include "common_header.h"

#include "longest_common_subsequence.h"


namespace {

using TwoDimensionalArrayType =
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, unsigned>>;

using ThreeDimensionalArrayType = std::unordered_map<
    std::size_t,
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, unsigned>>>;


inline auto LongestCommonSubsequence_DP(const std::string &X, const std::string &Y) {
    return LongestCommonSubsequence(X, Y);
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.4-4.
 * @reference   A Space Optimized Solution of LCS
 *              https://www.geeksforgeeks.org/space-optimized-solution-lcs/
 */
constexpr auto LongestCommonSubsequence_SpaceOptimized(const std::string_view X,
                                                       const std::string_view Y) {
    auto row_size = 2; //work around a GCC bug.
    unsigned LCS_table[row_size][Y.size() + 1] = {};

    for (std::size_t i = 1; i <= X.size(); ++i) {
        const auto current_row = i & 1;
        for (std::size_t j = 1; j <= Y.size(); ++j) {
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
unsigned LongestCommonSubsequence_Memoization(const std::string_view X,
                                              const std::size_t x_i,
                                              const std::string_view Y,
                                              const std::size_t y_i,
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

inline auto LongestCommonSubsequence_Memoization(const std::string_view X,
                                                 const std::string_view Y) {
    TwoDimensionalArrayType LCS_table;
    return LongestCommonSubsequence_Memoization(X, X.size(), Y, Y.size(), LCS_table);
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.4-2.
 * @reference   Printing Longest Common Subsequence
 *              https://www.geeksforgeeks.org/printing-longest-common-subsequence/
 */
inline auto LongestCommonSubsequenceString(const std::string &X, const std::string &Y) {
    std::string the_lcs;
    LongestCommonSubsequence(X, Y, &the_lcs);
    return the_lcs;
}


/**
 * @reference   Delete Operation for Two Strings
 *              https://leetcode.com/problems/delete-operation-for-two-strings/
 *
 * Given two strings word1 and word2, return the minimum number of steps required to make word1 and
 * word2 the same.
 * In one step, you can delete exactly one character in either string.
 */


/**
 * @reference   Printing Longest Common Subsequence | Set 2 (Printing All)
 *              https://www.geeksforgeeks.org/printing-longest-common-subsequence-set-2-printing/
 */
auto AllLongestCommonSubsequenceStrings(const std::string_view X,
                                        const std::size_t x_i,
                                        const std::string_view Y,
                                        const std::size_t y_i,
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

auto AllLongestCommonSubsequenceStrings(const std::string_view X, const std::string_view Y) {
    TwoDimensionalArrayType LCS_table = {};

    for (std::size_t i = 1; i <= X.size(); ++i) {
        for (std::size_t j = 1; j <= Y.size(); ++j) {
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
constexpr auto LongestCommonSubsequenceOfThree(const std::string_view X,
                                               const std::string_view Y,
                                               const std::string_view Z) {
    unsigned LCS_table[X.size() + 1][Y.size() + 1][Z.size() + 1] = {};

    for (std::size_t i = 1; i <= X.size(); ++i) {
        for (std::size_t j = 1; j <= Y.size(); ++j) {
            for (std::size_t k = 1; k <= Z.size(); ++k) {
                if (X[i - 1] == Y[j - 1] and Y[j - 1] == Z[k - 1]) {
                    LCS_table[i][j][k] = LCS_table[i - 1][j - 1][k - 1] + 1;
                } else
                    LCS_table[i][j][k] = std::max(
                        {LCS_table[i - 1][j][k], LCS_table[i][j - 1][k], LCS_table[i][j][k - 1]});
            }
        }
    }

    return LCS_table[X.size()][Y.size()][Z.size()];
}


/**
 * @reference   Memoization (1D, 2D and 3D)
 *              https://www.geeksforgeeks.org/memoization-1d-2d-and-3d/
 */
unsigned LongestCommonSubsequenceOfThree_Memoization(const std::string_view X,
                                                     const std::size_t x_i,
                                                     const std::string_view Y,
                                                     const std::size_t y_i,
                                                     const std::string_view Z,
                                                     const std::size_t z_i,
                                                     ThreeDimensionalArrayType &LCS_table) {
    if (x_i == 0 or y_i == 0 or z_i == 0) {
        return 0;
    }

    if (LCS_table[x_i - 1][y_i - 1].find(z_i - 1) == LCS_table[x_i - 1][y_i - 1].cend()) {
        if (X[x_i - 1] == Y[y_i - 1] and Y[y_i - 1] == Z[z_i - 1]) {
            LCS_table[x_i - 1][y_i - 1][z_i - 1] =
                1 + LongestCommonSubsequenceOfThree_Memoization(
                        X, x_i - 1, Y, y_i - 1, Z, z_i - 1, LCS_table);
        } else
            LCS_table[x_i - 1][y_i - 1][z_i - 1] =
                std::max({LongestCommonSubsequenceOfThree_Memoization(
                              X, x_i, Y, y_i - 1, Z, z_i, LCS_table),
                          LongestCommonSubsequenceOfThree_Memoization(
                              X, x_i - 1, Y, y_i, Z, z_i, LCS_table),
                          LongestCommonSubsequenceOfThree_Memoization(
                              X, x_i, Y, y_i, Z, z_i - 1, LCS_table)});
    }

    return LCS_table[x_i - 1][y_i - 1][z_i - 1];
}

inline auto LongestCommonSubsequenceOfThree_Memoization(const std::string_view X,
                                                        const std::string_view Y,
                                                        const std::string_view Z) {
    ThreeDimensionalArrayType LCS_table;
    return LongestCommonSubsequenceOfThree_Memoization(
        X, X.size(), Y, Y.size(), Z, Z.size(), LCS_table);
}

} //namespace


constexpr auto SAMPLE1_X = "ABCDGH";
constexpr auto SAMPLE1_Y = "AEDFHR";
const std::string EXPECTED1 = "ADH";

constexpr auto SAMPLE2_X = "AGGTAB";
constexpr auto SAMPLE2_Y = "GXTXAYB";
const std::string EXPECTED2 = "GTAB";

constexpr auto SAMPLE3_X = "10010101";
constexpr auto SAMPLE3_Y = "010110110";
const std::string EXPECTED3 = "010101";

const std::string SAMPLE14_X = "abcde";
const std::string SAMPLE14_Y = "ace";

constexpr auto SAMPLE15_X = "abc";
constexpr auto SAMPLE15_Y = "def";


THE_BENCHMARK(LongestCommonSubsequence_DP, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubsequence_DP, TestSAMPLE1, EXPECTED1.size(), SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubsequence_DP, TestSAMPLE2, EXPECTED2.size(), SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubsequence_DP, TestSAMPLE3, EXPECTED3.size(), SAMPLE3_X, SAMPLE3_Y);
SIMPLE_TEST(LongestCommonSubsequence_DP, TestSAMPLE4, SAMPLE14_Y.size(), SAMPLE14_X, SAMPLE14_Y);
SIMPLE_TEST(LongestCommonSubsequence_DP, TestSAMPLE5, 0, SAMPLE15_X, SAMPLE15_Y);


THE_BENCHMARK(LongestCommonSubsequence_SpaceOptimized, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(
    LongestCommonSubsequence_SpaceOptimized, TestSAMPLE1, EXPECTED1.size(), SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(
    LongestCommonSubsequence_SpaceOptimized, TestSAMPLE2, EXPECTED2.size(), SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(
    LongestCommonSubsequence_SpaceOptimized, TestSAMPLE3, EXPECTED3.size(), SAMPLE3_X, SAMPLE3_Y);


THE_BENCHMARK(LongestCommonSubsequence_Memoization, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(
    LongestCommonSubsequence_Memoization, TestSAMPLE1, EXPECTED1.size(), SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(
    LongestCommonSubsequence_Memoization, TestSAMPLE2, EXPECTED2.size(), SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(
    LongestCommonSubsequence_Memoization, TestSAMPLE3, EXPECTED3.size(), SAMPLE3_X, SAMPLE3_Y);


THE_BENCHMARK(LongestCommonSubsequenceString, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubsequenceString, TestSAMPLE1, EXPECTED1, SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubsequenceString, TestSAMPLE2, EXPECTED2, SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubsequenceString, TestSAMPLE3, EXPECTED3, SAMPLE3_X, SAMPLE3_Y);


constexpr auto SAMPLE4_X = "AGTGATG";
constexpr auto SAMPLE4_Y = "GTTAG";
const std::unordered_set<std::string> EXPECTED4 = {"GTAG", "GTTG"};

constexpr auto SAMPLE5_X = "AATCC";
constexpr auto SAMPLE5_Y = "ACACG";
const std::unordered_set<std::string> EXPECTED5 = {"ACC", "AAC"};

constexpr auto SAMPLE6_X = "ABCBDAB";
constexpr auto SAMPLE6_Y = "BDCABA";
const std::unordered_set<std::string> EXPECTED6 = {"BCAB", "BCBA", "BDAB"};


THE_BENCHMARK(AllLongestCommonSubsequenceStrings, SAMPLE4_X, SAMPLE4_Y);

SIMPLE_TEST(AllLongestCommonSubsequenceStrings, TestSAMPLE4, EXPECTED4, SAMPLE4_X, SAMPLE4_Y);
SIMPLE_TEST(AllLongestCommonSubsequenceStrings, TestSAMPLE5, EXPECTED5, SAMPLE5_X, SAMPLE5_Y);
SIMPLE_TEST(AllLongestCommonSubsequenceStrings, TestSAMPLE6, EXPECTED6, SAMPLE6_X, SAMPLE6_Y);


constexpr std::string_view SAMPLE7_X = "geeks";
constexpr auto SAMPLE7_Y = "geeksfor";
constexpr auto SAMPLE7_Z = "geeksforgeeks";

constexpr auto SAMPLE8_X = "abcd1e2";
constexpr auto SAMPLE8_Y = "bc12ea";
constexpr auto SAMPLE8_Z = "bd1ea";
constexpr std::string_view EXPECTED8 = "b1e";


THE_BENCHMARK(LongestCommonSubsequenceOfThree, SAMPLE7_X, SAMPLE7_Y, SAMPLE7_Z);

SIMPLE_TEST(LongestCommonSubsequenceOfThree,
            TestSAMPLE7,
            SAMPLE7_X.size(),
            SAMPLE7_X,
            SAMPLE7_Y,
            SAMPLE7_Z);
SIMPLE_TEST(LongestCommonSubsequenceOfThree,
            TestSAMPLE8,
            EXPECTED8.size(),
            SAMPLE8_X,
            SAMPLE8_Y,
            SAMPLE8_Z);


THE_BENCHMARK(LongestCommonSubsequenceOfThree_Memoization, SAMPLE7_X, SAMPLE7_Y, SAMPLE7_Z);

SIMPLE_TEST(LongestCommonSubsequenceOfThree_Memoization,
            TestSAMPLE7,
            SAMPLE7_X.size(),
            SAMPLE7_X,
            SAMPLE7_Y,
            SAMPLE7_Z);
SIMPLE_TEST(LongestCommonSubsequenceOfThree_Memoization,
            TestSAMPLE8,
            EXPECTED8.size(),
            SAMPLE8_X,
            SAMPLE8_Y,
            SAMPLE8_Z);
