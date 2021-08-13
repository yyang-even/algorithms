#include "common_header.h"


namespace {

/** Flip String to Monotone Increasing
 *
 * @reference   https://leetcode.com/problems/flip-string-to-monotone-increasing/
 *
 * A binary string is monotone increasing if it consists of some number of 0's (possibly
 * none), followed by some number of 1's (also possibly none). You are given a binary
 * string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0. Return the minimum
 * number of flips to make s monotone increasing.
 */
constexpr auto FlipStringToMonotoneIncreasing_DP(const std::string_view binary) {
    const int N = binary.size();

    int prefix_sum[N + 1] = {};
    for (int i = 0; i < N; ++i) {
        prefix_sum[i + 1] = prefix_sum[i] + (binary[i] == '1' ? 1 : 0);
    }

    auto result = INT_MAX;
    for (int i = 0; i <= N; ++i) {
        result = std::min(result, prefix_sum[i] + N - i - (prefix_sum[N] - prefix_sum[i]));
    }

    return result;
}


constexpr auto FlipStringToMonotoneIncreasing(const std::string_view binary) {
    int one = 0;
    int flip = 0;

    for (std::size_t i = 0; i < binary.size(); ++i) {
        if (binary[i] == '1') {
            ++one;
        } else {
            ++flip;
        }
        flip = std::min(one, flip);
    }

    return flip;
}

}//namespace


THE_BENCHMARK(FlipStringToMonotoneIncreasing_DP, "10011111110010111011");

SIMPLE_TEST(FlipStringToMonotoneIncreasing_DP, TestSAMPLE1, 1, "00110");
SIMPLE_TEST(FlipStringToMonotoneIncreasing_DP, TestSAMPLE2, 2, "010110");
SIMPLE_TEST(FlipStringToMonotoneIncreasing_DP, TestSAMPLE3, 2, "00011000");
SIMPLE_TEST(FlipStringToMonotoneIncreasing_DP, TestSAMPLE4, 0, "00000");
SIMPLE_TEST(FlipStringToMonotoneIncreasing_DP, TestSAMPLE5, 0, "11111");
SIMPLE_TEST(FlipStringToMonotoneIncreasing_DP, TestSAMPLE6, 3, "0101100011");
SIMPLE_TEST(FlipStringToMonotoneIncreasing_DP, TestSAMPLE7, 5, "10011111110010111011");


THE_BENCHMARK(FlipStringToMonotoneIncreasing, "10011111110010111011");

SIMPLE_TEST(FlipStringToMonotoneIncreasing, TestSAMPLE1, 1, "00110");
SIMPLE_TEST(FlipStringToMonotoneIncreasing, TestSAMPLE2, 2, "010110");
SIMPLE_TEST(FlipStringToMonotoneIncreasing, TestSAMPLE3, 2, "00011000");
SIMPLE_TEST(FlipStringToMonotoneIncreasing, TestSAMPLE4, 0, "00000");
SIMPLE_TEST(FlipStringToMonotoneIncreasing, TestSAMPLE5, 0, "11111");
SIMPLE_TEST(FlipStringToMonotoneIncreasing, TestSAMPLE6, 3, "0101100011");
SIMPLE_TEST(FlipStringToMonotoneIncreasing, TestSAMPLE7, 5, "10011111110010111011");
