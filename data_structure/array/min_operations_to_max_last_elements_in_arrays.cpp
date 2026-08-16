#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Minimum Operations to Maximize Last Elements in Arrays
 *              https://leetcode.com/problems/minimum-operations-to-maximize-last-elements-in-arrays/
 *
 * You are given two 0-indexed integer arrays, nums1 and nums2, both having length n.
 * You are allowed to perform a series of operations (possibly none).
 * In an operation, you select an index i in the range [0, n - 1] and swap the values of nums1[i] and
 * nums2[i].
 * Your task is to find the minimum number of operations required to satisfy the following conditions:
 *  nums1[n - 1] is equal to the maximum value among all elements of nums1, i.e., nums1[n - 1] =
 *  max(nums1[0], nums1[1], ..., nums1[n - 1]).
 *  nums2[n - 1] is equal to the maximum value among all elements of nums2, i.e., nums2[n - 1] =
 *  max(nums2[0], nums2[1], ..., nums2[n - 1]).
 * Return an integer denoting the minimum number of operations needed to meet both conditions, or -1 if
 * it is impossible to satisfy both conditions.
 */
auto countOperations(const ArrayType &nums1,
                     const int last1,
                     const ArrayType &nums2,
                     const int last2) {
    const int N = nums1.size();

    int count = 0;
    for (int i = 0; i < N - 1; ++i) {
        if (nums1[i] <= last1 and nums2[i] <= last2) {
        } else if (nums1[i] <= last2 and nums2[i] <= last1) {
            ++count;
        } else {
            return -1;
        }
    }

    return count;
}

int MinOperations(const ArrayType &nums1, const ArrayType &nums2) {
    const auto count1 = countOperations(nums1, nums1.back(), nums2, nums2.back());
    const auto count2 = countOperations(nums1, nums2.back(), nums2, nums1.back());

    if (count1 == -1 and count2 == -1) {
        return -1;
    }
    return std::min(count1, count2 + 1);
}

} //namespace


const ArrayType SAMPLE1A = {1, 2, 7};
const ArrayType SAMPLE1B = {4, 5, 3};

const ArrayType SAMPLE2A = {2, 3, 4, 5, 9};
const ArrayType SAMPLE2B = {8, 8, 4, 4, 4};

const ArrayType SAMPLE3A = {1, 5, 4};
const ArrayType SAMPLE3B = {2, 5, 3};


THE_BENCHMARK(MinOperations, SAMPLE1A, SAMPLE1B);

SIMPLE_TEST(MinOperations, TestSAMPLE1, 1, SAMPLE1A, SAMPLE1B);
SIMPLE_TEST(MinOperations, TestSAMPLE2, 2, SAMPLE2A, SAMPLE2B);
SIMPLE_TEST(MinOperations, TestSAMPLE3, -1, SAMPLE3A, SAMPLE3B);
