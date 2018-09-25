#include "common_header.h"

/** Count words in a given string
 *
 * @reference   https://www.geeksforgeeks.org/count-words-in-a-given-string/
 *
 * Given a string, count number of words in it. The words are separated by following
 * characters: space (' ') or new line ('\n') or tab ('\t') or a combination of these.
 */
auto CountWordsInGivenString(const std::string &input){
    std::string::size_type count = 0ul;
    bool in_word = false;

    for(const auto c: input){
        if(c == ' ' or c == '\n' or c == '\t') {
            in_word = false;
        } else if (not in_word) {
            in_word = true;
            ++count;
        }
    }

    return count;
}


SIMPLE_BENCHMARK(CountWordsInGivenString, std::string("One two         three\n    four\tfive  "));

SIMPLE_TEST(CountWordsInGivenString, TestSAMPLE1, 5ul, std::string("One two         three\n    four\tfive  "));
