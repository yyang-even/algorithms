#include "common_header.h"

#include "hash/hash.h"


namespace {

/** Longest Palindrome
 *
 * @reference   https://leetcode.com/problems/longest-palindrome/
 *
 * Given a string s which consists of lowercase or uppercase letters, return the length
 * of the longest palindrome that can be built with those letters. Letters are case
 * sensitive, for example, "Aa" is not considered a palindrome here.
 */
constexpr auto LongestPalindrome(const std::string_view text) {
    int counts[256] = {};
    int count_odd = 0;

    for (const int c : text) {
        if (++counts[c] & 1) {
            ++count_odd;
        } else {
            --count_odd;
        }
    }

    if (count_odd) {
        return text.size() + 1 - count_odd;
    }
    return text.size();
}


auto LongestPalindrome_TwoLoop(const std::string_view text) {
    const auto counts = ToFrequencyHashTable(text);

    std::size_t result = 0;
    for (const auto [_, a_count] : counts) {
        result += (a_count >> 1 << 1);
    }

    return result + (text.size() > result);
}

}//namespace


THE_BENCHMARK(LongestPalindrome, "abccccdd");

SIMPLE_TEST(LongestPalindrome, TestSAMPLE1, 7, "abccccdd");
SIMPLE_TEST(LongestPalindrome, TestSAMPLE2, 1, "a");
SIMPLE_TEST(LongestPalindrome, TestSAMPLE3, 2, "bb");


THE_BENCHMARK(LongestPalindrome_TwoLoop, "abccccdd");

SIMPLE_TEST(LongestPalindrome_TwoLoop, TestSAMPLE1, 7, "abccccdd");
SIMPLE_TEST(LongestPalindrome_TwoLoop, TestSAMPLE2, 1, "a");
SIMPLE_TEST(LongestPalindrome_TwoLoop, TestSAMPLE3, 2, "bb");
