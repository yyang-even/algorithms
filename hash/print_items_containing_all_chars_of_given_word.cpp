#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Print list items containing all characters of a given word
 *
 * @reference   https://www.geeksforgeeks.org/print-list-items-containing-all-characters-of-a-given-word/
 *
 * There is a list of items. Given a specific word, e.g., "sun", print out all the items
 * in list which contain all the characters of "sun". For example if the given word is
 * "sun" and the items are "sunday", "geeksforgeeks", "utensils", "just" and "sss", then
 * the program should print "sunday" and "utensils".
 */
auto ItemsContainingAllCharsOfGivenWord(const ArrayType &items,
                                        const std::string_view word) {
    const auto counters = ToFrequencyHashTable(word);

    ArrayType output;
    for (const auto item : items) {
        auto length = word.size();
        auto temp_counters = counters;
        for (const auto c : item) {
            const auto iter = temp_counters.find(c);
            if (iter != temp_counters.cend() and iter->second != 0) {
                --(iter->second);
                if (not --length) {
                    output.push_back(item);
                    break;
                }
            }
        }
    }

    return output;
}


/**
 * @reference   Shortest Completing Word
 *              https://leetcode.com/problems/shortest-completing-word/
 *
 * Given a string licensePlate and an array of strings words, find the shortest
 * completing word in words. A completing word is a word that contains all the letters
 * in licensePlate. Ignore numbers and spaces in licensePlate, and treat letters as case
 * insensitive. If a letter appears more than once in licensePlate, then it must appear
 * in the word the same number of times or more. For example, if licensePlate = "aBc 12c",
 * then it contains letters 'a', 'b' (ignoring case), and 'c' twice. Possible completing
 * words are "abccdef", "caaacab", and "cbca". Return the shortest completing word in
 * words. It is guaranteed an answer exists. If there are multiple shortest completing
 * words, return the first one that occurs in words.
 * words[i] consists of lower case English letters.
 */

}//namespace


const ArrayType SAMPLE = {"geeksforgeeks", "unsorted", "sunday", "just", "sss"};
const ArrayType EXPECTED = {"unsorted", "sunday"};


THE_BENCHMARK(ItemsContainingAllCharsOfGivenWord, SAMPLE, "sun");

SIMPLE_TEST(ItemsContainingAllCharsOfGivenWord, TestSAMPLE1, EXPECTED, SAMPLE, "sun");
