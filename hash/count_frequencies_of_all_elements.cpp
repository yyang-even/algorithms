#include "common_header.h"

#include "count_frequencies_of_all_elements.h"
#include "hash.h"

#include "mathematics/matrix/matrix.h"
#include "ordering/count_occurrences_in_sorted_array.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Count frequencies of all elements in array in O(1) extra space and O(n) time
 *              https://www.geeksforgeeks.org/count-frequencies-elements-array-o1-extra-space-time/
 *
 * Given an unsorted array of n integers which can contain integers from 1 to n. Some elements can be
 * repeated multiple times and some other elements can be absent from the array. Count frequency of all
 * elements that are present and print the missing elements.
 *
 * @reference   Counting frequencies of array elements
 *              https://www.geeksforgeeks.org/counting-frequencies-of-array-elements/
 *
 * @tags    #hash-table #in-place-hash
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


/**
 * @reference   Print numbers in descending order along with their frequencies
 *              https://www.geeksforgeeks.org/print-numbers-in-descending-order-along-with-their-frequencies/
 * @reference   Print 2-D co-ordinate points in ascending order followed by their frequencies
 *              https://www.geeksforgeeks.org/print-2-d-co-ordinate-points-in-ascending-order-followed-by-their-frequencies/
 * @reference   Descending order in Map and Multimap of C++ STL
 *              https://www.geeksforgeeks.org/descending-order-map-multimap-c-stl/
 *
 * @tags    #hash-table #sorting #ordered-set
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
 * Given a string str, the task is to print the characters in decreasing order of their frequency.  If
 * the frequency of two characters is same then sort them in descending order alphabetically.
 *
 * @tags    #hash-table #sorting
 */


/**
 * @reference   Print characters and their frequencies in order of occurrence
 *              https://www.geeksforgeeks.org/print-characters-frequencies-order-occurrence/
 *
 * Given a string str containing only lowercase characters. The problem is to print the characters along
 * with their frequency in the order of their occurrence and in the given format explained in the
 * examples below.
 *
 * @tags    #hash-table
 */


/**
 * @reference   Find All Numbers Disappeared in an Array
 *              https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 *
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the
 * integers in the range [1, n] that do not appear in nums.
 * Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned list
 * does not count as extra space.
 *
 * @tags    #hash-table #in-place-hash
 */


/**
 * @reference   Find All Duplicates in an Array
 *              https://leetcode.com/problems/find-all-duplicates-in-an-array/
 *
 * Given an integer array nums of length n where all the integers of nums are in the range [1, n] and
 * each integer appears once or twice, return an array of all the integers that appears twice.
 * You must write an algorithm that runs in O(n) time and uses only constant extra space.
 *
 * @tags    #hash-table #in-place-hash
 */


/**
 * @reference   Find Lucky Integer in an Array
 *              https://leetcode.com/problems/find-lucky-integer-in-an-array/
 *
 * Given an array of integers arr, a lucky integer is an integer that has a frequency in the array equal
 * to its value.
 * Return the largest lucky integer in the array. If there is no lucky integer return -1.
 * 1 <= arr[i] <= 500
 *
 * @tags    #hash-table #min-max-element
 */


/**
 * @reference   Counting Elements
 *              https://leetcode.ca/all/1426.html
 *
 * Given an integer array arr, count how many elements x there are, such that x + 1 is also in arr.
 * If there're duplicates in arr, count them seperately.
 * 0 <= arr[i] <= 1000
 *
 * @tags    #hash-table
 */


/**
 * @reference   Number of Good Pairs
 *              https://leetcode.com/problems/number-of-good-pairs/
 *
 * Given an array of integers nums, return the number of good pairs.
 * A pair (i, j) is called good if nums[i] == nums[j] and i < j.
 * 1 <= nums[i] <= 100
 *
 * @tags    #hash-table
 */


/**
 * @reference   Check if the Sentence Is Pangram
 *              https://leetcode.com/problems/check-if-the-sentence-is-pangram/
 *
 * A pangram is a sentence where every letter of the English alphabet appears at least once.
 * Given a string sentence containing only lowercase English letters, return true if sentence is a
 * pangram, or false otherwise.
 *
 * @tags    #hash-table
 */


/**
 * @reference   Redistribute Characters to Make All Strings Equal
 *              https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/
 *
 * You are given an array of strings words (0-indexed).
 * In one operation, pick two distinct indices i and j, where words[i] is a non-empty string, and move
 * any character from words[i] to any position in words[j].
 * Return true if you can make every string in words equal using any number of operations, and false
 * otherwise.
 * words[i] consists of lowercase English letters.
 *
 * @tags    #hash-table
 */


/**
 * @reference   Check if All Characters Have Equal Number of Occurrences
 *              https://leetcode.com/problems/check-if-all-characters-have-equal-number-of-occurrences/
 *
 * Given a string s, return true if s is a good string, or false otherwise.
 * A string s is good if all the characters that appear in s have the same number of occurrences (i.e.,
 * the same frequency).
 *
 * @tags    #hash-table
 */


