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

}//namespace


THE_BENCHMARK(CountStringsWithConsonantAndVowelsAtAlternatePosition, "s$$e$");

SIMPLE_TEST(CountStringsWithConsonantAndVowelsAtAlternatePosition, TestSAMPLE1, 2205,
            "s$$e$");
SIMPLE_TEST(CountStringsWithConsonantAndVowelsAtAlternatePosition, TestSAMPLE2, 5,
            "y$s");
