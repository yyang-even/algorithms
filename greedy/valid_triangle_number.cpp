#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Valid Triangle Number
 *
 * @reference   https://leetcode.com/problems/valid-triangle-number/
 *
 * Given an integer array nums, return the number of triplets chosen from the array that
 * can make triangles if we take them as side lengths of a triangle.
 */
auto ValidTriangleNumber(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    const int SIZE = nums.size();
    int total = 0;
    for (int i = 0; i < SIZE - 2; ++i) {
        auto k = i + 2;
        for (auto j = i + 1; j < SIZE - 1 and nums[i]; ++j) {
            while (k < SIZE and (nums[i] + nums[j] > nums[k])) {
                ++k;
            }
            total += k - j - 1;
        }
    }

    return total;
}


auto ValidTriangleNumber_BinarySearch(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    const int SIZE = nums.size();
    int total = 0;
    for (int i = 0; i < SIZE - 2; ++i) {
        auto k = i + 2;
        for (auto j = i + 1; j < SIZE - 1 and nums[i]; ++j) {
            const auto lower = std::lower_bound(nums.cbegin() + k, nums.cend(), nums[i] + nums[j]);
            k = lower - nums.cbegin();
            total += k - j - 1;
        }
    }

    return total;
}


auto ValidTriangleNumber_TwoPointers(ArrayType nums) {
    std::sort(nums.begin(), nums.end());
    int count = 0;
    for (int k = nums.size() - 1; k >= 1; --k) {
        int low = 0, high = k - 1;
        while (low < high) {
            if (nums[low] + nums[high] > nums[k]) {
                count += (high--) - low;
            } else {
                ++low;
            }
        }

    }
    return count;
}


/**
 * @reference   Largest Perimeter Triangle
 *              https://leetcode.com/problems/largest-perimeter-triangle/
 *
 * Given an integer array nums, return the largest perimeter of a triangle with a
 * non-zero area, formed from three of these lengths. If it is impossible to form any
 * triangle of a non-zero area, return 0.
 */


/**
 * @reference   Minimum Subsequence in Non-Increasing Order
 *              https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/
 *
 * Given the array nums, obtain a subsequence of the array whose sum of elements is
 * strictly greater than the sum of the non included elements in such subsequence. If
 * there are multiple solutions, return the subsequence with minimum size and if there
 * still exist multiple solutions, return the subsequence with the maximum total sum of
 * all its elements. A subsequence of an array can be obtained by erasing some (possibly
 * zero) elements from the array. Note that the solution with the given constraints is
 * guaranteed to be unique. Also return the answer sorted in non-increasing order.
 */

}//namespace


const ArrayType SAMPLE1 = {0, 0, 0};
const ArrayType SAMPLE2 = {2, 2, 3, 4};
const ArrayType SAMPLE3 = {4, 2, 3, 4};


THE_BENCHMARK(ValidTriangleNumber, SAMPLE1);

SIMPLE_TEST(ValidTriangleNumber, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(ValidTriangleNumber, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(ValidTriangleNumber, TestSAMPLE3, 4, SAMPLE3);


THE_BENCHMARK(ValidTriangleNumber_BinarySearch, SAMPLE1);

SIMPLE_TEST(ValidTriangleNumber_BinarySearch, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(ValidTriangleNumber_BinarySearch, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(ValidTriangleNumber_BinarySearch, TestSAMPLE3, 4, SAMPLE3);


THE_BENCHMARK(ValidTriangleNumber_TwoPointers, SAMPLE1);

SIMPLE_TEST(ValidTriangleNumber_TwoPointers, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(ValidTriangleNumber_TwoPointers, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(ValidTriangleNumber_TwoPointers, TestSAMPLE3, 4, SAMPLE3);
