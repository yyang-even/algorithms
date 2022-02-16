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
 * @reference   Recursive Programs to find Minimum and Maximum elements of array
 *              https://www.geeksforgeeks.org/recursive-programs-to-find-minimum-and-maximum-elements-of-array/
 * @reference   Find smallest and largest elements in singly linked list
 *              https://www.geeksforgeeks.org/find-smallest-largest-elements-singly-linked-list/
 * @reference   Find the largest node in Doubly linked list
 *              https://www.geeksforgeeks.org/find-largest-node-doubly-linked-list/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 9.1.
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
inline auto MaxElement_Bit(ArrayType values) {
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
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.4.
 */
inline constexpr int Min_Xor(const int x, const int y) {
    return y ^ ((x ^ y) & -(x < y));
}


inline constexpr int Max_Xor(const int x, const int y) {
    return x ^ ((x ^ y) & -(x < y));
}


//If and only if INT_MIN <= x - y <= INT_MAX
inline constexpr int Min_QuickDirty(const int x, const int y) {
    const auto diff = x - y;
    return y + ((diff) & ((diff) >> (BitsNumber<decltype(diff)> - 1)));
}


//If and only if INT_MIN <= x - y <= INT_MAX
inline constexpr int Max_QuickDirty(const int x, const int y) {
    const auto diff = x - y;
    return x - ((diff) & ((diff) >> (BitsNumber<decltype(diff)> - 1)));
}


/** Smallest of three integers without comparison operators
 *
 * @reference   https://www.geeksforgeeks.org/smallest-of-three-integers-without-comparison-operators/
 * @reference   C program to Find the Largest Number Among Three Numbers
 *              https://www.geeksforgeeks.org/c-program-to-find-the-largest-number-among-three-numbers/
 * @reference   TCS Coding Practice Question | Greatest of 3 Numbers
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-greatest-of-3-numbers/
 */


/**
 * @reference   Slowest Key
 *              https://leetcode.com/problems/slowest-key/
 *
 * A newly designed keypad was tested, where a tester pressed a sequence of n keys, one
 * at a time. You are given a string keysPressed of length n, where keysPressed[i] was
 * the ith key pressed in the testing sequence, and a sorted list releaseTimes, where
 * releaseTimes[i] was the time the ith key was released. Both arrays are 0-indexed. The
 * 0th key was pressed at the time 0, and every subsequent key was pressed at the exact
 * time the previous key was released. The tester wants to know the key of the keypress
 * that had the longest duration. The ith keypress had a duration of
 * releaseTimes[i] - releaseTimes[i - 1], and the 0th keypress had a duration of
 * releaseTimes[0]. Note that the same key could have been pressed multiple times during
 * the test, and these multiple presses of the same key may not have had the same
 * duration. Return the key of the keypress that had the longest duration. If there are
 * multiple such keypresses, return the lexicographically largest key of the keypresses.
 */


/**
 * @reference   Kids With the Greatest Number of Candies
 *              https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/
 *
 * There are n kids with candies. You are given an integer array candies, where each
 * candies[i] represents the number of candies the ith kid has, and an integer extraCandies,
 * denoting the number of extra candies that you have. Return a boolean array result of
 * length n, where result[i] is true if, after giving the ith kid all the extraCandies,
 * they will have the greatest number of candies among all the kids, or false otherwise.
 * Note that multiple kids can have the greatest number of candies.
 */


/**
 * @reference   Largest Subarray Length K
 *              https://leetcode.ca/2021-02-11-1708-Largest-Subarray-Length-K/
 *
 * An array A is larger than some array B if for the first index i where A[i] != B[i],
 * A[i] > B[i].
 * For example, consider 0-indexing:
 *  [1,3,2,4] > [1,2,2,4], since at index 1, 3 > 2.
 *  [1,4,4,4] < [2,1,1,1], since at index 0, 1 < 2.
 * A subarray is a contiguous subsequence of the array.
 * Given an integer array nums of distinct integers, return the largest subarray of nums
 * of length k.
 * All the integers of nums are unique.
 * Follow up: What if the integers in nums are not distinct?
 */


/**
 * @reference   Number Of Rectangles That Can Form The Largest Square
 *              https://leetcode.com/problems/number-of-rectangles-that-can-form-the-largest-square/
 *
 * You are given an array rectangles where rectangles[i] = [li, wi] represents the ith
 * rectangle of length li and width wi.
 * You can cut the ith rectangle to form a square with a side length of k if both k <= li
 * and k <= wi. For example, if you have a rectangle [4,6], you can cut it to get a square
 * with a side length of at most 4.
 * Let maxLen be the side length of the largest square you can obtain from any of the
 * given rectangles.
 * Return the number of rectangles that can make a square with a side length of maxLen.
 */


/**
 * @reference   Find Nearest Point That Has the Same X or Y Coordinate
 *              https://leetcode.com/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/
 *
 * You are given two integers, x and y, which represent your current location on a Cartesian
 * grid: (x, y). You are also given an array points where each points[i] = [ai, bi]
 * represents that a point exists at (ai, bi). A point is valid if it shares the same
 * x-coordinate or the same y-coordinate as your location.
 * Return the index (0-indexed) of the valid point with the smallest Manhattan distance
 * from your current location. If there are multiple, return the valid point with the
 * smallest index. If there are no valid points, return -1.
 * The Manhattan distance between two points (x1, y1) and (x2, y2) is
 * abs(x1 - x2) + abs(y1 - y2).
 */

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {4, 8, 12, 16};
const ArrayType VALUES5 = {15, 0, 2, 15};


THE_BENCHMARK(MaxElement_Bit, VALUES5);

SIMPLE_TEST(MaxElement_Bit, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE2, 1, VALUES2);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE3, 2, VALUES3);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE4, 16, VALUES4);
SIMPLE_TEST(MaxElement_Bit, TestSAMPLE5, 15, VALUES5);


