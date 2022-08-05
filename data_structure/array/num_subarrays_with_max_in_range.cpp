#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;


/** Number of subarrays with maximum values in given range
 *
 * @reference   https://www.geeksforgeeks.org/number-subarrays-maximum-value-given-range/
 * @reference   Number of Subarrays with Bounded Maximum
 *              https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/
 *
 * Given an array of N elements and L and R, print the number of sub-arrays such that the value of the
 * maximum array element in that subarray is at least L and at most R.
 */
inline constexpr long numSubarraysOfSize(const unsigned N) {
    return N * (N + 1) / 2;
}

auto NumSubarraysWithMaxInRange(const ArrayType &elements,
                                const ArrayType::value_type left,
                                const ArrayType::value_type right) {
    long result = 0;
    ArrayType::size_type num_no_more_than_right = 0;
    ArrayType::size_type num_smaller_than_left = 0;

    for (const auto an_element : elements) {
        if (an_element > right) {
            result += (numSubarraysOfSize(num_no_more_than_right) -
                       numSubarraysOfSize(num_smaller_than_left));
            num_no_more_than_right = num_smaller_than_left = 0;
        } else if (an_element < left) {
            ++num_no_more_than_right;
            ++num_smaller_than_left;
        } else {
            result -= numSubarraysOfSize(num_smaller_than_left);
            num_smaller_than_left = 0;
            ++num_no_more_than_right;
        }
    }

    result +=
        (numSubarraysOfSize(num_no_more_than_right) - numSubarraysOfSize(num_smaller_than_left));

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {2, 0, 11, 3, 0};
const ArrayType SAMPLE2 = {3, 4, 1};


THE_BENCHMARK(NumSubarraysWithMaxInRange, SAMPLE1, 1, 10);

SIMPLE_TEST(NumSubarraysWithMaxInRange, TestSAMPLE1, 4, SAMPLE1, 1, 10);
SIMPLE_TEST(NumSubarraysWithMaxInRange, TestSAMPLE2, 5, SAMPLE2, 2, 4);
