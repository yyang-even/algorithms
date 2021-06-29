#pragma once


/** Largest Sum Contiguous Subarray
 *
 * @reference   Largest Sum Contiguous Subarray
 *              https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
 * @reference   Size of The Subarray With Maximum Sum
 *              https://www.geeksforgeeks.org/size-subarray-maximum-sum/
 * @reference   Maximum Subarray
 *              https://leetcode.com/problems/maximum-subarray/
 *
 * Write an efficient C program to find the sum of contiguous subarray within a
 * one-dimensional array of numbers which has the largest sum.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.8.
 *
 * @complexity  O(n)
 */
template <typename Container>
static inline constexpr auto
LargestSumContiguousSubarray_Kadane(const Container &array,
                                    Container *const max_sum_subarray = nullptr) {
    assert(not array.empty());

    auto max_so_far = std::numeric_limits<typename Container::value_type>::min();
    typename Container::value_type max_ending_here = 0;
    typename Container::size_type max_start = 0;
    typename Container::size_type max_last = 0;
    typename Container::size_type current_start = 0;

    for (typename Container::size_type i = 0; i < array.size(); ++i) {
        max_ending_here += array[i];

        // <= instead of <, would return the longest such subarray.
        if (max_so_far <= max_ending_here) {
            max_so_far = max_ending_here;
            max_start = current_start;
            max_last = i;
        }

        if (max_ending_here < 0) {
            max_ending_here = 0;
            current_start = i + 1;
        }
    }

    if (max_sum_subarray) {
        *max_sum_subarray =
            Container(array.cbegin() + max_start, array.cbegin() + max_last + 1);
    }

    return max_so_far;
}
