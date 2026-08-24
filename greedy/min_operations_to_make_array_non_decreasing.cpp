#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Minimum Operations to Make Array Non Decreasing
 *              https://leetcode.com/problems/minimum-operations-to-make-array-non-decreasing/
 *
 * You are given an integer array nums of length n.
 * In one operation, you may choose any subarray nums[l..r] and increase each element in that subarray
 * by x, where x is any positive integer.
 * Return the minimum possible sum of the values of x across all operations required to make the array
 * non-decreasing.
 * An array is non-decreasing if nums[i] <= nums[i + 1] for all 0 <= i < n - 1.
 *
 * @tags    #greedy #sliding-window
 */
auto MinOperations(const ArrayType &nums) {
    long long result = 0;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[i - 1] > nums[i]) {
            result += nums[i - 1] - nums[i];
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {3, 3, 2, 1};
const ArrayType SAMPLE2 = {5, 1, 2, 3};


THE_BENCHMARK(MinOperations, SAMPLE1);

SIMPLE_TEST(MinOperations, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinOperations, TestSAMPLE2, 4, SAMPLE2);
