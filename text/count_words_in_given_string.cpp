#include "common_header.h"


namespace {

/** Count words in a given string
 *
 * @reference   https://www.geeksforgeeks.org/count-words-in-a-given-string/
 * @reference   stringstream in C++ and its applications
 *              https://www.geeksforgeeks.org/stringstream-c-applications/
 *
 * Given a string, count number of words in it. The words are separated by following
 * characters: space (' ') or new line ('\n') or tab ('\t') or a combination of these.
 */
auto CountWordsInGivenString(const std::string &input) {
    std::string::size_type count = 0;
    auto in_word = false;

    for (const auto c : input) {
        if (c == ' ' or c == '\n' or c == '\t') {
            in_word = false;
        } else if (not in_word) {
            in_word = true;
            ++count;
        }
    }

    return count;
}


auto CountWordsInGivenString_StringStream(const std::string &input) {
    std::stringstream ss(input);

    std::string::size_type count = 0;
    for (std::string word; ss >> word; ++count);

    return count;
}

}//namespace


THE_BENCHMARK(CountWordsInGivenString,
              "One two         three\n    four\tfive  ");

SIMPLE_TEST(CountWordsInGivenString, TestSAMPLE1, 5,
            "One two         three\n    four\tfive  ");


THE_BENCHMARK(CountWordsInGivenString_StringStream,
              "One two         three\n    four\tfive  ");

SIMPLE_TEST(CountWordsInGivenString_StringStream, TestSAMPLE1, 5,
            "One two         three\n    four\tfive  ");
