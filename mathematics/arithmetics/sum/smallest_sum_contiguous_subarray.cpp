#include "common_header.h"

using ArrayType = std::vector<int>;
/** Smallest sum contiguous subarray
 *
 * @reference   https://www.geeksforgeeks.org/smallest-sum-contiguous-subarray/
 *
 * Given an array containing n integers. The problem is to find the sum of the
 * elements of the contiguous subarray having the smallest(minimum) sum.
 */
auto SmallestSumContiguousSubarray(const ArrayType &integers) {
    auto min_ending_here = std::numeric_limits<ArrayType::value_type>::max();
    auto min_so_far = min_ending_here;

    for (const auto num : integers) {
        if (min_ending_here > 0) {
            min_ending_here = num;
        } else {
            min_ending_here += num;
        }
        if (min_so_far > min_ending_here) {
            min_so_far = min_ending_here;
        }
    }

    return min_so_far;
}


const ArrayType SAMPLE1 = {3, -4, 2, -3, -1, 7, -5};
const ArrayType SAMPLE2 = {2, 6, 8, 1, 4};

SIMPLE_BENCHMARK(SmallestSumContiguousSubarray, SAMPLE1);

SIMPLE_TEST(SmallestSumContiguousSubarray, TestSAMPLE1, -6, SAMPLE1);
SIMPLE_TEST(SmallestSumContiguousSubarray, TestSAMPLE2, 1, SAMPLE2);
