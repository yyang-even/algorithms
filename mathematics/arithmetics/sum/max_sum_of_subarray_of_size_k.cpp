#include "common_header.h"

#include "mathematics/numbers/numbers.h"


namespace {

using ArrayType = std::vector<int>;

/** Find maximum (or minimum) sum of a subarray of size k
 *
 * @reference   https://www.geeksforgeeks.org/find-maximum-minimum-sum-subarray-size-k/
 * @reference   Window Sliding Technique
 *              https://www.geeksforgeeks.org/window-sliding-technique/
 */
auto MaxSumOfSubarrayOfSizeK(const ArrayType &elements, const ArrayType::size_type K) {
    assert(elements.size() >= K);

    auto max_sum = std::accumulate(elements.cbegin(), elements.cbegin() + K, 0);
    auto current_sum = max_sum;
    for (auto i = K; i < elements.size(); ++i) {
        current_sum += elements[i] - elements[i - K];
        if (max_sum < current_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}


/**
 * @reference   Subarray of size k with given sum
 *              https://www.geeksforgeeks.org/subarray-of-size-k-with-given-sum/
 */


/**
 * @reference   Largest product of a subarray of size k
 *              https://www.geeksforgeeks.org/largest-product-subarray-size-k/
 */


/**
 * @reference   Find the subarray of size K with minimum XOR
 *              https://www.geeksforgeeks.org/find-the-subarray-of-size-k-with-minimum-xor/
 */


/**
 * @reference   Maximum Average Subarray I
 *              https://leetcode.com/problems/maximum-average-subarray-i/
 *
 * You are given an integer array nums consisting of n elements, and an integer k. Find
 * a contiguous subarray whose length is equal to k that has the maximum average value
 * and return this value. Any answer with a calculation error less than 10-5 will be
 * accepted.
 */


/**
 * @reference   Maximum Average Subarray II
 *              https://protegejj.gitbook.io/algorithm-practice/leetcode/binary-search/644-maximum-average-subarray-ii
 *
 * Given an array consisting ofnintegers, find the contiguous subarray whose length is
 * greater than or equal tokthat has the maximum average value. And you need to output
 * the maximum average value.
 */
auto isValidSubarrayAverage(const ArrayType &nums, const double average,
                            const std::size_t k) {
    double prefix_sum = 0;
    std::size_t i = 0;
    for (; i < k; ++i) {
        prefix_sum += nums[i] - average;
    }

    if (prefix_sum >= 0) {
        return true;
    }

    double before_window_prefix_sum = 0;
    double min_before_window_sum = 0;
    for (; i < nums.size(); ++i) {
        prefix_sum += nums[i] - average;
        before_window_prefix_sum += nums[i - k] - average;
        min_before_window_sum = std::min(min_before_window_sum,
                                         before_window_prefix_sum);

        if (prefix_sum > min_before_window_sum) {
            return true;
        }
    }

    return false;
}

auto MaxAverageNoShorterThanK(const ArrayType &nums, const int k) {
    const auto minmax_pair = std::minmax_element(nums.cbegin(), nums.cend());

    double left = *minmax_pair.first;
    double right = *minmax_pair.second;
    while (right - left > epsilon) {
        const double mid = (left + right) / 2;

        if (isValidSubarrayAverage(nums, mid, k)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return left;
}

}//namespace


const ArrayType SAMPLE1 = {100, 200, 300, 400};
const ArrayType SAMPLE2 = {1, 4, 2, 10, 23, 3, 1, 0, 20};


THE_BENCHMARK(MaxSumOfSubarrayOfSizeK, SAMPLE1, 2);

SIMPLE_TEST(MaxSumOfSubarrayOfSizeK, TestSAMPLE1, 700, SAMPLE1, 2);
SIMPLE_TEST(MaxSumOfSubarrayOfSizeK, TestSAMPLE2, 39, SAMPLE2, 4);


const ArrayType SAMPLE3 = {1, 12, -5, -6, 50, 3};


THE_BENCHMARK(MaxAverageNoShorterThanK, SAMPLE3, 4);

SIMPLE_TEST(CloseEnough, TestSAMPLE3, true,
            12.75, MaxAverageNoShorterThanK(SAMPLE3, 4));
