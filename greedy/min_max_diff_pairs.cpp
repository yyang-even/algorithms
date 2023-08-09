#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Minimize the Maximum Difference of Pairs
 *
 * @reference   https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/
 *
 * You are given a 0-indexed integer array nums and an integer p. Find p pairs of indices of nums such
 * that the maximum difference amongst all the pairs is minimized. Also, ensure no index appears more
 * than once amongst the p pairs.
 * Note that for a pair of elements at the index i and j, the difference of this pair is |nums[i] -
 * nums[j]|, where |x| represents the absolute value of x.
 * Return the minimum maximum difference among all p pairs. We define the maximum of an empty set to be
 * zero.
 */
int countValidPairs(const ArrayType &nums, const int threshold) {
    int count = 0;
    for (std::size_t i = 0; i < nums.size() - 1; ++i) {
        if (nums[i + 1] - nums[i] <= threshold) {
            ++count;
            ++i;
        }
    }

    return count;
}

auto MinMaxDiffPairs(ArrayType nums, const int p) {
    std::sort(nums.begin(), nums.end());

    int left = 0;
    int right = nums.back() - nums.front();
    while (left < right) {
        const int mid = (left + right) / 2;

        if (countValidPairs(nums, mid) >= p) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

} //namespace


const ArrayType SAMPLE1 = {10, 1, 2, 7, 1, 3};
const ArrayType SAMPLE2 = {4, 2, 1, 2};
const ArrayType SAMPLE3 = {1, 2, 2, 3};
const ArrayType SAMPLE4 = {2, 2, 3, 4, 4};


THE_BENCHMARK(MinMaxDiffPairs, SAMPLE1, 2);

SIMPLE_TEST(MinMaxDiffPairs, TestSAMPLE1, 1, SAMPLE1, 2);
SIMPLE_TEST(MinMaxDiffPairs, TestSAMPLE2, 0, SAMPLE2, 1);
SIMPLE_TEST(MinMaxDiffPairs, TestSAMPLE3, 1, SAMPLE3, 2);
SIMPLE_TEST(MinMaxDiffPairs, TestSAMPLE4, 0, SAMPLE4, 2);