/**
 * @reference   Rings and Rods
 *              https://leetcode.com/problems/rings-and-rods/
 *
 * There are n rings and each ring is either red, green, or blue. The rings are distributed across ten
 * rods labeled from 0 to 9.
 * You are given a string rings of length 2n that describes the n rings that are placed onto the rods.
 * Every two characters in rings forms a color-position pair that is used to describe each ring where:
 *  The first character of the ith pair denotes the ith ring's color ('R', 'G', 'B').
 *  The second character of the ith pair denotes the rod that the ith ring is placed on ('0' to '9').
 * For example, "R3G2B1" describes n == 3 rings: a red ring placed onto the rod labeled 3, a green ring
 * placed onto the rod labeled 2, and a blue ring placed onto the rod labeled 1.
 * Return the number of rods that have all three colors of rings on them.
 *
 * @tags    #hash-table #bit-hash
 */


/**
 * @reference   Keep Multiplying Found Values by Two
 *              https://leetcode.com/problems/keep-multiplying-found-values-by-two/
 *
 * You are given an array of integers nums. You are also given an integer original which is the first
 * number that needs to be searched for in nums.
 * You then do the following steps:
 *  If original is found in nums, multiply it by two (i.e., set original = 2 * original).
 *  Otherwise, stop the process.
 *  Repeat this process with the new number as long as you keep finding the number.
 * Return the final value of original.
 * 1 <= nums[i], original <= 1000
 *
 * @tags    #hash-table
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
 *
 * @tags    #hash-table
 */


/**
 * @reference   Find Duplicate File in System
 *              https://leetcode.com/problems/find-duplicate-file-in-system/
 *
 * Given a list paths of directory info, including the directory path, and all the files with contents
 * in this directory, return all the duplicate files in the file system in terms of their paths. You may
 * return the answer in any order.
 * A group of duplicate files consists of at least two files that have the same content.
 * A single directory info string in the input list has the following format:
 *  "root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"
 * It means there are n files (f1.txt, f2.txt ... fn.txt) with content (f1_content, f2_content ...
 * fn_content) respectively in the directory "root/d1/d2/.../dm". Note that n >= 1 and m >= 0. If m = 0,
 * it means the directory is just the root directory.
 * The output is a list of groups of duplicate file paths. For each group, it contains all the file
 * paths of the files that have the same content. A file path is a string that has the following format:
 *  "directory_path/file_name.txt"
 * Follow up:
 * Imagine you are given a real file system, how will you search files? DFS or BFS?
 * If the file content is very large (GB level), how will you modify your solution?
 * If you can only read the file by 1kb each time, how will you modify your solution?
 * What is the time complexity of your modified solution? What is the most time-consuming part and
 * memory-consuming part of it? How to optimize?
 * How to make sure the duplicated files you find are not false positive?
 *
 * @tags    #hash-table
 */


/**
 * @reference   Minimum Rounds to Complete All Tasks
 *              https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/
 *
 * You are given a 0-indexed integer array tasks, where tasks[i] represents the difficulty level of a
 * task. In each round, you can complete either 2 or 3 tasks of the same difficulty level.
 * Return the minimum rounds required to complete all the tasks, or -1 if it is not possible to complete
 * all the tasks.
 *
 * @tags    #hash-table
 */
auto MinRounds(const ArrayType &tasks) {
    const auto counts = ToFrequencyHashTable(tasks);

    int result = 0;
    for (const auto &[_, c] : counts) {
        if (c == 1) {
            return -1;
        }
        result += (c + 2) / 3;
    }

    return result;
}


/**
 * @reference   Equal Row and Column Pairs
 *              https://leetcode.com/problems/equal-row-and-column-pairs/
 *
 * Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri, cj) such that row ri and
 * column cj are equal.
 * A row and column pair is considered equal if they contain the same elements in the same order (i.e.,
 * an equal array).
 *
 * @tags    #hash-table
 */
auto NumEqualPairs(const MatrixType &grid) {
    const auto N = grid.size();

    std::map<MatrixType::value_type, int> column_map;
    for (std::size_t c = 0; c < N; ++c) {
        MatrixType::value_type column;
        for (std::size_t r = 0; r < N; ++r) {
            column.push_back(grid[r][c]);
        }

        ++(column_map[column]);
    }

    int result = 0;
    for (const auto &row : grid) {
        if (const auto iter = column_map.find(row); iter != column_map.cend()) {
            result += iter->second;
        }
    }

    return result;
}


