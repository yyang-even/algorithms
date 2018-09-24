#include "common_header.h"


template <std::size_t N>
using ArrayType = std::array<int, N>;

/** Maximum Product Subarray
 *
 * @reference   Maximum Product Subarray
 *              https://www.geeksforgeeks.org/maximum-product-subarray/
 *              https://www.geeksforgeeks.org/maximum-product-subarray-set-2-using-two-traversals/
 *
 * Given an array that contains both positive and negative integers,
 * find the product of the maximum product subarray.
 *
 * @complexity  O(n)
 */
template <typename Container>
auto MaximumProductSubarray(const Container &array) {
    typename Container::value_type max_ending_here = 1;
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


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<7> VALUES2 = {1, -2, -3, 0, 7, -8, -2};
constexpr ArrayType<5> VALUES3 = {6, -3, -10, 0, 2};
constexpr ArrayType<5> VALUES4 = { -1, -3, -10, 0, 60};
constexpr ArrayType<5> VALUES5 = { -2, -3, 0, -2, -40};

SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE1, 1, VALUES1);
SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE2, 112, VALUES2);
SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE3, 180, VALUES3);
SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE4, 60, VALUES4);
SIMPLE_TEST(MaximumProductSubarray, TestSAMPLE5, 80, VALUES5);
