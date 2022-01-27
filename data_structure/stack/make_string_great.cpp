#include "common_header.h"


namespace {

/** Make The String Great
 *
 * @reference   https://leetcode.com/problems/make-the-string-great/
 *
 * Given a string s of lower and upper case English letters.
 * A good string is a string which doesn't have two adjacent characters s[i] and s[i + 1]
 * where:
 *  0 <= i <= s.length - 2
 *  s[i] is a lower-case letter and s[i + 1] is the same letter but in upper-case or
 *      vice-versa.
 * To make the string good, you can choose two adjacent characters that make the string
 * bad and remove them. You can keep doing this until the string becomes good.
 * Return the string after making it good. The answer is guaranteed to be unique under
 * the given constraints.
 * Notice that an empty string is also good.
 */
auto MakeStrGreat(const std::string_view s) {
    constexpr auto DIFF = std::abs('a' - 'A');

    std::string result;
    for (const auto c : s) {
        if (not result.empty() and std::abs(c - result.back()) == DIFF) {
            result.pop_back();
        } else {
            result.push_back(c);
        }
    }

    return result;
}

}//namespace


THE_BENCHMARK(MakeStrGreat, "leEeetcode");

SIMPLE_TEST(MakeStrGreat, TestSAMPLE1, "leetcode", "leEeetcode");
SIMPLE_TEST(MakeStrGreat, TestSAMPLE2, "", "abBAcC");
SIMPLE_TEST(MakeStrGreat, TestSAMPLE3, "s", "s");
