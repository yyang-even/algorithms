#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Maximum Product Subarray
 *
 * @reference   Maximum Product Subarray
 *              https://www.geeksforgeeks.org/maximum-product-subarray/
 *
 * Given an array that contains both positive and negative integers, find the product of
 * the maximum product subarray.
 *
 * @reference   Maximum Product Subarray | Set 2 (Using Two Traversals)
 *              https://www.geeksforgeeks.org/maximum-product-subarray-set-2-using-two-traversals/
 *
 * @reference   Maximum Product Subarray
 *              https://leetcode.com/problems/maximum-product-subarray/
 *
 * Given an integer array nums, find a contiguous non-empty subarray within the array
 * that has the largest product, and return the product. It is guaranteed that the answer
 * will fit in a 32-bit integer. A subarray is a contiguous subsequence of the array.
 */
auto MaximumProductSubarray_TwoWays(const ArrayType &nums) {
    if (nums.empty()) {
        return 0;
    }

    int product = 1, result = INT_MIN;
    for (const auto i : nums) {
        product *= i;
        result = std::max(product, result);
        if (product == 0) {
            product = 1;
        }
    }

    product = 1;
    for (int i = nums.size() - 1; i >= 0; --i) {
        product *= nums[i];
        result = std::max(product, result);
        if (product == 0) {
            product = 1;
        }
    }

    return result;
}


/**
 * @reference   Maximum Product Subarray | Set 3
 *              https://www.geeksforgeeks.org/maximum-product-subarray-set-3/
 * @reference   Maximum Product Subarray | Added negative product case
 *              https://www.geeksforgeeks.org/maximum-product-subarray-added-negative-product-case/
 */
auto MaximumProductSubarray_Swap(const ArrayType &nums) {
    if (nums.empty()) {
        return 0;
    }

    auto min_ending_here = nums.front();
    auto max_ending_here = min_ending_here;
    auto max_product = min_ending_here;

    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] < 0) {
            std::swap(min_ending_here, max_ending_here);
        }

        min_ending_here = std::min(nums[i], min_ending_here * nums[i]);
        max_ending_here = std::max(nums[i], max_ending_here * nums[i]);

        max_product = std::max(max_ending_here, max_product);
    }

    return max_product;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1, -2, -3, 0, 7, -8, -2};
const ArrayType VALUES3 = {6, -3, -10, 0, 2};
const ArrayType VALUES4 = { -1, -3, -10, 0, 60};
const ArrayType VALUES5 = { -2, -3, 0, -2, -40};
const ArrayType VALUES6 = {-2};


THE_BENCHMARK(MaximumProductSubarray_TwoWays, VALUES2);

SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE2, 112, VALUES2);
SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE3, 180, VALUES3);
SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE4, 60, VALUES4);
SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE5, 80, VALUES5);
SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE6, -2, VALUES6);


THE_BENCHMARK(MaximumProductSubarray_Swap, VALUES2);

SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE2, 112, VALUES2);
SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE3, 180, VALUES3);
SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE4, 60, VALUES4);
SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE5, 80, VALUES5);
SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE6, -2, VALUES6);
