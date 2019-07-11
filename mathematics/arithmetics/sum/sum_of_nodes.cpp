#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Sum of array using pointer arithmetic
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-array-using-pointer-arithmetic/
 *
 * https://www.geeksforgeeks.org/sum-of-array-using-pointer-arithmetic/
 */
/** Program to find sum of elements in a given array
 *
 * @reference   https://www.geeksforgeeks.org/program-find-sum-elements-given-array/
 * @reference   Sum of array elements using recursion
 *              https://www.geeksforgeeks.org/sum-array-elements-using-recursion/
 * @reference   Recursion
 *              https://www.geeksforgeeks.org/recursion/
 * @reference   Difference between Recursion and Iteration
 *              https://www.geeksforgeeks.org/difference-between-recursion-and-iteration/
 * @reference   Tail recursion to calculate sum of array elements.
 *              https://www.geeksforgeeks.org/tail-recursion-to-calculate-sum-of-array-elements/
 */
auto Sum_RecursiveHelper(const ArrayType::const_iterator cbegin,
                         const ArrayType::const_iterator cend) {
    if (cbegin == cend)
        return ArrayType::value_type{0};
    else {
        return Sum_RecursiveHelper(cbegin + 1, cend) + *cbegin;
    }
}
auto Sum_Recursive(const ArrayType &elements) {
    return Sum_RecursiveHelper(elements.cbegin(), elements.cend());
}


auto Sum_TailRecursive(const ArrayType::const_iterator cbegin,
                       const ArrayType::const_iterator cend,
                       const ArrayType::value_type sum_so_far = 0) {
    if (cbegin == cend) {
        return sum_so_far;
    }
    return Sum_TailRecursive(cbegin + 1, cend, sum_so_far + *cbegin);
}
auto Sum_TailRecursive(const ArrayType &elements) {
    return Sum_TailRecursive(elements.cbegin(), elements.cend());
}


/** Sum of the nodes of a Singly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-the-nodes-of-a-singly-linked-list/
 */

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3};
const ArrayType SAMPLE2 = {15, 12, 13, 10};
const ArrayType SAMPLE3 = {1, 2, 3, 4, 5 };


SIMPLE_BENCHMARK(Sum_Recursive, SAMPLE1);

SIMPLE_TEST(Sum_Recursive, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(Sum_Recursive, TestSAMPLE2, 50, SAMPLE2);
SIMPLE_TEST(Sum_Recursive, TestSAMPLE3, 15, SAMPLE3);


SIMPLE_BENCHMARK(Sum_TailRecursive, SAMPLE1);

SIMPLE_TEST(Sum_TailRecursive, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(Sum_TailRecursive, TestSAMPLE2, 50, SAMPLE2);
SIMPLE_TEST(Sum_TailRecursive, TestSAMPLE3, 15, SAMPLE3);
