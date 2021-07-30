#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Valid Word Abbreviation
 *
 * @reference   http://buttercola.blogspot.com/2019/01/leetcode-408-valid-word-abbreviation.html
 *
 * Given a non-empty string word and an abbreviation abbr, return whether the string
 * matches with the given abbreviation. A string such as "word" contains only the
 * following valid abbreviations:
 *  ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1",
 *  "w1r1", "1o2", "2r1", "3d", "w3", "4"]
 * Where 1 means one character is omitted, 2 means two characters are omitted, and so on.
 * Notice that only the above abbreviations are valid abbreviations of the string word.
 * Any other string is not a valid abbreviation of word.
 */
constexpr auto
ValidAbbreviation(const std::string_view word, const std::string_view abbreviation) {
    std::size_t word_i = 0, abbr_i = 0;
    while (word_i < word.size() and abbr_i < abbreviation.size()) {
        if (std::isdigit(abbreviation[abbr_i])) {
            if (abbreviation[abbr_i] == '0') {
                return false;
            }

            int value = 0;
            while (abbr_i < abbreviation.size() and std::isdigit(abbreviation[abbr_i])) {
                value = value * 10 + abbreviation[abbr_i++] - '0';
            }

            word_i += value;
        } else {
            if (word[word_i++] != abbreviation[abbr_i++]) {
                return false;
            }
        }
    }

    return word_i == word.size() and abbr_i == abbreviation.size();
}


constexpr auto
ValidAbbreviation_OnePointer(const std::string_view word,
                             const std::string_view abbreviation) {
    std::size_t i = 0, value = 0;
    for (const auto c : abbreviation) {
        if (std::isdigit(c)) {
            if (value == 0 and c == '0') {
                return false;
            }
            value = 10 * value + c - '0';
        } else {
            i += value;
            if (i >= word.size() or word[i++] != c) {
                return false;
            }
            value = 0;
        }
    }

    return i + value == word.size();
}

}//namespace


THE_BENCHMARK(ValidAbbreviation, "word", "4");

SIMPLE_TEST(ValidAbbreviation, TestSAMPLE1, true, "word", "4");
SIMPLE_TEST(ValidAbbreviation, TestSAMPLE2, false, "word", "5");
SIMPLE_TEST(ValidAbbreviation, TestSAMPLE3, true, "internationalization", "i12iz4n");
SIMPLE_TEST(ValidAbbreviation, TestSAMPLE4, false, "apple", "a2e");


THE_BENCHMARK(ValidAbbreviation_OnePointer, "word", "4");

SIMPLE_TEST(ValidAbbreviation_OnePointer, TestSAMPLE1, true, "word", "4");
SIMPLE_TEST(ValidAbbreviation_OnePointer, TestSAMPLE2, false, "word", "5");
SIMPLE_TEST(ValidAbbreviation_OnePointer, TestSAMPLE3, true,
            "internationalization", "i12iz4n");
SIMPLE_TEST(ValidAbbreviation_OnePointer, TestSAMPLE4, false, "apple", "a2e");