/**
 * @reference   Group the People Given the Group Size They Belong To
 *              https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/
 *
 * There are n people that are split into some unknown number of groups. Each person is labeled with a
 * unique ID from 0 to n - 1.
 * You are given an integer array groupSizes, where groupSizes[i] is the size of the group that person i
 * is in. For example, if groupSizes[1] = 3, then person 1 must be in a group of size 3.
 * Return a list of groups such that each person i is in a group of size groupSizes[i].
 * Each person should appear in exactly one group, and every person must be in a group. If there are
 * multiple answers, return any of them. It is guaranteed that there will be at least one valid solution
 * for the given input.
 *
 * @tags    #greedy #hash-table
 */


/**
 * @reference   Convert an Array Into a 2D Array With Conditions
 *              https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/
 *
 * You are given an integer array nums. You need to create a 2D array from nums satisfying the following
 * conditions:
 *  The 2D array should contain only the elements of the array nums.
 *  Each row in the 2D array contains distinct integers.
 *  The number of rows in the 2D array should be minimal.
 * Return the resulting array. If there are multiple answers, return any of them.
 * Note that the 2D array can have a different number of elements on each row.
 */


/**
 * @reference   Minimum Number of Operations to Make Array Empty
 *              https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/
 *
 * You are given a 0-indexed array nums consisting of positive integers.
 * There are two types of operations that you can apply on the array any number of times:
 *  Choose two elements with equal values and delete them from the array.
 *  Choose three elements with equal values and delete them from the array.
 * Return the minimum number of operations required to make the array empty, or -1 if it is not
 * possible.
 */


/**
 * @reference   Minimum Number of Steps to Make Two Strings Anagram
 *              https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/
 *
 * You are given two strings of the same length s and t. In one step you can choose any character of t
 * and replace it with another character.
 * Return the minimum number of steps to make t an anagram of s.
 * An Anagram of a string is a string that contains the same characters with a different (or the same)
 * ordering.
 */


/**
 * @reference   Minimum Number of Steps to Make Two Strings Anagram II
 *              https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram-ii/
 *
 * You are given two strings s and t. In one step, you can append any character to either s or t.
 * Return the minimum number of steps to make s and t anagrams of each other.
 * An anagram of a string is a string that contains the same characters with a different (or the same)
 * ordering.
 */


/**
 * @reference   Determine if Two Strings Are Close
 *              https://leetcode.com/problems/determine-if-two-strings-are-close/
 *
 * Two strings are considered close if you can attain one from the other using the following operations:
 *  Operation 1: Swap any two existing characters.
 *      For example, abcde -> aecdb
 *  Operation 2: Transform every occurrence of one existing character into another existing character,
 *  and do the same with the other character.
 *      For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
 * You can use the operations on either string as many times as necessary.
 * Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.
 * word1 and word2 contain only lowercase English letters.
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


/**
 * @reference   Maximum Odd Binary Number
 *              https://leetcode.com/problems/maximum-odd-binary-number/
 *
 * You are given a binary string s that contains at least one '1'.
 * You have to rearrange the bits in such a way that the resulting binary number is the maximum odd
 * binary number that can be created from this combination.
 * Return a string representing the maximum odd binary number that can be created from the given
 * combination.
 * Note that the resulting string can have leading zeros.
 */


/**
 * @reference   Count Elements With Maximum Frequency
 *              https://leetcode.com/problems/count-elements-with-maximum-frequency/
 *
 * You are given an array nums consisting of positive integers.
 * Return the total frequencies of elements in nums such that those elements all have the maximum
 * frequency.
 * The frequency of an element is the number of occurrences of that element in the array.
 *
 * @tags    #hash-table #min-max-element
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


const ArrayType SAMPLE1M = {2, 2, 3, 3, 2, 4, 4, 4, 4, 4};
const ArrayType SAMPLE2M = {2, 3, 3};


THE_BENCHMARK(MinRounds, SAMPLE1M);

SIMPLE_TEST(MinRounds, TestSAMPLE1, 4, SAMPLE1M);
SIMPLE_TEST(MinRounds, TestSAMPLE2, -1, SAMPLE2M);


// clang-format off
const MatrixType SAMPLE1G = {
    {3, 2, 1},
    {1, 7, 6},
    {2, 7, 7}
};

const MatrixType SAMPLE2G = {
    {3, 1, 2, 2},
    {1, 4, 4, 5},
    {2, 4, 2, 2},
    {2, 4, 2, 2}
};
// clang-format on


THE_BENCHMARK(NumEqualPairs, SAMPLE2G);

SIMPLE_TEST(NumEqualPairs, TestSAMPLE1, 1, SAMPLE1G);
SIMPLE_TEST(NumEqualPairs, TestSAMPLE2, 3, SAMPLE2G);


THE_BENCHMARK(DetermineIfTwoStrsAreClose, "abc", "bca");

SIMPLE_TEST(DetermineIfTwoStrsAreClose, TestSAMPLE1, true, "abc", "bca");
SIMPLE_TEST(DetermineIfTwoStrsAreClose, TestSAMPLE2, true, "cabbba", "abbccc");
SIMPLE_TEST(DetermineIfTwoStrsAreClose, TestSAMPLE3, false, "a", "aa");
