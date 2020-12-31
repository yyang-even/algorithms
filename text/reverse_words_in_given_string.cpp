#include "common_header.h"


namespace {

/** Reverse words in a given string
 *
 * @reference   https://www.geeksforgeeks.org/reverse-words-in-a-given-string/
 *
 * Example: Let the input string be “i like this program very much”. The
 * function should change the string to “much very program this like i”
 *
 * @reference   Print words of a string in reverse order
 *              https://www.geeksforgeeks.org/print-words-string-reverse-order/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 6.
 */
auto ReverseWordsInGivenString(std::string input) {
    auto word_begin = input.begin();
    auto in_word = false;

    for (auto iter = input.begin(); iter != input.end();) {
        if (not in_word and * iter != ' ') {
            word_begin = iter;
            in_word = true;
        }
        ++iter;
        if (in_word and (iter == input.end() or * iter == ' ')) {
            in_word = false;
            std::reverse(word_begin, iter);
        }
    }

    std::reverse(input.begin(), input.end());

    return input;
}


/**
 * @reference   Reverse the Sentence using Stack
 *              https://www.geeksforgeeks.org/reverse-the-sentence-using-stack/
 */
auto ReverseWordsInGivenString_Stack(std::string input) {
    static const auto *delimiters = " ";

    std::stack<const char *> words_stack;
    for (auto *token = std::strtok(const_cast<char *>(input.c_str()), delimiters);
         token != nullptr;
         token = std::strtok(nullptr, delimiters)) {
        words_stack.push(token);
    }

    std::string output;
    for (; not words_stack.empty(); words_stack.pop()) {
        if (not output.empty()) {
            output.append(1, ' ');
        }
        output.append(words_stack.top());
    }

    return output;
}

}//namespace


SIMPLE_BENCHMARK(ReverseWordsInGivenString, Sample1, "geeks quiz practice code");

SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE1, "code practice quiz geeks",
            "geeks quiz practice code");
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE2,
            "practice of lot a needs coding at good getting",
            "getting good at coding needs a lot of practice");
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE3, "much very program this like i",
            "i like this program very much");
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE4, "  much very  ", "  very much  ");


SIMPLE_BENCHMARK(ReverseWordsInGivenString_Stack, Sample1, "geeks quiz practice code");

SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE1, "code practice quiz geeks",
            "geeks quiz practice code");
SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE2,
            "practice of lot a needs coding at good getting",
            "getting good at coding needs a lot of practice");
SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE3,
            "much very program this like i",
            "i like this program very much");
SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE4, "much very", "  very much  ");
