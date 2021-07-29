#include "common_header.h"


namespace {

/** Check whether second string can be formed from characters of first string
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-second-string-can-formed-first-string-using-count-array/
 */
auto CanSecondStringBeFormedFromFirst(const std::string_view given_str,
                                      const std::string_view candidate) {
    std::unordered_map<char, int> char_counts;
    for (const auto c : candidate) {
        ++char_counts[c];
    }

    for (const auto c : given_str) {
        if (const auto iter = char_counts.find(c); iter != char_counts.cend()) {
            if (--iter->second == 0) {
                char_counts.erase(iter);
                if (char_counts.empty()) {
                    return true;
                }
            }
        }
    }

    return false;
}


/** Check whether second string can be formed from words of first string
 *
 * @reference   Section VI. Five Algorithm Approaches.
 *              Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *
 * A ransom note can be formed by cutting words out of a magazine to form a new sentence.
 * How would your figure out if a ransom note (represented as a string) can be formed
 * from a given magazine (string)?
 *
 * @reference   Ransom Note
 *              https://leetcode.com/problems/ransom-note/
 *
 * Given two stings ransomNote and magazine, return true if ransomNote can be constructed
 * from magazine and false otherwise. Each letter in magazine can only be used once in
 * ransomNote.
 */
constexpr auto
CanConstruct(const std::string_view ransom_note, const std::string_view magazine) {
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

}//namespace


THE_BENCHMARK(CanSecondStringBeFormedFromFirst, "geekforgeeks", "geeks");

SIMPLE_TEST(CanSecondStringBeFormedFromFirst, TestSAMPLE1, true,
            "geekforgeeks", "geeks");
SIMPLE_TEST(CanSecondStringBeFormedFromFirst, TestSAMPLE2, false,
            "geekforgeeks", "and");
SIMPLE_TEST(CanSecondStringBeFormedFromFirst, TestSAMPLE3, true,
            "geekforgeeks", "geeeek");


THE_BENCHMARK(CanConstruct, "geeks", "geekforgeeks");

SIMPLE_TEST(CanConstruct, TestSAMPLE1, true, "geeks", "geekforgeeks");
SIMPLE_TEST(CanConstruct, TestSAMPLE2, false, "and", "geekforgeeks");
SIMPLE_TEST(CanConstruct, TestSAMPLE3, true, "geeeek", "geekforgeeks");
