#include "common_header.h"


namespace {

/** Count strings with consonants and vowels at alternate position
 *
 * @reference   Given a string str. The task is to find all possible number of strings
 * that can be obtained by replacing the "$" with alphabets in the given string.
 * Note: Alphabets should be placed in such a way that the string is always alternating
 * in vowels and consonants, and the string must always start with a consonant. It is
 * assumed that such a string is always possible, i.e. There is no need to care about
 * the characters other than "$".
 */
auto CountStringsWithConsonantAndVowelsAtAlternatePosition(const std::string &str) {
    std::string::size_type total = 1ul;

    for (std::string::size_type i = 0ul; i < str.size(); ++i) {
        if (str[i] == '$') {
            total *= (i % 2 ? 5ul : 21ul);
        }
    }

    return total;
}

}//namespace


SIMPLE_BENCHMARK(CountStringsWithConsonantAndVowelsAtAlternatePosition, Sample1,
                 "s$$e$");

SIMPLE_TEST(CountStringsWithConsonantAndVowelsAtAlternatePosition, TestSAMPLE1, 2205ul,
            "s$$e$");
SIMPLE_TEST(CountStringsWithConsonantAndVowelsAtAlternatePosition, TestSAMPLE2, 5ul,
            "y$s");
