#include "common_header.h"


namespace {

/** Maximum Score After Splitting a String
 *
 * @reference   https://leetcode.com/problems/maximum-score-after-splitting-a-string/
 *
 * Given a string s of zeros and ones, return the maximum score after splitting the
 * string into two non-empty substrings (i.e. left substring and right substring). The
 * score after splitting a string is the number of zeros in the left substring plus the
 * number of ones in the right substring.
 */
auto MaxScore(const std::string_view s) {
    int right_ones = 0, left_zeros = 0;
    for (const auto c : s) {
        right_ones += c - '0';
    }

    int score = 0;
    for (std::size_t i = 0; i < s.size() - 1; ++i) {
        if (s[i] == '0') {
            ++left_zeros;
        } else {
            --right_ones;
        }
        score = std::max(score, left_zeros + right_ones);
    }

    return score;
}

}//namespace


THE_BENCHMARK(MaxScore, "011101");

SIMPLE_TEST(MaxScore, TestSAMPLE1, 5, "011101");
SIMPLE_TEST(MaxScore, TestSAMPLE2, 5, "00111");
SIMPLE_TEST(MaxScore, TestSAMPLE3, 3, "1111");
SIMPLE_TEST(MaxScore, TestSAMPLE4, 1, "00");
