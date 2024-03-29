#include "common_header.h"


namespace {

#include "counting_sort.h"

using ArrayType = std::vector<int>;

/** Counting Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 8.2.
 * @reference   https://www.geeksforgeeks.org/counting-sort/
 * @reference   C Program for Counting Sort
 *              https://www.geeksforgeeks.org/c-program-for-counting-sort-2/
 *
 * Counting sort is efficient if the range of input data is not significantly greater than the number of
 * objects to be sorted.
 *
 * @reference   Sort string of characters
 *              https://www.geeksforgeeks.org/sort-string-characters/
 * @reference   Program to sort string in descending order
 *              https://www.geeksforgeeks.org/program-sort-string-descending-order/
 * @reference   How to sort an Array in descending order using STL in C++?
 *              https://www.geeksforgeeks.org/how-to-sort-an-array-in-descending-order-using-stl-in-c/
 * @reference   How to sort a Vector in descending order using STL in C++?
 *              https://www.geeksforgeeks.org/how-to-sort-a-vector-in-descending-order-using-stl-in-c/
 * @reference   Sorting of Vector of Tuple in C++ (Ascending Order)
 *              https://www.geeksforgeeks.org/sorting-vector-tuple-c-ascending-order/
 * @reference   Sorting of Vector of Tuple in C++ (Descending Order)
 *              https://www.geeksforgeeks.org/sorting-vector-tuple-c-descending-order/
 * @reference   Sorting Vector of Pairs in C++ | Set 1 (Sort by first and second)
 *              https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/
 * @reference   Sorting Vector of Pairs in C++ | Set 2 (Sort in descending order by first and second)
 *              https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-2-sort-in-descending-order-by-first-and-second/
 * @reference   Keep track of previous indexes after sorting a vector in C++ STL
 *              https://www.geeksforgeeks.org/keep-track-of-previous-indexes-after-sorting-a-vector-in-c-stl/
 * @reference   Sorting a vector in C++
 *              https://www.geeksforgeeks.org/sorting-a-vector-in-c/
 * @reference   Sorting without comparison of elements
 *              https://www.geeksforgeeks.org/sorting-without-comparison-of-elements/
 */
inline auto CountingSort_NoNegative(ArrayType values) {
    static constexpr ArrayType::value_type MAXIMUM = 1 << 8;

    assert(std::all_of(values.cbegin(), values.cend(), [](const auto v) {
        return v >= 0 and v < MAXIMUM;
    }));

    return CountingSort(std::move(values), MAXIMUM, Copy);
}


/**
 * @reference   C++14 Language Extensions: Generalized lambda captures
 *              https://isocpp.org/wiki/faq/cpp14-language#lambda-captures
 */
inline auto CountingSort(ArrayType values) {
    if (values.empty()) {
        return values;
    }

    const auto [min_iter, max_iter] = std::minmax_element(values.cbegin(), values.cend());
    const auto RANGE = *max_iter - *min_iter + 1;

    return CountingSort(std::move(values), RANGE, [min = *min_iter](const auto v) {
        return v - min;
    });
}


inline auto CountingSort_STL(ArrayType values) {
    return CountingSort_STL(std::move(values), Copy);
}


/**
 * @reference   Actors and Directors Who Cooperated At Least Three Times
 *              https://leetcode.com/problems/height-checker/
 *
 * A school is trying to take an annual photo of all the students. The students are asked to stand in a
 * single file line in non-decreasing order by height. Let this ordering be represented by the integer
 * array expected where expected[i] is the expected height of the ith student in line.
 * You are given an integer array heights representing the current order that the students are standing
 * in. Each heights[i] is the height of the ith student in line (0-indexed).
 * Return the number of indices where heights[i] != expected[i].
 * 1 <= heights[i] <= 100
 */


/**
 * @reference   How Many Numbers Are Smaller Than the Current Number
 *              https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/
 *
 * Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it.
 * That is, for each nums[i] you have to count the number of valid j's such that j != i and
 * nums[j] < nums[i].
 * Return the answer in an array.
 * 0 <= nums[i] <= 100
 */


/**
 * @reference   Increasing Decreasing String
 *              https://leetcode.com/problems/increasing-decreasing-string/
 *
 * You are given a string s. Reorder the string using the following algorithm:
 *  Pick the smallest character from s and append it to the result.
 *  Pick the smallest character from s which is greater than the last appended character to the result
 *      and append it.
 *  Repeat step 2 until you cannot pick more characters.
 *  Pick the largest character from s and append it to the result.
 *  Pick the largest character from s which is smaller than the last appended character to the result
 *      and append it.
 *  Repeat step 5 until you cannot pick more characters.
 *  Repeat the steps from 1 to 6 until you pick all characters from s.
 * In each step, If the smallest or the largest character appears more than once you can choose any
 * occurrence and append it to the result. Return the result string after sorting s with this algorithm.
 * s consists of only lowercase English letters.
 */


/**
 * @reference   Special Array With X Elements Greater Than or Equal X
 *              https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/
 *
 * You are given an array nums of non-negative integers. nums is considered special if there exists a
 * number x such that there are exactly x numbers in nums that are greater than or equal to x.
 * Notice that x does not have to be an element in nums.
 * Return x if the array is special, otherwise, return -1. It can be proven that if nums is special, the
 * value for x is unique.
 * 1 <= nums.length <= 100
 * 0 <= nums[i] <= 1000
 */
auto SpecialArrayNumber(const ArrayType &nums) {
    int count[1002] = {};
    for (const auto n : nums) {
        ++count[n];
    }

    for (int i = 1000; i >= 0; --i) {
        count[i] += count[i + 1];
        if (i == count[i]) {
            return i;
        }
    }

    return -1;
}


/**
 * @reference   Design an Ordered Stream
 *              https://leetcode.com/problems/design-an-ordered-stream/
 *
 * There is a stream of n (idKey, value) pairs arriving in an arbitrary order, where idKey is an integer
 * between 1 and n and value is a string. No two pairs have the same id.
 * Design a stream that returns the values in increasing order of their IDs by returning a chunk (list)
 * of values after each insertion. The concatenation of all the chunks should result in a list of the
 * sorted values.
 * Implement the OrderedStream class:
 *  OrderedStream(int n) Constructs the stream to take n values.
 *  String[] insert(int idKey, String value) Inserts the pair (idKey, value) into the stream, then
 *      returns the largest possible chunk of currently inserted values that appear next in the order.
 */


/**
 * @reference   Check if array elements are consecutive | Added Method 4
 *              https://www.geeksforgeeks.org/check-if-array-elements-are-consecutive/
 * @reference   Check if array elements are consecutive in O(n) time and O(1) space (Handles Both Positive and negative numbers)
 *              https://www.geeksforgeeks.org/check-array-elements-consecutive-time-o1-space-handles-positive-negative-numbers/
 *
 * Given an unsorted array of distinct numbers, write a function that returns true if array consists of
 * consecutive numbers.
 */
auto areConsecutive(const ArrayType &nums) {
    auto minimum = *std::min_element(nums.cbegin(), nums.cend());

    int result = 0;
    for (const auto n : nums) {
        result ^= (n ^ minimum++);
    }

    return result == 0;
}


/**
 * @reference   Find Original Array From Doubled Array
 *              https://leetcode.com/problems/find-original-array-from-doubled-array/
 *
 * An integer array original is transformed into a doubled array changed by appending twice the value of
 * every element in original, and then randomly shuffling the resulting array.
 * Given an array changed, return original if changed is a doubled array. If changed is not a doubled
 * array, return an empty array. The elements in original may be returned in any order.
 */
ArrayType FindOriginalArray(const ArrayType &nums) {
    if (nums.size() % 2 == 1) {
        return {};
    }

    int counts[100001] = {};

    for (const auto n : nums) {
        ++counts[n];
    }

    ArrayType result;
    if (counts[0]) {
        if (counts[0] % 2 == 1) {
            return {};
        }

        result.insert(result.cend(), counts[0] / 2, 0);
    }

    for (int i = 1; i < 100001; ++i) {
        if (counts[i]) {
            if (i * 2 >= 100001 or counts[i * 2] < counts[i]) {
                return {};
            }
            counts[i * 2] -= counts[i];
            result.insert(result.cend(), counts[i], i);
        }
    }

    return result;
}


/**
 * @reference   Maximum Element After Decreasing and Rearranging
 *              https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/
 *
 * You are given an array of positive integers arr. Perform some operations (possibly none) on arr so
 * that it satisfies these conditions:
 *  The value of the first element in arr must be 1.
 *  The absolute difference between any 2 adjacent elements must be less than or equal to 1. In other
 *  words, abs(arr[i] - arr[i - 1]) <= 1 for each i where 1 <= i < arr.length (0-indexed).  abs(x) is
 *  the absolute value of x.
 * There are 2 types of operations that you can perform any number of times:
 *  Decrease the value of any element of arr to a smaller positive integer.
 *  Rearrange the elements of arr to be in any order.
 * Return the maximum possible value of an element in arr after performing the operations to satisfy the
 * conditions.
 */


/**
 * @reference   Sort Vowels in a String
 *              https://leetcode.com/problems/sort-vowels-in-a-string/
 *
 * Given a 0-indexed string s, permute s to get a new string t such that:
 *  All consonants remain in their original places. More formally, if there is an index i with 0 <= i <
 *  s.length such that s[i] is a consonant, then t[i] = s[i].
 *  The vowels must be sorted in the nondecreasing order of their ASCII values. More formally, for pairs
 *  of indices i, j with 0 <= i < j < s.length such that s[i] and s[j] are vowels, then t[i] must not
 *  have a higher ASCII value than t[j].
 * Return the resulting string.
 * The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in lowercase or uppercase. Consonants
 * comprise all letters that are not vowels.
 */


/**
 * @reference   Reduction Operations to Make the Array Elements Equal
 *              https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/
 *
 * Given an integer array nums, your goal is to make all elements in nums equal. To complete one
 * operation, follow these steps:
 *  Find the largest value in nums. Let its index be i (0-indexed) and its value be largest. If there
 *  are multiple elements with the largest value, pick the smallest i.
 *  Find the next largest value in nums strictly smaller than largest. Let its value be nextLargest.
 *  Reduce nums[i] to nextLargest.
 * Return the number of operations to make all elements in nums equal.
 */

} //namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

