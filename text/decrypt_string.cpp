#include "common_header.h"


namespace {

/** Decrypt String from Alphabet to Integer Mapping
 *
 * @reference   https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/
 *
 * Given a string s formed by digits ('0' - '9') and '#' . We want to map s to English
 * lowercase characters as follows:
 *  Characters ('a' to 'i') are represented by ('1' to '9') respectively.
 *  Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.
 * Return the string formed after mapping. It's guaranteed that a unique mapping will
 * always exist.
 */
auto DecryptString(const std::string_view s) {
    std::string result;
    for (std::size_t i = 0; i < s.size();) {
        int c = s[i++] - '0';
        if (i + 1 < s.size() and s[i + 1] == '#') {
            c = c * 10 + s[i] - '0';
            i += 2;
        }

        result.push_back('a' + c - 1);
    }

    return result;
}

}//namespace


THE_BENCHMARK(DecryptString, "10#11#12");

SIMPLE_TEST(DecryptString, TestSAMPLE1, "jkab", "10#11#12");
SIMPLE_TEST(DecryptString, TestSAMPLE2, "acz", "1326#");
SIMPLE_TEST(DecryptString, TestSAMPLE3, "y", "25#");
SIMPLE_TEST(DecryptString, TestSAMPLE4, "abcdefghijklmnopqrstuvwxyz",
            "12345678910#11#12#13#14#15#16#17#18#19#20#21#22#23#24#25#26#");
