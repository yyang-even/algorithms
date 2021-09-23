#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Break a Palindrome
 *
 * @reference   https://leetcode.com/problems/break-a-palindrome/
 *
 * Given a palindromic string of lowercase English letters palindrome, replace exactly
 * one character with any lowercase English letter so that the resulting string is not
 * a palindrome and that it is the lexicographically smallest one possible. Return the
 * resulting string. If there is no way to replace a character to make it not a
 * palindrome, return an empty string. A string a is lexicographically smaller than a
 * string b (of the same length) if in the first position where a and b differ, a has a
 * character strictly smaller than the corresponding character in b. For example, "abcc"
 * is lexicographically smaller than "abcd" because the first position they differ is at
 * the fourth character, and 'c' is smaller than 'd'.
 */
std::string BreakPalindrome(std::string palindrome) {
    const auto size = palindrome.size();
    if (size <= 1) {
        return "";
    }

    for (std::size_t i = 0; i < size / 2; ++i) {
        if (palindrome[i] != 'a') {
            palindrome[i] = 'a';
            return palindrome;
        }
    }

    palindrome.back() = 'b';
    return palindrome;
}

}//namespace


THE_BENCHMARK(BreakPalindrome, "abccba");

SIMPLE_TEST(BreakPalindrome, TestSAMPLE1, "aaccba", "abccba");
SIMPLE_TEST(BreakPalindrome, TestSAMPLE2, "", "a");
SIMPLE_TEST(BreakPalindrome, TestSAMPLE3, "ab", "aa");
SIMPLE_TEST(BreakPalindrome, TestSAMPLE4, "abb", "aba");
