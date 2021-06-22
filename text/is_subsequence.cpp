#include "common_header.h"


namespace {

/** Given two strings, find if first string is a subsequence of second
 *
 * @reference   https://www.geeksforgeeks.org/given-two-strings-find-first-string-subsequence-second/
 *
 * Given two strings str1 and str2, find if str1 is a subsequence of str2. A subsequence
 * is a sequence that can be derived from another sequence by deleting some elements
 * without changing the order of the remaining elements. Expected time complexity is
 * linear.
 */
constexpr auto
isSubsequence(const std::string_view sub, const std::string_view text) {
    assert(sub.size() <= text.size());
    assert(not sub.empty());

    std::size_t i = 0;
    for (const auto c : text) {
        if (sub[i] == c) {
            ++i;
        }
    }

    return i == sub.size();
}

}//namespace


THE_BENCHMARK(isSubsequence, "AXY", "ADXCPY");

SIMPLE_TEST(isSubsequence, TestSAMPLE1, true, "AXY", "ADXCPY");
SIMPLE_TEST(isSubsequence, TestSAMPLE2, false, "AXY", "YADXCP");
SIMPLE_TEST(isSubsequence, TestSAMPLE3, true, "gksrek", "geeksforgeeks");
