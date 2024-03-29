#include "common_header.h"

#include "largest_sum_contiguous_subarray.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Maximum Subarray Sum using Divide and Conquer algorithm
 *              https://www.geeksforgeeks.org/maximum-subarray-sum-using-divide-and-conquer-algorithm/
 */
auto maxCrossingSum(const ArrayType &elements, const int low, const int mid, const int high) {
    ArrayType::value_type sum = 0;
    auto left_sum = std::numeric_limits<ArrayType::value_type>::min();
    for (auto i = mid; i >= low; --i) {
        sum = sum + elements[i];
        if (sum > left_sum) {
            left_sum = sum;
        }
    }

    sum = 0;
    int right_sum = std::numeric_limits<ArrayType::value_type>::min();
    for (auto i = mid + 1; i <= high; ++i) {
        sum = sum + elements[i];
        if (sum > right_sum) {
            right_sum = sum;
        }
    }

    return std::max({left_sum + right_sum, left_sum, right_sum});
}

auto LargestSumContiguousSubarray_DivideAndConquer(const ArrayType &elements,
                                                   const int low,
                                                   const int high) {
    if (low == high) {
        return elements[low];
    }

    const int mid = (low + high) / 2;

    return std::max({LargestSumContiguousSubarray_DivideAndConquer(elements, low, mid),
                     LargestSumContiguousSubarray_DivideAndConquer(elements, mid + 1, high),
                     maxCrossingSum(elements, low, mid, high)});
}

inline auto LargestSumContiguousSubarray_DivideAndConquer(const ArrayType &elements) {
    assert(not elements.empty());

    return LargestSumContiguousSubarray_DivideAndConquer(elements, 0, elements.size() - 1);
}


inline auto TheLargestSumContiguousSubarray(const ArrayType &elements) {
    ArrayType the_max_sum_subarray;
    LargestSumContiguousSubarray_Kadane(elements, &the_max_sum_subarray);
    return the_max_sum_subarray;
}


/**
 * @reference   Maximum subarray sum in O(n) using prefix sum
 *              https://www.geeksforgeeks.org/maximum-subarray-sum-using-prefix-sum/
 *
 * @note    This solution is less efficient, and slightly more complicate.
 */


/**
 * @reference   Longest subarray having maximum sum
 *              https://www.geeksforgeeks.org/longest-subarray-having-maximum-sum/
 *
 * Given an array arr[] containing n integers. The problem is to find the length of the subarray having
 * maximum sum. If there exists two or more subarrays with maximum sum then print the length of the
 * longest subarray.
 */
inline auto LengthOfLargestSumContiguousSubarray(const ArrayType &elements) {
    return TheLargestSumContiguousSubarray(elements).size();
}


/** Smallest sum contiguous subarray
 *
 * @reference   https://www.geeksforgeeks.org/smallest-sum-contiguous-subarray/
 */
auto SmallestSumContiguousSubarray(const ArrayType &elements) {
    assert(not elements.empty());

    auto min_so_far = std::numeric_limits<ArrayType::value_type>::max();
    auto min_ending_here = min_so_far;

    for (const auto number : elements) {
        if (min_ending_here > 0) {
            min_ending_here = 0;
        }
        min_ending_here += number;

        min_so_far = std::min(min_so_far, min_ending_here);
    }

    return min_so_far;
}


/**
 * @reference   Maximum Sum Circular Subarray
 *              https://leetcode.com/problems/maximum-sum-circular-subarray/
 *
 * Given a circular integer array nums of length n, return the maximum possible sum of a non-empty
 * subarray of nums.
 * A circular array means the end of the array connects to the beginning of the array. Formally, the
 * next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 + n) % n].
 * A subarray may only include each element of the fixed buffer nums at most once. Formally, for a
 * subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.
 */
auto MaxSumCircularSubarray(const ArrayType &nums) {
    int curr_max {}, curr_min {}, total {};
    auto max_sum = nums.front();
    auto min_sum = nums.front();

    for (const auto n : nums) {
        curr_max = std::max(curr_max + n, n);
        max_sum = std::max(max_sum, curr_max);

        curr_min = std::min(curr_min + n, n);
        min_sum = std::min(min_sum, curr_min);

        total += n;
    }

    return max_sum > 0 ? std::max(max_sum, total - min_sum) : max_sum;
}

} //namespace


