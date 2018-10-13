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
