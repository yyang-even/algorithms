#include "common_header.h"

#include "longest_common_subsequence.h"


namespace {

using TwoDimensionalArrayType =
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, unsigned>>;

/** Edit Distance
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 15-5.
 * @reference   Edit Distance | DP-5
 *              https://www.geeksforgeeks.org/edit-distance-dp-5/
 *
 * Given two strings str1 and str2 and below operations that can performed on str1.
 * Find minimum number of edits (operations) required to convert 'str1' into 'str2'.
 *
 *     Insert   Remove  Replace
 *
 * All of the above operations are of equal cost.
 */
auto EditDistance(const std::string &str1, const std::string &str2) {
    unsigned min_distances[str1.size() + 1][str2.size() + 1] = {};

    for (std::string::size_type i = 0; i <= str1.size(); ++i) {
        for (std::string::size_type j = 0; j <= str2.size(); ++j) {
            if (i == 0) {
                min_distances[i][j] = j;
            } else if (j == 0) {
                min_distances[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                min_distances[i][j] = min_distances[i - 1][j - 1];
            } else {
                min_distances[i][j] = 1 + std::min(min_distances[i][j - 1],                 // Insert
                                                   std::min(min_distances[i - 1][j],        // Remove
                                                            min_distances[i - 1][j - 1]));   // Replace
            }
        }
    }

    return min_distances[str1.size()][str2.size()];
}


auto EditDistance_SpaceOptimized(const std::string &str1, const std::string &str2) {
    auto row_size = 2;  //work around a GCC bug.
    unsigned min_distances[row_size][str2.size() + 1] = {};

    for (std::string::size_type i = 0; i <= str1.size(); ++i) {
        const auto current_row = i % 2;
        for (std::string::size_type j = 0; j <= str2.size(); ++j) {
            if (i == 0) {
                min_distances[i][j] = j;
            } else if (j == 0) {
                min_distances[current_row][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                min_distances[current_row][j] = min_distances[1 - current_row][j - 1];
            } else {
                min_distances[current_row][j] = 1 + std::min(
                                                    std::min(min_distances[current_row][j - 1], // Insert
                                                             min_distances[1 - current_row][j]), // Remove
                                                    min_distances[1 - current_row][j - 1]);     // Replace
            }
        }
    }

    return min_distances[str1.size() % 2][str2.size()];
}


/**
 * @reference   Edit Distance | DP using Memoization
 *              https://www.geeksforgeeks.org/edit-distance-dp-using-memoization/
 */
unsigned EditDistance_Memoization(const std::string &str1,
                                  const std::string::size_type i,
                                  const std::string &str2, const std::string::size_type j,
                                  TwoDimensionalArrayType &min_distances) {
    if (i == 0) {
        return j;
    }
    if (j == 0) {
        return i;
    }

    if (min_distances[i].find(j) != min_distances[i].cend()) {
        return min_distances[i][j];
    }

    if (str1[i - 1] == str2[j - 1]) {
        return min_distances[i][j] = EditDistance_Memoization(str1, i - 1, str2, j - 1,
                                                              min_distances);
    }

    return min_distances[i][j] = 1 + std::min(
                                     std::min(EditDistance_Memoization(str1, i, str2, j - 1, min_distances),    // Insert
                                              EditDistance_Memoization(str1, i - 1, str2, j, min_distances)),    // Remove
                                     EditDistance_Memoization(str1, i - 1, str2, j - 1, min_distances));        // Replace
}

auto EditDistance_Memoization(const std::string &str1, const std::string &str2) {
    TwoDimensionalArrayType min_distances;
    return EditDistance_Memoization(str1, str1.size(), str2, str2.size(), min_distances);
}


/** Check whether Strings are k distance apart or not
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-strings-k-distance-apart-not/
 */
auto areKDistanceApart(const std::string &str1, const std::string &str2,
                       const unsigned K) {
    const auto length_diff =
        str1.size() > str2.size() ? str1.size() - str2.size() : str2.size() - str1.size();
    if (length_diff > K) {
        return false;
    }

    return EditDistance_SpaceOptimized(str1, str2) <= K;
}


/** Check if edit distance between two strings is one
 *
 * @reference   https://www.geeksforgeeks.org/check-if-two-given-strings-are-at-edit-distance-one/
 */
auto areOneDistanceApart(const std::string &str1, const std::string &str2) {
    const auto length_diff =
        str1.size() > str2.size() ? str1.size() - str2.size() : str2.size() - str1.size();
    if (length_diff > 1) {
        return false;
    }

    unsigned distance = 0;
    std::string::size_type i = 0;
    std::string::size_type j = 0;
    while (i < str1.size() and j < str2.size()) {
        if (str1[i] != str2[j]) {
            if (distance == 1) {
                return false;
            }

            if (str1.size() > str2.size()) {
                ++i;
            } else if (str1.size() < str2.size()) {
                ++j;
            } else {
                ++i;
                ++j;
            }

            ++distance;
        } else {
            ++i;
            ++j;
        }
    }

    if (i < str1.size() or j < str2.size()) {
        ++distance;
    }

    return distance == 1;
}


/** Edit distance and LCS (Longest Common Subsequence)
 *
 * @reference   https://www.geeksforgeeks.org/edit-distance-and-lcs-longest-common-subsequence/
 *
 * In standard Edit Distance where we are allowed 3 operations, insert, delete and replace.
 * Consider a variation of edit distance where we are allowed only two operations insert
 * and delete, find edit distance in this variation.
 */
auto EditDistanceWithInsertAndDeleteOnly(const std::string &str1,
                                         const std::string &str2) {
    const auto LCS = LongestCommonSubsequence(str1, str2);
    return (str1.size() - LCS) + (str2.size() - LCS);
}

}//namespace


SIMPLE_BENCHMARK(EditDistance, Sample1, "geek", "gesek");

SIMPLE_TEST(EditDistance, TestSAMPLE1, 1, "geek", "gesek");
SIMPLE_TEST(EditDistance, TestSAMPLE2, 1, "cat", "cut");
SIMPLE_TEST(EditDistance, TestSAMPLE3, 3, "sunday", "saturday");
SIMPLE_TEST(EditDistance, TestSAMPLE4, 4, "food", "money");


SIMPLE_BENCHMARK(EditDistance_SpaceOptimized, Sample1, "geek", "gesek");

SIMPLE_TEST(EditDistance_SpaceOptimized, TestSAMPLE1, 1, "geek", "gesek");
SIMPLE_TEST(EditDistance_SpaceOptimized, TestSAMPLE2, 1, "cat", "cut");
SIMPLE_TEST(EditDistance_SpaceOptimized, TestSAMPLE3, 3, "sunday", "saturday");
SIMPLE_TEST(EditDistance_SpaceOptimized, TestSAMPLE4, 4, "food", "money");


SIMPLE_BENCHMARK(EditDistance_Memoization, Sample1, "geek", "gesek");

SIMPLE_TEST(EditDistance_Memoization, TestSAMPLE1, 1, "geek", "gesek");
SIMPLE_TEST(EditDistance_Memoization, TestSAMPLE2, 1, "cat", "cut");
SIMPLE_TEST(EditDistance_Memoization, TestSAMPLE3, 3, "sunday", "saturday");
SIMPLE_TEST(EditDistance_Memoization, TestSAMPLE4, 4, "food", "money");


SIMPLE_BENCHMARK(areKDistanceApart, Sample1, "geeksforgeeks", "geeksforgeek", 1);

SIMPLE_TEST(areKDistanceApart, TestSAMPLE1, true, "geeksforgeeks", "geeksforgeek", 1);
SIMPLE_TEST(areKDistanceApart, TestSAMPLE2, false, "nishant", "nisha", 1);
SIMPLE_TEST(areKDistanceApart, TestSAMPLE3, false, "practice", "prac", 3);
SIMPLE_TEST(areKDistanceApart, TestSAMPLE4, true, "Ping", "Paging", 2);


SIMPLE_BENCHMARK(areOneDistanceApart, Sample1, "geeks", "geek");

SIMPLE_TEST(areOneDistanceApart, TestSAMPLE1, true, "geeks", "geek");
SIMPLE_TEST(areOneDistanceApart, TestSAMPLE2, false, "geeks", "geeks");
SIMPLE_TEST(areOneDistanceApart, TestSAMPLE3, false, "peaks", "geeks");
SIMPLE_TEST(areOneDistanceApart, TestSAMPLE4, true, "geaks", "geeks");


SIMPLE_BENCHMARK(EditDistanceWithInsertAndDeleteOnly, Sample1, "cat", "cut");

SIMPLE_TEST(EditDistanceWithInsertAndDeleteOnly, TestSAMPLE1, 2, "cat", "cut");
SIMPLE_TEST(EditDistanceWithInsertAndDeleteOnly, TestSAMPLE2, 1, "acb", "ab");
SIMPLE_TEST(EditDistanceWithInsertAndDeleteOnly, TestSAMPLE3, 2, "acd", "abc");
