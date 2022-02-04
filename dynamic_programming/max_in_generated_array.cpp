#include "common_header.h"


namespace {

/** Get Maximum in Generated Array
 *
 * @reference   https://leetcode.com/problems/get-maximum-in-generated-array/
 *
 * You are given an integer n. A 0-indexed integer array nums of length n + 1 is generated
 * in the following way:
 *  nums[0] = 0
 *  nums[1] = 1
 *  nums[2 * i] = nums[i] when 2 <= 2 * i <= n
 *  nums[2 * i + 1] = nums[i] + nums[i + 1] when 2 <= 2 * i + 1 <= n
 * Return the maximum integer in the array nums.
 */
auto MaxInGeneratedArray(const int n) {
    if (n < 2) {
        return n;
    }

    std::vector<int> nums = {0, 1};
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        if (i % 2 == 0) {
            nums.push_back(nums[i / 2]);
        } else {
            nums.push_back(nums[i / 2] + nums[i / 2 + 1]);
        }

        result = std::max(result, nums.back());
    }

    return result;
}

}//namespace


THE_BENCHMARK(MaxInGeneratedArray, 15);

SIMPLE_TEST(MaxInGeneratedArray, TestSAMPLE1, 5, 15);
SIMPLE_TEST(MaxInGeneratedArray, TestSAMPLE2, 3, 7);
SIMPLE_TEST(MaxInGeneratedArray, TestSAMPLE3, 1, 2);
SIMPLE_TEST(MaxInGeneratedArray, TestSAMPLE4, 2, 3);
