#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Sum of XOR of all possible subsets
 *
 * @reference   https://www.geeksforgeeks.org/sum-xor-possible-subsets/
 *
 * Given an array arr[] of size n, we need to find sum of all the
 * values that comes from XORing all the elements of the subsets.
 * The final sum will be 2n-1 times the bitwise OR of all the inputs.
 */
unsigned SumOfXorOfAllSubsets(const ArrayType &arr) {
    return std::pow(2, arr.size() - 1) *
           std::accumulate(arr.cbegin(), arr.cend(), 0u, std::bit_or<ArrayType::value_type> {});
}

}//namespace


const ArrayType VALUES1 = {1, 5, 6};
const ArrayType VALUES2 = {1, 2};


SIMPLE_BENCHMARK(SumOfXorOfAllSubsets, Sample1, VALUES1);

SIMPLE_TEST(SumOfXorOfAllSubsets, TestSample1, 28u, VALUES1);
SIMPLE_TEST(SumOfXorOfAllSubsets, TestSample2, 6u, VALUES2);
