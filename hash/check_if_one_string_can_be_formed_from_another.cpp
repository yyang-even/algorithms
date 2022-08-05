#include "common_header.h"

#include "hash.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Print list items containing all characters of a given word
 *
 * @reference   https://www.geeksforgeeks.org/print-list-items-containing-all-characters-of-a-given-word/
 *
 * There is a list of items. Given a specific word, e.g., "sun", print out all the items in list
 * which contain all the characters of "sun". For example if the given word is "sun" and the items
 * are "sunday", "geeksforgeeks", "utensils", "just" and "sss", then the program should print
 * "sunday" and "utensils".
 */
auto ItemsContainingAllCharsOfGivenWord(const ArrayType &items, const std::string_view word) {
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
 * Given a string licensePlate and an array of strings words, find the shortest completing word
 * in words.
 * A completing word is a word that contains all the letters in licensePlate. Ignore numbers and
 * spaces in licensePlate, and treat letters as case insensitive. If a letter appears more than
 * once in licensePlate, then it must appear in the word the same number of times or more.
 * For example, if licensePlate = "aBc 12c", then it contains letters 'a', 'b' (ignoring case),
 * and 'c' twice. Possible completing words are "abccdef", "caaacab", and "cbca".
 * Return the shortest completing word in words. It is guaranteed an answer exists. If there are
 * multiple shortest completing words, return the first one that occurs in words.
 */


/** Check whether second string can be formed from words of first string
 *
 * @reference   Section VI. Five Algorithm Approaches.
 *              Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *
 * A ransom note can be formed by cutting words out of a magazine to form a new sentence. How
 * would your figure out if a ransom note (represented as a string) can be formed from a given
 * magazine (string)?
 *
 * @reference   Check whether second string can be formed from characters of first string
 *              https://www.geeksforgeeks.org/check-whether-second-string-can-formed-first-string-using-count-array/
 *
 * @reference   Ransom Note
 *              https://leetcode.com/problems/ransom-note/
 *
 * Given two stings ransomNote and magazine, return true if ransomNote can be constructed from
 * magazine and false otherwise.
 * Each letter in magazine can only be used once in ransomNote.
 */
constexpr auto CanConstruct(const std::string_view ransom_note, const std::string_view magazine) {
    int counts[256] = {};
    for (const int c : magazine) {
        ++counts[c];
    }

    for (const int c : ransom_note) {
        if (counts[c]-- == 0) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Find Words That Can Be Formed by Characters
 *              https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/
 *
 * You are given an array of strings words and a string chars.
 * A string is good if it can be formed by characters from chars (each character can only be used
 * once).
 * Return the sum of lengths of all good strings in words.
 * words[i] and chars consist of lowercase English letters.
 */


/**
 * @reference   Count the Number of Consistent Strings
 *              https://leetcode.com/problems/count-the-number-of-consistent-strings/
 *
 * You are given a string allowed consisting of distinct characters and an array of strings words.
 * A string is consistent if all characters in the string appear in the string allowed.
 * Return the number of consistent strings in the array words.
 * words[i] and allowed contain only lowercase English letters.
 */
auto CountConsistentStrings(const std::string_view allowed, const ArrayType &words) {
    bool hash[26] = {};
    for (const auto c : allowed) {
        hash[c - 'a'] = true;
    }

    int result = words.size();
    for (const auto &s : words) {
        for (const auto c : s) {
            if (not hash[c - 'a']) {
                --result;
                break;
            }
        }
    }

    return result;
}


/**
 * @reference   Word Subsets
 *              https://leetcode.com/problems/word-subsets/
 *
 * You are given two string arrays words1 and words2.
 * A string b is a subset of string a if every letter in b occurs in a including multiplicity.
 *  For example, "wrr" is a subset of "warrior" but is not a subset of "world".
 * A string a from words1 is universal if for every string b in words2, b is a subset of a.
 * Return an array of all the universal strings in words1. You may return the answer in any order.
 */

} //namespace


THE_BENCHMARK(CanConstruct, "geeks", "geekforgeeks");

SIMPLE_TEST(CanConstruct, TestSAMPLE1, true, "geeks", "geekforgeeks");
SIMPLE_TEST(CanConstruct, TestSAMPLE2, false, "and", "geekforgeeks");
SIMPLE_TEST(CanConstruct, TestSAMPLE3, true, "geeeek", "geekforgeeks");


const ArrayType SAMPLE = {"geeksforgeeks", "unsorted", "sunday", "just", "sss"};
const ArrayType EXPECTED = {"unsorted", "sunday"};


THE_BENCHMARK(ItemsContainingAllCharsOfGivenWord, SAMPLE, "sun");

SIMPLE_TEST(ItemsContainingAllCharsOfGivenWord, TestSAMPLE1, EXPECTED, SAMPLE, "sun");


const ArrayType SAMPLE1 = {"ad", "bd", "aaab", "baa", "badab"};
const ArrayType SAMPLE2 = {"a", "b", "c", "ab", "ac", "bc", "abc"};
const ArrayType SAMPLE3 = {"cc", "acd", "b", "ba", "bac", "bad", "ac", "d"};


THE_BENCHMARK(CountConsistentStrings, "ab", SAMPLE1);

SIMPLE_TEST(CountConsistentStrings, TestSAMPLE1, 2, "ab", SAMPLE1);
SIMPLE_TEST(CountConsistentStrings, TestSAMPLE2, 7, "abc", SAMPLE2);
SIMPLE_TEST(CountConsistentStrings, TestSAMPLE3, 4, "cad", SAMPLE3);
