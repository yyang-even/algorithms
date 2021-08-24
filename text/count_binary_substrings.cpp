#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Count Binary Substrings
 *
 * @reference   https://leetcode.com/problems/count-binary-substrings/
 *
 * Give a binary string s, return the number of non-empty substrings that have the same
 * number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped
 * consecutively. Substrings that occur multiple times are counted the number of times
 * they occur.
 */
constexpr auto CountBinarySubstrs(const std::string_view s) {
    int prev = 0;
    int count = 1;
    int total = 0;

    for (std::size_t i = 1; i < s.size(); ++i) {
        if (s[i - 1] == s[i]) {
            ++count;
        } else {
            total += std::min(prev, count);
            prev = count;
            count = 1;
        }
    }

    return total + std::min(prev, count);
}

}//namespace


THE_BENCHMARK(CountBinarySubstrs, "00110011");

SIMPLE_TEST(CountBinarySubstrs, TestSAMPLE1, 6, "00110011");
SIMPLE_TEST(CountBinarySubstrs, TestSAMPLE2, 4, "10101");

