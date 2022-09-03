#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<int>;

/** Sort elements by frequency | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/sort-elements-by-frequency/
 * @reference   Sort elements by frequency | Set 2
 *              https://www.geeksforgeeks.org/sort-elements-by-frequency-set-2/
 * @reference   Sorting Array Elements By Frequency | Set 3 (Using STL)
 *              https://www.geeksforgeeks.org/sorting-array-elements-frequency-set-3-using-stl/
 * @reference   Sort elements by frequency | Set 4 (Efficient approach using hash)
 *              https://www.geeksforgeeks.org/sort-elements-frequency-set-4-efficient-approach-using-hash/
 * @reference   Sort elements by frequency | Set 5 (using Java Map)
 *              https://www.geeksforgeeks.org/sort-elements-by-frequency-set-5-using-java-map/
 *
 * Print the elements of an array in the decreasing frequency if 2 numbers have same
 * frequency then print the one which came first.
 *
 * @reference   Sort a string according to the frequency of characters
 *              https://www.geeksforgeeks.org/sort-a-string-according-to-the-frequency-of-characters/
 *
 * @reference   Sort Array by Increasing Frequency
 *              https://leetcode.com/problems/sort-array-by-increasing-frequency/
 *
 * Given an array of integers nums, sort the array in increasing order based on the
 * frequency of the values. If multiple values have the same frequency, sort them in
 * decreasing order. Return the sorted array.
 */
auto SortByFrequency(ArrayType elements) {
    using MinIndex_Count_Pair = std::pair<ArrayType::size_type, ArrayType::size_type>;
    std::unordered_map<ArrayType::value_type, MinIndex_Count_Pair> counter;

    const auto N = elements.size();
    for (ArrayType::size_type i = 0; i < N; ++i) {
        const auto elem = elements[i];
        if (const auto iter = counter.find(elem); iter == counter.end()) {
            counter.emplace(elem, MinIndex_Count_Pair {i, 1});
        } else {
            ++(iter->second.second);
        }
    }

    std::sort(elements.begin(), elements.end(), [&counter](const auto &lhs, const auto &rhs) {
        const auto [lhs_index, lhs_count] = counter.at(lhs);
        const auto [rhs_index, rhs_count] = counter.at(rhs);
        if (lhs_count == rhs_count) {
            return lhs_index < rhs_index;
        } else {
            return lhs_count > rhs_count;
        }
    });

    return elements;
}


/**
 * Print the elements of an array in the decreasing frequency if 2 numbers have same
 * frequency then keeps their relative order.
 */
inline auto SortByFrequency_Stable(ArrayType elements) {
    const auto counter = ToFrequencyHashTable(elements);
    std::stable_sort(
        elements.begin(), elements.end(), [&counter](const auto &lhs, const auto &rhs) {
            return counter.at(lhs) > counter.at(rhs);
        });

    return elements;
}


/**
 * @reference   Sort Characters By Frequency
 *              https://leetcode.com/problems/sort-characters-by-frequency/
 *
 * Given a string s, sort it in decreasing order based on the frequency of the characters.
 * The frequency of a character is the number of times it appears in the string. Return
 * the sorted string. If there are multiple answers, return any of them.
 */
auto SortByFrequency_Unstable(const std::string_view s) {
    const auto counts = ToFrequencyHashTable(s);

    using FrequencyCharPair = std::pair<int, char>;
    std::vector<FrequencyCharPair> char_groups;
    for (const auto [c, frequency] : counts) {
        char_groups.emplace_back(frequency, c);
    }

    std::sort(char_groups.begin(), char_groups.end(), std::greater<FrequencyCharPair> {});

    std::string result;
    for (const auto &[frequency, c] : char_groups) {
        result.append(frequency, c);
    }

    return result;
}


auto SortByFrequency_Unstable_BucketSort(const std::string_view s) {
    const auto counts = ToFrequencyHashTable(s);

    std::vector<std::vector<char>> buckets(s.size() + 1);
    for (const auto [c, frequency] : counts) {
        buckets[frequency].push_back(c);
    }

    std::string result;
    for (int frequency = s.size(); frequency > 0; --frequency) {
        for (const auto c : buckets[frequency]) {
            result.append(frequency, c);
        }
    }

    return result;
}


/**
 * @reference   Reorder Data in Log Files
 *              https://leetcode.com/problems/reorder-data-in-log-files/
 *
 * You are given an array of logs. Each log is a space-delimited string of words, where
 * the first word is the identifier. There are two types of logs:
 *  Letter-logs: All words (except the identifier) consist of lowercase English letters.
 *  Digit-logs: All words (except the identifier) consist of digits.
 * Reorder these logs so that:
 *  The letter-logs come before all digit-logs.
 *  The letter-logs are sorted lexicographically by their contents. If their contents are
 *      the same, then sort them lexicographically by their identifiers.
 *  The digit-logs maintain their relative ordering.
 * Return the final order of the logs.
 */
