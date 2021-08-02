#include "common_header.h"


namespace {

/** License Key Formatting
 *
 * @reference   https://leetcode.com/problems/license-key-formatting/
 *
 * You are given a license key represented as a string s that consists of only
 * alphanumeric characters and dashes. The string is separated into n + 1 groups by n
 * dashes. You are also given an integer k. We want to reformat the string s such that
 * each group contains exactly k characters, except for the first group, which could be
 * shorter than k but still must contain at least one character. Furthermore, there must
 * be a dash inserted between two groups, and you should convert all lowercase letters
 * to uppercase. Return the reformatted license key.
 */
auto LicenseKeyFormatting(const std::string_view s, const int K) {
    std::string result;
    int count = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] != '-') {
            if (count++ % K == 0) {
                result.push_back('-');
            }
            result.push_back(std::toupper(s[i]));
        }
    }

    std::reverse(result.begin(), result.end());
    if (not result.empty()) {
        result.pop_back();
    }
    return result;
}

}//namespace


THE_BENCHMARK(LicenseKeyFormatting, "5F3Z-2e-9-w", 4);

SIMPLE_TEST(LicenseKeyFormatting, TestSAMPLE1, "5F3Z-2E9W", "5F3Z-2e-9-w", 4);
SIMPLE_TEST(LicenseKeyFormatting, TestSAMPLE2, "2-5G-3J", "2-5g-3-J", 2);
