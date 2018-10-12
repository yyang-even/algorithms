#include "common_header.h"

#include "merge_sort.h"
#include "merge_two_sorted_arrays.h"


using ArrayType = std::vector<int>;

auto Partition(ArrayType::iterator begin, ArrayType::iterator end,
               const std::function<bool(const ArrayType::value_type)> predicate) {
    auto j = begin;
    for (; begin != end; ++begin) {
        if (predicate(*begin)) {
            std::iter_swap(begin, j++);
        }
    }

    return j;
}


/** Move all negative elements to end in order with extra space allowed
 *
 * @reference   https://www.geeksforgeeks.org/move-ve-elements-end-order-extra-space-allowed/
 *
 * Given an unsorted array of both negative and positive integer. The task is place all
 * negative element at the end of array without changing the order of positive element
 * and negative element.
 */
auto RearrangePositiveAndNegativeNumbersSimple(const ArrayType &input) {
    ArrayType output;

    for (const auto c : input) {
        if (c >= 0) {
            output.push_back(c);
        }
    }

    for (const auto c : input) {
        if (c < 0) {
            output.push_back(c);
        }
    }

    return output;
}

void Merge(const ArrayType::iterator begin, const ArrayType::iterator middle,
           const ArrayType::iterator end) {
    const auto L = ArrayType(begin, middle);
    const auto R = ArrayType(middle, end);

    MergeTwoSortedArrays(L.cbegin(), L.cend(), R.cbegin(), R.cend(), begin,
    [](const ArrayType::value_type lv, const ArrayType::value_type rv) {
        if (lv < 0) {
            return true;
        } else if (rv < 0) {
            return false;
        } else {
            return true;
        }
    });
}
auto RearrangePositiveAndNegativeNumbersMerge(ArrayType input) {
    MergeSort<ArrayType>(input.begin(), input.size(), Merge);
    return input;
}

/** Rearrange positive and negative numbers with constant extra space
 *
 * @reference   https://www.geeksforgeeks.org/rearrange-positive-and-negative-numbers/
 *
 * Given an array of positive and negative numbers, arrange them such that all negative
 * integers appear before all the positive integers in the array without using any
 * additional data structure like hash table, arrays, etc. The order of appearance
 * should be maintained.
 */
auto isNegative(const ArrayType::value_type v) {
    return v < 0;
}
auto RearrangePositiveAndNegativeNumbersSTL(ArrayType input) {
    std::stable_partition(input.begin(), input.end(), isNegative);

    return input;
}

auto RearrangePositiveAndNegativeNumbersInsertion(ArrayType input) {
    for (ArrayType::size_type j = 1; j < input.size(); ++j) {
        auto key_value = input[j];
        if (key_value < 0) {
            int i = j - 1;
            for (; (i >= 0) and input[i] > 0; --i) {
                input[i + 1] = input[i];
            }
            input[i + 1] = key_value;
        }
    }
    return input;
}

auto isPositive(const ArrayType::value_type v) {
    return v > 0;
}
void MergeReverse(const ArrayType::iterator begin, const ArrayType::iterator middle,
                  const ArrayType::iterator end) {
    const auto left_mid = std::find_if(begin, middle, isPositive);
    const auto right_mid = std::find_if(middle, end, isPositive);
    std::reverse(left_mid, middle);
    std::reverse(middle, right_mid);
    std::reverse(left_mid, right_mid);
}
auto RearrangePositiveAndNegativeNumbersMergeReverse(ArrayType input) {
    MergeSort<ArrayType>(input.begin(), input.size(), Merge);
    return input;
}

/** Move all zeroes to end of array
 *
 * @reference   https://www.geeksforgeeks.org/move-zeroes-end-array/
 *
 * Given an array of random numbers, Push all the zero’s of a given array to the end
 * of the array. For example, if the given arrays is {1, 9, 8, 4, 0, 0, 2, 7, 0, 6, 0},
 * it should be changed to {1, 9, 8, 4, 2, 7, 6, 0, 0, 0, 0}. The order of all other
 * elements should be same. Expected time complexity is O(n) and extra space is O(1).
 */
auto RearrangeZeros(ArrayType input) {
    Partition(input.begin(), input.end(), [](const ArrayType::value_type v) {
        return static_cast<bool>(v);
    });

    return input;
}

/** Rearrange positive and negative numbers in O(n) time and O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/rearrange-positive-and-negative-numbers-publish/
 *
 * An array contains both positive and negative numbers in random order. Rearrange
 * the array elements so that positive and negative numbers are placed alternatively.
 * Number of positive and negative numbers need not be equal. If there are more
 * positive numbers they appear at the end of the array. If there are more negative
 * numbers, they too appear in the end of the array.
 */
