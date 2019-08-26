#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;
using InputType = int;

#include "mathematics/numbers/binary/maximum_and_value_of_pair.h"

/** Program to find largest element in an array
 *
 * @reference   Program to find largest element in an array
 *              https://www.geeksforgeeks.org/c-program-find-largest-element-array/
 * @reference   Program to find the minimum (or maximum) element of an array
 *              https://www.geeksforgeeks.org/program-find-minimum-maximum-element-array/
 * @reference   C Program to find largest element in an array
 *              https://www.geeksforgeeks.org/c-program-for-program-to-find-largest-element-in-an-array/
 * @reference   Recursive Programs to find Minimum and Maximum elements of array
 *              https://www.geeksforgeeks.org/recursive-programs-to-find-minimum-and-maximum-elements-of-array/
 * @reference   Find smallest and largest elements in singly linked list
 *              https://www.geeksforgeeks.org/find-smallest-largest-elements-singly-linked-list/
 * @reference   Find the largest node in Doubly linked list
 *              https://www.geeksforgeeks.org/find-largest-node-doubly-linked-list/
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


/** Compute the minimum (min) or maximum (max) of two integers without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the minimum (min) or maximum (max) of two integers without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Compute the minimum or maximum of two integers without branching
 *              https://www.geeksforgeeks.org/compute-the-minimum-or-maximum-max-of-two-integers-without-branching/
 * @reference   What are the differences between bitwise and logical AND operators in C/C++?
 *              https://www.geeksforgeeks.org/what-are-the-differences-between-bitwise-and-logical-and-operators-in-cc/
 */
InputType Min_Xor(const InputType x, const InputType y) {
    return y ^ ((x ^ y) & -(x < y));
}


InputType Max_Xor(const InputType x, const InputType y) {
    return x ^ ((x ^ y) & -(x < y));
}


//If and only if INT_MIN <= x - y <= INT_MAX
InputType Min_QuickDirty(const InputType x, const InputType y) {
    auto diff = x - y;
    return y + ((diff) & ((diff) >> (Bits_Number<decltype(diff)>() - 1)));
}


//If and only if INT_MIN <= x - y <= INT_MAX
InputType Max_QuickDirty(const InputType x, const InputType y) {
    auto diff = x - y;
    return x - ((diff) & ((diff) >> (Bits_Number<decltype(diff)>() - 1)));
}


/** Smallest of three integers without comparison operators
 *
 * @reference   https://www.geeksforgeeks.org/smallest-of-three-integers-without-comparison-operators/
 * @reference   C program to Find the Largest Number Among Three Numbers
 *              https://www.geeksforgeeks.org/c-program-to-find-the-largest-number-among-three-numbers/
 * @reference   TCS Coding Practice Question | Greatest of 3 Numbers
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-greatest-of-3-numbers/
 */

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {4, 8, 12, 16};
const ArrayType VALUES5 = {15, 0, 2, 15};


SIMPLE_BENCHMARK(MaxElement_Bit, VALUES5);

SIMPLE_TEST(MaxElement_Bit, TestSAMPLE1, 0u, VALUES1);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE2, 1u, VALUES2);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE3, 2u, VALUES3);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE4, 16u, VALUES4);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE5, 15u, VALUES5);


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(Min_Xor, -1, 0);
SIMPLE_BENCHMARK(Min_Xor, -1, 1);
SIMPLE_BENCHMARK(Min_Xor, LOWER, UPPER);

SIMPLE_TEST(Min_Xor, TestSample1, -1, -1, 0);
SIMPLE_TEST(Min_Xor, TestSample2, -1, -1, -1);
SIMPLE_TEST(Min_Xor, TestSample3, 0, 0, 1);
SIMPLE_TEST(Min_Xor, TestSample4, 1, 1, 1);
SIMPLE_TEST(Min_Xor, TestSample5, -1, -1, 1);
SIMPLE_TEST(Min_Xor, TestSample6, 0, 0, 0);
SIMPLE_TEST(Min_Xor, TestSample7, LOWER, LOWER, UPPER);
SIMPLE_TEST(Min_Xor, TestSample8, LOWER, LOWER, LOWER);


SIMPLE_BENCHMARK(Max_Xor, -1, 0);
SIMPLE_BENCHMARK(Max_Xor, -1, 1);
SIMPLE_BENCHMARK(Max_Xor, LOWER, UPPER);

SIMPLE_TEST(Max_Xor, TestSample1, 0, -1, 0);
SIMPLE_TEST(Max_Xor, TestSample2, -1, -1, -1);
SIMPLE_TEST(Max_Xor, TestSample3, 1, 0, 1);
SIMPLE_TEST(Max_Xor, TestSample4, 1, 1, 1);
SIMPLE_TEST(Max_Xor, TestSample5, 1, -1, 1);
SIMPLE_TEST(Max_Xor, TestSample6, 0, 0, 0);
SIMPLE_TEST(Max_Xor, TestSample7, UPPER, LOWER, UPPER);
SIMPLE_TEST(Max_Xor, TestSample8, LOWER, LOWER, LOWER);


SIMPLE_BENCHMARK(Min_QuickDirty, -1, 0);
SIMPLE_BENCHMARK(Min_QuickDirty, -1, 1);
SIMPLE_BENCHMARK(Min_QuickDirty, LOWER, UPPER);

SIMPLE_TEST(Min_QuickDirty, TestSample1, -1, -1, 0);
SIMPLE_TEST(Min_QuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(Min_QuickDirty, TestSample3, 0, 0, 1);
SIMPLE_TEST(Min_QuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(Min_QuickDirty, TestSample5, -1, -1, 1);
SIMPLE_TEST(Min_QuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(Min_QuickDirty, TestSample7, LOWER, LOWER, LOWER);


SIMPLE_BENCHMARK(Max_QuickDirty, -1, 0);
SIMPLE_BENCHMARK(Max_QuickDirty, -1, 1);
SIMPLE_BENCHMARK(Max_QuickDirty, LOWER, UPPER);

SIMPLE_TEST(Max_QuickDirty, TestSample1, 0, -1, 0);
SIMPLE_TEST(Max_QuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(Max_QuickDirty, TestSample3, 1, 0, 1);
SIMPLE_TEST(Max_QuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(Max_QuickDirty, TestSample5, 1, -1, 1);
SIMPLE_TEST(Max_QuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(Max_QuickDirty, TestSample7, LOWER, LOWER, LOWER);
