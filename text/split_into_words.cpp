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


/**
 * @reference   Occurrences After Bigram
 *              https://leetcode.com/problems/occurrences-after-bigram/
 *
 * Given two strings first and second, consider occurrences in some text of the form
 * "first second third", where second comes immediately after first, and third comes
 * immediately after second. Return an array of all the words third for each occurrence
 * of "first second third".
 * All the words in text a separated by a single space.
 */
auto
WordAfterBigram(const std::string &text, const std::string &first,
                const std::string &second) {
    ArrayType result;
    std::istringstream iss(text);
    std::string current, pre, pre_pre;
    while (iss >> current) {
        if (pre_pre == first and pre == second) {
            result.push_back(current);
        }
        pre_pre = pre;
        pre = current;
    }

    return result;
}


/**
 * @reference   Check If a Word Occurs As a Prefix of Any Word in a Sentence
 *              https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/
 *
 * Given a sentence that consists of some words separated by a single space, and a
 * searchWord, check if searchWord is a prefix of any word in sentence. Return the index
 * of the word in sentence (1-indexed) where searchWord is a prefix of this word. If
 * searchWord is a prefix of more than one word, return the index of the first word
 * (minimum index). If there is no such word return -1. A prefix of a string s is any
 * leading contiguous substring of s.
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


THE_BENCHMARK(CountWordsInGivenString,
              "One two         three\n    four\tfive  ");

SIMPLE_TEST(CountWordsInGivenString, TestSAMPLE1, 5,
            "One two         three\n    four\tfive  ");


THE_BENCHMARK(CountWordsInGivenString_StringStream,
              "One two         three\n    four\tfive  ");

SIMPLE_TEST(CountWordsInGivenString_StringStream, TestSAMPLE1, 5,
            "One two         three\n    four\tfive  ");


const ArrayType EXPECTED1B = {"girl", "student"};
const ArrayType EXPECTED2B = {"we", "rock"};
const ArrayType EXPECTED3B = {"student"};


THE_BENCHMARK(WordAfterBigram, "alice is a good girl she is a good student", "a",
              "good");

SIMPLE_TEST(WordAfterBigram, TestSAMPLE1, EXPECTED1B,
            "alice is a good girl she is a good student", "a", "good");
SIMPLE_TEST(WordAfterBigram, TestSAMPLE2, EXPECTED2B,
            "we will we will rock you", "we", "will");
SIMPLE_TEST(WordAfterBigram, TestSAMPLE3, EXPECTED3B,
            "alice is aa good girl she is a good student", "a", "good");
