#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Maximum Product of Three Numbers
 *
 * @reference   https://leetcode.com/problems/maximum-product-of-three-numbers/
 *
 * Given an integer array nums, find three numbers whose product is maximum and return
 * the maximum product.
 *
 * @note    We need not necessarily sort the given nums array to find the maximum
 * product. Instead, we can only find the required 2 smallest values and the three
 * largest values in the nums array, by iterating over the nums array only once.
 */
auto MaxProductOf3_Sort(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    const auto N = nums.size();
    return std::max(nums[0] * nums[1] * nums[N - 1],
                    nums[N - 1] * nums[N - 2] * nums[N - 3]);
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3};
const ArrayType SAMPLE2 = {1, 2, 3, 4};
const ArrayType SAMPLE3 = {-1, -2, -3};
const ArrayType SAMPLE4 = {-1, -2, -3, 4};
const ArrayType SAMPLE5 = {-1, -2, -3, 4, 5};
const ArrayType SAMPLE6 = {-100, -98, -1, 2, 3, 4};


THE_BENCHMARK(MaxProductOf3_Sort, SAMPLE6);

SIMPLE_TEST(MaxProductOf3_Sort, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MaxProductOf3_Sort, TestSAMPLE2, 24, SAMPLE2);
SIMPLE_TEST(MaxProductOf3_Sort, TestSAMPLE3, -6, SAMPLE3);
SIMPLE_TEST(MaxProductOf3_Sort, TestSAMPLE4, 24, SAMPLE4);
SIMPLE_TEST(MaxProductOf3_Sort, TestSAMPLE5, 30, SAMPLE5);
SIMPLE_TEST(MaxProductOf3_Sort, TestSAMPLE6, 39200, SAMPLE6);
