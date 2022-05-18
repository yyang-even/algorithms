#include "common_header.h"


namespace {

/** Longest Palindromic Substring
 *
 * @reference   Longest Palindromic Substring | Set 1
 *              https://www.geeksforgeeks.org/longest-palindrome-substring-set-1/
 *
 * @reference   Longest Palindromic Substring
 *              https://leetcode.com/problems/longest-palindromic-substring/
 *
 * Given a string s, return the longest palindromic substring in s.
 */
constexpr auto LongestPalindromicSubstring_DP(const std::string_view elements) {
    bool LPSs[elements.size()][elements.size()] = {};

    for (std::size_t i = 0; i < elements.size(); ++i) {
        LPSs[i][i] = true;
    }

    std::size_t max_length = 1;
    std::size_t start_position = 0;
    for (std::size_t length = 2; length <= elements.size(); ++length) {
        for (std::size_t i = 0; i <= elements.size() - length; ++i) {
            const auto j = i + length - 1;
            if (elements[i] == elements[j]) {
                if (length == 2 or LPSs[i + 1][j - 1]) {
                    LPSs[i][j] = true;
                    if (length > max_length) {
                        start_position = i;
                        max_length = length;
                    }
                }
            }
        }
    }

    return elements.substr(start_position, max_length);
}


/**
 * @reference   Longest Palindromic Substring | Set 2
 *              https://www.geeksforgeeks.org/longest-palindromic-substring-set-2/
 */
constexpr auto LongestPalindromicSubstring_EvenOddCenter(const std::string_view elements) {
    std::size_t max_length = 1;
    std::size_t start_position = 0;

    for (std::size_t i = 1; i < elements.size(); ++i) {
        for (int is_odd = false; is_odd < 2; ++is_odd) {
            int low = i - 1;
            std::size_t high = i + is_odd;
            for (; low >= 0 and high < elements.size() and elements[low] == elements[high];
                 --low, ++high) {
                const auto length = high - low + 1;
                if (length > max_length) {
                    start_position = low;
                    max_length = length;
                }
            }
        }
    }

    return elements.substr(start_position, max_length);
}


/**
 * @reference   Manacher’s Algorithm – Linear Time Longest Palindromic Substring – Part 1
 *              https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/
 * @reference   Manacher’s Algorithm – Linear Time Longest Palindromic Substring – Part 2
 *              https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-2/
 * @reference   Manacher’s Algorithm – Linear Time Longest Palindromic Substring – Part 3
 *              https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-3-2/
 * @reference   Manacher’s Algorithm – Linear Time Longest Palindromic Substring – Part 4
 *              https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-4/
 *
 * @note    This implement Part 4.
 */
constexpr auto LongestPalindromicSubstring_Manacher(const std::string_view elements) {
    assert(not elements.empty());

    const int position_size = 2 * elements.size() + 1;
    int LPS_lengths[position_size] = {0, 1};
    int center_position = 1;
    int center_right_position = 2;
    int max_length = 0;
    int max_center_position = 0;

    for (int i = 2; i < position_size; ++i) {
        const auto iMirror = 2 * center_position - i;
        LPS_lengths[i] = 0;
        const auto diff = center_right_position - i;

        if (diff > 0) {
            LPS_lengths[i] = std::min(LPS_lengths[iMirror], diff);
        }

        while (
            ((i + LPS_lengths[i]) < position_size and (i - LPS_lengths[i]) > 0) and
            (((i + LPS_lengths[i] + 1) % 2 == 0) or (elements[(i + LPS_lengths[i] + 1) / 2] ==
                                                     elements[(i - LPS_lengths[i] - 1) / 2]))) {
            ++LPS_lengths[i];
        }

        if (LPS_lengths[i] > max_length) {
            max_length = LPS_lengths[i];
            max_center_position = i;
        }

        if (i + LPS_lengths[i] > center_right_position) {
            center_position = i;
            center_right_position = i + LPS_lengths[i];
        }
    }

    const auto start_position = (max_center_position - max_length) / 2;
    return elements.substr(start_position, max_length);
}

} //namespace


constexpr auto SAMPLE1 = "forgeeksskeegfor";
constexpr auto EXPECTED1 = "geeksskeeg";

constexpr auto SAMPLE2 = "abaaba";

constexpr auto SAMPLE3 = "abababa";


THE_BENCHMARK(LongestPalindromicSubstring_DP, SAMPLE1);

SIMPLE_TEST(LongestPalindromicSubstring_DP, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(LongestPalindromicSubstring_DP, TestSAMPLE2, SAMPLE2, SAMPLE2);
SIMPLE_TEST(LongestPalindromicSubstring_DP, TestSAMPLE3, SAMPLE3, SAMPLE3);
SIMPLE_TEST(LongestPalindromicSubstring_DP, TestSAMPLE4, "bab", "babad");
SIMPLE_TEST(LongestPalindromicSubstring_DP, TestSAMPLE5, "bb", "cbbd");


THE_BENCHMARK(LongestPalindromicSubstring_EvenOddCenter, SAMPLE1);

SIMPLE_TEST(LongestPalindromicSubstring_EvenOddCenter, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(LongestPalindromicSubstring_EvenOddCenter, TestSAMPLE2, SAMPLE2, SAMPLE2);
SIMPLE_TEST(LongestPalindromicSubstring_EvenOddCenter, TestSAMPLE3, SAMPLE3, SAMPLE3);
SIMPLE_TEST(LongestPalindromicSubstring_EvenOddCenter, TestSAMPLE4, "bab", "babad");
SIMPLE_TEST(LongestPalindromicSubstring_EvenOddCenter, TestSAMPLE5, "bb", "cbbd");


THE_BENCHMARK(LongestPalindromicSubstring_Manacher, SAMPLE1);

SIMPLE_TEST(LongestPalindromicSubstring_Manacher, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(LongestPalindromicSubstring_Manacher, TestSAMPLE2, SAMPLE2, SAMPLE2);
SIMPLE_TEST(LongestPalindromicSubstring_Manacher, TestSAMPLE3, SAMPLE3, SAMPLE3);
SIMPLE_TEST(LongestPalindromicSubstring_Manacher, TestSAMPLE4, "bab", "babad");
SIMPLE_TEST(LongestPalindromicSubstring_Manacher, TestSAMPLE5, "bb", "cbbd");