constexpr auto LOWER = std::numeric_limits<int>::min();
constexpr auto UPPER = std::numeric_limits<int>::max();


SIMPLE_BENCHMARK(Min_Xor, Sample1, -1, 0);
SIMPLE_BENCHMARK(Min_Xor, Sample2, -1, 1);

SIMPLE_TEST(Min_Xor, TestSample1, -1, -1, 0);
SIMPLE_TEST(Min_Xor, TestSample2, -1, -1, -1);
SIMPLE_TEST(Min_Xor, TestSample3, 0, 0, 1);
SIMPLE_TEST(Min_Xor, TestSample4, 1, 1, 1);
SIMPLE_TEST(Min_Xor, TestSample5, -1, -1, 1);
SIMPLE_TEST(Min_Xor, TestSample6, 0, 0, 0);
SIMPLE_TEST(Min_Xor, TestSample7, LOWER, LOWER, UPPER);
SIMPLE_TEST(Min_Xor, TestSample8, LOWER, LOWER, LOWER);


SIMPLE_BENCHMARK(Max_Xor, Sample1, -1, 0);
SIMPLE_BENCHMARK(Max_Xor, Sample2, -1, 1);

SIMPLE_TEST(Max_Xor, TestSample1, 0, -1, 0);
SIMPLE_TEST(Max_Xor, TestSample2, -1, -1, -1);
SIMPLE_TEST(Max_Xor, TestSample3, 1, 0, 1);
SIMPLE_TEST(Max_Xor, TestSample4, 1, 1, 1);
SIMPLE_TEST(Max_Xor, TestSample5, 1, -1, 1);
SIMPLE_TEST(Max_Xor, TestSample6, 0, 0, 0);
SIMPLE_TEST(Max_Xor, TestSample7, UPPER, LOWER, UPPER);
SIMPLE_TEST(Max_Xor, TestSample8, LOWER, LOWER, LOWER);


SIMPLE_BENCHMARK(Min_QuickDirty, Sample1, -1, 0);
SIMPLE_BENCHMARK(Min_QuickDirty, Sample2, -1, 1);

SIMPLE_TEST(Min_QuickDirty, TestSample1, -1, -1, 0);
SIMPLE_TEST(Min_QuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(Min_QuickDirty, TestSample3, 0, 0, 1);
SIMPLE_TEST(Min_QuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(Min_QuickDirty, TestSample5, -1, -1, 1);
SIMPLE_TEST(Min_QuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(Min_QuickDirty, TestSample7, LOWER, LOWER, LOWER);


SIMPLE_BENCHMARK(Max_QuickDirty, Sample1, -1, 0);
SIMPLE_BENCHMARK(Max_QuickDirty, Sample2, -1, 1);

SIMPLE_TEST(Max_QuickDirty, TestSample1, 0, -1, 0);
SIMPLE_TEST(Max_QuickDirty, TestSample2, -1, -1, -1);
SIMPLE_TEST(Max_QuickDirty, TestSample3, 1, 0, 1);
SIMPLE_TEST(Max_QuickDirty, TestSample4, 1, 1, 1);
SIMPLE_TEST(Max_QuickDirty, TestSample5, 1, -1, 1);
SIMPLE_TEST(Max_QuickDirty, TestSample6, 0, 0, 0);
SIMPLE_TEST(Max_QuickDirty, TestSample7, LOWER, LOWER, LOWER);
