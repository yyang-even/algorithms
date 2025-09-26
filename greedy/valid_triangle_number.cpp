#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Valid Triangle Number
 *              https://leetcode.com/problems/valid-triangle-number/
 *
 * Given an integer array nums, return the number of triplets chosen from the array that can make
 * triangles if we take them as side lengths of a triangle.
 *
 * @tags    #greedy #sorting #binary-search #two-pointers
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
            const auto lower =
                std::lower_bound(nums.cbegin() + k, nums.cend(), nums[i] + nums[j]);
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
 * Given an integer array nums, return the largest perimeter of a triangle with a non-zero area, formed
 * from three of these lengths. If it is impossible to form any triangle of a non-zero area, return 0.
 *
 * @tags    #greedy #sorting
 */


/**
 * @reference   Minimum Subsequence in Non-Increasing Order
 *              https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/
 *
 * Given the array nums, obtain a subsequence of the array whose sum of elements is strictly greater
 * than the sum of the non included elements in such subsequence.
 * If there are multiple solutions, return the subsequence with minimum size and if there still exist
 * multiple solutions, return the subsequence with the maximum total sum of all its elements. A
 * subsequence of an array can be obtained by erasing some (possibly zero) elements from the array.
 * Note that the solution with the given constraints is guaranteed to be unique. Also return the answer
 * sorted in non-increasing order.
 *
 * @tags    #greedy #sorting
 */


/**
 * @reference   Find Polygon With the Largest Perimeter
 *              https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/
 *
 * You are given an array of positive integers nums of length n.
 * A polygon is a closed plane figure that has at least 3 sides. The longest side of a polygon is
 * smaller than the sum of its other sides.
 * Conversely, if you have k (k >= 3) positive real numbers a1, a2, a3, ..., ak where a1 <= a2 <= a3 <=
 * ... <= ak and a1 + a2 + a3 + ... + ak-1 > ak, then there always exists a polygon with k sides whose
 * lengths are a1, a2, a3, ..., ak.
 * The perimeter of a polygon is the sum of lengths of its sides.
 * Return the largest possible perimeter of a polygon whose sides can be formed from nums, or -1 if it
 * is not possible to create a polygon.
 *
 * @tags    #greedy #sorting
 */

} //namespace


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
