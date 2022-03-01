#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Sum of XOR of all possible subsets
 *
 * @reference   https://www.geeksforgeeks.org/sum-xor-possible-subsets/
 *
 * Given an array arr[] of size n, we need to find sum of all the values that comes from
 * XORing all the elements of the subsets. The final sum will be 2^(n-1) times the bitwise
 * OR of all the inputs.
 *
 * @reference   Sum of All Subset XOR Totals
 *              https://leetcode.com/problems/sum-of-all-subset-xor-totals/
 *
 * The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if
 * the array is empty.
 *  For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
 * Given an array nums, return the sum of all XOR totals for every subset of nums.
 * Note: Subsets with the same elements should be counted multiple times.
 * An array a is a subset of an array b if a can be obtained from b by deleting some
 * (possibly zero) elements of b.
 */
inline unsigned SumOfXorOfAllSubsets(const ArrayType &arr) {
    return std::accumulate(arr.cbegin(), arr.cend(), 0u, std::bit_or<ArrayType::value_type> {})
           << (arr.size() - 1);
}

}//namespace


const ArrayType VALUES1 = {1, 5, 6};
const ArrayType VALUES2 = {1, 2};
const ArrayType VALUES3 = {1, 3};
const ArrayType VALUES4 = {3, 4, 5, 6, 7, 8};


THE_BENCHMARK(SumOfXorOfAllSubsets, VALUES1);

SIMPLE_TEST(SumOfXorOfAllSubsets, TestSample1, 28, VALUES1);
SIMPLE_TEST(SumOfXorOfAllSubsets, TestSample2, 6, VALUES2);
SIMPLE_TEST(SumOfXorOfAllSubsets, TestSample3, 6, VALUES3);
SIMPLE_TEST(SumOfXorOfAllSubsets, TestSample4, 480, VALUES4);
