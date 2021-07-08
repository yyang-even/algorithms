#include "common_header.h"


namespace {

/** Longest Common Substring
 *
 * @reference   Longest Common Substring | DP-29
 *              https://www.geeksforgeeks.org/longest-common-substring-dp-29/
 * @reference   Longest common substring in binary representation of two numbers
 *              https://www.geeksforgeeks.org/longest-common-substring-binary-representation-two-numbers/
 *
 * @reference   Longest common subarray in the given two arrays
 *              https://www.geeksforgeeks.org/longest-common-subarray-in-the-given-two-arrays/
 * @reference   Maximum Length of Repeated Subarray
 *              https://leetcode.com/problems/maximum-length-of-repeated-subarray/
 *
 * Given two integer arrays nums1 and nums2, return the maximum length of a subarray
 * that appears in both arrays.
 */
constexpr auto
LongestCommonSubstring(const std::string_view X, const std::string_view Y) {
    std::size_t longest_common_suffix[X.size() + 1][Y.size() + 1] = {};
    std::size_t max_length = 0;

    for (std::size_t i = 1; i <= X.size(); ++i) {
        for (std::size_t j = 1; j <= Y.size(); ++j) {
            if (X[i - 1] == Y[j - 1]) {
                longest_common_suffix[i][j] = longest_common_suffix[i - 1][j - 1] + 1;
                if (max_length < longest_common_suffix[i][j]) {
                    max_length = longest_common_suffix[i][j];
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
    std::size_t longest_common_suffix[row_size][Y.size() + 1] = {};
    std::size_t max_length = 0;
    std::size_t the_end = 0;

    for (std::size_t i = 1; i <= X.size(); ++i) {
        const auto current_row = i % 2;
        for (std::size_t j = 1; j <= Y.size(); ++j) {
            if (X[i - 1] == Y[j - 1]) {
                longest_common_suffix[current_row][j] =
                    longest_common_suffix[1 - current_row][j - 1] + 1;
                if (max_length < longest_common_suffix[current_row][j]) {
                    max_length = longest_common_suffix[current_row][j];
                    the_end = i - 1;
                }
            } else {
                longest_common_suffix[current_row][j] = 0;
            }
        }
    }

    return X.substr(the_end - max_length + 1, max_length);
}


constexpr auto
LongestCommonSubstring_SlidingWindow(const std::string_view X,
                                     const std::string_view Y) {
    std::size_t result = 0;
    const long x_size = X.size();
    const long y_size = Y.size();
    for (long i = 0; i < x_size + y_size - 1; ++i) {
        auto x_index = std::max(0l, x_size - 1 - i);
        auto y_index = std::max(0l, i - (x_size - 1));
        std::size_t common_substring = 0;
        for (; x_index < x_size and y_index < y_size; ++x_index, ++y_index) {
            if (X[x_index] == Y[y_index]) {
                ++common_substring;
            } else {
                common_substring = 0;
            }

            result = std::max(result, common_substring);
        }
    }

    return result;
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


THE_BENCHMARK(LongestCommonSubstring_SlidingWindow, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(LongestCommonSubstring_SlidingWindow, TestSAMPLE1, EXPECTED1.size(),
            SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(LongestCommonSubstring_SlidingWindow, TestSAMPLE2, EXPECTED2.size(),
            SAMPLE2_X, SAMPLE2_Y);
SIMPLE_TEST(LongestCommonSubstring_SlidingWindow, TestSAMPLE3, EXPECTED3.size(),
            SAMPLE3_X, SAMPLE3_Y);
