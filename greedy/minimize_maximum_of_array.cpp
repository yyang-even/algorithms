#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Minimize Maximum of Array
 *
 * @reference   https://leetcode.com/problems/minimize-maximum-of-array/
 *
 * You are given a 0-indexed array nums comprising of n non-negative integers.
 * In one operation, you must:
 *  Choose an integer i such that 1 <= i < n and nums[i] > 0.
 *  Decrease nums[i] by 1.
 *  Increase nums[i - 1] by 1.
 * Return the minimum possible value of the maximum integer of nums after performing any number of
 * operations.
 */
auto MinimizeMaxOfArray(const ArrayType &nums) {
    std::size_t result = 0;
    std::size_t prefix_sum = 0;

    for (std::size_t i = 0; i < nums.size(); ++i) {
        prefix_sum += nums[i];
        result = std::max(result, (prefix_sum + i) / (i + 1));
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {3, 7, 1, 6};
const ArrayType SAMPLE2 = {10, 1};


THE_BENCHMARK(MinimizeMaxOfArray, SAMPLE1);

SIMPLE_TEST(MinimizeMaxOfArray, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(MinimizeMaxOfArray, TestSAMPLE2, 10, SAMPLE2);
