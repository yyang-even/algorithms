#include "common_header.h"


namespace {

/** Determine if Two Strings Are Close
 *
 * @reference   https://leetcode.com/problems/determine-if-two-strings-are-close/
 *
 * Two strings are considered close if you can attain one from the other using the following operations:
 *  Operation 1: Swap any two existing characters.
 *      For example, abcde -> aecdb
 *  Operation 2: Transform every occurrence of one existing character into another existing character,
 *  and do the same with the other character.
 *      For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
 * You can use the operations on either string as many times as necessary.
 * Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.
 */
auto DetermineIfTwoStrsAreClose(const std::string_view word1, const std::string_view word2) {
    std::vector<int> count1(26, 0);
    std::vector<int> count2(26, 0);
    std::vector<bool> char1(26, false);
    std::vector<bool> char2(26, false);

    for (const auto c : word1) {
        const int i = c - 'a';
        ++count1[i];
        char1[i] = true;
    }

    for (const auto c : word2) {
        const int i = c - 'a';
        ++count2[i];
        char2[i] = true;
    }

    std::sort(count1.begin(), count1.end());
    std::sort(count2.begin(), count2.end());

    return count1 == count2 and char1 == char2;
}

} //namespace


THE_BENCHMARK(DetermineIfTwoStrsAreClose, "abc", "bca");

SIMPLE_TEST(DetermineIfTwoStrsAreClose, TestSAMPLE1, true, "abc", "bca");
SIMPLE_TEST(DetermineIfTwoStrsAreClose, TestSAMPLE2, true, "cabbba", "abbccc");
SIMPLE_TEST(DetermineIfTwoStrsAreClose, TestSAMPLE3, false, "a", "aa");
