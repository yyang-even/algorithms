#include "common_header.h"


namespace {

/** Check if two strings have a common substring
 *
 * @reference   https://www.geeksforgeeks.org/check-two-strings-common-substring/
 * @reference   Check if there is any common character in two given strings
 *              https://www.geeksforgeeks.org/check-if-there-is-any-common-character-in-two-given-strings/
 */
auto HaveCommonSubstring(const std::string &X, const std::string &Y) {
    std::unordered_set<std::string::value_type> one_set_characters(X.cbegin(), X.cend());
    for (const auto c : Y) {
        if (one_set_characters.find(c) != one_set_characters.cend()) {
            return true;
        }
    }

    return false;
}


/** Count common characters in two strings
 *
 * @reference   https://www.geeksforgeeks.org/count-common-characters-in-two-strings/
 *
 * Given two strings s1 and s2 consisting of lowercase English alphabets, the task is to count all the
 * pairs of indices (i, j) from the given strings such that s1[i] = s2[j] and all the indices are
 * distinct i.e. if s1[i] pairs with some s2[j] then these two characters will not be paired with any
 * other character.
 */
auto CountCommonChars(const std::string &X, const std::string &Y) {
    std::unordered_map<std::string::value_type, int> one_set_characters;
    for (const auto c : X) {
        ++(one_set_characters[c]);
    }

    unsigned count = 0;
    for (const auto c : Y) {
        if ((one_set_characters[c])-- > 0) {
            ++count;
        }
    }

    return count;
}

}//namespace


SIMPLE_BENCHMARK(HaveCommonSubstring, "HELLO", "WORLD");

SIMPLE_TEST(HaveCommonSubstring, TestSAMPLE1, true, "HELLO", "WORLD");
SIMPLE_TEST(HaveCommonSubstring, TestSAMPLE2, false, "HI", "ALL");


SIMPLE_BENCHMARK(CountCommonChars, "HELLO", "WORLD");

SIMPLE_TEST(CountCommonChars, TestSAMPLE1, 2, "HELLO", "WORLD");
SIMPLE_TEST(CountCommonChars, TestSAMPLE2, 0, "HI", "ALL");
SIMPLE_TEST(CountCommonChars, TestSAMPLE3, 2, "abcd", "aad");
SIMPLE_TEST(CountCommonChars, TestSAMPLE4, 8, "geeksforgeeks", "platformforgeeks");
