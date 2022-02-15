#include "common_header.h"

#include "mathematics/numbers/binary/binary.h"


namespace {

/** Longest Nice Substring
 *
 * @reference   https://leetcode.com/problems/longest-nice-substring/
 *
 * A string s is nice if, for every letter of the alphabet that s contains, it appears
 * both in uppercase and lowercase. For example, "abABB" is nice because 'A' and 'a'
 * appear, and 'B' and 'b' appear. However, "abA" is not because 'b' appears, but 'B'
 * does not.
 * Given a string s, return the longest substring of s that is nice. If there are multiple,
 * return the substring of the earliest occurrence. If there are none, return an empty
 * string.
 * 1 <= s.length <= 100
 */
constexpr auto LongestNiceSubstr_BruteForce(const std::string_view s) {
    std::size_t maximum = 0;
    int start = 0;
    for (std::size_t i = 0; i < s.size(); ++i) {
        unsigned lower_mask = 0;
        unsigned upper_mask = 0;
        for (auto j = i; j < s.size(); ++j) {
            const auto c = s[j];

            if (std::islower(c)) {
                lower_mask |= 1 << (c - 'a');
            } else {
                upper_mask |= 1 << (c - 'A');
            }

            if (lower_mask == upper_mask) {
                const auto length = j - i + 1;
                if (length > maximum) {
                    maximum = length;
                    start = i;
                }
            }
        }
    }

    return s.substr(start, maximum);
}


std::string_view LongestNiceSubstr_Recursive(const std::string_view s) {
    if (s.size() < 2) {
        return "";
    }

    std::unordered_set<char> hash(s.cbegin(), s.cend());

    for (std::size_t i = 0; i < s.size(); ++i) {
        const auto c = s[i];
        const auto other = ToggleCase(c);
        if (hash.find(c) == hash.cend() or hash.find(other) == hash.cend()) {
            const auto left = LongestNiceSubstr_Recursive(s.substr(0, i));
            const auto right = LongestNiceSubstr_Recursive(s.substr(i + 1));
            return left.size() >= right.size() ? left : right;
        }
    }

    return s;
}

}//namespace


THE_BENCHMARK(LongestNiceSubstr_BruteForce, "YazaAay");

SIMPLE_TEST(LongestNiceSubstr_BruteForce, TestSAMPLE1, "aAa", "YazaAay");
SIMPLE_TEST(LongestNiceSubstr_BruteForce, TestSAMPLE2, "Bb", "Bb");
SIMPLE_TEST(LongestNiceSubstr_BruteForce, TestSAMPLE3, "", "c");


THE_BENCHMARK(LongestNiceSubstr_Recursive, "YazaAay");

SIMPLE_TEST(LongestNiceSubstr_Recursive, TestSAMPLE1, "aAa", "YazaAay");
SIMPLE_TEST(LongestNiceSubstr_Recursive, TestSAMPLE2, "Bb", "Bb");
SIMPLE_TEST(LongestNiceSubstr_Recursive, TestSAMPLE3, "", "c");
