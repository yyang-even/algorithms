#include "common_header.h"


namespace {

/** Reverse words in a given string
 *
 * @reference   https://www.geeksforgeeks.org/reverse-words-in-a-given-string/
 *
 * Example: Let the input string be "i like this program very much". The function should
 * change the string to "much very program this like i".
 *
 * @reference   Print words of a string in reverse order
 *              https://www.geeksforgeeks.org/print-words-string-reverse-order/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 6.
 *
 * @reference   Reverse Words in a String II
 *              https://evanyang.gitbooks.io/leetcode/content/LeetCode/reverse_words_in_a_string_ii.html
 *
 * Given an input string, reverse the string word by word. A word is defined as a sequence
 * of non-space characters. The input string does not contain leading or trailing spaces
 * and the words are always separated by a single space. For example, Given s = "the sky
 * is blue", return "blue is sky the". Could you do it in-place without allocating extra
 * space?
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
 *
 * @reference   Reverse Words in a String
 *              https://leetcode.com/problems/reverse-words-in-a-string/
 *
 * Given an input string s, reverse the order of the words. A word is defined as a
 * sequence of non-space characters. The words in s will be separated by at least one
 * space. Return a string of the words in reverse order concatenated by a single space.
 * Note that s may contain leading or trailing spaces or multiple spaces between two
 * words. The returned string should only have a single space separating the words. Do
 * not include any extra spaces.
 * There is at least one word in s.
 * Follow-up: If the string data type is mutable in your language, can you solve it
 * in-place with O(1) extra space?
 * @hint    Remove extra spaces first.
 */
auto ReverseWordsInGivenString_Stack(std::string input) {
    std::stack<const char *> words_stack;
    for (auto *token = std::strtok(input.data(), SPACES);
         token != nullptr;
         token = std::strtok(nullptr, SPACES)) {
        words_stack.push(token);
    }

    std::string output;
    for (; not words_stack.empty(); words_stack.pop()) {
        if (not output.empty()) {
            output.push_back(' ');
        }
        output.append(words_stack.top());
    }

    return output;
}


auto ReverseWordsInGivenString_SS(const std::string &s) {
    std::stringstream ss{s};

    std::string result;
    for (std::string word; ss >> word;) {
        std::reverse(word.begin(), word.end());
        result += word + " ";
    }
    result.pop_back();

    std::reverse(result.begin(), result.end());
    return result;
}

}//namespace


THE_BENCHMARK(ReverseWordsInGivenString, "geeks quiz practice code");

SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE1, "code practice quiz geeks",
            "geeks quiz practice code");
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE2,
            "practice of lot a needs coding at good getting",
            "getting good at coding needs a lot of practice");
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE3, "much very program this like i",
            "i like this program very much");
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE4, "  much very  ", "  very much  ");
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE5, "the sky is blue",
            "blue is sky the");
SIMPLE_TEST(ReverseWordsInGivenString, TestSAMPLE6, "Alice does not even like bob",
            "bob like even not does Alice");


THE_BENCHMARK(ReverseWordsInGivenString_Stack, "geeks quiz practice code");

SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE1, "code practice quiz geeks",
            "geeks quiz practice code");
SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE2,
            "practice of lot a needs coding at good getting",
            "getting good at coding needs a lot of practice");
SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE3,
            "much very program this like i",
            "i like this program very much");
SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE4, "much very", "  very much  ");
SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE5, "the sky is blue",
            "blue is sky the");
SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE6,
            "Alice does not even like bob",
            "bob like even not does Alice");
SIMPLE_TEST(ReverseWordsInGivenString_Stack, TestSAMPLE7, "example good a",
            "a good   example");


THE_BENCHMARK(ReverseWordsInGivenString_SS, "geeks quiz practice code");

SIMPLE_TEST(ReverseWordsInGivenString_SS, TestSAMPLE1, "code practice quiz geeks",
            "geeks quiz practice code");
SIMPLE_TEST(ReverseWordsInGivenString_SS, TestSAMPLE2,
            "practice of lot a needs coding at good getting",
            "getting good at coding needs a lot of practice");
SIMPLE_TEST(ReverseWordsInGivenString_SS, TestSAMPLE3,
            "much very program this like i",
            "i like this program very much");
SIMPLE_TEST(ReverseWordsInGivenString_SS, TestSAMPLE4, "much very", "  very much  ");
SIMPLE_TEST(ReverseWordsInGivenString_SS, TestSAMPLE5, "the sky is blue",
            "blue is sky the");
SIMPLE_TEST(ReverseWordsInGivenString_SS, TestSAMPLE6,
            "Alice does not even like bob",
            "bob like even not does Alice");
SIMPLE_TEST(ReverseWordsInGivenString_SS, TestSAMPLE7, "example good a",
            "a good   example");
