#include "common_header.h"

#include "count_frequencies_of_all_elements.h"
#include "ordering/count_occurrences_in_sorted_array.h"


namespace {

using ArrayType = std::vector<int>;

/** Count frequencies of all elements in array in O(1) extra space and O(n) time
 *
 * @reference   https://www.geeksforgeeks.org/count-frequencies-elements-array-o1-extra-space-time/
 *
 * Given an unsorted array of n integers which can contain integers from 1 to n. Some elements
 * can be repeated multiple times and some other elements can be absent from the array. Count
 * frequency of all elements that are present and print the missing elements.
 *
 * @reference   Counting frequencies of array elements
 *              https://www.geeksforgeeks.org/counting-frequencies-of-array-elements/
 */
auto CountFrequenciesOfAllElements_InPlace_Sign(ArrayType elements) {
    for (auto iter = elements.begin(); iter != elements.end();) {
        auto &elem = *iter;
        if (elem > 0) {
            const auto index = elem - 1;
            auto &count = elements[index];
            if (count > 0) {
                elem = count;
                count = -1;
            } else {
                --count;
                elem = 0;
                ++iter;
            }
        } else {
            ++iter;
        }
    }

    std::map<ArrayType::value_type, ArrayType::size_type> output;
    const auto N = elements.size();
    for (ArrayType::size_type i = 0; i < N; ++i) {
        output.emplace(i + 1, abs(elements[i]));
    }

    return output;
}


auto CountFrequenciesOfAllElements_STL(const ArrayType &elements) {
    std::map<ArrayType::value_type, ArrayType::size_type> output;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        ++output[elements[i]];
        output[i + 1];
    }

    return output;
}


auto CountFrequenciesOfAllElements_InPlace_Mod(ArrayType elements) {
    std::transform(elements.cbegin(), elements.cend(), elements.begin(), [](const auto elem) {
        return elem - 1;
    });

    const auto N = elements.size();
    TransformToInplaceCounterArray(elements, N);

    std::map<ArrayType::value_type, ArrayType::size_type> output;
    for (ArrayType::size_type i = 0; i < N; ++i) {
        output.emplace(i + 1, (elements[i] / N));
    }

    return output;
}


/** Print numbers in descending order along with their frequencies
 *
 * @reference   https://www.geeksforgeeks.org/print-numbers-in-descending-order-along-with-their-frequencies/
 * @reference   Print 2-D co-ordinate points in ascending order followed by their frequencies
 *              https://www.geeksforgeeks.org/print-2-d-co-ordinate-points-in-ascending-order-followed-by-their-frequencies/
 * @reference   Descending order in Map and Multimap of C++ STL
 *              https://www.geeksforgeeks.org/descending-order-map-multimap-c-stl/
 */
using ValueCountPair = std::pair<ArrayType::value_type, ArrayType::size_type>;

inline auto SortAndCount(ArrayType values) {
    std::sort(values.begin(), values.end(), std::greater<ArrayType::value_type> {});
    return CountAllOccurrencesInSortedArray_STL(values);
}


auto SortAndCount_BucketSort(const ArrayType &values) {
    std::map<ArrayType::value_type, ArrayType::size_type, std::greater<ArrayType::value_type>>
        buckets;
    for (const auto v : values) {
        ++buckets[v];
    }

    std::vector<ValueCountPair> outputs;
    for (const auto &value_count_pair : buckets) {
        outputs.emplace_back(value_count_pair);
    }

    return outputs;
}


/**
 * @reference   Print characters in decreasing order of frequency
 *              https://www.geeksforgeeks.org/print-characters-in-decreasing-order-of-frequency/
 *
 * Given a string str, the task is to print the characters in decreasing order of their frequency.
 * If the frequency of two characters is same then sort them in descending order alphabetically.
 */


/**
 * @reference   Print characters and their frequencies in order of occurrence
 *              https://www.geeksforgeeks.org/print-characters-frequencies-order-occurrence/
 *
 * Given a string str containing only lowercase characters. The problem is to print the characters
 * along with their frequency in the order of their occurrence and in the given format explained
 * in the examples below.
 */


/**
 * @reference   Find All Numbers Disappeared in an Array
 *              https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 *
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all
 * the integers in the range [1, n] that do not appear in nums.
 * Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned
 * list does not count as extra space.
 */


/**
 * @reference   Find All Duplicates in an Array
 *              https://leetcode.com/problems/find-all-duplicates-in-an-array/
 *
 * Given an integer array nums of length n where all the integers of nums are in the range [1, n]
 * and each integer appears once or twice, return an array of all the integers that appears twice.
 * You must write an algorithm that runs in O(n) time and uses only constant extra space.
 */


/**
 * @reference   Find Lucky Integer in an Array
 *              https://leetcode.com/problems/find-lucky-integer-in-an-array/
 *
 * Given an array of integers arr, a lucky integer is an integer that has a frequency in the array
 * equal to its value.
 * Return the largest lucky integer in the array. If there is no lucky integer return -1.
 * 1 <= arr[i] <= 500
 */


/**
 * @reference   Counting Elements
 *              https://leetcode.ca/all/1426.html
 *
 * Given an integer array arr, count how many elements x there are, such that x + 1 is also in arr.
 * If there're duplicates in arr, count them seperately.
 * 0 <= arr[i] <= 1000
 */


/**
 * @reference   Number of Good Pairs
 *              https://leetcode.com/problems/number-of-good-pairs/
 *
 * Given an array of integers nums, return the number of good pairs.
 * A pair (i, j) is called good if nums[i] == nums[j] and i < j.
 * 1 <= nums[i] <= 100
 */