auto SortLogs(std::vector<std::string_view> logs) {
    std::stable_sort(logs.begin(), logs.end(), [](const auto &one, const auto &another) {
        const auto isOneDigit = std::isdigit(one.back());
        const auto isAnotherDigit = std::isdigit(another.back());

        if (not isOneDigit and isAnotherDigit) {
            return true;
        } else if (not isOneDigit and not isAnotherDigit) {
            const auto one_space_position = one.find(' ');
            const auto one_identifier = one.substr(0, one_space_position);
            const auto one_content = one.substr(one_space_position + 1);
            const auto another_space_pos = another.find(' ');
            const auto another_identifier = another.substr(0, another_space_pos);
            const auto another_content = another.substr(another_space_pos + 1);

            if (one_content == another_content) {
                return one_identifier < another_identifier;
            }
            return one_content < another_content;
        }

        return false;
    });

    return logs;
}


/**
 * @reference   Top K Frequent Elements
 *              https://leetcode.com/problems/top-k-frequent-elements/
 *
 * Given an integer array nums and an integer k, return the k most frequent elements. You
 * may return the answer in any order.
 * It is guaranteed that the answer is unique.
 * Follow up: Your algorithm's time complexity must be better than O(n log n), where n is
 * the array's size.
 */

} //namespace


const ArrayType SAMPLE1 = {2, 5, 2, 8, 5, 6, 8, 8};
const ArrayType EXPECTED1 = {8, 8, 8, 2, 2, 5, 5, 6};
const ArrayType EXPECTED_STABLE1 = {8, 8, 8, 2, 5, 2, 5, 6};

const ArrayType SAMPLE2 = {2, 5, 2, 6, -1, 9999999, 5, 8, 8, 8};
const ArrayType EXPECTED2 = {8, 8, 8, 2, 2, 5, 5, 6, -1, 9999999};
const ArrayType EXPECTED_STABLE2 = {8, 8, 8, 2, 5, 2, 5, 6, -1, 9999999};

const ArrayType SAMPLE3 = {2, 3, 2, 4, 5, 12, 2, 3, 3, 3, 12};
const ArrayType EXPECTED3 = {3, 3, 3, 3, 2, 2, 2, 12, 12, 4, 5};


THE_BENCHMARK(SortByFrequency, SAMPLE1);

SIMPLE_TEST(SortByFrequency, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortByFrequency, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(SortByFrequency, TestSAMPLE3, EXPECTED3, SAMPLE3);


THE_BENCHMARK(SortByFrequency_Stable, SAMPLE1);

SIMPLE_TEST(SortByFrequency_Stable, TestSAMPLE1, EXPECTED_STABLE1, SAMPLE1);
SIMPLE_TEST(SortByFrequency_Stable, TestSAMPLE2, EXPECTED_STABLE2, SAMPLE2);
SIMPLE_TEST(SortByFrequency_Stable, TestSAMPLE3, EXPECTED3, SAMPLE3);


const std::vector<std::string_view> SAMPLE1L = {
    "dig1 8 1 5 1", "let1 art can", "dig2 3 6", "let2 own kit dig", "let3 art zero"};
const std::vector<std::string_view> EXPECTED1L = {
    "let1 art can", "let3 art zero", "let2 own kit dig", "dig1 8 1 5 1", "dig2 3 6"};

const std::vector<std::string_view> SAMPLE2L = {
    "a1 9 2 3 1", "g1 act car", "zo4 4 7", "ab1 off key dog", "a8 act zoo"};
const std::vector<std::string_view> EXPECTED2L = {
    "g1 act car", "a8 act zoo", "ab1 off key dog", "a1 9 2 3 1", "zo4 4 7"};


THE_BENCHMARK(SortLogs, SAMPLE1L);

SIMPLE_TEST(SortLogs, TestSAMPLE1, EXPECTED1L, SAMPLE1L);
SIMPLE_TEST(SortLogs, TestSAMPLE2, EXPECTED2L, SAMPLE2L);


THE_BENCHMARK(SortByFrequency_Unstable, "tree");

SIMPLE_TEST(SortByFrequency_Unstable, TestSAMPLE1, "eet", "tee");
SIMPLE_TEST(SortByFrequency_Unstable, TestSAMPLE2, "aaacc", "ccaaa");
SIMPLE_TEST(SortByFrequency_Unstable, TestSAMPLE3, "bbA", "Abb");


THE_BENCHMARK(SortByFrequency_Unstable_BucketSort, "tree");

SIMPLE_TEST(SortByFrequency_Unstable_BucketSort, TestSAMPLE1, "eet", "tee");
SIMPLE_TEST(SortByFrequency_Unstable_BucketSort, TestSAMPLE2, "aaacc", "ccaaa");
SIMPLE_TEST(SortByFrequency_Unstable_BucketSort, TestSAMPLE3, "bbA", "Abb");