const ArrayType SAMPLE1 = {-1, -2, -3};
const ArrayType EXPECTED1 = {-1};

const ArrayType SAMPLE2 = {-2, -3, 4, -1, -2, 1, 5, -3};
const ArrayType EXPECTED2 = {4, -1, -2, 1, 5};

const ArrayType SAMPLE3 = {-2, -1, -3};

const ArrayType SAMPLE4 = {5, -2, -1, 3, -4};
const ArrayType EXPECTED4 = {5, -2, -1, 3};

const ArrayType SAMPLE5 = {2, 3, -8, -1, 2, 4, -2, 3};
const ArrayType EXPECTED5 = {2, 4, -2, 3};


THE_BENCHMARK(LargestSumContiguousSubarray_Kadane, SAMPLE2);

SIMPLE_TEST(LargestSumContiguousSubarray_Kadane, TestSAMPLE1, -1, SAMPLE1);
SIMPLE_TEST(LargestSumContiguousSubarray_Kadane, TestSAMPLE2, 7, SAMPLE2);
SIMPLE_TEST(LargestSumContiguousSubarray_Kadane, TestSAMPLE4, 5, SAMPLE4);
SIMPLE_TEST(LargestSumContiguousSubarray_Kadane, TestSAMPLE5, 7, SAMPLE5);


THE_BENCHMARK(LargestSumContiguousSubarray_DivideAndConquer, SAMPLE2);

SIMPLE_TEST(LargestSumContiguousSubarray_DivideAndConquer, TestSAMPLE1, -1, SAMPLE1);
SIMPLE_TEST(LargestSumContiguousSubarray_DivideAndConquer, TestSAMPLE2, 7, SAMPLE2);
SIMPLE_TEST(LargestSumContiguousSubarray_DivideAndConquer, TestSAMPLE4, 5, SAMPLE4);
SIMPLE_TEST(LargestSumContiguousSubarray_DivideAndConquer, TestSAMPLE5, 7, SAMPLE5);


THE_BENCHMARK(TheLargestSumContiguousSubarray, SAMPLE2);

SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE3, EXPECTED1, SAMPLE3);
SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE4, EXPECTED4, SAMPLE4);
SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE5, EXPECTED5, SAMPLE5);


THE_BENCHMARK(LengthOfLargestSumContiguousSubarray, SAMPLE2);

SIMPLE_TEST(LengthOfLargestSumContiguousSubarray, TestSAMPLE1, EXPECTED1.size(), SAMPLE1);
SIMPLE_TEST(LengthOfLargestSumContiguousSubarray, TestSAMPLE2, EXPECTED2.size(), SAMPLE2);
SIMPLE_TEST(LengthOfLargestSumContiguousSubarray, TestSAMPLE4, EXPECTED4.size(), SAMPLE4);
SIMPLE_TEST(LengthOfLargestSumContiguousSubarray, TestSAMPLE5, EXPECTED5.size(), SAMPLE5);


const ArrayType SAMPLE6 = {3, -4, 2, -3, -1, 7, -5};
const ArrayType SAMPLE7 = {2, 6, 8, 1, 4};


THE_BENCHMARK(SmallestSumContiguousSubarray, SAMPLE6);

SIMPLE_TEST(SmallestSumContiguousSubarray, TestSAMPLE6, -6, SAMPLE6);
SIMPLE_TEST(SmallestSumContiguousSubarray, TestSAMPLE7, 1, SAMPLE7);


const ArrayType SAMPLE1C = {1, -2, 3, -2};
const ArrayType SAMPLE2C = {5, -3, 5};
const ArrayType SAMPLE3C = {-3, -2, -3};


THE_BENCHMARK(MaxSumCircularSubarray, SAMPLE1C);

SIMPLE_TEST(MaxSumCircularSubarray, TestSAMPLE1, 3, SAMPLE1C);
SIMPLE_TEST(MaxSumCircularSubarray, TestSAMPLE2, 10, SAMPLE2C);
SIMPLE_TEST(MaxSumCircularSubarray, TestSAMPLE3, -2, SAMPLE3C);
