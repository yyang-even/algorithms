#include "common_header.h"

#include "remove_characters.h"
#include "hash/hash.h"


namespace {

/** Remove spaces from a given string
 *
 * @reference   https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/
 * @reference   C++ Program to remove spaces from a string
 *              https://www.geeksforgeeks.org/c-program-remove-spaces-string/
 *
 * Given a string, remove all spaces from the string and return it. Expected time
 * complexity is O(n) and only one traversal of string.
 */
inline auto RemoveSpaces_TwoPointers(std::string input) {
    return RemoveCharacters_TwoPointers(std::move(input),
                                        ToNegationLambda(std::isspace));
}


/**
 * @reference   Removing spaces from a string using Stringstream
 *              https://www.geeksforgeeks.org/removing-spaces-string-using-stringstream/
 */
inline auto RemoveSpaces_StringStream(std::string input) {

    std::stringstream ss(input);
    for (input.clear(); ss;) {
        std::string word;
        ss >> word;
        input.append(std::move(word));
    }

    return input;
}


template <typename UnaryPredicate>
inline constexpr auto
RemoveCharacters_Partition(std::string input, const UnaryPredicate p) {
    const auto end = std::stable_partition(input.begin(), input.end(), p);
    input.resize(std::distance(input.begin(), end));
    return input;
}

inline auto RemoveSpaces_Partition(std::string input) {
    return RemoveCharacters_Partition(std::move(input), ToNegationLambda(std::isspace));
}


/**
 * @reference   Move spaces to front of string in single traversal
 *              https://www.geeksforgeeks.org/move-spaces-front-string-single-traversal/
 */


/** Remove all occurrences of a character in a string
 *
 * @reference   https://www.geeksforgeeks.org/remove-all-occurrences-of-a-character-in-a-string/
 */
inline auto RemoveCharactersByKey_Partition(std::string input,
                                            const std::string::value_type key) {
    return RemoveCharacters_Partition(std::move(input), [key](const auto c) {
        return key != c;
    });
}


/**
 * @reference   Remove Element
 *              https://leetcode.com/problems/remove-element/
 */
auto RemoveCharactersByKey_Unstable(std::string input, const char key) {
    int left = 0;
    int right = input.size();
    while (left < right) {
        if (input[left] == key) {
            input[left] = input[--right];
        } else {
            left++;
        }
    }
    input.resize(right);

    return input;
}

inline auto testRemoveCharactersByKey_Unstable(std::string input, const char key) {
    input = RemoveCharactersByKey_Unstable(std::move(input), key);
    std::sort(input.begin(), input.end());

    return input;
}


/** Removing punctuations from a given string
 *
 * @reference   https://www.geeksforgeeks.org/removing-punctuations-given-string/
 */
inline auto RemovePunctuations_Partition(std::string input) {
    return RemoveCharacters_Partition(std::move(input), ToNegationLambda(std::ispunct));
}


/** Remove characters from the first string which are present in the second string
 *
 * @reference   https://www.geeksforgeeks.org/remove-characters-from-the-first-string-which-are-present-in-the-second-string/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 6.
 */
inline auto RemoveCharactersPresentInTheSecond_Partition(std::string input,
                                                         const std::string_view mask) {
    const auto counter = ToUnorderedSet(mask);

    return RemoveCharacters_Partition(std::move(input), [&counter](const auto c) {
        return counter.find(c) == counter.cend();
    });
}


/** Remove even frequency characters from the string
 *
 * @reference   https://www.geeksforgeeks.org/remove-even-frequency-characters-from-the-string/
 */
inline auto RemoveCharactersWithEvenFrequency_Partition(std::string input) {
    const auto counter = ToFrequencyHashTable(input);

    return RemoveCharacters_Partition(std::move(input), [&counter](const auto c) {
        return counter.at(c) % 2 != 0;
    });
}


/**
 * @reference   Remove odd frequency characters from the string
 *              https://www.geeksforgeeks.org/remove-odd-frequency-characters-from-the-string/
 */


/** Remove characters from string that appears strictly less than K times
 *
 * @reference   https://www.geeksforgeeks.org/remove-characters-from-string-that-appears-strictly-less-than-k-times/
 * @reference   Remove elements that appear strictly less than k times
 *              https://www.geeksforgeeks.org/remove-elements-that-appear-strictly-less-than-k-times/
 *
 * @reference   Remove elements from the array which appear more than k times
 *              https://www.geeksforgeeks.org/remove-elements-from-the-array-which-appear-more-than-k-times/
 * @reference   Remove characters that appear more than k times
 *              https://www.geeksforgeeks.org/remove-characters-that-appear-more-than-k-times/
 *
 * @reference   Remove elements from the array whose frequency lies in the range [l, r]
 *              https://www.geeksforgeeks.org/remove-elements-from-the-array-whose-frequency-lies-in-the-range-l-r/
 */
inline auto
RemoveCharactersAppearLessThanK_Partition(std::string input, const int K) {
    const auto counter = ToFrequencyHashTable(input);

    return RemoveCharacters_Partition(std::move(input), [&counter, K](const auto c) {
        return counter.at(c) >= K;
    });
}


/** Remove all characters other than alphabets from string
 *
 * @reference   https://www.geeksforgeeks.org/remove-characters-alphabets-string/
 */
inline auto RemoveNonalphabetsCharacters_Partition(std::string input) {
    return RemoveCharacters_Partition(std::move(input), ToLambda(std::isalpha));
}


/**
 * @reference   Program to remove vowels from a String
 *              https://www.geeksforgeeks.org/program-remove-vowels-string/
 * @reference   Program to remove consonants from a String
 *              https://www.geeksforgeeks.org/program-to-remove-consonants-from-a-string/
 */

}//namespace


