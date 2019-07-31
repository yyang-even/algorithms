#include "common_header.h"


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
auto FindTopKMostFrequentNumbers(const ArrayType &stream, const ArrayType::size_type K) {
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

}//namespace


const ArrayType SAMPLE = {1, 1, 2, 3, 3, 3, 4, 5, 2, 2, 2};
const std::vector<ArrayType> EXPECTED1 = {{1}, {1}, {1, 2}, {1, 2, 3}, {1, 3, 2}, {3, 1, 2}, {3, 1, 2, 4}, {3, 1, 2, 4}, {3, 1, 2, 4}, {3, 2, 1, 4}, {2, 3, 1, 4}};
const std::vector<ArrayType> EXPECTED2 = {{1}, {1}, {1}, {1}, {1}, {3}, {3}, {3}, {3}, {3}, {2}};


SIMPLE_BENCHMARK(FindTopKMostFrequentNumbers, SAMPLE, 4);

SIMPLE_TEST(FindTopKMostFrequentNumbers, TestSAMPLE1, EXPECTED1, SAMPLE, 4);
SIMPLE_TEST(FindTopKMostFrequentNumbers, TestSAMPLE2, EXPECTED2, SAMPLE, 1);
