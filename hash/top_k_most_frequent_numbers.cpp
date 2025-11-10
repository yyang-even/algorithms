#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Find top k (or most frequent) numbers in a stream
 *              https://www.geeksforgeeks.org/find-top-k-or-most-frequent-numbers-in-a-stream/
 *
 * Given an array of n numbers. Your task is to read numbers from the array and keep at-most K numbers
 * at the top (According to their decreasing frequency) every time a new number is read. We basically
 * need to print top k numbers sorted by frequency when input stream has included k distinct elements,
 * else need to print all distinct elements sorted by frequency.
 *
 * @tags    #hash-table #sorting
 */
auto FindTopKMostFrequentNumbers_Stream(const ArrayType &stream, const ArrayType::size_type K) {
    assert(K);

    std::unordered_map<ArrayType::value_type, ArrayType::size_type> frequency_map;
    ArrayType top_numbers(K + 1);
    std::vector<ArrayType> outputs;

    for (const auto number : stream) {

        const auto last_index = std::min(frequency_map.size(), K);
        top_numbers[last_index] = number;
        ++frequency_map[number];

        const auto last = std::next(top_numbers.begin(), last_index);
        auto iter = std::find(top_numbers.begin(), last, number);
        const auto is_new_number = (last_index != K) and (iter == last);
        for (auto prev = iter; iter != top_numbers.begin(); iter = prev) {
            prev = std::prev(iter);
            if (frequency_map[*prev] < frequency_map[*iter]) {
                std::iter_swap(prev, iter);
            } else {
                break;
            }
        }

        outputs.emplace_back(top_numbers.begin(), std::next(last, is_new_number));
    }

    return outputs;
}


/**
 * @reference   Find k numbers with most occurrences in the given array
 *              https://www.geeksforgeeks.org/find-k-numbers-occurrences-given-array/
 *
 * Given an array of n numbers and a positive integer k. The problem is to find k numbers with most
 * occurrences, i.e., the top k numbers having the maximum frequency. If two numbers have same frequency
 * then the larger number should be given preference. The numbers should be displayed in decreasing
 * order of their frequencies. It is assumed that the array consists of k numbers with most occurrences.
 *
 * @reference   Top K Frequent Elements
 *              https://leetcode.com/problems/top-k-frequent-elements/
 *
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return the
 * answer in any order.
 * It is guaranteed that the answer is unique.
 * Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's
 * size.
 *
 * @tags    #hash-table #sorting
 */
auto FindTopKMostFrequentNumbers(const ArrayType &numbers, const ArrayType::size_type K) {
    assert(K);

    const auto frequency_map = ToFrequencyHashTable(numbers);

    std::vector<decltype(frequency_map)::const_iterator> number_frequency_array;
    for (auto iter = frequency_map.cbegin(); iter != frequency_map.cend(); ++iter) {
        number_frequency_array.push_back(iter);
    }

    constexpr auto compare_function = [](const auto &lhs, const auto &rhs) {
        return lhs->second == rhs->second ? lhs->first > rhs->first : lhs->second > rhs->second;
    };
    const auto kth = std::next(number_frequency_array.begin(), std::min(frequency_map.size(), K));
    std::partial_sort(
        number_frequency_array.begin(), kth, number_frequency_array.end(), compare_function);

    ArrayType output;
    for (auto iter = number_frequency_array.cbegin(); iter != kth; ++iter) {
        output.push_back((*iter)->first);
    }

    return output;
}


/**
 * @reference   Top K Frequent Words
 *              https://leetcode.com/problems/top-k-frequent-words/
 *
 * Given an array of strings words and an integer k, return the k most frequent strings.
 * Return the answer sorted by the frequency from highest to lowest. Sort the words with the same
 * frequency by their lexicographical order.
 * Follow-up: Could you solve it in O(n log(k)) time and O(n) extra space?
 *
 * @tags    #hash-table #sorting
 */


/**
 * @reference   Program to find second most frequent character
 *              https://www.geeksforgeeks.org/c-program-find-second-frequent-character/
 *
 * Given a string, find the second most frequent character in it. Expected time complexity is O(n) where
 * n is the length of the input string.
 *
 * @tags    #hash-table #sorting
 */