auto RearrangePositiveAndNegativeNumbersAlternative(ArrayType input) {
    auto positive_iter = Partition(input.begin(), input.end(), isNegative);

    for (auto negative_iter = input.begin();
         positive_iter != input.end() and negative_iter < positive_iter and * negative_iter < 0;
         ++positive_iter, negative_iter += 2) {
        std::iter_swap(negative_iter, positive_iter);
    }

    return input;
}


const ArrayType SAMPLE1 = { -12, 11, -13, -5, 6, -7, 5, -3, -6 };
const ArrayType EXPECTED1 = { -12, -13, -5, -7, -3, -6, 11, 6, 5};

const ArrayType SAMPLE2 = {12, 11, -13, -5, 6, -7, 5, -3, -6};
const ArrayType EXPECTED2 = { -13, -5, -7, -3, -6, 12, 11, 6, 5};

SIMPLE_BENCHMARK(RearrangePositiveAndNegativeNumbersSTL, SAMPLE1);

SIMPLE_TEST(RearrangePositiveAndNegativeNumbersSTL, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RearrangePositiveAndNegativeNumbersSTL, TestSAMPLE2, EXPECTED2, SAMPLE2);

SIMPLE_BENCHMARK(RearrangePositiveAndNegativeNumbersInsertion, SAMPLE1);

SIMPLE_TEST(RearrangePositiveAndNegativeNumbersInsertion, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RearrangePositiveAndNegativeNumbersInsertion, TestSAMPLE2, EXPECTED2, SAMPLE2);

SIMPLE_BENCHMARK(RearrangePositiveAndNegativeNumbersMerge, SAMPLE1);

SIMPLE_TEST(RearrangePositiveAndNegativeNumbersMerge, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RearrangePositiveAndNegativeNumbersMerge, TestSAMPLE2, EXPECTED2, SAMPLE2);

SIMPLE_BENCHMARK(RearrangePositiveAndNegativeNumbersMergeReverse, SAMPLE1);

SIMPLE_TEST(RearrangePositiveAndNegativeNumbersMergeReverse, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RearrangePositiveAndNegativeNumbersMergeReverse, TestSAMPLE2, EXPECTED2, SAMPLE2);

const ArrayType SAMPLE3 = {1, -1, 3, 2, -7, -5, 11, 6 };
const ArrayType EXPECTED3 = {1, 3, 2, 11, 6, -1, -7, -5};

const ArrayType SAMPLE4 = { -5, 7, -3, -4, 9, 10, -1, 11};
const ArrayType EXPECTED4 = {7, 9, 10, 11, -5, -3, -4, -1};

SIMPLE_BENCHMARK(RearrangePositiveAndNegativeNumbersSimple, SAMPLE3);

SIMPLE_TEST(RearrangePositiveAndNegativeNumbersSimple, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(RearrangePositiveAndNegativeNumbersSimple, TestSAMPLE4, EXPECTED4, SAMPLE4);

const ArrayType SAMPLE5 = { -1, 2, -3, 4, 5, 6, -7, 8, 9};
const ArrayType EXPECTED5 = {4, -3, 5, -1, 6, -7, 2, 8, 9};

const ArrayType SAMPLE6 = { -5, 7, -3, -4, 9, 10, -1, -11};
const ArrayType EXPECTED6 = {10, -3, 7, -1, 9, -5, -4, -11};

SIMPLE_BENCHMARK(RearrangePositiveAndNegativeNumbersAlternative, SAMPLE5);

SIMPLE_TEST(RearrangePositiveAndNegativeNumbersAlternative, TestSAMPLE5, EXPECTED5, SAMPLE5);
SIMPLE_TEST(RearrangePositiveAndNegativeNumbersAlternative, TestSAMPLE6, EXPECTED6, SAMPLE6);


const ArrayType SAMPLE7 = {1, 2, 0, 4, 3, 0, 5, 0};
const ArrayType EXPECTED7 = {1, 2, 4, 3, 5, 0, 0, 0};

const ArrayType SAMPLE8 = {1, 2, 0, 0, 0, 3, 6};
const ArrayType EXPECTED8 = {1, 2, 3, 6, 0, 0, 0};

const ArrayType SAMPLE9 = {1, 9, 8, 4, 0, 0, 2, 7, 0, 6, 0, 9};
const ArrayType EXPECTED9 = {1, 9, 8, 4, 2, 7, 6, 9, 0, 0, 0, 0};

SIMPLE_BENCHMARK(RearrangeZeros, SAMPLE7);

SIMPLE_TEST(RearrangeZeros, TestSAMPLE7, EXPECTED7, SAMPLE7);
SIMPLE_TEST(RearrangeZeros, TestSAMPLE8, EXPECTED8, SAMPLE8);
SIMPLE_TEST(RearrangeZeros, TestSAMPLE9, EXPECTED9, SAMPLE9);
