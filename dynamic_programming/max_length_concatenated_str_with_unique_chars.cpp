#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Maximum Length of a Concatenated String with Unique Characters
 *
 * @reference   https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
 *
 * Given an array of strings arr. String s is a concatenation of a sub-sequence of arr
 * which have unique characters. Return the maximum possible length of s.
 * arr[i] contains only lower case English letters.
 */
void
MaxLengthConcatenatedStrWithUniqueChars(const ArrayType &strs, const std::size_t i,
                                        int mask, const std::size_t length, std::size_t &result) {
    if (i == strs.size()) {
        result = std::max(result, length);
        return;
    }

    MaxLengthConcatenatedStrWithUniqueChars(strs, i + 1, mask, length, result);

    for (const auto c : strs[i]) {
        if (mask & (1 << (c - 'a'))) {
            return;
        } else {
            mask |= (1 << (c - 'a'));
        }
    }

    MaxLengthConcatenatedStrWithUniqueChars(strs, i + 1, mask,
                                            length + strs[i].size(), result);
}

inline auto MaxLengthConcatenatedStrWithUniqueChars(const ArrayType &strs) {
    std::size_t result = 0;
    MaxLengthConcatenatedStrWithUniqueChars(strs, 0, 0, 0, result);
    return result;
}


/**
 * @reference   Maximize length of the String by concatenating characters from an Array of Strings
 *              https://www.geeksforgeeks.org/maximize-length-of-the-string-by-concatenating-characters-from-an-array-of-strings/
 */
auto MaxLengthConcatenatedStrWithUniqueChars_DP(const ArrayType &strs) {
    std::vector<std::bitset<26>> dp = { std::bitset<26>() };
    std::size_t result = 0;

    for (const auto s : strs) {
        std::bitset<26> current_set;
        for (const auto c : s) {
            current_set.set(c - 'a');
        }
        assert(current_set.count() == s.size());

        for (int i = dp.size() - 1; i >= 0; --i) {
            if ((dp[i] & current_set).any()) {
                continue;
            }
            dp.push_back(dp[i] | current_set);
            result = std::max(result, dp[i].count() + s.size());
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {"un", "iq", "ue"};
const ArrayType SAMPLE2 = {"cha", "r", "act", "ers"};
const ArrayType SAMPLE3 = {"abcdefghijklmnopqrstuvwxyz"};
const ArrayType SAMPLE4 = {"abcdefghijklm", "bcdefghijklmn", "cdefghijklmno", "nopqrstuvwxyz", "opqrstuvwxyza"};


THE_BENCHMARK(MaxLengthConcatenatedStrWithUniqueChars, SAMPLE1);

SIMPLE_TEST(MaxLengthConcatenatedStrWithUniqueChars, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxLengthConcatenatedStrWithUniqueChars, TestSAMPLE2, 6, SAMPLE2);
SIMPLE_TEST(MaxLengthConcatenatedStrWithUniqueChars, TestSAMPLE3, 26, SAMPLE3);
SIMPLE_TEST(MaxLengthConcatenatedStrWithUniqueChars, TestSAMPLE4, 26, SAMPLE4);


THE_BENCHMARK(MaxLengthConcatenatedStrWithUniqueChars_DP, SAMPLE1);

SIMPLE_TEST(MaxLengthConcatenatedStrWithUniqueChars_DP, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxLengthConcatenatedStrWithUniqueChars_DP, TestSAMPLE2, 6, SAMPLE2);
SIMPLE_TEST(MaxLengthConcatenatedStrWithUniqueChars_DP, TestSAMPLE3, 26, SAMPLE3);
SIMPLE_TEST(MaxLengthConcatenatedStrWithUniqueChars_DP, TestSAMPLE4, 26, SAMPLE4);
