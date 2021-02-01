#include "common_header.h"


namespace {

/** Count Occurences of Anagrams
 *
 * @reference   https://www.geeksforgeeks.org/count-occurences-of-anagrams/
 *
 * Given a word and a text, return the count of the occurences of anagrams of the word
 * in the text(For eg: anagrams of word for are for, ofr, rof etc.)
 */
auto AreAllCharZero(
    const std::unordered_map<std::string::value_type, int> &char_counts) {
    for (const auto &pair : char_counts) {
        if (pair.second) {
            return false;
        }
    }

    return true;
}

auto CountAnagrams(const std::string &text, const std::string &word) {
    std::unordered_map<std::string::value_type, int> char_counts;
    for (std::string::size_type i = 0; i < word.size(); ++i) {
        ++(char_counts[text[i]]);
        --(char_counts[word[i]]);
    }

    int count = AreAllCharZero(char_counts);

    for (auto i = word.size(); i < text.size(); ++i) {
        --(char_counts[text[i - word.size()]]);
        ++(char_counts[text[i]]);

        if (AreAllCharZero(char_counts)) {
            ++count;
        }
    }

    return count;
}


/** Check whether two strings are anagram of each other
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-two-strings-are-anagram-of-each-other/
 * @reference   Check whether two strings are anagrams of each other using unordered_map in C++
 *              https://www.geeksforgeeks.org/check-whether-two-strings-are-anagrams-of-each-other-using-unordered_map-in-c/
 * @reference   Check if two strings are permutation of each other
 *              https://www.geeksforgeeks.org/check-if-two-strings-are-permutation-of-each-other/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.3.
 *
 * @reference   Check if two arrays are equal or not
 *              https://www.geeksforgeeks.org/check-if-two-arrays-are-equal-or-not/
 *
 * Given two given arrays of equal length, the task is to find if given arrays are equal
 * or not. Two arrays are said to be equal if both of them contain same set of elements,
 * arrangements (or permutation) of elements may be different though.
 * Note: If there are repetitions, then counts of repeated elements must also be same for
 * two array to be equal.
 */
auto AreAnagrams(const std::string &s1, const std::string &s2) {
    if (s1.size() != s2.size()) {
        return false;
    }

    std::unordered_map<std::string::value_type, int> char_counts;
    for (std::string::size_type i = 0; i < s1.size(); ++i) {
        ++(char_counts[s1[i]]);
        --(char_counts[s2[i]]);
    }

    return AreAllCharZero(char_counts);
}

}//namespace


SIMPLE_BENCHMARK(CountAnagrams, Sample1, "forxxorfxdofr", "for");

SIMPLE_TEST(CountAnagrams, TestSAMPLE1, 3, "forxxorfxdofr", "for");
SIMPLE_TEST(CountAnagrams, TestSAMPLE2, 4, "aabaabaa", "aaba");


SIMPLE_BENCHMARK(AreAnagrams, Sample1, "abcd", "dabc");

SIMPLE_TEST(AreAnagrams, TestSAMPLE1, true, "abcd", "dabc");
SIMPLE_TEST(AreAnagrams, TestSAMPLE2, true, "geeksforgeeks", "forgeeksgeeks");
SIMPLE_TEST(AreAnagrams, TestSAMPLE3, false, "geeksforgeeks", "geeks");
