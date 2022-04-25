#include "common_header.h"

#include "count_frequencies_of_all_elements.h"
#include "hash.h"


namespace {

using StrArray = std::vector<std::string_view>;

/** Return maximum occurring character in an input string
 *
 * @reference   https://www.geeksforgeeks.org/return-maximum-occurring-character-in-the-input-string/
 *
 * Write an efficient function to return maximum occurring character in the input string
 * e.g., if input string is "test" then function should return 't'.
 *
 * @reference   Most frequent element in an array
 *              https://www.geeksforgeeks.org/frequent-element-array/
 * @reference   Least frequent element in an array
 *              https://www.geeksforgeeks.org/least-frequent-element-array/
 * @reference   Mode
 *              https://www.geeksforgeeks.org/mode/
 */
auto MaximumOccurringChar_Position(const std::string_view input) {
    std::unordered_map<char, std::size_t> counters;
    std::size_t max = 1;
    auto max_char = input.front();

    for (const auto c : input) {
        const auto count = ++counters[c];
        if (count > max) {
            max_char = c;
            max = count;
        }
    }

    return max_char;
}


/** Maximum occurring character in an input string | Set-2
 *
 * @reference   https://www.geeksforgeeks.org/maximum-occurring-character-in-an-input-string-set-2/
 *
 * Given a string containing lowercase characters. The task is to print the maximum
 * occurring character in the input string. If 2 or more characters appear the same
 * number of times, print the lexicographically (alphabetically) lowest (first)
 * character.
 */
auto MaximumOccurringChar_Alphabet(const std::string_view input) {
    std::unordered_map<char, std::size_t> counters;
    std::size_t max = 1;
    auto max_char = input.front();

    for (const auto c : input) {
        const auto count = ++counters[c];
        if (count > max) {
            max_char = c;
            max = count;
        } else if (count == max and c < max_char) {
            max_char = c;
        }
    }

    return max_char;
}

/** Find the most frequent digit without using array/string
 *
 * @reference   https://www.geeksforgeeks.org/find-the-most-frequent-digit-without-using-arraystring/
 *
 * Given an integer, find the most occurring digit in it. If two or more digits occur
 * same number of times, then return the highest of them. Input integer is given as an
 * int variable, not as a string or array. Use of hash or array or string is not allowed.
 */


/** Find the maximum repeating number in O(n) time and O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/find-the-maximum-repeating-number-in-ok-time/
 *
 * Given an array of size n, the array contains numbers in range from 0 to k-1 where k is
 * a positive integer and k <= n. Find the maximum repeating number in this array.
 * For example, let k be 10 the given array be arr[] =
 * {1, 2, 2, 2, 0, 2, 0, 2, 3, 8, 0, 9, 2, 3}, the maximum repeating number would be 2.
 * Expected time complexity is O(n) and extra space allowed is O(1). Modifications to
 * array are allowed.
 */
using ArrayType = std::vector<unsigned>;

inline auto
MaximumRepeatingNumber_Inplace(ArrayType numbers, const ArrayType::value_type K) {
    assert(K <= numbers.size());

    TransformToInplaceCounterArray(numbers, K);

    return std::max_element(numbers.cbegin(), numbers.cend()) - numbers.cbegin();
}


/**
 * @reference   Most Common Word
 *              https://leetcode.com/problems/most-common-word/
 *
 * Given a string paragraph and a string array of the banned words banned, return the
 * most frequent word that is not banned. It is guaranteed there is at least one word
 * that is not banned, and that the answer is unique. The words in paragraph are
 * case-insensitive and the answer should be returned in lowercase.
 * paragraph consists of English letters, space ' ', or one of the symbols: "!?',;.".
 * banned[i] consists of only lowercase English letters.
 */
auto
MostFrequentWordNotBanned(const std::string_view paragraph, const StrArray &banned) {
    const auto banned_set = ToUnorderedSet(banned);

    std::unordered_map<std::string, int> counts;
    std::string word;
    for (const auto c : paragraph) {
        if (std::isalpha(c)) {
            word.push_back(std::tolower(c));
        } else if (not word.empty()) {
            if (banned_set.find(word) == banned_set.cend()) {
                ++counts[word];
            }
            word.clear();
        }
    }

    if (not word.empty()) {
        if (banned_set.find(word) == banned_set.cend()) {
            ++counts[word];
        }
    }

    int max_freq = INT_MIN;
    std::string result;
    for (const auto &[a_word, freq] : counts) {
        if (freq > max_freq) {
            max_freq = freq;
            result = a_word;
        }
    }

    return result;
}


/**
 * @reference   Most Frequent Number Following Key In an Array
 *              https://leetcode.com/problems/most-frequent-number-following-key-in-an-array/
 *
 * You are given a 0-indexed integer array nums. You are also given an integer key, which
 * is present in nums.
 * For every unique integer target in nums, count the number of times target immediately
 * follows an occurrence of key in nums. In other words, count the number of indices i
 * such that:
 *  0 <= i <= nums.length - 2,
 *  nums[i] == key and,
 *  nums[i + 1] == target.
 * Return the target with the maximum count. The test cases will be generated such that
 * the target with maximum count is unique.
 * 1 <= nums[i] <= 1000
 */

}//namespace


THE_BENCHMARK(MaximumOccurringChar_Position, "sample string");

SIMPLE_TEST(MaximumOccurringChar_Position, TestSAMPLE1, 's', "sample string");
SIMPLE_TEST(MaximumOccurringChar_Position, TestSAMPLE2, 't', "test");


THE_BENCHMARK(MaximumOccurringChar_Alphabet, "test sample");

SIMPLE_TEST(MaximumOccurringChar_Alphabet, TestSAMPLE1, 'e', "test sample");
SIMPLE_TEST(MaximumOccurringChar_Alphabet, TestSAMPLE2, 'a', "sample program");


const ArrayType SAMPLE1 = {1, 2, 2, 2, 0, 2, 0, 2, 3, 8, 0, 9, 2, 3};
const ArrayType SAMPLE2 = {2, 3, 3, 5, 3, 4, 1, 7};


THE_BENCHMARK(MaximumRepeatingNumber_Inplace, SAMPLE1, 10);

SIMPLE_TEST(MaximumRepeatingNumber_Inplace, TestSAMPLE1, 2, SAMPLE1, 10);
SIMPLE_TEST(MaximumRepeatingNumber_Inplace, TestSAMPLE2, 3, SAMPLE2, 8);


const StrArray SAMPLE1B = {"hit"};
const StrArray SAMPLE2B = {};


THE_BENCHMARK(MostFrequentWordNotBanned,
              "Bob hit a ball, the hit BALL flew far after it was hit.", SAMPLE1B);

SIMPLE_TEST(MostFrequentWordNotBanned, TestSAMPLE1,
            "ball", "Bob hit a ball, the hit BALL flew far after it was hit.", SAMPLE1B);
SIMPLE_TEST(MostFrequentWordNotBanned, TestSAMPLE2, "a", "a.", SAMPLE2B);
SIMPLE_TEST(MostFrequentWordNotBanned, TestSAMPLE3, "a", "a", SAMPLE2B);
