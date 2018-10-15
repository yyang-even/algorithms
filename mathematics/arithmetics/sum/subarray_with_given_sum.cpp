#include "common_header.h"

using ArrayType = std::vector<int>;

/** Find subarray with given sum | Set 1 (Nonnegative Numbers)
 *
 * @reference   https://www.geeksforgeeks.org/find-subarray-with-given-sum/
 *
 * Given an unsorted array of nonnegative integers, find a continuous
 * subarray which adds to a given number.
 */
std::pair<int, int> FindSubarrayWithGivenSum(const ArrayType &integers,
        const ArrayType::value_type SUM) {
    assert(not integers.empty());

    auto start = integers.cbegin();
    auto current_sum = *start;
    for (auto i = start + 1; i != integers.cend(); ++i) {
        while (current_sum > SUM and start < i - 1) {
            current_sum -= *start++;
        }

        if (current_sum == SUM) {
            return std::make_pair(start - integers.cbegin(), i - integers.cbegin() - 1);
        }

        current_sum += *i;
    }

    return std::make_pair(-1, -1);
}

/** Find subarray with given sum | Set 2 (Handles Negative Numbers)
 *
 * @reference   https://www.geeksforgeeks.org/find-subarray-with-given-sum-in-array-of-integers/
 */
std::pair<int, int> FindSubarrayWithGivenSumMap(const ArrayType &integers,
        const ArrayType::value_type SUM) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> sum_index_map;
    ArrayType::value_type current_sum = 0;

    for (ArrayType::size_type i = 0ul; i < integers.size(); ++i) {
        current_sum += integers[i];

        if (current_sum == SUM) {
            return std::make_pair(0, i);
        }

        const auto expected_subarray_sum = current_sum - SUM;
        const auto iter = sum_index_map.find(expected_subarray_sum);
        if (iter != sum_index_map.cend()) {
            return std::make_pair(iter->second + 1, i);
        }

        sum_index_map[current_sum] = i;
    }

    return std::make_pair(-1, -1);
}


const ArrayType SAMPLE1 = {1, 4, 20, 3, 10, 5};
const ArrayType SAMPLE2 = {1, 4, 0, 0, 3, 10, 5};
const ArrayType SAMPLE3 = {1, 4};
const ArrayType SAMPLE4 = {15, 2, 4, 8, 9, 5, 10};

SIMPLE_BENCHMARK(FindSubarrayWithGivenSum, SAMPLE1, 33);

SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample1, std::make_pair(2, 4), SAMPLE1, 33);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample2, std::make_pair(1, 4), SAMPLE2, 7);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample3, std::make_pair(-1, -1), SAMPLE3, 0);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample4, std::make_pair(1, 4), SAMPLE4, 23);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample5, std::make_pair(3, 3), SAMPLE4, 8);

const ArrayType SAMPLE6 = {10, 2, -2, -20, 10};
const ArrayType SAMPLE7 = { -10, 0, 2, -2, -20, 10};

SIMPLE_BENCHMARK(FindSubarrayWithGivenSumMap, SAMPLE1, 33);

SIMPLE_TEST(FindSubarrayWithGivenSumMap, TestSample1, std::make_pair(2, 4), SAMPLE1, 33);
SIMPLE_TEST(FindSubarrayWithGivenSumMap, TestSample2, std::make_pair(1, 4), SAMPLE2, 7);
SIMPLE_TEST(FindSubarrayWithGivenSumMap, TestSample3, std::make_pair(-1, -1), SAMPLE3, 0);
SIMPLE_TEST(FindSubarrayWithGivenSumMap, TestSample4, std::make_pair(1, 4), SAMPLE4, 23);
SIMPLE_TEST(FindSubarrayWithGivenSumMap, TestSample5, std::make_pair(3, 3), SAMPLE4, 8);
SIMPLE_TEST(FindSubarrayWithGivenSumMap, TestSample6, std::make_pair(0, 3), SAMPLE6, -10);
SIMPLE_TEST(FindSubarrayWithGivenSumMap, TestSample7, std::make_pair(-1, -1), SAMPLE7, 20);
