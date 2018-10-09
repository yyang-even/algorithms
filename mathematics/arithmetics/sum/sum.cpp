#include "common_header.h"

using ArrayType = std::vector<int>;

/** Program to find sum of elements in a given array
 *
 * @reference   https://www.geeksforgeeks.org/program-find-sum-elements-given-array/
 *              Sum of array elements using recursion
 *              https://www.geeksforgeeks.org/sum-array-elements-using-recursion/
 */
auto SumRecursiveHelper(const ArrayType::const_iterator cbegin, const ArrayType::const_iterator cend) {
    if(cbegin == cend)
        return ArrayType::value_type{0};
    else
        return SumRecursiveHelper(cbegin + 1, cend) + *cbegin;
}
auto SumRecursive(const ArrayType &elements) {
    return SumRecursiveHelper(elements.cbegin(), elements.cend());
}


const ArrayType SAMPLE1 = {1, 2, 3};
const ArrayType SAMPLE2 = {15, 12, 13, 10};
const ArrayType SAMPLE3 = {1, 2, 3, 4, 5 };

SIMPLE_BENCHMARK(SumRecursive, SAMPLE1L, SAMPLE1);

SIMPLE_TEST(SumRecursive, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(SumRecursive, TestSAMPLE2, 50, SAMPLE2);
SIMPLE_TEST(SumRecursive, TestSAMPLE3, 15, SAMPLE3);
