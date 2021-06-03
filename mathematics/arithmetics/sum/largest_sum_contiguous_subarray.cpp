#include "common_header.h"

#include "largest_sum_contiguous_subarray.h"


namespace {

using ArrayType = std::vector<int>;

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
 * Given an array arr[] containing n integers. The problem is to find the length of the
 * subarray having maximum sum. If there exists two or more subarrays with maximum sum
 * then print the length of the longest subarray.
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

}//namespace


const ArrayType SAMPLE1 = { -1, -2, -3};
const ArrayType EXPECTED1 = { -1};

const ArrayType SAMPLE2 = { -2, -3, 4, -1, -2, 1, 5, -3};
const ArrayType EXPECTED2 = {4, -1, -2, 1, 5};

const ArrayType SAMPLE3 = { -2, -1, -3};

const ArrayType SAMPLE4 = {5, -2, -1, 3, -4};
const ArrayType EXPECTED4 = {5, -2, -1, 3};

const ArrayType SAMPLE5 = {2, 3, -8, -1, 2, 4, -2, 3};
const ArrayType EXPECTED5 = {2, 4, -2, 3};


THE_BENCHMARK(LargestSumContiguousSubarray_Kadane, SAMPLE2);

SIMPLE_TEST(LargestSumContiguousSubarray_Kadane, TestSAMPLE1, -1, SAMPLE1);
SIMPLE_TEST(LargestSumContiguousSubarray_Kadane, TestSAMPLE2, 7, SAMPLE2);
SIMPLE_TEST(LargestSumContiguousSubarray_Kadane, TestSAMPLE4, 5, SAMPLE4);
SIMPLE_TEST(LargestSumContiguousSubarray_Kadane, TestSAMPLE5, 7, SAMPLE5);


THE_BENCHMARK(TheLargestSumContiguousSubarray, SAMPLE2);

SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE3, EXPECTED1, SAMPLE3);
SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE4, EXPECTED4, SAMPLE4);
SIMPLE_TEST(TheLargestSumContiguousSubarray, TestSAMPLE5, EXPECTED5, SAMPLE5);


THE_BENCHMARK(LengthOfLargestSumContiguousSubarray, SAMPLE2);

SIMPLE_TEST(LengthOfLargestSumContiguousSubarray, TestSAMPLE1, EXPECTED1.size(),
            SAMPLE1);
SIMPLE_TEST(LengthOfLargestSumContiguousSubarray, TestSAMPLE2, EXPECTED2.size(),
            SAMPLE2);
SIMPLE_TEST(LengthOfLargestSumContiguousSubarray, TestSAMPLE4, EXPECTED4.size(),
            SAMPLE4);
SIMPLE_TEST(LengthOfLargestSumContiguousSubarray, TestSAMPLE5, EXPECTED5.size(),
            SAMPLE5);


const ArrayType SAMPLE6 = {3, -4, 2, -3, -1, 7, -5};
const ArrayType SAMPLE7 = {2, 6, 8, 1, 4};


THE_BENCHMARK(SmallestSumContiguousSubarray, SAMPLE6);

SIMPLE_TEST(SmallestSumContiguousSubarray, TestSAMPLE6, -6, SAMPLE6);
SIMPLE_TEST(SmallestSumContiguousSubarray, TestSAMPLE7, 1, SAMPLE7);
