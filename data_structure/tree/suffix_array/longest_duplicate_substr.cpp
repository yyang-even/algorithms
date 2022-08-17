#include "common_header.h"


namespace {

/** Longest Duplicate Substring
 *
 * @reference   https://leetcode.com/problems/longest-duplicate-substring/
 *
 * Given a string s, consider all duplicated substrings: (contiguous) substrings of s that occur 2 or
 * more times. The occurrences may overlap.
 * Return any duplicated substring that has the longest possible length. If s does not have a duplicated
 * substring, the answer is "".
 */
int check(const std::string_view s, const std::size_t length) {
    std::unordered_set<std::string_view> count;
    for (std::size_t i = 0; i + length <= s.size(); ++i) {
        if (not count.emplace(s.substr(i, length)).second) {
            return i;
        }
    }

    return -1;
}

auto LongestDuplicateSubstr(const std::string_view s) {
    int left = 0;
    int right = s.size();

    std::string_view result;
    while (left < right) {
        const auto mid = (left + right + 1) / 2;
        if (const auto position = check(s, mid); position != -1) {
            left = mid;
            result = s.substr(position, mid);
        } else {
            right = mid - 1;
        }
    }

    return result;
}

} //namespace


THE_BENCHMARK(LongestDuplicateSubstr, "banana");

SIMPLE_TEST(LongestDuplicateSubstr, TestSAMPLE1, "ana", "banana");
SIMPLE_TEST(LongestDuplicateSubstr, TestSAMPLE2, "", "abcd");
