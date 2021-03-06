#include "common_header.h"


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


auto SplitIntoWords_StringStream(const std::string &sentence) {
    std::stringstream ss(sentence);

    ArrayType outputs;
    for (std::string word; ss >> word;) {
        outputs.push_back(std::move(word));
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

}//namespace


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


THE_BENCHMARK(SplitIntoWords_StringStream, "One two         three\n    four\tfive  ");

SIMPLE_TEST(SplitIntoWords_StringStream, TestSAMPLE1, EXPECTED1,
            "One two         three\n    four\tfive  ");
SIMPLE_TEST(SplitIntoWords_StringStream, TestSAMPLE2, EXPECTED2, "Geeks for Geeks");
SIMPLE_TEST(SplitIntoWords_StringStream, TestSAMPLE3, EXPECTED3,
            "a computer science portal");
