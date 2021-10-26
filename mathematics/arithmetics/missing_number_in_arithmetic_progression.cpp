#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the missing number in Arithmetic Progression
 *
 * @reference   https://www.geeksforgeeks.org/find-missing-number-arithmetic-progression/
 *
 * Given an array that represents elements of arithmetic progression in order. One
 * element is missing in the progression, find the missing number.
 *
 * @reference   Missing Number In Arithmetic Progression
 *              https://leetcode.ca/all/1228.html
 *
 * In some array arr, the values were in arithmetic progression: the values
 * arr[i+1] - arr[i] are all equal for every 0 <= i < arr.length - 1. Then, a value
 * from arr was removed that was not the first or last value in the array. Return the
 * removed value.
 */
auto MissingNumberInArithmeticProgression(const ArrayType &nums,
                                          const int left, const int right, const int diff) {
    if (left >= right) {
        return INT_MAX;
    }

    const auto mid = (left + right) / 2;
    if (nums[mid + 1] - nums[mid] != diff) {
        return nums[mid] + diff;
    }

    if (0 < mid and nums[mid] - nums[mid - 1] != diff) {
        return nums[mid - 1] + diff;
    }

    if (nums[mid] == nums.front() + mid * diff) {
        return MissingNumberInArithmeticProgression(nums, mid + 1, right, diff);
    }
    return MissingNumberInArithmeticProgression(nums, left, mid - 1, diff);
}

inline auto MissingNumberInArithmeticProgression(const ArrayType &nums) {
    const int size = nums.size();
    const auto diff = (nums.back() - nums.front()) / size;
    return MissingNumberInArithmeticProgression(nums, 0, nums.size() - 1, diff);
}


auto MissingNumberInArithmeticProgression_Iterative(const ArrayType &nums) {
    const int size = nums.size();
    const auto diff = (nums.back() - nums.front()) / size;

    int left = 0;
    int right = size - 1;
    while (left <= right) {
        const auto mid = (left + right) / 2;
        if ((nums[mid] - nums[0]) / diff == mid) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return nums[right] + diff;
}

}//namespace


const ArrayType SAMPLE1 = {2, 4, 8, 10, 12, 14};
const ArrayType SAMPLE2 = {1, 6, 11, 16, 21, 31};
const ArrayType SAMPLE3 = {5, 7, 11, 13};
const ArrayType SAMPLE4 = {15, 13, 12};


THE_BENCHMARK(MissingNumberInArithmeticProgression, SAMPLE1);

SIMPLE_TEST(MissingNumberInArithmeticProgression, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MissingNumberInArithmeticProgression, TestSAMPLE2, 26, SAMPLE2);
SIMPLE_TEST(MissingNumberInArithmeticProgression, TestSAMPLE3, 9, SAMPLE3);
SIMPLE_TEST(MissingNumberInArithmeticProgression, TestSAMPLE4, 14, SAMPLE4);


THE_BENCHMARK(MissingNumberInArithmeticProgression_Iterative, SAMPLE1);

SIMPLE_TEST(MissingNumberInArithmeticProgression_Iterative, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MissingNumberInArithmeticProgression_Iterative, TestSAMPLE2, 26, SAMPLE2);
SIMPLE_TEST(MissingNumberInArithmeticProgression_Iterative, TestSAMPLE3, 9, SAMPLE3);
SIMPLE_TEST(MissingNumberInArithmeticProgression_Iterative, TestSAMPLE4, 14, SAMPLE4);
