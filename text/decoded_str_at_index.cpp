#include "common_header.h"


namespace {

/** Decoded String at Index
 *
 * @reference   https://leetcode.com/problems/decoded-string-at-index/
 *
 * You are given an encoded string s. To decode the string to a tape, the encoded string is read one
 * character at a time and the following steps are taken:
 *  If the character read is a letter, that letter is written onto the tape.
 *  If the character read is a digit d, the entire current tape is repeatedly written d - 1 more times
 *  in total.
 * Given an integer k, return the kth letter (1-indexed) in the decoded string.
 */
std::string DecodedStrAtIndex(const std::string_view s, int K) {
    long length = 0;
    int i = 0;
    for (; length < K; ++i) {
        const auto c = s[i];
        if (std::isdigit(c)) {
            length *= (c - '0');
        } else {
            ++length;
        }
    }

    while (i--) {
        const auto c = s[i];
        if (std::isdigit(c)) {
            length /= c - '0';
            K %= length;
        } else if (K % length-- == 0) {
            return std::string(1, c);
        }
    }

    return "";
}

} //namespace


THE_BENCHMARK(DecodedStrAtIndex, "leet2code3", 10);

SIMPLE_TEST(DecodedStrAtIndex, TestSAMPLE1, "o", "leet2code3", 10);
SIMPLE_TEST(DecodedStrAtIndex, TestSAMPLE2, "h", "ha22", 5);
SIMPLE_TEST(DecodedStrAtIndex, TestSAMPLE3, "a", "a2345678999999999999999", 1);
