#include "common_header.h"

#include "mathematics/arithmetics/progression/arithmetic_progression.h"
#include "mathematics/numbers/count_digits_in_integer.h"


namespace {

/** Printing frequency of each character just after its consecutive occurrences
 *
 * @reference   https://www.geeksforgeeks.org/printing-frequency-of-each-character-just-after-its-consecutive-occurrences/
 *
 * Given a string in such a way that every character occurs in a repeated manner. Your task is to print
 * the string by inserting the frequency of each unique character after it and also eliminating all
 * repeated characters.
 *
 * @reference   Run Length Encoding
 *              https://www.geeksforgeeks.org/run-length-encoding/
 *
 * Given an input string, write a function that returns the Run Length Encoded string for the input
 * string. For example, if the input string is "wwwwaaadexxxxxx", then the function should return
 * "w4a3d1e1x6".
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
 * @reference   Count and Say
 *              https://leetcode.com/problems/count-and-say/
 *
 * The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
 *  countAndSay(1) = "1"
 *  countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1), which is then
 *      converted into a different digit string.
 * To determine how you "say" a digit string, split it into the minimal number of substrings such that
 * each substring contains exactly one unique digit. Then for each substring, say the number of digits,
 * then say the digit. Finally, concatenate every said digit.
 * Given a positive integer n, return the nth term of the count-and-say sequence.
 */


/**
 * @reference   Positions of Large Groups
 *              https://leetcode.com/problems/positions-of-large-groups/
 *
 * In a string s of lowercase letters, these letters form consecutive groups of the same character.
 * For example, a string like s = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z", and "yy".
 * A group is identified by an interval [start, end], where start and end denote the start and end
 * indices (inclusive) of the group. In the above example, "xxxx" has the interval [3,6].
 * A group is considered large if it has 3 or more characters.
 * Return the intervals of every large group sorted in increasing order by start index.
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
 * We are given a list nums of integers representing a list compressed with run-length encoding.
 * Consider each adjacent pair of elements [freq, val] = [nums[2*i], nums[2*i+1]] (with i >= 0).  For
 * each such pair, there are freq elements with value val concatenated in a sublist.  Concatenate all
 * the sublists from left to right to generate the decompressed list.
 * Return the decompressed list.
 */


/**
 * @reference   Check if String Is Decomposable Into Value-Equal Substrings
 *              https://leetcode.ca/2021-08-06-1933-Check-if-String-Is-Decomposable-Into-Value-Equal-Substrings/
 *
 * A value-equal string is a string where all characters are the same.
 *  For example, "1111" and "33" are value-equal strings.
 *  In contrast, "123" is not a value-equal string.
 * Given a digit string s, decompose the string into some number of consecutive value-equal substrings
 * where exactly one substring has a length of 2 and the remaining substrings have a length of 3.
 * Return true if you can decompose s according to the above rules. Otherwise, return false.
 */


/**
 * @reference   String Compression
 *              https://leetcode.com/problems/string-compression/
 *
 * Given an array of characters chars, compress it using the following algorithm:
 * Begin with an empty string s. For each group of consecutive repeating characters in chars:
 *  If the group's length is 1, append the character to s.
 *  Otherwise, append the character followed by the group's length.
 * The compressed string s should not be returned separately, but instead, be stored in the input
 * character array chars. Note that group lengths that are 10 or longer will be split into multiple
 * characters in chars.
 * After you are done modifying the input array, return the new length of the array.
 * You must write an algorithm that uses only constant extra space.
 */


/**
 * @reference   String Compression II
 *              https://leetcode.com/problems/string-compression-ii/
 *
 * Run-length encoding is a string compression method that works by replacing consecutive identical
 * characters (repeated 2 or more times) with the concatenation of the character and the number marking
 * the count of the characters (length of the run). For example, to compress the string "aabccc" we
 * replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes "a2bc3".
 * Notice that in this problem, we are not adding '1' after single characters.
 * Given a string s and an integer k. You need to delete at most k characters from s such that the
 * run-length encoded version of s has minimum length.
 * Find the minimum length of the run-length encoded version of s after deleting at most k characters.
 */
auto StringCompression(const int left,
                       const std::string_view s,
                       const int k,
                       std::vector<std::vector<int>> &memo) {
    constexpr int MAXIMUM = 1e9;

    if (k < 0) {
        return MAXIMUM;
    }

    const int N = s.size();
    if (left >= N or N - left <= k) {
        return 0;
    }

    if (memo[left][k] != -1) {
        return memo[left][k];
    }

    auto result = MAXIMUM;
    int counts[26] = {};
    int most = 0;
    for (auto i = left; i < N; ++i) {
        most = std::max(most, ++counts[s[i] - 'a']);
        result = std::min(result,
                          1 + CountDigits_Iterative(most) +
                              StringCompression(i + 1, s, k - (i - left + 1 - most), memo));
    }

    return memo[left][k] = result;
}

auto StringCompression(const std::string_view s, const int k) {
    std::vector memo(s.size(), std::vector(k + 1, -1));
    return StringCompression(0, s, k, memo);
}

} //namespace


THE_BENCHMARK(RunLengthEncoding, "GeeeEEKKKss");

SIMPLE_TEST(RunLengthEncoding, TestSAMPLE1, "G1e3E2K3s2", "GeeeEEKKKss");
SIMPLE_TEST(RunLengthEncoding, TestSAMPLE2, "c4O1d2E3", "ccccOddEEE");
SIMPLE_TEST(RunLengthEncoding, TestSAMPLE3, "a2b1c5a3", "aabcccccaaa");
SIMPLE_TEST(RunLengthEncoding, TestSAMPLE4, "w4a3d1e1x6", "wwwwaaadexxxxxx");


THE_BENCHMARK(CountSubstrWithOneDistinctLetter, "aaaba");

SIMPLE_TEST(CountSubstrWithOneDistinctLetter, TestSAMPLE1, 8, "aaaba");
SIMPLE_TEST(CountSubstrWithOneDistinctLetter, TestSAMPLE2, 55, "aaaaaaaaaa");


THE_BENCHMARK(StringCompression, "aaabcccd", 2);

SIMPLE_TEST(StringCompression, TestSAMPLE1, 4, "aaabcccd", 2);
SIMPLE_TEST(StringCompression, TestSAMPLE2, 2, "aabbaa", 2);
SIMPLE_TEST(StringCompression, TestSAMPLE3, 3, "aaaaaaaaaaa", 0);
