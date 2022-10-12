#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Increasing Triplet Subsequence
 *
 * @reference   https://leetcode.com/problems/increasing-triplet-subsequence/
 *
 * Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that
 * i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.
 * Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space
 * complexity?
 */
auto IncreasingTripletSubsequence(const ArrayType &nums) {
    int first = INT_MAX;
    int second = INT_MAX;

    for (const auto n : nums) {
        if (n <= first) {
            first = n;
        } else if (n <= second) {
            second = n;
        } else {
            return true;
        }
    }

    return false;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5};
const ArrayType SAMPLE2 = {5, 4, 3, 2, 1};
const ArrayType SAMPLE3 = {2, 1, 5, 0, 4, 6};


THE_BENCHMARK(IncreasingTripletSubsequence, SAMPLE1);

SIMPLE_TEST(IncreasingTripletSubsequence, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(IncreasingTripletSubsequence, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(IncreasingTripletSubsequence, TestSAMPLE3, true, SAMPLE3);