/**
 * @reference   Check if the Sentence Is Pangram
 *              https://leetcode.com/problems/check-if-the-sentence-is-pangram/
 *
 * A pangram is a sentence where every letter of the English alphabet appears at least once.
 * Given a string sentence containing only lowercase English letters, return true if sentence is
 * a pangram, or false otherwise.
 */


/**
 * @reference   Redistribute Characters to Make All Strings Equal
 *              https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/
 *
 * You are given an array of strings words (0-indexed).
 * In one operation, pick two distinct indices i and j, where words[i] is a non-empty string, and
 * move any character from words[i] to any position in words[j].
 * Return true if you can make every string in words equal using any number of operations, and
 * false otherwise.
 * words[i] consists of lowercase English letters.
 */


/**
 * @reference   Check if All Characters Have Equal Number of Occurrences
 *              https://leetcode.com/problems/check-if-all-characters-have-equal-number-of-occurrences/
 *
 * Given a string s, return true if s is a good string, or false otherwise.
 * A string s is good if all the characters that appear in s have the same number of occurrences
 * (i.e., the same frequency).
 */


/**
 * @reference   Rings and Rods
 *              https://leetcode.com/problems/rings-and-rods/
 *
 * There are n rings and each ring is either red, green, or blue. The rings are distributed across
 * ten rods labeled from 0 to 9.
 * You are given a string rings of length 2n that describes the n rings that are placed onto the
 * rods. Every two characters in rings forms a color-position pair that is used to describe each
 * ring where:
 *  The first character of the ith pair denotes the ith ring's color ('R', 'G', 'B').
 *  The second character of the ith pair denotes the rod that the ith ring is placed on ('0' to '9').
 * For example, "R3G2B1" describes n == 3 rings: a red ring placed onto the rod labeled 3, a green
 * ring placed onto the rod labeled 2, and a blue ring placed onto the rod labeled 1.
 * Return the number of rods that have all three colors of rings on them.
 */


/**
 * @reference   Keep Multiplying Found Values by Two
 *              https://leetcode.com/problems/keep-multiplying-found-values-by-two/
 *
 * You are given an array of integers nums. You are also given an integer original which is the
 * first number that needs to be searched for in nums.
 * You then do the following steps:
 *  If original is found in nums, multiply it by two (i.e., set original = 2 * original).
 *  Otherwise, stop the process.
 *  Repeat this process with the new number as long as you keep finding the number.
 * Return the final value of original.
 * 1 <= nums[i], original <= 1000
 */


/**
 * @reference   Divide Array Into Equal Pairs
 *              https://leetcode.com/problems/divide-array-into-equal-pairs/
 *
 * You are given an integer array nums consisting of 2 * n integers.
 * You need to divide nums into n pairs such that:
 *  Each element belongs to exactly one pair.
 *  The elements present in a pair are equal.
 * Return true if nums can be divided into n pairs, otherwise return false.
 */

} //namespace


const ArrayType SAMPLE1 = {2, 3, 3, 2, 5};
const ArrayType SAMPLE2 = {1};
const ArrayType SAMPLE3 = {4, 4, 4, 4};
const ArrayType SAMPLE4 = {1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 1};
const ArrayType SAMPLE5 = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
const ArrayType SAMPLE6 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const ArrayType SAMPLE7 = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};


THE_BENCHMARK(CountFrequenciesOfAllElements_InPlace_Sign, SAMPLE1);

MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE1,
                   SAMPLE1);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE2,
                   SAMPLE2);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE3,
                   SAMPLE3);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE4,
                   SAMPLE4);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE5,
                   SAMPLE5);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE6,
                   SAMPLE6);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE7,
                   SAMPLE7);


THE_BENCHMARK(CountFrequenciesOfAllElements_STL, SAMPLE1);


THE_BENCHMARK(CountFrequenciesOfAllElements_InPlace_Mod, SAMPLE1);

MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE1,
                   SAMPLE1);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE2,
                   SAMPLE2);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE3,
                   SAMPLE3);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE4,
                   SAMPLE4);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE5,
                   SAMPLE5);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE6,
                   SAMPLE6);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL,
                   CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE7,
                   SAMPLE7);


const ArrayType VALUES1 = {1, 1, 2, 2, 2, 2, 3};
const std::vector<ValueCountPair> EXPECTED1 = {{3, 1}, {2, 4}, {1, 2}};
const ArrayType VALUES2 = {1, 3, 3, 3, 4, 4, 5};
const std::vector<ValueCountPair> EXPECTED2 = {{5, 1}, {4, 2}, {3, 3}, {1, 1}};
const ArrayType VALUES3 = {1, 1, 1, 2, 3, 4, 9, 9, 10};
const std::vector<ValueCountPair> EXPECTED3 = {{10, 1}, {9, 2}, {4, 1}, {3, 1}, {2, 1}, {1, 3}};


THE_BENCHMARK(SortAndCount, VALUES1);

SIMPLE_TEST(SortAndCount, TestSAMPLE1, EXPECTED1, VALUES1);
SIMPLE_TEST(SortAndCount, TestSAMPLE2, EXPECTED2, VALUES2);
SIMPLE_TEST(SortAndCount, TestSAMPLE3, EXPECTED3, VALUES3);


THE_BENCHMARK(SortAndCount_BucketSort, VALUES1);

SIMPLE_TEST(SortAndCount_BucketSort, TestSAMPLE1, EXPECTED1, VALUES1);
SIMPLE_TEST(SortAndCount_BucketSort, TestSAMPLE2, EXPECTED2, VALUES2);
SIMPLE_TEST(SortAndCount_BucketSort, TestSAMPLE3, EXPECTED3, VALUES3);
