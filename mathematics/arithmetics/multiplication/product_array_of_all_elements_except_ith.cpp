#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** A Product Array Puzzle
 *
 * @reference   https://www.geeksforgeeks.org/a-product-array-puzzle/
 *
 * Given an array arr[] of n integers, construct a Product Array prod[] (of same size)
 * such that prod[i] is equal to the product of all the elements of arr[] except arr[i].
 * Solve it without division operator in O(n) time.
 *
 * @reference   Product of Array Except Self
 *              https://leetcode.com/problems/product-of-array-except-self/
 *
 * Given an integer array nums, return an array answer such that answer[i] is equal to
 * the product of all the elements of nums except nums[i]. The product of any prefix or
 * suffix of nums is guaranteed to fit in a 32-bit integer. You must write an algorithm
 * that runs in O(n) time and without using the division operation.
 *
 * @reference   A Sum Array Puzzle
 *              https://www.geeksforgeeks.org/a-sum-array-puzzle/
 *
 * Given an array arr[] of n integers, construct a Sum Array sum[] (of same size) such
 * that sum[i] is equal to the sum of all the elements of arr[] except arr[i]. Solve
 * it without subtraction operator and in O(n).
 */
auto ProductArrayOfAllElementsExceptIth(const ArrayType &elements) {
    ArrayType products;

    ArrayType::value_type prefix_product = 1;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        products.push_back(prefix_product);
        prefix_product *= elements[i];
    }

    ArrayType::value_type suffix_product = 1;
    for (int i = elements.size() - 1; i >= 0; --i) {
        products[i] *= suffix_product;
        suffix_product *= elements[i];
    }

    return products;
}


/**
 * @reference   A product array puzzle | Set 2 (O(1) Space)
 *              https://www.geeksforgeeks.org/product-array-puzzle-set-2-o1-space/
 */
auto ProductArrayOfAllElementsExceptIth_Log(const ArrayType &elements) {
    const auto log_sum = std::accumulate(elements.cbegin(), elements.cend(), 0.0,
    [](const auto & sum, const auto & elem) {
        return sum + std::log10(elem);
    });

    ArrayType products;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        products.push_back(1e-9 + std::pow(10.0, log_sum - std::log10(elements[i])));
    }

    return products;
}


auto ProductArrayOfAllElementsExceptIth_Power(const ArrayType &elements) {
    const auto the_product =
        std::accumulate(elements.cbegin(), elements.cend(), 1,
                        std::multiplies<ArrayType::value_type> {});

    ArrayType products;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        products.push_back(the_product * std::pow(elements[i], -1));
    }

    return products;
}


/**
 * @reference   Construct an array from XOR of all elements of array except element at same index
 *              https://www.geeksforgeeks.org/construct-an-array-from-xor-of-all-elements-of-array-except-element-at-same-index/
 *
 * Given an array A[] having n positive elements. The task to create another array B[]
 * such as B[i] is XOR of all elements of array A[] except A[i].
 */
auto XorArrayOfAllElementsExceptIth(const ArrayType &elements) {
    const auto the_xor =
        std::accumulate(elements.cbegin(), elements.cend(), 0,
                        std::bit_xor<ArrayType::value_type> {});

    ArrayType results;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        results.push_back(the_xor ^ elements[i]);
    }

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {10, 3, 5, 6, 2};
const ArrayType EXPECTED1 = {180, 600, 360, 300, 900};

const ArrayType SAMPLE2 = {1, 2, 3, 4, 5};
const ArrayType EXPECTED2 = {120, 60, 40, 30, 24};


THE_BENCHMARK(ProductArrayOfAllElementsExceptIth, SAMPLE1);

SIMPLE_TEST(ProductArrayOfAllElementsExceptIth, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ProductArrayOfAllElementsExceptIth, TestSAMPLE2, EXPECTED2, SAMPLE2);


THE_BENCHMARK(ProductArrayOfAllElementsExceptIth_Log, SAMPLE1);

SIMPLE_TEST(ProductArrayOfAllElementsExceptIth_Log, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ProductArrayOfAllElementsExceptIth_Log, TestSAMPLE2, EXPECTED2, SAMPLE2);


THE_BENCHMARK(ProductArrayOfAllElementsExceptIth_Power, SAMPLE1);

SIMPLE_TEST(ProductArrayOfAllElementsExceptIth_Power, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ProductArrayOfAllElementsExceptIth_Power, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = {2, 1, 5, 9};
const ArrayType EXPECTED3 = {13, 14, 10, 6};

const ArrayType SAMPLE4 = {2, 1, 3, 6};
const ArrayType EXPECTED4 = {4, 7, 5, 0};

const ArrayType SAMPLE5 = {2, 4, 1, 3, 5};
const ArrayType EXPECTED5 = {3, 5, 0, 2, 4};


THE_BENCHMARK(XorArrayOfAllElementsExceptIth, SAMPLE5);

SIMPLE_TEST(XorArrayOfAllElementsExceptIth, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(XorArrayOfAllElementsExceptIth, TestSAMPLE4, EXPECTED4, SAMPLE4);
SIMPLE_TEST(XorArrayOfAllElementsExceptIth, TestSAMPLE5, EXPECTED5, SAMPLE5);
