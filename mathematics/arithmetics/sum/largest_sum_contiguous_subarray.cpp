#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

template <std::size_t N>
using ArrayType = std::array<int, N>;

/** Largest Sum Contiguous Subarray
 *
 * @reference   Largest Sum Contiguous Subarray
 *              https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
 *
 * Write an efficient C program to find the sum of contiguous subarray within
 * a one-dimensional array of numbers which has the largest sum.
 *
 * @complexity  O(n)
 */
template <typename Container>
auto LargestSumContiguousSubarrayKadane(const Container &array) {
    auto max_so_far = std::numeric_limits<typename Container::value_type>::min();
    typename Container::value_type max_ending_here = 0;

    for (const auto num : array) {
        max_ending_here += num;
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
        if (max_ending_here < 0) {
            max_ending_here = 0;
        }
    }

    return max_so_far;
}


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<3> VALUES2 = { -1, -2, -3};
constexpr ArrayType<8> VALUES3 = { -2, -3, 4, -1, -2, 1, 5, -3};

SIMPLE_TEST(LargestSumContiguousSubarrayKadane, TestSAMPLE1, std::numeric_limits<int>::min(),
            VALUES1);
SIMPLE_TEST(LargestSumContiguousSubarrayKadane, TestSAMPLE2, -1, VALUES2);
SIMPLE_TEST(LargestSumContiguousSubarrayKadane, TestSAMPLE3, 7, VALUES3);
