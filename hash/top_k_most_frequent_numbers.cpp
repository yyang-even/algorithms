#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<int>;

/** Find top k (or most frequent) numbers in a stream
 *
 * @reference   https://www.geeksforgeeks.org/find-top-k-or-most-frequent-numbers-in-a-stream/
 *
 * Given an array of n numbers. Your task is to read numbers from the array and keep at-most K
 * numbers at the top (According to their decreasing frequency) every time a new number is read.
 * We basically need to print top k numbers sorted by frequency when input stream has included
 * k distinct elements, else need to print all distinct elements sorted by frequency.
 */
auto FindTopKMostFrequentNumbers_Stream(const ArrayType &stream,
                                        const ArrayType::size_type K) {
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
        const auto is_new_number = (last_index != K) and (iter == last) ;
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


/** Find k numbers with most occurrences in the given array
 *
 * @reference   https://www.geeksforgeeks.org/find-k-numbers-occurrences-given-array/
 *
 * Given an array of n numbers and a positive integer k. The problem is to find k numbers
 * with most occurrences, i.e., the top k numbers having the maximum frequency. If two
 * numbers have same frequency then the larger number should be given preference. The
 * numbers should be displayed in decreasing order of their frequencies. It is assumed
 * that the array consists of k numbers with most occurrences.
 */
auto FindTopKMostFrequentNumbers(const ArrayType &numbers,
                                 const ArrayType::size_type K) {
    assert(K);

    const auto frequency_map = ToFrequencyHashTable(numbers);

    std::vector<decltype(frequency_map)::const_iterator> number_frequency_array;
    for (auto iter = frequency_map.cbegin(); iter != frequency_map.cend(); ++iter) {
        number_frequency_array.push_back(iter);
    }

    constexpr auto compare_function = [](const auto & lhs, const auto & rhs) {
        return lhs->second == rhs->second ? lhs->first > rhs->first : lhs->second > rhs->second;
    };
    const auto kth = std::next(number_frequency_array.begin(),
                               std::min(frequency_map.size(), K));
    std::partial_sort(number_frequency_array.begin(), kth, number_frequency_array.end(),
                      compare_function);

    ArrayType output;
    for (auto iter = number_frequency_array.cbegin(); iter != kth; ++iter) {
        output.push_back((*iter)->first);
    }

    return output;
}

}//namespace


const ArrayType SAMPLE = {1, 1, 2, 3, 3, 3, 4, 5, 2, 2, 2};
const std::vector<ArrayType> EXPECTED1 = {{1}, {1}, {1, 2}, {1, 2, 3}, {1, 3, 2}, {3, 1, 2}, {3, 1, 2, 4}, {3, 1, 2, 4}, {3, 1, 2, 4}, {3, 2, 1, 4}, {2, 3, 1, 4}};
const std::vector<ArrayType> EXPECTED2 = {{1}, {1}, {1}, {1}, {1}, {3}, {3}, {3}, {3}, {3}, {2}};


SIMPLE_BENCHMARK(FindTopKMostFrequentNumbers_Stream, Sample1, SAMPLE, 4);

SIMPLE_TEST(FindTopKMostFrequentNumbers_Stream, TestSAMPLE1, EXPECTED1, SAMPLE, 4);
SIMPLE_TEST(FindTopKMostFrequentNumbers_Stream, TestSAMPLE2, EXPECTED2, SAMPLE, 1);


const ArrayType SAMPLE1 = {3, 1, 4, 4, 5, 2, 6, 1};
const ArrayType EXPECTED_ARRAY1 = {4, 1};
const ArrayType SAMPLE2 = {7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9};
const ArrayType EXPECTED_ARRAY2 = {5, 11, 7, 10};


SIMPLE_BENCHMARK(FindTopKMostFrequentNumbers, Sample1, SAMPLE1, 2);

SIMPLE_TEST(FindTopKMostFrequentNumbers, TestSAMPLE1, EXPECTED_ARRAY1, SAMPLE1, 2);
SIMPLE_TEST(FindTopKMostFrequentNumbers, TestSAMPLE2, EXPECTED_ARRAY2, SAMPLE2, 4);
