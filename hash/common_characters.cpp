#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

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


/** Print common characters of two Strings in alphabetical order
 *
 * @reference   https://www.geeksforgeeks.org/print-common-characters-two-strings-alphabetical-order-2/
 *
 * Given two strings, print all the common characters in lexicographical order.
 * If there are no common letters, print -1. All letters are lower case.
 */
auto GetCommonChars(const std::string &X, const std::string &Y) {
    assert(std::all_of(X.cbegin(), X.cend(), islower));
    assert(std::all_of(Y.cbegin(), Y.cend(), islower));

    std::unordered_map<std::string::value_type, int> one_set_characters;
    for (const auto c : X) {
        ++(one_set_characters[c]);
    }

    std::vector<unsigned> common_chars(26, 0);
    for (const auto c : Y) {
        if ((one_set_characters[c])-- > 0) {
            ++(common_chars[c - 'a']);
        }
    }

    std::string results;
    for (int i = 0; i < 26; ++i) {
        for (unsigned j = 0; j < common_chars[i]; ++j) {
            results.push_back('a' + i);
        }
    }

    return results;
}


/** Common characters in n strings
 *
 * @reference   https://www.geeksforgeeks.org/common-characters-n-strings/
 */
auto CommonCharsOfStrings(const ArrayType &strings) {
    assert(std::all_of(strings.cbegin(), strings.cend(), [](const auto & a_string) {
        return std::all_of(a_string.cbegin(), a_string.cend(), islower);
    }));

    std::vector<int> all_common_chars(26, std::numeric_limits<int>::max());
    for (const auto &a_string : strings) {
        std::vector<int> common_chars_of_two(26, 0);
        for (const auto c : a_string) {
            const auto index = c - 'a';
            if ((all_common_chars[index])-- > 0) {
                ++(common_chars_of_two[index]);
            }
        }

        all_common_chars.swap(common_chars_of_two);
    }

    std::string results;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < all_common_chars[i]; ++j) {
            results.push_back('a' + i);
        }
    }

    return results;
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


SIMPLE_BENCHMARK(GetCommonChars, "geeks", "forgeeks");

SIMPLE_TEST(GetCommonChars, TestSAMPLE1, "eegks", "geeks", "forgeeks");
SIMPLE_TEST(GetCommonChars, TestSAMPLE2, "hhh", "hhhhhello", "gfghhmh");


const ArrayType SAMPLE1 = {"geeksforgeeks", "gemkstones", "acknowledges", "aguelikes"};
const ArrayType SAMPLE2 = {"apple", "orange"};


SIMPLE_BENCHMARK(CommonCharsOfStrings, SAMPLE1);

SIMPLE_TEST(CommonCharsOfStrings, TestSAMPLE1, "eegks", SAMPLE1);
SIMPLE_TEST(CommonCharsOfStrings, TestSAMPLE2, "ae", SAMPLE2);