constexpr InitializerType VALUES1 = {};
constexpr InitializerType VALUES2 = {1};
constexpr InitializerType VALUES3 = {1, 2};
constexpr InitializerType VALUES4 = {2, 3, 1};
constexpr InitializerType EXPECTED4 = {1, 2, 3};
constexpr InitializerType VALUES5 = {4, 3, 2, 1};
constexpr InitializerType EXPECTED5 = {1, 2, 3, 4};
constexpr InitializerType VALUES6 = {1, 2, 3, 1, 2, 2};
constexpr InitializerType EXPECTED6 = {1, 1, 2, 2, 2, 3};


THE_BENCHMARK(CountingSort_NoNegative, VALUES6);

SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE6, EXPECTED6, VALUES6);


constexpr InitializerType VALUES7 = {-5, -10, 0, -3, 8, 5, -1, 10};
constexpr InitializerType EXPECTED7 = {-10, -5, -3, -1, 0, 5, 8, 10};


THE_BENCHMARK(CountingSort, VALUES6);

SIMPLE_TEST(CountingSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(CountingSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(CountingSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(CountingSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(CountingSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(CountingSort, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(CountingSort, TestSAMPLE7, EXPECTED7, VALUES7);


THE_BENCHMARK(CountingSort_STL, VALUES6);

SIMPLE_TEST(CountingSort_STL, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE7, EXPECTED7, VALUES7);


const ArrayType SAMPLE1 = {3, 5};
const ArrayType SAMPLE2 = {0, 0};
const ArrayType SAMPLE3 = {0, 4, 3, 0, 4};


THE_BENCHMARK(SpecialArrayNumber, SAMPLE1);

SIMPLE_TEST(SpecialArrayNumber, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(SpecialArrayNumber, TestSAMPLE2, -1, SAMPLE2);
SIMPLE_TEST(SpecialArrayNumber, TestSAMPLE3, 3, SAMPLE3);


const ArrayType SAMPLE1C = {5, 2, 3, 1, 4};
const ArrayType SAMPLE2C = {83, 78, 80, 81, 79, 82};
const ArrayType SAMPLE3C = {34, 23, 52, 12, 3};
const ArrayType SAMPLE4C = {7, 6, 5, 5, 3, 4};
const ArrayType SAMPLE5C = {2, 1, 0, -3, -1, -2};


THE_BENCHMARK(areConsecutive, SAMPLE1C);

SIMPLE_TEST(areConsecutive, TestSAMPLE1, true, SAMPLE1C);
SIMPLE_TEST(areConsecutive, TestSAMPLE2, true, SAMPLE2C);
SIMPLE_TEST(areConsecutive, TestSAMPLE3, false, SAMPLE3C);
SIMPLE_TEST(areConsecutive, TestSAMPLE4, false, SAMPLE4C);
SIMPLE_TEST(areConsecutive, TestSAMPLE5, true, SAMPLE5C);


const ArrayType SAMPLE1D = {1, 3, 4, 2, 6, 8};
const ArrayType EXPECTED1D = {1, 3, 4};

const ArrayType SAMPLE2D = {6, 3, 0, 1};
const ArrayType EXPECTED2D = {};

const ArrayType SAMPLE3D = {1};


THE_BENCHMARK(FindOriginalArray, SAMPLE1D);

SIMPLE_TEST(FindOriginalArray, TestSAMPLE1, EXPECTED1D, SAMPLE1D);
SIMPLE_TEST(FindOriginalArray, TestSAMPLE2, EXPECTED2D, SAMPLE2D);
SIMPLE_TEST(FindOriginalArray, TestSAMPLE3, EXPECTED2D, SAMPLE3D);
