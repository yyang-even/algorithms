#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Shifting Letters
 *
 * @reference   https://leetcode.com/problems/shifting-letters/
 *
 * You are given a string s of lowercase English letters and an integer array shifts of
 * the same length. Call the shift() of a letter, the next letter in the alphabet,
 * (wrapping around so that 'z' becomes 'a').
 *  For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.
 * Now for each shifts[i] = x, we want to shift the first i + 1 letters of s, x times.
 * Return the final string after all such shifts to s are applied.
 */
auto ShiftLetters(std::string s, ArrayType shifts) {
    for (int i = shifts.size() - 2; i >= 0; --i) {
        shifts[i] = (shifts[i] + shifts[i + 1]) % 26;
    }

    for (std::size_t i = 0; i < s.size(); ++i) {
        s[i] = (s[i] - 'a' + shifts[i]) % 26 + 'a';
    }

    return s;
}

}//namespace


const ArrayType SAMPLE1 = {3, 5, 9};
const ArrayType SAMPLE2 = {1, 2, 3};


THE_BENCHMARK(ShiftLetters, "abc", SAMPLE1);

SIMPLE_TEST(ShiftLetters, TestSAMPLE1, "rpl", "abc", SAMPLE1);
SIMPLE_TEST(ShiftLetters, TestSAMPLE2, "gfd", "aaa", SAMPLE2);