auto FindSecondFrequentChar(const std::string_view input) {
    assert(input.size() > 1);

    const auto counters = ToFrequencyHashTable(input);

    int first_frequency = 0, second_frequency = 0;
    char first {}, second {};
    for (const auto [key, count] : counters) {
        if (count > first_frequency) {
            second_frequency = first_frequency;
            second = first;
            first_frequency = count;
            first = key;
        } else if (count > second_frequency) {
            second_frequency = count;
            second = key;
        }
    }

    return second;
}


/**
 * @reference   Unique Number of Occurrences
 *              https://leetcode.com/problems/unique-number-of-occurrences/
 *
 * Given an array of integers arr, return true if the number of occurrences of each value in the array
 * is unique, or false otherwise.
 *
 * @tags    #hash-table
 */


/**
 * @reference   Sort elements by frequency | Set 1
 *              https://www.geeksforgeeks.org/sort-elements-by-frequency/
 * @reference   Sort elements by frequency | Set 2
 *              https://www.geeksforgeeks.org/sort-elements-by-frequency-set-2/
 * @reference   Sorting Array Elements By Frequency | Set 3 (Using STL)
 *              https://www.geeksforgeeks.org/sorting-array-elements-frequency-set-3-using-stl/
 * @reference   Sort elements by frequency | Set 4 (Efficient approach using hash)
 *              https://www.geeksforgeeks.org/sort-elements-frequency-set-4-efficient-approach-using-hash/
 * @reference   Sort elements by frequency | Set 5 (using Java Map)
 *              https://www.geeksforgeeks.org/sort-elements-by-frequency-set-5-using-java-map/
 *
 * Print the elements of an array in the decreasing frequency if 2 numbers have same frequency then
 * print the one which came first.
 *
 * @reference   Sort a string according to the frequency of characters
 *              https://www.geeksforgeeks.org/sort-a-string-according-to-the-frequency-of-characters/
 *
 * @reference   Sort Array by Increasing Frequency
 *              https://leetcode.com/problems/sort-array-by-increasing-frequency/
 *
 * Given an array of integers nums, sort the array in increasing order based on the frequency of the
 * values. If multiple values have the same frequency, sort them in decreasing order.
 * Return the sorted array.
 *
 * @tags    #hash-table #sorting
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
 * Print the elements of an array in the decreasing frequency if 2 numbers have same frequency then
 * keeps their relative order.
 *
 * @tags    #hash-table #sorting
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
 * Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency
 * of a character is the number of times it appears in the string.
 * Return the sorted string. If there are multiple answers, return any of them.
 *
 * @tags    #hash-table #sorting
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
 * @reference   Find X-Sum of All K-Long Subarrays I
 *              https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/
 *
 * You are given an array nums of n integers and two integers k and x.
 * The x-sum of an array is calculated by the following procedure:
 *  Count the occurrences of all elements in the array.
 *  Keep only the occurrences of the top x most frequent elements. If two elements have the same number
 *      of occurrences, the element with the bigger value is considered more frequent.
 *  Calculate the sum of the resulting array.
 * Note that if an array has less than x distinct elements, its x-sum is the sum of the array.
 * Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray
 * nums[i..i + k - 1].
 *
 * @tags    #hash-table #sliding-window #sorting
 */


/**
 * @reference   Reorder Data in Log Files
 *              https://leetcode.com/problems/reorder-data-in-log-files/
 *
 * You are given an array of logs. Each log is a space-delimited string of words, where the first word
 * is the identifier. There are two types of logs:
 *  Letter-logs: All words (except the identifier) consist of lowercase English letters.
 *  Digit-logs: All words (except the identifier) consist of digits.
 * Reorder these logs so that:
 *  The letter-logs come before all digit-logs.
 *  The letter-logs are sorted lexicographically by their contents. If their contents are the same, then
 *      sort them lexicographically by their identifiers.
 *  The digit-logs maintain their relative ordering.
 * Return the final order of the logs.
 *
 * @tags    #sorting
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
 * @reference   Least Number of Unique Integers after K Removals
 *              https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/
 *
 * Given an array of integers arr and an integer k. Find the least number of unique integers after
 * removing exactly k elements.
 *
 * @tags    #hash-table #sorting
 */

} //namespace


