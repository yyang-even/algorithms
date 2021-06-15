#include "common_header.h"


namespace {

/** Longest Common Substring
 *
 * @reference   Longest Common Substring | DP-29
 *              https://www.geeksforgeeks.org/longest-common-substring-dp-29/
 * @reference   Longest common substring in binary representation of two numbers
 *              https://www.geeksforgeeks.org/longest-common-substring-binary-representation-two-numbers/
 */
constexpr auto
LongestCommonSubstring(const std::string_view X, const std::string_view Y) {
    std::size_t LCSs[X.size() + 1][Y.size() + 1] = {};
    std::size_t max_length = 0;

    for (std::size_t i = 1; i <= X.size(); ++i) {
        for (std::size_t j = 1; j <= Y.size(); ++j) {
            if (X[i - 1] == Y[j - 1]) {
                LCSs[i][j] = LCSs[i - 1][j - 1] + 1;
                if (max_length < LCSs[i][j]) {
                    max_length = LCSs[i][j];
                }
            }
        }
    }

    return max_length;
}


/**
 * @reference   Longest Common Substring (Space optimized DP solution)
 *              https://www.geeksforgeeks.org/longest-common-substring-space-optimized-dp-solution/
 * @reference   Print the longest common substring
 *              https://www.geeksforgeeks.org/print-longest-common-substring/
 */
constexpr auto
LongestCommonSubstring_SpaceOptimized(const std::string_view X,
                                      const std::string_view Y) {
    auto row_size = 2;  //work around a GCC bug.
    std::size_t LCSs[row_size][Y.size() + 1] = {};
    std::size_t max_length = 0;
    std::size_t the_end = 0;

    for (std::size_t i = 1; i <= X.size(); ++i) {
        const auto current_row = i % 2;
        for (std::size_t j = 1; j <= Y.size(); ++j) {
            if (X[i - 1] == Y[j - 1]) {
                LCSs[current_row][j] = LCSs[1 - current_row][j - 1] + 1;
                if (max_length < LCSs[current_row][j]) {
                    max_length = LCSs[current_row][j];
                    the_end = i - 1;
                }
            } else {
                LCSs[current_row][j] = 0;
            }
        }
    }

    return X.substr(the_end - max_length + 1, max_length);
}


/**
 * @reference   Longest Common Substring in an Array of Strings
 *              https://www.geeksforgeeks.org/longest-common-substring-array-strings/
 */

}//namespace


constexpr std::string_view SAMPLE1_X = "GeeksforGeeks";
constexpr std::string_view SAMPLE1_Y = "GeeksQuiz";
constexpr std::string_view EXPECTED1 = "Geeks";

constexpr std::string_view SAMPLE2_X = "abcdxyz";
constexpr std::string_view SAMPLE2_Y = "xyzabcd";
constexpr std::string_view EXPECTED2 = "abcd";

constexpr std::string_view SAMPLE3_X = "zxabcdezy";
constexpr std::string_view SAMPLE3_Y = "yzabcdezx";
constexpr std::string_view EXPECTED3 = "abcdez";


THE_BENCHMARK(LongestCommonSubstring, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubstring, TestSAMPLE1, EXPECTED1.size(),
            SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubstring, TestSAMPLE2, EXPECTED2.size(),
            SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubstring, TestSAMPLE3, EXPECTED3.size(),
            SAMPLE3_X, SAMPLE3_Y);


THE_BENCHMARK(LongestCommonSubstring_SpaceOptimized, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubstring_SpaceOptimized, TestSAMPLE1, EXPECTED1,
            SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubstring_SpaceOptimized, TestSAMPLE2, EXPECTED2,
            SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubstring_SpaceOptimized, TestSAMPLE3, EXPECTED3,
            SAMPLE3_X, SAMPLE3_Y);
