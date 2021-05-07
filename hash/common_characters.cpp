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
    std::unordered_set one_set_characters(X.cbegin(), X.cend());
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
    for (char i = 0; i < 26; ++i) {
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
    for (char i = 0; i < 26; ++i) {
        for (int j = 0; j < all_common_chars[i]; ++j) {
            results.push_back('a' + i);
        }
    }

    return results;
}


/**
 * @reference   Find uncommon characters of the two strings
 *              https://www.geeksforgeeks.org/find-uncommon-characters-two-strings/
 *
 * Find and print the uncommon characters of the two given strings in sorted order.
 * Here uncommon character means that either the character is present in one string
 * or it is present in other string but not in both. The strings contain only
 * lowercase characters and can contain duplicates.
 */
auto UncommonChars_Hash(const std::string &X, const std::string &Y) {
    assert(std::all_of(X.cbegin(), X.cend(), islower));
    assert(std::all_of(Y.cbegin(), Y.cend(), islower));

    std::unordered_map<std::string::value_type, int> char_map;
    for (const auto c : X) {
        char_map[c] = 1;
    }

    for (const auto c : Y) {
        if (char_map[c] == 1) {
            char_map[c] = -1;
        } else if (char_map[c] != -1) {
            char_map[c] = 2;
        }
    }

    std::string results;
    for (char i = 0; i < 26; ++i) {
        const auto c = 'a' + i;
        if (char_map[c] > 0) {
            results.push_back(c);
        }
    }

    return results;
}


/**
 * @reference   Find uncommon characters of the two strings | Set 2
 *              https://www.geeksforgeeks.org/find-uncommon-characters-of-the-two-strings-set-2/
 */
auto UncommonChars_Bits(const std::string &X, const std::string &Y) {
    assert(std::all_of(X.cbegin(), X.cend(), islower));
    assert(std::all_of(Y.cbegin(), Y.cend(), islower));

    unsigned char_set_x = 0;
    for (const auto c : X) {
        char_set_x |= (1 << (c - 'a'));
    }

    unsigned char_set_y = 0;
    for (const auto c : Y) {
        char_set_y |= (1 << (c - 'a'));
    }

    auto uncommon_chars_set = char_set_x ^ char_set_y;
    std::string results;
    for (char i = 0; i < 26; ++i, uncommon_chars_set >>= 1) {
        if ((uncommon_chars_set & 1) == 1) {
            results.push_back('a' + i);
        }
    }

    return results;
}

}//namespace


SIMPLE_BENCHMARK(HaveCommonSubstring, Sample1, "HELLO", "WORLD");

SIMPLE_TEST(HaveCommonSubstring, TestSAMPLE1, true, "HELLO", "WORLD");
SIMPLE_TEST(HaveCommonSubstring, TestSAMPLE2, false, "HI", "ALL");


SIMPLE_BENCHMARK(CountCommonChars, Sample1, "HELLO", "WORLD");

SIMPLE_TEST(CountCommonChars, TestSAMPLE1, 2, "HELLO", "WORLD");
SIMPLE_TEST(CountCommonChars, TestSAMPLE2, 0, "HI", "ALL");
SIMPLE_TEST(CountCommonChars, TestSAMPLE3, 2, "abcd", "aad");
SIMPLE_TEST(CountCommonChars, TestSAMPLE4, 8, "geeksforgeeks", "platformforgeeks");


SIMPLE_BENCHMARK(GetCommonChars, Sample1, "geeks", "forgeeks");

SIMPLE_TEST(GetCommonChars, TestSAMPLE1, "eegks", "geeks", "forgeeks");
SIMPLE_TEST(GetCommonChars, TestSAMPLE2, "hhh", "hhhhhello", "gfghhmh");


const ArrayType SAMPLE1 = {"geeksforgeeks", "gemkstones", "acknowledges", "aguelikes"};
const ArrayType SAMPLE2 = {"apple", "orange"};


SIMPLE_BENCHMARK(CommonCharsOfStrings, Sample1, SAMPLE1);

SIMPLE_TEST(CommonCharsOfStrings, TestSAMPLE1, "eegks", SAMPLE1);
SIMPLE_TEST(CommonCharsOfStrings, TestSAMPLE2, "ae", SAMPLE2);


SIMPLE_BENCHMARK(UncommonChars_Hash, Sample1, "characters", "alphabets");

SIMPLE_TEST(UncommonChars_Hash, TestSAMPLE1, "bclpr", "characters", "alphabets");
SIMPLE_TEST(UncommonChars_Hash, TestSAMPLE2, "fioqruz", "geeksforgeeks", "geeksquiz");


SIMPLE_BENCHMARK(UncommonChars_Bits, Sample1, "characters", "alphabets");

SIMPLE_TEST(UncommonChars_Bits, TestSAMPLE1, "bclpr", "characters", "alphabets");
SIMPLE_TEST(UncommonChars_Bits, TestSAMPLE2, "fioqruz", "geeksforgeeks", "geeksquiz");
