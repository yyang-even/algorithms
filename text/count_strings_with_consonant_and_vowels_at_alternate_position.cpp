#include "common_header.h"


namespace {

/** Count strings with consonants and vowels at alternate position
 *
 * @reference   https://www.geeksforgeeks.org/count-strings-with-consonants-and-vowels-at-alternate-position/
 *
 * Given a string str. The task is to find all possible number of strings that can be
 * obtained by replacing the "$" with alphabets in the given string. Note: Alphabets
 * should be placed in such a way that the string is always alternating in vowels and
 * consonants, and the string must always start with a consonant. It is assumed that
 * such a string is always possible, i.e. There is no need to care about the characters
 * other than "$".
 */
inline constexpr auto
CountStringsWithConsonantAndVowelsAtAlternatePosition(const std::string_view str) {
    std::size_t total = 1;

    for (std::size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '$') {
            total *= (i % 2 ? 5 : 21);
        }
    }

    return total;
}


/**
 * @reference   Minimum Changes To Make Alternating Binary String
 *              https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/
 *
 * You are given a string s consisting only of the characters '0' and '1'. In one
 * operation, you can change any '0' to '1' or vice versa.
 * The string is called alternating if no two adjacent characters are equal. For example,
 * the string "010" is alternating, while the string "0100" is not.
 * Return the minimum number of operations needed to make s alternating.
 */
constexpr auto MinChanges(const std::string_view s) {
    const int N = s.size();
    int diff = 0;
    for (int i = 0; i < N; ++i) {
        if (s[i] - '0' != i % 2) {
            ++diff;
        }
    }

    return std::min(diff, N - diff);
}

}//namespace


THE_BENCHMARK(CountStringsWithConsonantAndVowelsAtAlternatePosition, "s$$e$");

SIMPLE_TEST(CountStringsWithConsonantAndVowelsAtAlternatePosition, TestSAMPLE1, 2205,
            "s$$e$");
SIMPLE_TEST(CountStringsWithConsonantAndVowelsAtAlternatePosition, TestSAMPLE2, 5,
            "y$s");


THE_BENCHMARK(MinChanges, "0100");

SIMPLE_TEST(MinChanges, TestSAMPLE1, 1, "0100");
SIMPLE_TEST(MinChanges, TestSAMPLE2, 0, "10");
SIMPLE_TEST(MinChanges, TestSAMPLE3, 2, "1111");
