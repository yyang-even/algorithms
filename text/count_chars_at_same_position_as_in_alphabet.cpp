#include "common_header.h"


namespace {

/** Count characters at same position as in English alphabet
 *
 * @reference   https://www.geeksforgeeks.org/count-characters-at-same-position-as-in-english-alphabet/
 *
 * Given a string of lower and uppercase characters, the task is to find that how many
 * characters are at same position as in English alphabet.
 */
constexpr auto CountCharsAtSamePositionAsInAlphabet(const std::string_view input) {
    auto count = 0;

    for (int i = 0; static_cast<std::string_view::size_type>(i) < input.size(); ++i) {
        if (i == (input[i] - 'a') or i == (input[i] - 'A')) {
            ++count;
        }
    }

    return count;
}

}//namespace


THE_BENCHMARK(CountCharsAtSamePositionAsInAlphabet, "geeksforgeeks");

SIMPLE_TEST(CountCharsAtSamePositionAsInAlphabet, TestSAMPLE1, 3, "ABcED");
SIMPLE_TEST(CountCharsAtSamePositionAsInAlphabet, TestSAMPLE2, 1, "geeksforgeeks");
SIMPLE_TEST(CountCharsAtSamePositionAsInAlphabet, TestSAMPLE3, 3, "alphabetical");
SIMPLE_TEST(CountCharsAtSamePositionAsInAlphabet, TestSAMPLE4, 5, "AbgdeF");
