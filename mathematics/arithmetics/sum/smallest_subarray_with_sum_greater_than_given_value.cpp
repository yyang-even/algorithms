#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Smallest subarray with sum greater than a given value
 *
 * @reference   https://www.geeksforgeeks.org/minimum-length-subarray-sum-greater-given-value/
 *
 * Given an array of integers and a number x, find the smallest subarray with sum greater
 * than the given value.
 *
 * @reference   Minimum Size Subarray Sum
 *              https://leetcode.com/problems/minimum-size-subarray-sum/
 *
 * Given an array of positive integers nums and a positive integer target, return the minimal length of
 * a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0
 * instead.
 * Follow up: If you have figured out the O(n) solution, try coding another solution of which the time
 * complexity is O(n log(n)).
 */
auto SmallestSubarraySumGreaterThanK(const ArrayType &integers, const ArrayType::value_type k) {
    assert(not integers.empty());

    auto start = integers.cbegin();
    auto current_sum = *start;
    ArrayType::difference_type min_length = integers.size() + 1;

    for (auto i = start + 1; i != integers.cend(); ++i) {
        while (current_sum > k) {
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


auto SmallestSubarraySumNoLessThanK_IndexSlidingWindow(const ArrayType &nums,
                                                       const ArrayType::value_type k) {
    std::size_t left = 0;
    std::size_t right = 0;
    unsigned sum = 0;

    std::size_t result = INT_MAX;
    while (true) {
        if (sum < k and right < nums.size()) {
            sum += nums[right++];
        } else if (sum >= k and left < right) {
            sum -= nums[left++];
        } else {
            break;
        }

        if (sum >= k) {
            result = std::min(result, right - left);
        }
    }

    return result == INT_MAX ? 0 : result;
}


auto SmallestSubarraySumNoLessThanK_BinarySearch(const ArrayType &nums,
                                                 const ArrayType::value_type k) {
    ArrayType sums(nums.size() + 1, 0);
    for (std::size_t i = 1; i <= nums.size(); ++i) {
        sums[i] = sums[i - 1] + nums[i - 1];
    }

    int result = INT_MAX;
    for (int i = nums.size(); i >= 0 and sums[i] >= k; --i) {
        const int j = std::upper_bound(sums.cbegin(), sums.cend(), sums[i] - k) - sums.cbegin();
        result = std::min(result, i - j + 1);
    }

    return result == INT_MAX ? 0 : result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 4, 45, 6, 0, 19};
const ArrayType SAMPLE2 = {1, 10, 5, 2, 7};
const ArrayType SAMPLE3 = {1, 11, 100, 1, 0, 200, 3, 2, 1, 250};
const ArrayType SAMPLE4 = {1, 2, 4};
const ArrayType SAMPLE5 = {9, 1, 2, 4};
const ArrayType SAMPLE6 = {2, 3, 1, 2, 4, 3};
const ArrayType SAMPLE7 = {1, 4, 4};
const ArrayType SAMPLE8 = {1, 1, 1, 1, 1, 1, 1, 1};


THE_BENCHMARK(SmallestSubarraySumGreaterThanK, SAMPLE1, 51);

SIMPLE_TEST(SmallestSubarraySumGreaterThanK, TestSample1, 3, SAMPLE1, 51);
SIMPLE_TEST(SmallestSubarraySumGreaterThanK, TestSample2, 1, SAMPLE2, 9);
SIMPLE_TEST(SmallestSubarraySumGreaterThanK, TestSample3, 4, SAMPLE3, 280);
SIMPLE_TEST(SmallestSubarraySumGreaterThanK, TestSample4, SAMPLE4.size() + 1, SAMPLE4, 8);
SIMPLE_TEST(SmallestSubarraySumGreaterThanK, TestSample5, 1, SAMPLE5, 8);


THE_BENCHMARK(SmallestSubarraySumNoLessThanK_IndexSlidingWindow, SAMPLE1, 51);

SIMPLE_TEST(SmallestSubarraySumNoLessThanK_IndexSlidingWindow, TestSample1, 2, SAMPLE1, 51);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_IndexSlidingWindow, TestSample2, 1, SAMPLE2, 9);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_IndexSlidingWindow, TestSample3, 4, SAMPLE3, 280);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_IndexSlidingWindow, TestSample4, 0, SAMPLE4, 8);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_IndexSlidingWindow, TestSample5, 1, SAMPLE5, 8);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_IndexSlidingWindow, TestSample6, 2, SAMPLE6, 7);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_IndexSlidingWindow, TestSample7, 1, SAMPLE7, 4);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_IndexSlidingWindow, TestSample8, 0, SAMPLE8, 11);


THE_BENCHMARK(SmallestSubarraySumNoLessThanK_BinarySearch, SAMPLE1, 51);

SIMPLE_TEST(SmallestSubarraySumNoLessThanK_BinarySearch, TestSample1, 2, SAMPLE1, 51);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_BinarySearch, TestSample2, 1, SAMPLE2, 9);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_BinarySearch, TestSample3, 4, SAMPLE3, 280);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_BinarySearch, TestSample4, 0, SAMPLE4, 8);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_BinarySearch, TestSample5, 1, SAMPLE5, 8);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_BinarySearch, TestSample6, 2, SAMPLE6, 7);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_BinarySearch, TestSample7, 1, SAMPLE7, 4);
SIMPLE_TEST(SmallestSubarraySumNoLessThanK_BinarySearch, TestSample8, 0, SAMPLE8, 11);
