#include "common_header.h"


namespace {

/** Repeated Substring Pattern
 *
 * @reference   https://leetcode.com/problems/repeated-substring-pattern/
 *
 * Given a string s, check if it can be constructed by taking a substring of it and
 * appending multiple copies of the substring together.
 *
 * @reference   Find if a given string can be represented from a substring by iterating the substring “n” times
 *              https://www.geeksforgeeks.org/find-given-string-can-represented-substring-iterating-substring-n-times/
 */
inline auto RepeatedSubstrPattern_Concatenate(const std::string &str) {
    const auto concatenate = str + str.substr(0, str.size() - 1);
    return concatenate.find(str, 1) != std::string::npos;
}


constexpr auto allSubstrEqual(const std::string_view s, const std::size_t length) {
    if (s.size() % length != 0) {
        return false;
    }

    for (auto i = length; i < s.size(); i += length) {
        if (s.substr(0, length) != s.substr(i, length)) {
            return false;
        }
    }
    return true;
}

constexpr auto RepeatedSubstrPattern_Length(const std::string_view s) {
    for (std::size_t length = 1; length <= s.size() / 2; ++length) {
        if (allSubstrEqual(s, length)) {
            return true;
        }
    }

    return false;
}


constexpr auto RepeatedSubstrPattern_KMP(const std::string_view str) {
    const auto N = str.size();
    int LPS[N] = {};

    int j = 0;
    for (std::size_t i = 1; i < N;) {
        if (str[i] == str[j]) {
            LPS[i++] = ++j;
        } else {
            if (j != 0) {
                j = LPS[j - 1];
            } else {
                LPS[i++] = 0;
            }
        }
    }

    return LPS[N - 1] and (LPS[N - 1] % (N - LPS[N - 1]) == 0);
}

}//namespace


THE_BENCHMARK(RepeatedSubstrPattern_Concatenate, "abcabcabcabc");

SIMPLE_TEST(RepeatedSubstrPattern_Concatenate, TestSAMPLE1, true, "abcabcabcabc");
SIMPLE_TEST(RepeatedSubstrPattern_Concatenate, TestSAMPLE2, true, "abab");
SIMPLE_TEST(RepeatedSubstrPattern_Concatenate, TestSAMPLE3, true, "ababab");
SIMPLE_TEST(RepeatedSubstrPattern_Concatenate, TestSAMPLE4, true, "abcabcabc");
SIMPLE_TEST(RepeatedSubstrPattern_Concatenate, TestSAMPLE5, false, "aba");
SIMPLE_TEST(RepeatedSubstrPattern_Concatenate, TestSAMPLE6, false, "aaacaaaa");


THE_BENCHMARK(RepeatedSubstrPattern_Length, "abcabcabcabc");

SIMPLE_TEST(RepeatedSubstrPattern_Length, TestSAMPLE1, true, "abcabcabcabc");
SIMPLE_TEST(RepeatedSubstrPattern_Length, TestSAMPLE2, true, "abab");
SIMPLE_TEST(RepeatedSubstrPattern_Length, TestSAMPLE3, true, "ababab");
SIMPLE_TEST(RepeatedSubstrPattern_Length, TestSAMPLE4, true, "abcabcabc");
SIMPLE_TEST(RepeatedSubstrPattern_Length, TestSAMPLE5, false, "aba");
SIMPLE_TEST(RepeatedSubstrPattern_Length, TestSAMPLE6, false, "aaacaaaa");


THE_BENCHMARK(RepeatedSubstrPattern_KMP, "abcabcabcabc");

SIMPLE_TEST(RepeatedSubstrPattern_KMP, TestSAMPLE1, true, "abcabcabcabc");
SIMPLE_TEST(RepeatedSubstrPattern_KMP, TestSAMPLE2, true, "abab");
SIMPLE_TEST(RepeatedSubstrPattern_KMP, TestSAMPLE3, true, "ababab");
SIMPLE_TEST(RepeatedSubstrPattern_KMP, TestSAMPLE4, true, "abcabcabc");
SIMPLE_TEST(RepeatedSubstrPattern_KMP, TestSAMPLE5, false, "aba");
SIMPLE_TEST(RepeatedSubstrPattern_KMP, TestSAMPLE6, false, "aaacaaaa");
