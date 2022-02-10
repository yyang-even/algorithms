#include "common_header.h"

#include "mathematics/arithmetics/progression/sum_of_natural_numbers.h"


namespace {

/** Printing frequency of each character just after its consecutive occurrences
 *
 * @reference   https://www.geeksforgeeks.org/printing-frequency-of-each-character-just-after-its-consecutive-occurrences/
 *
 * Given a string in such a way that every character occurs in a repeated manner. Your
 * task is to print the string by inserting the frequency of each unique character after
 * it and also eliminating all repeated characters.
 *
 * @reference   Run Length Encoding
 *              https://www.geeksforgeeks.org/run-length-encoding/
 *
 * Given an input string, write a function that returns the Run Length Encoded string for
 * the input string. For example, if the input string is "wwwwaaadexxxxxx", then the
 * function should return "w4a3d1e1x6".
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.5.
 */
auto RunLengthEncoding(const std::string &text) {
    std::string result;
    for (std::string::size_type i = 0; text[i]; ++i) {
        int count = 1;
        for (; text[i] == text[i + 1]; ++i) {
            ++count;
        }

        result.push_back(text[i]);
        result.append(std::to_string(count));
    }

    return result;
}


/**
 * @reference   Positions of Large Groups
 *              https://leetcode.com/problems/positions-of-large-groups/
 *
 * In a string s of lowercase letters, these letters form consecutive groups of the same
 * character. For example, a string like s = "abbxxxxzyy" has the groups "a", "bb",
 * "xxxx", "z", and "yy". A group is identified by an interval [start, end], where start
 * and end denote the start and end indices (inclusive) of the group. In the above
 * example, "xxxx" has the interval [3,6]. A group is considered large if it has 3 or
 * more characters. Return the intervals of every large group sorted in increasing order
 * by start index.
 */


/**
 * @reference   Count Substrings with Only One Distinct Letter
 *              http://lixinchengdu.github.io/algorithmbook/leetcode/count-substrings-with-only-one-distinct-letter.html
 *
 * Given a string S, return the number of substrings that have only one distinct letter.
 */
constexpr auto CountSubstrWithOneDistinctLetter(const std::string_view s) {
    int result = 0;
    int consecutive = 1;
    for (std::size_t i = 1; i < s.size(); ++i) {
        if (s[i] == s[i - 1]) {
            ++consecutive;
        } else {
            result += SumOfNaturals(consecutive);
            consecutive = 1;
        }
    }

    return result + SumOfNaturals(consecutive);
}


/**
 * @reference   Decompress Run-Length Encoded List
 *              https://leetcode.com/problems/decompress-run-length-encoded-list/
 *
 * We are given a list nums of integers representing a list compressed with run-length
 * encoding. Consider each adjacent pair of elements [freq, val] = [nums[2*i], nums[2*i+1]]
 * (with i >= 0).  For each such pair, there are freq elements with value val concatenated
 * in a sublist. Concatenate all the sublists from left to right to generate the
 * decompressed list. Return the decompressed list.
 */

}//namespace


THE_BENCHMARK(RunLengthEncoding, "GeeeEEKKKss");

SIMPLE_TEST(RunLengthEncoding, TestSAMPLE1, "G1e3E2K3s2", "GeeeEEKKKss");
SIMPLE_TEST(RunLengthEncoding, TestSAMPLE2, "c4O1d2E3", "ccccOddEEE");
SIMPLE_TEST(RunLengthEncoding, TestSAMPLE3, "a2b1c5a3", "aabcccccaaa");
SIMPLE_TEST(RunLengthEncoding, TestSAMPLE4, "w4a3d1e1x6", "wwwwaaadexxxxxx");


THE_BENCHMARK(CountSubstrWithOneDistinctLetter, "aaaba");

SIMPLE_TEST(CountSubstrWithOneDistinctLetter, TestSAMPLE1, 8, "aaaba");
SIMPLE_TEST(CountSubstrWithOneDistinctLetter, TestSAMPLE2, 55, "aaaaaaaaaa");