THE_BENCHMARK(RemoveSpaces_TwoPointers, "g  eeks   for ge  eeks  ");

SIMPLE_TEST(RemoveSpaces_TwoPointers, TestSAMPLE1, "geeksforgeeeks",
            "g  eeks   for ge  eeks  ");


THE_BENCHMARK(RemoveSpaces_StringStream, "g  eeks   for ge  eeks  ");

SIMPLE_TEST(RemoveSpaces_StringStream, TestSAMPLE1, "geeksforgeeeks",
            "g  eeks   for ge  eeks  ");


THE_BENCHMARK(RemoveSpaces_Partition, "g  eeks   for ge  eeks  ");

SIMPLE_TEST(RemoveSpaces_Partition, TestSAMPLE1, "geeksforgeeeks",
            "g  eeks   for ge  eeks  ");


THE_BENCHMARK(RemoveCharactersByKey_Partition, "g  eeks   for ge  eeks  ", ' ');

SIMPLE_TEST(RemoveCharactersByKey_Partition, TestSAMPLE1, "geeksforgeeeks",
            "g  eeks   for ge  eeks  ", ' ');
SIMPLE_TEST(RemoveCharactersByKey_Partition, TestSAMPLE2, "gksforgks",
            "geeksforgeeks", 'e');
SIMPLE_TEST(RemoveCharactersByKey_Partition, TestSAMPLE3, "eeksforeeks",
            "geeksforgeeks", 'g');


THE_BENCHMARK(RemoveCharactersByKey_Unstable, "g  eeks   for ge  eeks  ", ' ');

SIMPLE_TEST(testRemoveCharactersByKey_Unstable, TestSAMPLE1, "22", "3223", '3');
SIMPLE_TEST(testRemoveCharactersByKey_Unstable, TestSAMPLE2, "00134", "01223042", '2');
SIMPLE_TEST(testRemoveCharactersByKey_Unstable, TestSAMPLE3, "1235", "12354", '4');
SIMPLE_TEST(testRemoveCharactersByKey_Unstable, TestSAMPLE4, "1235", "412354", '4');
SIMPLE_TEST(testRemoveCharactersByKey_Unstable, TestSAMPLE5, "", "22", '2');


THE_BENCHMARK(RemovePunctuations_Partition, "%welcome' to @geeksforgeek<s");

SIMPLE_TEST(RemovePunctuations_Partition, TestSAMPLE1, "welcome to geeksforgeeks",
            "%welcome' to @geeksforgeek<s");
SIMPLE_TEST(RemovePunctuations_Partition, TestSAMPLE2, "Hello he said and went",
            "Hello!!!, he said ---and went.");


THE_BENCHMARK(RemoveCharactersPresentInTheSecond_Partition, "geeksforgeeks", "mask");

SIMPLE_TEST(RemoveCharactersPresentInTheSecond_Partition, TestSAMPLE1, "geeforgee",
            "geeksforgeeks", "mask");


THE_BENCHMARK(RemoveCharactersWithEvenFrequency_Partition, "aabbbddeeecc");

SIMPLE_TEST(RemoveCharactersWithEvenFrequency_Partition, TestSAMPLE1, "bbbeee",
            "aabbbddeeecc");
SIMPLE_TEST(RemoveCharactersWithEvenFrequency_Partition, TestSAMPLE2, "zzzweee",
            "zzzxxweeerr");


THE_BENCHMARK(RemoveCharactersAppearLessThanK_Partition, "geeksforgeeks", 3);

SIMPLE_TEST(RemoveCharactersAppearLessThanK_Partition, TestSAMPLE1, "geeksgeeks",
            "geeksforgeeks", 2);
SIMPLE_TEST(RemoveCharactersAppearLessThanK_Partition, TestSAMPLE2, "eeee",
            "geeksforgeeks", 3);


THE_BENCHMARK(RemoveNonalphabetsCharacters_Partition, "$Gee*k;s..fo, r'Ge^eks?");

SIMPLE_TEST(RemoveNonalphabetsCharacters_Partition, TestSAMPLE1, "GeeksforGeeks",
            "$Gee*k;s..fo, r'Ge^eks?");
SIMPLE_TEST(RemoveNonalphabetsCharacters_Partition, TestSAMPLE2, "PraBHatkumarsingh",
            "P&ra+$BHa;;t*ku, ma$r@@s#in}gh");
