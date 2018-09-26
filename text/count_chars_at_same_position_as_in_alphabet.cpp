#include "common_header.h"

/** Count characters at same position as in English alphabet
 *
 * @reference   https://www.geeksforgeeks.org/count-characters-at-same-position-as-in-english-alphabet/
 *
 * Given a string of lower and uppercase characters, the task is to find
 * that how many characters are at same position as in English alphabet.
 */
auto CountCharsAtSamePositionAsInAlphabet(const std::string &input) {
    std::string::size_type count = 0ul;

    for(std::string::size_type i = 0; i < input.size(); ++i) {
        if(i == input[i] - 'a' or i == input[i] - 'A') {
            ++count;
        }
    }

    return count;
}


SIMPLE_BENCHMARK(CountCharsAtSamePositionAsInAlphabet, std::string("geeksforgeeks"));

SIMPLE_TEST(CountCharsAtSamePositionAsInAlphabet, TestSAMPLE1, 3ul, std::string("ABcED"));
SIMPLE_TEST(CountCharsAtSamePositionAsInAlphabet, TestSAMPLE2, 1ul, std::string("geeksforgeeks"));
SIMPLE_TEST(CountCharsAtSamePositionAsInAlphabet, TestSAMPLE3, 3ul, std::string("alphabetical"));
SIMPLE_TEST(CountCharsAtSamePositionAsInAlphabet, TestSAMPLE4, 5ul, std::string("AbgdeF"));