const ArrayType SAMPLE = {1, 1, 2, 3, 3, 3, 4, 5, 2, 2, 2};
const std::vector<ArrayType> EXPECTED1 = {{1},
                                          {1},
                                          {1, 2},
                                          {1, 2, 3},
                                          {1, 3, 2},
                                          {3, 1, 2},
                                          {3, 1, 2, 4},
                                          {3, 1, 2, 4},
                                          {3, 1, 2, 4},
                                          {3, 2, 1, 4},
                                          {2, 3, 1, 4}};
const std::vector<ArrayType> EXPECTED2 = {{1}, {1}, {1}, {1}, {1}, {3}, {3}, {3}, {3}, {3}, {2}};


THE_BENCHMARK(FindTopKMostFrequentNumbers_Stream, SAMPLE, 4);

SIMPLE_TEST(FindTopKMostFrequentNumbers_Stream, TestSAMPLE1, EXPECTED1, SAMPLE, 4);
SIMPLE_TEST(FindTopKMostFrequentNumbers_Stream, TestSAMPLE2, EXPECTED2, SAMPLE, 1);


const ArrayType SAMPLE1 = {3, 1, 4, 4, 5, 2, 6, 1};
const ArrayType EXPECTED_ARRAY1 = {4, 1};
const ArrayType SAMPLE2 = {7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9};
const ArrayType EXPECTED_ARRAY2 = {5, 11, 7, 10};


THE_BENCHMARK(FindTopKMostFrequentNumbers, SAMPLE1, 2);

SIMPLE_TEST(FindTopKMostFrequentNumbers, TestSAMPLE1, EXPECTED_ARRAY1, SAMPLE1, 2);
SIMPLE_TEST(FindTopKMostFrequentNumbers, TestSAMPLE2, EXPECTED_ARRAY2, SAMPLE2, 4);


THE_BENCHMARK(FindSecondFrequentChar, "geeksforgee");

SIMPLE_TEST(FindSecondFrequentChar, TestSAMPLE1, 'g', "geeksforgee");
SIMPLE_TEST(FindSecondFrequentChar, TestSAMPLE2, 'b', "aabababa");


const ArrayType SAMPLE1S = {2, 5, 2, 8, 5, 6, 8, 8};
const ArrayType EXPECTED1S = {8, 8, 8, 2, 2, 5, 5, 6};
const ArrayType EXPECTED_STABLE1 = {8, 8, 8, 2, 5, 2, 5, 6};

const ArrayType SAMPLE2S = {2, 5, 2, 6, -1, 9999999, 5, 8, 8, 8};
const ArrayType EXPECTED2S = {8, 8, 8, 2, 2, 5, 5, 6, -1, 9999999};
const ArrayType EXPECTED_STABLE2 = {8, 8, 8, 2, 5, 2, 5, 6, -1, 9999999};

const ArrayType SAMPLE3S = {2, 3, 2, 4, 5, 12, 2, 3, 3, 3, 12};
const ArrayType EXPECTED3S = {3, 3, 3, 3, 2, 2, 2, 12, 12, 4, 5};


THE_BENCHMARK(SortByFrequency, SAMPLE1S);

SIMPLE_TEST(SortByFrequency, TestSAMPLE1, EXPECTED1S, SAMPLE1S);
SIMPLE_TEST(SortByFrequency, TestSAMPLE2, EXPECTED2S, SAMPLE2S);
SIMPLE_TEST(SortByFrequency, TestSAMPLE3, EXPECTED3S, SAMPLE3S);


THE_BENCHMARK(SortByFrequency_Stable, SAMPLE1S);

SIMPLE_TEST(SortByFrequency_Stable, TestSAMPLE1, EXPECTED_STABLE1, SAMPLE1S);
SIMPLE_TEST(SortByFrequency_Stable, TestSAMPLE2, EXPECTED_STABLE2, SAMPLE2S);
SIMPLE_TEST(SortByFrequency_Stable, TestSAMPLE3, EXPECTED3S, SAMPLE3S);


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
