#include "common_header.h"

#include "subarrays_with_given_sum.h"


namespace {

using ArrayType = std::vector<int>;

/** Find subarray with given sum | Set 1 (Nonnegative Numbers)
 *
 * @reference   https://www.geeksforgeeks.org/find-subarray-with-given-sum/
 *
 * Given an unsorted array of nonnegative integers, find a continuous subarray which adds
 * to a given number.
 */
const auto NOT_FOUND = std::pair(-1, -1);
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
            return std::pair(start - integers.cbegin(), i - integers.cbegin() - 1);
        }

        current_sum += *i;
    }

    return NOT_FOUND;
}


/** Find subarray with given sum | Set 2 (Handles Negative Numbers)
 *
 * @reference   https://www.geeksforgeeks.org/find-subarray-with-given-sum-in-array-of-integers/
 */
std::pair<int, int> FindSubarrayWithGivenSum_Map(const ArrayType &integers,
                                                 const ArrayType::value_type SUM) {
    const auto all_such_arrays = AllSubarraysWithGivenSum(integers, SUM);

    if (all_such_arrays.empty()) {
        return NOT_FOUND;
    } else {
        return all_such_arrays.front();
    }
}


/** Find if there is a subarray with 0 sum
 *
 * @reference   https://www.geeksforgeeks.org/find-if-there-is-a-subarray-with-0-sum/
 *
 * Given an array of positive and negative numbers, find if there is a subarray (of size
 * at-least one) with 0 sum.
 */
bool FindSubarrayWith0Sum(const ArrayType &integers) {
    return not AllSubarraysWithGivenSum(integers, 0).empty();
}


/** Number of subarrays having sum exactly equal to k
 *
 * @reference   https://www.geeksforgeeks.org/number-subarrays-sum-exactly-equal-k/
 *
 * Given an unsorted array of integers, find number of subarrays having sum exactly equal
 * to a given number k.
 */
auto NumberOfSubarraysWithGivenSum(const ArrayType &integers,
                                   const ArrayType::value_type SUM) {
    return AllSubarraysWithGivenSum(integers, SUM).size();
}


/** Find the length of largest subarray with 0 sum
 *
 * @reference   https://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/
 *
 * Given an array of integers, find length of the largest subarray with sum equals to 0.
 */
auto LengthOfLargestSubarrayWith0Sum(const ArrayType &integers) {
    const auto all_such_arrays = AllSubarraysWithGivenSum(integers, 0);
    ArrayType::size_type largest_length = 0;

    for (const auto [left, right] : all_such_arrays) {
        const auto length = right - left + 1ul;
        if (length > largest_length) {
            largest_length = length;
        }
    }

    return largest_length;
}


/**
 * @reference   Largest subarray with equal number of 0s and 1s
 *              https://www.geeksforgeeks.org/largest-subarray-with-equal-number-of-0s-and-1s/
 *
 * @reference   Length of longest Subarray with equal number of odd and even elements
 *              https://www.geeksforgeeks.org/length-of-longest-subarray-with-equal-number-of-odd-and-even-elements/
 */
auto LargestSubarrayWithEqual0sAnd1s(ArrayType elements) {
    std::replace(elements.begin(), elements.end(), 0, -1);
    return LengthOfLargestSubarrayWith0Sum(elements);
}

}//namespace


const ArrayType SAMPLE1 = {1, 4, 20, 3, 10, 5};
const ArrayType SAMPLE2 = {1, 4, 0, 0, 3, 10, 5};
const ArrayType SAMPLE3 = {1, 4};
const ArrayType SAMPLE4 = {15, 2, 4, 8, 9, 5, 10};


THE_BENCHMARK(FindSubarrayWithGivenSum, SAMPLE1, 33);

SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample1, std::pair(2, 4), SAMPLE1, 33);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample2, std::pair(1, 4), SAMPLE2, 7);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample3, NOT_FOUND, SAMPLE3, 0);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample4, std::pair(1, 4), SAMPLE4, 23);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample5, std::pair(3, 3), SAMPLE4, 8);


const ArrayType SAMPLE6 = {10, 2, -2, -20, 10};
const ArrayType SAMPLE7 = { -10, 0, 2, -2, -20, 10};


THE_BENCHMARK(FindSubarrayWithGivenSum_Map, SAMPLE6, 33);

SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample1, std::pair(2, 4), SAMPLE1, 33);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample2, std::pair(1, 4), SAMPLE2, 7);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample3, NOT_FOUND, SAMPLE3, 0);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample4, std::pair(1, 4), SAMPLE4, 23);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample5, std::pair(3, 3), SAMPLE4, 8);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample6, std::pair(0, 3), SAMPLE6, -10);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample7, NOT_FOUND, SAMPLE7, 20);


const ArrayType SAMPLE8 = {4, 2, -3, 1, 6};
const ArrayType SAMPLE9 = {4, 2, 0, 1, 6};
const ArrayType SAMPLE10 = { -3, 2, 3, 1, 6};


THE_BENCHMARK(FindSubarrayWith0Sum, SAMPLE8);

SIMPLE_TEST(FindSubarrayWith0Sum, TestSample8, true, SAMPLE8);
SIMPLE_TEST(FindSubarrayWith0Sum, TestSample9, true, SAMPLE9);
SIMPLE_TEST(FindSubarrayWith0Sum, TestSample10, false, SAMPLE10);


const ArrayType SAMPLE11 = {9, 4, 20, 3, 10, 5};


THE_BENCHMARK(NumberOfSubarraysWithGivenSum, SAMPLE6, -10);

SIMPLE_TEST(NumberOfSubarraysWithGivenSum, TestSample6, 3u, SAMPLE6, -10);
SIMPLE_TEST(NumberOfSubarraysWithGivenSum, TestSample7, 0u, SAMPLE7, 20);
SIMPLE_TEST(NumberOfSubarraysWithGivenSum, TestSample11, 2u, SAMPLE11, 33);


const ArrayType SAMPLE12 = {15, -2, 2, -8, 1, 7, 10, 23};
const ArrayType SAMPLE13 = {1, 2, 3};
const ArrayType SAMPLE14 = {1, 0, 3};


THE_BENCHMARK(LengthOfLargestSubarrayWith0Sum, SAMPLE12);

SIMPLE_TEST(LengthOfLargestSubarrayWith0Sum, TestSample12, 5u, SAMPLE12);
SIMPLE_TEST(LengthOfLargestSubarrayWith0Sum, TestSample13, 0u, SAMPLE13);
SIMPLE_TEST(LengthOfLargestSubarrayWith0Sum, TestSample14, 1u, SAMPLE14);


const ArrayType SAMPLE15 = {1, 0, 1, 1, 1, 0, 0};
const ArrayType SAMPLE16 = {1, 1, 1, 1};
const ArrayType SAMPLE17 = {0, 0, 1, 1, 0};


THE_BENCHMARK(LargestSubarrayWithEqual0sAnd1s, SAMPLE15);

SIMPLE_TEST(LargestSubarrayWithEqual0sAnd1s, TestSample15, 6, SAMPLE15);
SIMPLE_TEST(LargestSubarrayWithEqual0sAnd1s, TestSample16, 0, SAMPLE16);
SIMPLE_TEST(LargestSubarrayWithEqual0sAnd1s, TestSample17, 4, SAMPLE17);
