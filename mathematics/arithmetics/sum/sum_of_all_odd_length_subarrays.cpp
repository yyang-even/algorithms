#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Sum of All Odd Length Subarrays
 *
 * @reference   https://leetcode.com/problems/sum-of-all-odd-length-subarrays/
 *
 * Given an array of positive integers arr, calculate the sum of all possible odd-length
 * subarrays.
 * A subarray is a contiguous subsequence of the array.
 * Return the sum of all odd-length subarrays of arr.
 * @hint    In total, there are k = (i + 1) * (n - i) subarrays, that contains A[i].
 *          And there are (k + 1) / 2 subarrays with odd length, that contains A[i].
 *          And there are k / 2 subarrays with even length, that contains A[i].
 */
auto SumOfAllOddLengthSubarrays(const ArrayType &nums) {
    int result = 0;
    const int N = nums.size();
    for (int i = 0; i < N; ++i) {
        result += ((i + 1) * (N - i) + 1) / 2 * nums[i];
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {1, 4, 2, 5, 3};
const ArrayType SAMPLE2 = {1, 2};
const ArrayType SAMPLE3 = {10, 11, 12};


THE_BENCHMARK(SumOfAllOddLengthSubarrays, SAMPLE1);

SIMPLE_TEST(SumOfAllOddLengthSubarrays, TestSAMPLE1, 58, SAMPLE1);
SIMPLE_TEST(SumOfAllOddLengthSubarrays, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(SumOfAllOddLengthSubarrays, TestSAMPLE3, 66, SAMPLE3);
