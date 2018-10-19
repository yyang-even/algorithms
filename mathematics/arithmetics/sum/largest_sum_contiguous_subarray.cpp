#include "common_header.h"

#include "largest_sum_contiguous_subarray.h"

template <std::size_t N>
using ArrayType = std::array<int, N>;


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<3> VALUES2 = { -1, -2, -3};
constexpr ArrayType<8> VALUES3 = { -2, -3, 4, -1, -2, 1, 5, -3};

SIMPLE_TEST(LargestSumContiguousSubarrayKadane, TestSAMPLE1, std::numeric_limits<int>::min(),
            VALUES1);
SIMPLE_TEST(LargestSumContiguousSubarrayKadane, TestSAMPLE2, -1, VALUES2);
SIMPLE_TEST(LargestSumContiguousSubarrayKadane, TestSAMPLE3, 7, VALUES3);
