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
 *
 * @reference   Number of Segments in a String
 *              https://leetcode.com/problems/number-of-segments-in-a-string/
 *
 * You are given a string s, return the number of segments in the string. A segment is
 * defined to be a contiguous sequence of non-space characters.
 */
constexpr auto CountWordsInGivenString(const std::string_view input) {
    auto count = 0;
    auto in_word = false;

    for (const auto c : input) {
        if (std::isspace(c)) {
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

    auto count = 0;
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
