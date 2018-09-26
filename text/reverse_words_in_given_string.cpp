#include "common_header.h"

/** Reverse words in a given string
 *
 * @reference   https://www.geeksforgeeks.org/reverse-words-in-a-given-string/
 *
 * Example: Let the input string be “i like this program very much”. The
 * function should change the string to “much very program this like i”
 */
auto ReverseWordsInGivenString(std::string input){
    auto word_begin = input.begin();
    bool in_word = false;

    for(auto iter = input.begin(); iter != input.end();){
        if(not in_word and *iter != ' ') {
            word_begin = iter;
            in_word = true;
        } 
        ++iter;
        if (in_word and (iter == input.end() or *iter == ' ')) {
            in_word = false;
            std::reverse(word_begin, iter);
        }
    }

    std::reverse(input.begin(), input.end());

    return input;
}


SIMPLE_BENCHMARK(ReverseWordsInGivenString, std::string("geeks quiz practice code"));

SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE1, std::string("code practice quiz geeks"), std::string("geeks quiz practice code"));
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE2, std::string("practice of lot a needs coding at good getting"), std::string("getting good at coding needs a lot of practice"));
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE3, std::string("much very program this like i"), std::string("i like this program very much"));
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE4, std::string("  much very  "), std::string("  very much  "));
