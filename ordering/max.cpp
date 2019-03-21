#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

#include "mathematics/numbers/binary/maximum_and_value_of_pair.h"

/** Program to find largest element in an array
 *
 * @reference   Program to find largest element in an array
 *              https://www.geeksforgeeks.org/c-program-find-largest-element-array/
 * @reference   Program to find the minimum (or maximum) element of an array
 *              https://www.geeksforgeeks.org/program-find-minimum-maximum-element-array/
 * @reference   C Program to find largest element in an array
 *              https://www.geeksforgeeks.org/c-program-for-program-to-find-largest-element-in-an-array/
 * @reference   C program to Find the Largest Number Among Three Numbers
 *              https://www.geeksforgeeks.org/c-program-to-find-the-largest-number-among-three-numbers/
 * @reference   Recursive Programs to find Minimum and Maximum elements of array
 *              https://www.geeksforgeeks.org/recursive-programs-to-find-minimum-and-maximum-elements-of-array/
 *
 * @reference   Program to Find the Largest Number using Ternary Operator
 *              https://www.geeksforgeeks.org/program-to-find-the-largest-number-using-ternary-operator/
 * @reference   C/C++ Ternary Operator – Some Interesting Observations
 *              https://www.geeksforgeeks.org/cc-ternary-operator-some-interesting-observations/
 * @reference   C++ | Nested Ternary Operator
 *              https://www.geeksforgeeks.org/c-nested-ternary-operator/
 *
 * @reference   Find largest element from array without using conditional operator
 *              https://www.geeksforgeeks.org/find-largest-element-array-without-using-conditional-operator/
 *
 * Given an array of n-elements, we have to find the largest element among them without
 * using any conditional operator like greater than or less than.
 */
auto MaxElement_Bit(ArrayType values) {
    values.push_back(std::numeric_limits<ArrayType::value_type>::max());
    return MaxAndValueOfPair_Value(values);
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {4, 8, 12, 16};
const ArrayType VALUES5 = {15, 0, 2, 15};


SIMPLE_BENCHMARK(MaxElement_Bit, VALUES5);

SIMPLE_TEST(MaxElement_Bit, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE2, 1, VALUES2);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE3, 2, VALUES3);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE4, 16, VALUES4);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE5, 15, VALUES5);
