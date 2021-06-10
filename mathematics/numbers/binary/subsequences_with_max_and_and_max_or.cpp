#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Find subsequences with maximum Bitwise AND and Bitwise OR
 *
 * @reference   https://www.geeksforgeeks.org/find-subsequences-with-maximum-bitwise-and-and-bitwise-or/
 *
 * Given an array of n elements. The task is to print the maximum sum by selecting two
 * subsequences of the array (not necessarily different) such that the sum of bitwise
 * AND of all elements of the first subsequence and bitwise OR of all the elements of
 * the second subsequence is maximum.
 *
 * The maximum OR would be the or of all the numbers and the maximum AND would be the
 * maximum element in the array.
 * This is so because if (x | y) >= x, y and (x & y) <= x, y.
 */
inline ArrayType::value_type
SumOfMaxAndAndMaxOrSubSequences(const ArrayType &elements) {
    if (elements.empty()) {
        return 0;
    }

    const auto max_and = *std::max_element(elements.cbegin(), elements.cend());
    const auto max_or = std::accumulate(elements.cbegin(), elements.cend(),
                                        0u, std::bit_or<ArrayType::value_type> {});

    return max_and + max_or;
}

}//namespace


const ArrayType SAMPLE1 = {3, 5, 6, 1};
const ArrayType SAMPLE2 = {3, 3};


THE_BENCHMARK(SumOfMaxAndAndMaxOrSubSequences, SAMPLE1);

SIMPLE_TEST(SumOfMaxAndAndMaxOrSubSequences, TestSample1, 13, SAMPLE1);
SIMPLE_TEST(SumOfMaxAndAndMaxOrSubSequences, TestSample2, 6, SAMPLE2);
