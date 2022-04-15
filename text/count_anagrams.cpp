#include "common_header.h"

#include "text.h"


namespace {

using HashTable = std::unordered_map<char, int>;

/** Count Occurences of Anagrams
 *
 * @reference   https://www.geeksforgeeks.org/count-occurences-of-anagrams/
 *
 * Given a word and a text, return the count of the occurences of anagrams of the word in
 * the text(For eg: anagrams of word for are for, ofr, rof etc.)
 *
 * @reference   Find All Anagrams in a String
 *              https://leetcode.com/problems/find-all-anagrams-in-a-string/
 *
 * Given two strings s and p, return an array of all the start indices of p's anagrams in
 * s. You may return the answer in any order.
 * An Anagram is a word or phrase formed by rearranging the letters of a different word
 * or phrase, typically using all the original letters exactly once.
 * s and p consist of lowercase English letters.
 */
inline auto AreAllCharZero(const HashTable &char_counts) {
    for (const auto [_, count] : char_counts) {
        if (count) {
            return false;
        }
    }

    return true;
}

auto CountAnagrams(const std::string_view text, const std::string_view word) {
    assert(word.size() <= text.size());

    HashTable char_counts;
    for (std::size_t i = 0; i < word.size(); ++i) {
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
 * @reference   Valid Anagram
 *              https://leetcode.com/problems/valid-anagram/
 *
 * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 * Follow up: What if the inputs contain Unicode characters? How would you adapt your
 * solution to such a case?
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
auto AreAnagrams(const std::string_view s1, const std::string_view s2) {
    if (s1.size() != s2.size()) {
        return false;
    }

    HashTable char_counts;
    for (std::size_t i = 0; i < s1.size(); ++i) {
        ++(char_counts[s1[i]]);
        --(char_counts[s2[i]]);
    }

    return AreAllCharZero(char_counts);
}


/**
 * @reference   Find Anagram Mappings
 *              https://ttzztt.gitbooks.io/lc/content/find-anagram-mappings.html
 *
 * Given two lists A and B, and B is an anagram of A. B is an anagram of A means B is
 * made by randomizing the order of the elements in A. We want to find an index mapping
 * P, from A to B. A mapping P[i] = j means the ith element in A appears in B at index
 * j. These lists A and B may contain duplicates. If there are multiple answers, output
 * any of them.
 */


/**
 * @reference   Permutation in String
 *              https://leetcode.com/problems/permutation-in-string/
 *
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false
 * otherwise.
 * In other words, return true if one of s1's permutations is the substring of s2.
 * s1 and s2 consist of lowercase English letters.
 */
constexpr auto CheckAnagram(const std::string_view s1, const std::string_view s2) {
    if (s1.size() > s2.size()) {
        return false;
    }

    std::size_t i = 0;
    int counts[256] = {};
    for (; i < s1.size(); ++i) {
        ++counts[static_cast<int>(s1[i])];
        --counts[static_cast<int>(s2[i])];
    }

    int total_zeros = 0;
    for (int c = 'a'; c <= 'z'; ++c) {
        if (not counts[c]) {
            ++total_zeros;
        }
    }

    for (; i < s2.size(); ++i) {
        if (total_zeros == 26) {
            return true;
        }

        const int left = s2[i - s1.size()];
        if (const auto c = ++counts[left]; c == 1) {
            --total_zeros;
        } else if (c == 0) {
            ++total_zeros;
        }

        const int right = s2[i];
        if (const auto c = --counts[right]; c == -1) {
            --total_zeros;
        } else if (c == 0) {
            ++total_zeros;
        }
    }

    return total_zeros == 26;
}


/**
 * @reference   Substrings of Size Three with Distinct Characters
 *              https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/
 *
 * A string is good if there are no repeated characters.
 * Given a string s, return the number of good substrings of length three in s.
 * Note that if there are multiple occurrences of the same substring, every occurrence
 * should be counted.
 * A substring is a contiguous sequence of characters in a string.
 */


/**
 * @reference   Count Vowel Substrings of a String
 *              https://leetcode.com/problems/count-vowel-substrings-of-a-string/
 *
 * A substring is a contiguous (non-empty) sequence of characters within a string.
 * A vowel substring is a substring that only consists of vowels ('a', 'e', 'i', 'o', and
 * 'u') and has all five vowels present in it.
 * Given a string word, return the number of vowel substrings in word.
 */
auto CountVowelSubstrs(const std::string_view s) {
    std::unordered_map<char, int> counts;
    int num_vowels = 0;
    std::size_t j = 0;
    std::size_t k = 0;

    int result = 0;
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (isVowel(s[i])) {
            num_vowels += ++counts[s[i]] == 1;
            for (; num_vowels == 5; ++k) {
                num_vowels -= --counts[s[k]] == 0;
            }
            result += k - j;
        } else {
            counts.clear();
            num_vowels = 0;
            j = k = i + 1;
        }
    }

    return result;
}

}//namespace


THE_BENCHMARK(CountAnagrams, "forxxorfxdofr", "for");

SIMPLE_TEST(CountAnagrams, TestSAMPLE1, 3, "forxxorfxdofr", "for");
SIMPLE_TEST(CountAnagrams, TestSAMPLE2, 4, "aabaabaa", "aaba");
SIMPLE_TEST(CountAnagrams, TestSAMPLE3, 2, "cbaebabacd", "abc");
SIMPLE_TEST(CountAnagrams, TestSAMPLE4, 3, "abab", "ab");


THE_BENCHMARK(AreAnagrams, "abcd", "dabc");

SIMPLE_TEST(AreAnagrams, TestSAMPLE1, true, "abcd", "dabc");
SIMPLE_TEST(AreAnagrams, TestSAMPLE2, true, "geeksforgeeks", "forgeeksgeeks");
SIMPLE_TEST(AreAnagrams, TestSAMPLE3, false, "geeksforgeeks", "geeks");


THE_BENCHMARK(CheckAnagram, "ab", "eidbaooo");

SIMPLE_TEST(CheckAnagram, TestSAMPLE1, true, "ab", "eidbaooo");
SIMPLE_TEST(CheckAnagram, TestSAMPLE2, false, "ab", "eidboaoo");
SIMPLE_TEST(CheckAnagram, TestSAMPLE3, true, "adc", "dcda");
SIMPLE_TEST(CheckAnagram, TestSAMPLE4, true, "abc", "bbbca");


THE_BENCHMARK(CountVowelSubstrs, "aeiouu");

SIMPLE_TEST(CountVowelSubstrs, TestSAMPLE1, 2, "aeiouu");
SIMPLE_TEST(CountVowelSubstrs, TestSAMPLE2, 0, "unicornarihan");
SIMPLE_TEST(CountVowelSubstrs, TestSAMPLE3, 7, "cuaieuouac");
