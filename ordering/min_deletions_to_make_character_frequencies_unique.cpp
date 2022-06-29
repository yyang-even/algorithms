#include "common_header.h"


namespace {

/** Minimum Deletions to Make Character Frequencies Unique
 *
 * @reference   https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/
 *
 * A string s is called good if there are no two different characters in s that have the same
 * frequency.
 * Given a string s, return the minimum number of characters you need to delete to make s good.
 * The frequency of a character in a string is the number of times it appears in the string. For
 * example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.
 */
auto MinDeletionsToMakeCharFreqsUnique(const std::string_view s) {
    std::vector<int> frequencies(26, 0);
    for (const int c : s) {
        ++frequencies[c - 'a'];
    }

    std::sort(frequencies.begin(), frequencies.end(), std::greater<int> {});

    int result = 0;
    int max_freq_allowed = s.size();

    for (int i = 0; i < 26 and frequencies[i] > 0; ++i) {
        if (frequencies[i] > max_freq_allowed) {
            result += frequencies[i] - max_freq_allowed;
            frequencies[i] = max_freq_allowed;
        }

        max_freq_allowed = std::max(0, frequencies[i] - 1);
    }

    return result;
}

} //namespace


THE_BENCHMARK(MinDeletionsToMakeCharFreqsUnique, "ceabaacb");

SIMPLE_TEST(MinDeletionsToMakeCharFreqsUnique, TestSAMPLE1, 2, "ceabaacb");
SIMPLE_TEST(MinDeletionsToMakeCharFreqsUnique, TestSAMPLE2, 2, "aaabbbcc");
SIMPLE_TEST(MinDeletionsToMakeCharFreqsUnique, TestSAMPLE3, 0, "aab");
