#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Minimum Operations to Make the Array Increasing
 *
 * @reference   https://leetcode.com/problems/minimum-operations-to-make-the-array-increasing/
 *
 * You are given an integer array nums (0-indexed). In one operation, you can choose an
 * element of the array and increment it by 1.
 *  For example, if nums = [1,2,3], you can choose to increment nums[1] to make
 *      nums = [1,3,3].
 * Return the minimum number of operations needed to make nums strictly increasing.
 * An array nums is strictly increasing if nums[i] < nums[i+1] for all 0 <= i < nums.length - 1.
 * An array of length 1 is trivially strictly increasing.
 */
auto MinOperations(const ArrayType &nums) {
    auto curr = nums.front();
    int result = 0;
    for (const auto n : nums) {
        if (curr <= n) {
            curr = n + 1;
        } else {
            result += curr++ - n;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {1, 1, 1};
const ArrayType SAMPLE2 = {1, 5, 2, 4, 1};
const ArrayType SAMPLE3 = {8};


THE_BENCHMARK(MinOperations, SAMPLE1);

SIMPLE_TEST(MinOperations, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(MinOperations, TestSAMPLE2, 14, SAMPLE2);
SIMPLE_TEST(MinOperations, TestSAMPLE3, 0, SAMPLE3);
