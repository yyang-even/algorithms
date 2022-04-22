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


/**
 * @reference   Counting Words With a Given Prefix
 *              https://leetcode.com/problems/counting-words-with-a-given-prefix/
 *
 * You are given an array of strings words and a string pref.
 * Return the number of strings in words that contain pref as a prefix.
 * A prefix of a string s is any leading contiguous substring of s.
 */


/**
 * @reference   Rearrange Spaces Between Words
 *              https://leetcode.com/problems/rearrange-spaces-between-words/
 *
 * You are given a string text of words that are placed among some number of spaces. Each
 * word consists of one or more lowercase English letters and are separated by at least
 * one space. It's guaranteed that text contains at least one word.
 * Rearrange the spaces so that there is an equal number of spaces between every pair of
 * adjacent words and that number is maximized. If you cannot redistribute all the spaces
 * equally, place the extra spaces at the end, meaning the returned string should be the
 * same length as text.
 * Return the string after rearranging the spaces.
 */
auto RearrangeSpaces(const std::string_view text) {
    int spaces = 0;
    std::string a_word;
    std::vector<std::string> words;
    for (const auto c : text) {
        if (c == ' ') {
            ++spaces;
            if (not a_word.empty()) {
                words.push_back(a_word);
            }
            a_word.clear();
        } else {
            a_word.push_back(c);
        }
    }
    if (not a_word.empty()) {
        words.push_back(a_word);
    }

    if (words.size() == 1) {
        return words.back() + std::string(spaces, ' ');
    }

    const auto gap = spaces / (words.size() - 1);
    const auto extra = spaces % (words.size() - 1);
    auto result = words.front();
    for (std::size_t i = 1; i < words.size(); ++i) {
        result += std::string(gap, ' ') + words[i];
    }
    return result + std::string(extra, ' ');
}


/**
 * @reference   Number of Different Integers in a String
 *              https://leetcode.com/problems/number-of-different-integers-in-a-string/
 *
 * You are given a string word that consists of digits and lowercase English letters.
 * You will replace every non-digit character with a space. For example, "a123bc34d8ef34"
 * will become " 123  34 8  34". Notice that you are left with some integers that are
 * separated by at least one space: "123", "34", "8", and "34".
 * Return the number of different integers after performing the replacement operations on
 * word.
 * Two integers are considered different if their decimal representations without any
 * leading zeros are different.
 */
auto NumDiffInts(const std::string_view s) {
    std::unordered_set<std::string_view> hash{""};

    std::size_t i = 0, j = 0;
    for (; j < s.size(); ++j) {
        if (std::isdigit(s[j])) {
            if (i < j and s[i] == '0') {
                ++i;
            }
        } else {
            hash.insert(s.substr(i, j - i));
            i = j + 1;
        }
    }
    hash.insert(s.substr(i, j - i));

    return hash.size() - 1;
}


/**
 * @reference   Truncate Sentence
 *              https://leetcode.com/problems/truncate-sentence/
 *
 * A sentence is a list of words that are separated by a single space with no leading or
 * trailing spaces. Each of the words consists of only uppercase and lowercase English
 * letters (no punctuation).
 * For example, "Hello World", "HELLO", and "hello world hello world" are all sentences.
 * You are given a sentence s and an integer k. You want to truncate s such that it
 * contains only the first k words. Return s after truncating it.
 */


/**
 * @reference   Sorting the Sentence
 *              https://leetcode.com/problems/sorting-the-sentence/
 *
 * A sentence is a list of words that are separated by a single space with no leading or
 * trailing spaces. Each word consists of lowercase and uppercase English letters.
 * A sentence can be shuffled by appending the 1-indexed word position to each word then
 * rearranging the words in the sentence.
 *  For example, the sentence "This is a sentence" can be shuffled as "sentence4 a3 is2
 *      This1" or "is2 sentence4 This1 a3".
 * Given a shuffled sentence s containing no more than 9 words, reconstruct and return
 * the original sentence.
 */


/**
 * @reference   Maximum Number of Words You Can Type
 *              https://leetcode.com/problems/maximum-number-of-words-you-can-type/
 *
 * There is a malfunctioning keyboard where some letter keys do not work. All other keys
 * on the keyboard work properly.
 * Given a string text of words separated by a single space (no leading or trailing spaces)
 * and a string brokenLetters of all distinct letter keys that are broken, return the number
 * of words in text you can fully type using this keyboard.
 */


/**
 * @reference   Check if Numbers Are Ascending in a Sentence
 *              https://leetcode.com/problems/check-if-numbers-are-ascending-in-a-sentence/
 *
 * A sentence is a list of tokens separated by a single space with no leading or trailing
 * spaces. Every token is either a positive number consisting of digits 0-9 with no leading
 * zeros, or a word consisting of lowercase English letters.
 * For example, "a puppy has 2 eyes 4 legs" is a sentence with seven tokens: "2" and "4"
 * are numbers and the other tokens such as "puppy" are words.
 * Given a string s representing a sentence, you need to check if all the numbers in s are
 * strictly increasing from left to right (i.e., other than the last number, each number
 * is strictly smaller than the number on its right in s).
 * Return true if so, or false otherwise.
 */


/**
 * @reference   Maximum Number of Words Found in Sentences
 *              https://leetcode.com/problems/maximum-number-of-words-found-in-sentences/
 *
 * A sentence is a list of words that are separated by a single space with no leading or
 * trailing spaces.
 * You are given an array of strings sentences, where each sentences[i] represents a single
 * sentence.
 * Return the maximum number of words that appear in a single sentence.
 */


/**
 * @reference   Capitalize the Title
 *              https://leetcode.com/problems/capitalize-the-title/
 *
 * You are given a string title consisting of one or more words separated by a single
 * space, where each word consists of English letters. Capitalize the string by changing
 * the capitalization of each word such that:
 *  If the length of the word is 1 or 2 letters, change all letters to lowercase.
 *  Otherwise, change the first letter to uppercase and the remaining letters to lowercase.
 * Return the capitalized title.
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


THE_BENCHMARK(RearrangeSpaces, "  this   is  a sentence ");

SIMPLE_TEST(RearrangeSpaces, TestSAMPLE1, "this   is   a   sentence",
            "  this   is  a sentence ");
SIMPLE_TEST(RearrangeSpaces, TestSAMPLE2, "practice   makes   perfect ",
            " practice   makes   perfect");


THE_BENCHMARK(NumDiffInts, "a123bc34d8ef34");

SIMPLE_TEST(NumDiffInts, TestSAMPLE1, 3, "a123bc34d8ef34");
SIMPLE_TEST(NumDiffInts, TestSAMPLE2, 2, "leet1234code234");
SIMPLE_TEST(NumDiffInts, TestSAMPLE3, 1, "a1b01c001");
