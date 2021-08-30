#include "common_header.h"


namespace {

/** Backspace String Compare
 *
 * @reference   https://leetcode.com/problems/backspace-string-compare/
 *
 * Given two strings s and t, return true if they are equal when both are typed into
 * empty text editors. '#' means a backspace character. Note that after backspacing an
 * empty text, the text will continue empty.
 * Follow up: Can you solve it in O(n) time and O(1) space?
 */
constexpr void next(const std::string_view s, int &i, int &to_skip) {
    while (i >= 0) {
        if (s[i] == '#') {
            ++to_skip;
            --i;
        } else if (to_skip > 0) {
            --to_skip;
            --i;
        } else {
            break;
        }
    }
}

constexpr auto
BackspaceStrCompare(const std::string_view s, const std::string_view t) {
    int s_i = s.size() - 1;
    int t_i = t.size() - 1;
    int s_to_skip = 0;
    int t_to_skip = 0;

    while (s_i >= 0 or t_i >= 0) {
        next(s, s_i, s_to_skip);
        next(t, t_i, t_to_skip);

        if ((s_i >= 0) != (t_i >= 0)) {
            return false;
        }
        if (s_i >= 0 and s[s_i] != t[t_i]) {
            return false;
        }

        --s_i;
        --t_i;
    }

    return true;
}

}//namespace


THE_BENCHMARK(BackspaceStrCompare, "ab#c", "ad#c");

SIMPLE_TEST(BackspaceStrCompare, TestSAMPLE1, true, "ab#c", "ad#c");
SIMPLE_TEST(BackspaceStrCompare, TestSAMPLE2, true, "ab##", "c#d#");
SIMPLE_TEST(BackspaceStrCompare, TestSAMPLE3, true, "a##c", "#a#c");
SIMPLE_TEST(BackspaceStrCompare, TestSAMPLE4, false, "a#c", "b");
