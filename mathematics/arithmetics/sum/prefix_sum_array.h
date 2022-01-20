#pragma once


/** Prefix Sum Array – Implementation and Applications in Competitive Programming
 *
 * @reference   https://www.geeksforgeeks.org/prefix-sum-array-implementation-applications-competitive-programming/
 *
 * Given an array arr[] of size n, its prefix sum array is another array prefixSum[] of
 * same size such that the value of prefixSum[i] is arr[0] + arr[1] + arr[2] ... arr[i].
 *
 * @reference   Running Sum of 1d Array
 *              https://leetcode.com/problems/running-sum-of-1d-array/
 *
 * Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]...nums[i]).
 * Return the running sum of nums.
 */
template <typename ArrayType>
static inline constexpr auto
PrefixSumArray(ArrayType elements,
               const std::function
               <typename ArrayType::value_type(const typename ArrayType::value_type &, const typename ArrayType::value_type &) >
plus = std::plus<typename ArrayType::value_type> {}) {
    const auto N = elements.size();
    for (typename ArrayType::size_type i = 1; i < N; ++i) {
        elements[i] = plus(elements[i], elements[i - 1]);
    }

    return elements;
}
