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


/**
 * @reference   Greatest Common Divisor of Strings
 *              https://leetcode.com/problems/greatest-common-divisor-of-strings/
 *
 * For two strings s and t, we say "t divides s" if and only if s = t + ... + t  (t
 * concatenated with itself 1 or more times) Given two strings str1 and str2, return
 * the largest string x such that x divides both str1 and str2.
 */
constexpr std::string_view
GCDofStrs(const std::string_view one, const std::string_view another) {
    const int length_gcd = std::gcd(one.size(), another.size());
    for (auto length = length_gcd; length > 0; --length) {
        if (one.size() % length == 0 and another.size() % length == 0 and
            one.substr(0, length) == another.substr(0, length) and
            allSubstrEqual(one, length) and allSubstrEqual(another, length)) {
            return one.substr(0, length);
        }
    }

    return "";
}


std::string GCDofStrs_Concatenate(const std::string &one, const std::string &another) {
    if (one + another != another + one) {
        return "";
    }
    return one.substr(0, std::gcd(one.size(), another.size()));
}


/**
 * @reference   Maximum Repeating Substring
 *              https://leetcode.com/problems/maximum-repeating-substring/
 *
 * For a string sequence, a string word is k-repeating if word concatenated k times is a
 * substring of sequence. The word's maximum k-repeating value is the highest value k
 * where word is k-repeating in sequence. If word is not a substring of sequence, word's
 * maximum k-repeating value is 0.
 * Given strings sequence and word, return the maximum k-repeating value of word in sequence.
 */
auto MaxRepeatingSubstr(const std::string &sequence, const std::string &word) {
    int count = 0;
    auto temp = word;
    std::size_t pos = 0;
    while ((pos = sequence.find(temp, pos)) != std::string::npos) {
        ++count;
        temp.append(word);
    }

    return count;
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


THE_BENCHMARK(GCDofStrs, "ABCABC", "ABC");

SIMPLE_TEST(GCDofStrs, TestSAMPLE1, "ABC", "ABCABC", "ABC");
SIMPLE_TEST(GCDofStrs, TestSAMPLE2, "AB", "ABABAB", "ABAB");
SIMPLE_TEST(GCDofStrs, TestSAMPLE3, "", "LEET", "CODE");
SIMPLE_TEST(GCDofStrs, TestSAMPLE4, "", "ABCDEF", "ABC");


THE_BENCHMARK(GCDofStrs_Concatenate, "ABCABC", "ABC");

SIMPLE_TEST(GCDofStrs_Concatenate, TestSAMPLE1, "ABC", "ABCABC", "ABC");
SIMPLE_TEST(GCDofStrs_Concatenate, TestSAMPLE2, "AB", "ABABAB", "ABAB");
SIMPLE_TEST(GCDofStrs_Concatenate, TestSAMPLE3, "", "LEET", "CODE");
SIMPLE_TEST(GCDofStrs_Concatenate, TestSAMPLE4, "", "ABCDEF", "ABC");


THE_BENCHMARK(MaxRepeatingSubstr, "ababc", "ab");

SIMPLE_TEST(MaxRepeatingSubstr, TestSAMPLE1, 2, "ababc", "ab");
SIMPLE_TEST(MaxRepeatingSubstr, TestSAMPLE2, 1, "ababc", "ba");
SIMPLE_TEST(MaxRepeatingSubstr, TestSAMPLE3, 0, "ababc", "ac");
SIMPLE_TEST(MaxRepeatingSubstr, TestSAMPLE4, 5,
            "aaabaaaabaaabaaaabaaaabaaaabaaaaba", "aaaba");
SIMPLE_TEST(MaxRepeatingSubstr, TestSAMPLE5, 1, "a", "a");
