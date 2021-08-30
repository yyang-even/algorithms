#include "common_header.h"

#include "split_into_words.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Split a sentence into words in C++
 *
 * @reference   https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
 */
auto SplitIntoWords(const std::string_view sentence) {
    ArrayType outputs;
    std::string word;
    auto in_word = false;

    for (const auto c : sentence) {
        if (std::isspace(c)) {
            if (in_word) {
                outputs.push_back(std::move(word));
                word.clear();
                in_word = false;
            }
        } else {
            in_word = true;
            word.push_back(c);
        }
    }

    if (in_word) {
        outputs.push_back(std::move(word));
    }

    return outputs;
}


auto SplitIntoWords_strtok(std::string sentence) {
    ArrayType outputs;
    for (auto *token = std::strtok(sentence.data(), SPACES);
         token != nullptr;
         token = std::strtok(nullptr, SPACES)) {
        outputs.emplace_back(token);
    }

    return outputs;
}


/**
 * @reference   Length of Last Word
 *              https://leetcode.com/problems/length-of-last-word/
 *
 * Given a string s consists of some words separated by spaces, return the length of the
 * last word in the string. If the last word does not exist, return 0. A word is a
 * maximal substring consisting of non-space characters only.
 */


/**
 * @reference   Goat Latin
 *              https://leetcode.com/problems/goat-latin/
 *
 * You are given a string sentence that consist of words separated by spaces. Each word
 * consists of lowercase and uppercase letters only. We would like to convert the
 * sentence to "Goat Latin" (a made-up language similar to Pig Latin.) The rules of Goat
 * Latin are as follows:
 *  If a word begins with a vowel ('a', 'e', 'i', 'o', or 'u'), append "ma" to the end of
 *      the word. For example, the word "apple" becomes "applema".
 *  If a word begins with a consonant (i.e., not a vowel), remove the first letter and
 *      append it to the end, then add "ma". For example, the word "goat" becomes "oatgma".
 *  Add one letter 'a' to the end of each word per its word index in the sentence,
 *      starting with 1. For example, the first word gets "a" added to the end, the
 *      second word gets "aa" added to the end, and so on.
 * Return the final sentence representing the conversion from sentence to Goat Latin.
 */

}//namespace

constexpr auto SplitIntoWords_SS = SplitIntoWords_StringStream<ArrayType>;


const ArrayType EXPECTED1 = {"One", "two", "three", "four", "five"};
const ArrayType EXPECTED2 = {"Geeks", "for", "Geeks"};
const ArrayType EXPECTED3 = {"a", "computer", "science", "portal"};


THE_BENCHMARK(SplitIntoWords, "One two         three\n    four\tfive  ");

SIMPLE_TEST(SplitIntoWords, TestSAMPLE1, EXPECTED1,
            "One two         three\n    four\tfive  ");
SIMPLE_TEST(SplitIntoWords, TestSAMPLE2, EXPECTED2, "Geeks for Geeks");
SIMPLE_TEST(SplitIntoWords, TestSAMPLE3, EXPECTED3, "a computer science portal");


THE_BENCHMARK(SplitIntoWords_strtok, "One two         three\n    four\tfive  ");

SIMPLE_TEST(SplitIntoWords_strtok, TestSAMPLE1, EXPECTED1,
            "One two         three\n    four\tfive  ");
SIMPLE_TEST(SplitIntoWords_strtok, TestSAMPLE2, EXPECTED2, "Geeks for Geeks");
SIMPLE_TEST(SplitIntoWords_strtok, TestSAMPLE3, EXPECTED3, "a computer science portal");


THE_BENCHMARK(SplitIntoWords_SS, "One two         three\n    four\tfive  ");

SIMPLE_TEST(SplitIntoWords_SS, TestSAMPLE1, EXPECTED1,
            "One two         three\n    four\tfive  ");
SIMPLE_TEST(SplitIntoWords_SS, TestSAMPLE2, EXPECTED2, "Geeks for Geeks");
SIMPLE_TEST(SplitIntoWords_SS, TestSAMPLE3, EXPECTED3, "a computer science portal");
