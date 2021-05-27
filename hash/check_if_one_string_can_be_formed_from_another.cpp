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
 */

}//namespace


THE_BENCHMARK(CanSecondStringBeFormedFromFirst, "geekforgeeks", "geeks");

SIMPLE_TEST(CanSecondStringBeFormedFromFirst, TestSAMPLE1, true,
            "geekforgeeks", "geeks");
SIMPLE_TEST(CanSecondStringBeFormedFromFirst, TestSAMPLE2, false,
            "geekforgeeks", "and");
SIMPLE_TEST(CanSecondStringBeFormedFromFirst, TestSAMPLE3, true,
            "geekforgeeks", "geeeek");
