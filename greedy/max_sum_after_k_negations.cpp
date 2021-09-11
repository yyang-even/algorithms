#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Maximize Sum Of Array After K Negations
 *
 * @reference   https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/
 *
 * Given an integer array nums and an integer k, modify the array in the following way:
 *  choose an index i and replace nums[i] with -nums[i].
 * You should apply this process exactly k times. You may choose the same index i
 * multiple times. Return the largest possible sum of the array after modifying it in
 * this way.
 */
auto MaxSumAfterKNegations(ArrayType nums, int k) {
    std::sort(nums.begin(), nums.end());

    int left = 0;
    int right = nums.size() - 1;
    int sum = 0;
    while (left < right) {
        const auto next =
            (std::abs(nums[left]) > std::abs(nums[right])) ? nums[left++] : nums[right--];
        if (next < 0 and k-- > 0) {
            sum -= next;
        } else {
            sum += next;
        }
    }

    return sum + ((k > 0 and k % 2 == 1) ? -1 : 1) * nums[left];
}

}//namespace


const ArrayType SAMPLE1 = {4, 2, 3};
const ArrayType SAMPLE2 = {3, -1, 0, 2};
const ArrayType SAMPLE3 = {2, -3, -1, 5, -4};
const ArrayType SAMPLE4 = {-8, 3, -5, -3, -5, -2};


THE_BENCHMARK(MaxSumAfterKNegations, SAMPLE1, 1);

SIMPLE_TEST(MaxSumAfterKNegations, TestSAMPLE1, 5, SAMPLE1, 1);
SIMPLE_TEST(MaxSumAfterKNegations, TestSAMPLE2, 6, SAMPLE2, 3);
SIMPLE_TEST(MaxSumAfterKNegations, TestSAMPLE3, 13, SAMPLE3, 2);
SIMPLE_TEST(MaxSumAfterKNegations, TestSAMPLE4, 22, SAMPLE4, 6);
