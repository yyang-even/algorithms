#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Smallest subarray with sum greater than a given value
 *
 * @reference   https://www.geeksforgeeks.org/minimum-length-subarray-sum-greater-given-value/
 *
 * Given an array of integers and a number x, find the smallest subarray with sum greater than the given value.
 */
auto SmallestSubarrayWithSumGreaterThanGivenValue(const ArrayType &integers,
                                                  const ArrayType::value_type x) {
    assert(not integers.empty());

    auto start = integers.cbegin();
    auto current_sum = *start;
    ArrayType::difference_type min_length = integers.size() + 1;

    for (auto i = start + 1; i != integers.cend(); ++i) {
        while (current_sum > x) {
            const auto length = i - start;
            if (length < min_length) {
                min_length = length;
            }
            current_sum -= *start++;
        }

        current_sum += *i;
    }

    return min_length;
}

}//namespace


const ArrayType SAMPLE1 = {1, 4, 45, 6, 0, 19};
const ArrayType SAMPLE2 = {1, 10, 5, 2, 7};
const ArrayType SAMPLE3 = {1, 11, 100, 1, 0, 200, 3, 2, 1, 250};
const ArrayType SAMPLE4 = {1, 2, 4};
const ArrayType SAMPLE5 = {9, 1, 2, 4};


SIMPLE_BENCHMARK(SmallestSubarrayWithSumGreaterThanGivenValue, Sample1, SAMPLE1, 51);

SIMPLE_TEST(SmallestSubarrayWithSumGreaterThanGivenValue, TestSample1, 3u, SAMPLE1, 51);
SIMPLE_TEST(SmallestSubarrayWithSumGreaterThanGivenValue, TestSample2, 1u, SAMPLE2, 9);
SIMPLE_TEST(SmallestSubarrayWithSumGreaterThanGivenValue, TestSample3, 4u, SAMPLE3,
            280);
SIMPLE_TEST(SmallestSubarrayWithSumGreaterThanGivenValue, TestSample4,
            static_cast<ArrayType::difference_type>(SAMPLE4.size() + 1), SAMPLE4, 8);
SIMPLE_TEST(SmallestSubarrayWithSumGreaterThanGivenValue, TestSample5, 1u, SAMPLE5, 8);
