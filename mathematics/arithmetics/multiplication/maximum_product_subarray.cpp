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
 * @complexity  O(n)
 */
auto MaximumProductSubarray(const ArrayType &array) {
    if (array.empty()) {
        return 0;
    }

    ArrayType::value_type max_ending_here = 1;
    auto min_ending_here = max_ending_here;
    auto max_so_far = max_ending_here;

    for (const auto number : array) {
        if (number > 0) {
            max_ending_here *= number;
            min_ending_here = std::min(min_ending_here * number, 1);
        } else if (number == 0) {
            max_ending_here = min_ending_here = 1;
        } else {
            const auto temp = max_ending_here;
            max_ending_here = std::max(min_ending_here * number, 1);
            min_ending_here = temp * number;
        }

        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
    }

    return max_so_far;
}


/**
 * @reference   Maximum Product Subarray | Set 2 (Using Two Traversals)
 *              https://www.geeksforgeeks.org/maximum-product-subarray-set-2-using-two-traversals/
 */
template <typename Iterator>
auto MaximumProductSubarrayHelper(Iterator cbegin, const Iterator cend) {
    assert(cbegin != cend);

    auto max_till_now = *(cbegin++);
    auto max_product = max_till_now;
    bool has_zero_product_subarray = false;

    for (; cbegin != cend; ++cbegin) {
        max_till_now *= *cbegin;
        if (max_till_now == 0) {
            has_zero_product_subarray = true;
            max_till_now = 1;
        } else if (max_product < max_till_now) {
            max_product = max_till_now;
        }
    }

    return std::make_pair(has_zero_product_subarray, max_product);
}

auto MaximumProductSubarray_TwoWays(const ArrayType &array) {
    if (array.empty()) {
        return 0;
    }

    const auto [forward_product_has_zero, forward_product_max_product] =
        MaximumProductSubarrayHelper(array.cbegin(), array.cend());
    const auto [backward_product_has_zero, backward_product_max_product] =
        MaximumProductSubarrayHelper(array.crbegin(), array.crend());
    const auto max_product =
        std::max(forward_product_max_product, backward_product_max_product);

    return (forward_product_has_zero or backward_product_has_zero) ?
           std::max(0, max_product) : max_product;
}


/**
 * @reference   Maximum Product Subarray | Set 3
 *              https://www.geeksforgeeks.org/maximum-product-subarray-set-3/
 * @reference   Maximum Product Subarray | Added negative product case
 *              https://www.geeksforgeeks.org/maximum-product-subarray-added-negative-product-case/
 */
auto MaximumProductSubarray_Swap(const ArrayType &array) {
    if (array.empty()) {
        return 0;
    }

    auto iter = array.cbegin();
    auto min_ending_here = *(iter++);
    auto max_ending_here = min_ending_here;
    auto max_product = min_ending_here;

    for (; iter != array.cend(); ++iter) {
        if (*iter < 0) {
            std::swap(min_ending_here, max_ending_here);
        }

        min_ending_here = std::min(*iter, min_ending_here * (*iter));
        max_ending_here = std::max(*iter, max_ending_here * (*iter));

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


SIMPLE_BENCHMARK(MaximumProductSubarray, Sample1, VALUES2);

SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE2, 112, VALUES2);
SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE3, 180, VALUES3);
SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE4, 60, VALUES4);
SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE5, 80, VALUES5);


SIMPLE_BENCHMARK(MaximumProductSubarray_TwoWays, Sample1, VALUES2);

SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE2, 112, VALUES2);
SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE3, 180, VALUES3);
SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE4, 60, VALUES4);
SIMPLE_TEST(MaximumProductSubarray_TwoWays, TestSAMPLE5, 80, VALUES5);


SIMPLE_BENCHMARK(MaximumProductSubarray_Swap, Sample1, VALUES2);

SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE2, 112, VALUES2);
SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE3, 180, VALUES3);
SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE4, 60, VALUES4);
SIMPLE_TEST(MaximumProductSubarray_Swap, TestSAMPLE5, 80, VALUES5);
