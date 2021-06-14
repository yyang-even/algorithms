#include "common_header.h"


namespace {

/** Longest Common Substring
 *
 * @reference   Longest Common Substring | DP-29
 *              https://www.geeksforgeeks.org/longest-common-substring-dp-29/
 * @reference   Longest common substring in binary representation of two numbers
 *              https://www.geeksforgeeks.org/longest-common-substring-binary-representation-two-numbers/
 */
auto LongestCommonSubstring(const std::string &X, const std::string &Y) {
    std::string::size_type LCSs[X.size() + 1][Y.size() + 1] = {};
    std::string::size_type max_length = 0;

    for (std::string::size_type i = 1; i <= X.size(); ++i) {
        for (std::string::size_type j = 1; j <= Y.size(); ++j) {
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
auto LongestCommonSubstring_SpaceOptimized(const std::string &X, const std::string &Y) {
    auto row_size = 2;  //work around a GCC bug.
    std::string::size_type LCSs[row_size][Y.size() + 1] = {};
    std::string::size_type max_length = 0;
    std::string::size_type the_end = 0;

    for (std::string::size_type i = 1; i <= X.size(); ++i) {
        const auto current_row = i % 2;
        for (std::string::size_type j = 1; j <= Y.size(); ++j) {
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


const auto SAMPLE1_X = "GeeksforGeeks";
const auto SAMPLE1_Y = "GeeksQuiz";
const std::string EXPECTED1 = "Geeks";

const auto SAMPLE2_X = "abcdxyz";
const auto SAMPLE2_Y = "xyzabcd";
const std::string EXPECTED2 = "abcd";

const auto SAMPLE3_X = "zxabcdezy";
const auto SAMPLE3_Y = "yzabcdezx";
const std::string EXPECTED3 = "abcdez";


SIMPLE_BENCHMARK(LongestCommonSubstring, Sample1, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubstring, TestSAMPLE1, EXPECTED1.size(),
            SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubstring, TestSAMPLE2, EXPECTED2.size(),
            SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubstring, TestSAMPLE3, EXPECTED3.size(),
            SAMPLE3_X, SAMPLE3_Y);


SIMPLE_BENCHMARK(LongestCommonSubstring_SpaceOptimized, Sample1, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubstring_SpaceOptimized, TestSAMPLE1, EXPECTED1,
            SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubstring_SpaceOptimized, TestSAMPLE2, EXPECTED2,
            SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubstring_SpaceOptimized, TestSAMPLE3, EXPECTED3,
            SAMPLE3_X, SAMPLE3_Y);
