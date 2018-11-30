#include "common_header.h"

#include "mathematics/numbers/gcd/gcd.h"

using ArrayType = std::vector<int>;
/** Program for array rotation
 *
 * @reference   https://www.geeksforgeeks.org/array-rotation/
 *
 * Write a function rotate(ar[], d, n) that rotates arr[] of size n by d elements.
 */
auto LeftRotateSimple(const ArrayType &arr, const ArrayType::size_type d) {
    auto output = arr;
    const auto mid = arr.cbegin() + d;
    const auto iter = std::copy(mid, arr.cend(), output.begin());
    std::copy(arr.cbegin(), mid, iter);
    return output;
}

auto LeftRotateGCD(ArrayType arr, const ArrayType::size_type d) {
    const auto step = gcd(arr.size(), d);

    for (ArrayType::size_type i = 0; i < step; ++i) {
        auto j = i;
        while (true) {
            auto k = j + d;
            if (k >= arr.size()) {
                k -= arr.size();
            }
            if (k == i) {
                break;
            }
            std::swap(arr[j], arr[k]);
            j = k;
        }
    }
    return arr;
}

/** Block swap algorithm for array rotation
 *
 * @reference   https://www.geeksforgeeks.org/block-swap-algorithm-for-array-rotation/
 */
void BlockSwap(ArrayType::iterator begin1, ArrayType::iterator begin2, ArrayType::size_type n) {
    while (n--) {
        std::iter_swap(begin1++, begin2++);
    }
}
void LeftRotateBlockSwapRecursive(const ArrayType::iterator begin, const ArrayType::size_type d,
                                  const ArrayType::size_type n) {
    if (d == 0 or d == n) {
        return;
    }
    const auto right_size = n - d;
    if (right_size == d) {
        BlockSwap(begin, begin + d, d);
        return;
    }
    if (d < right_size) {
        BlockSwap(begin, begin + n - d, d);
        LeftRotateBlockSwapRecursive(begin, d, right_size);
    } else {
        BlockSwap(begin, begin + d, right_size);
        LeftRotateBlockSwapRecursive(begin + right_size, 2 * d - n, d);
    }
}
auto LeftRotateBlockSwapRecursive(ArrayType arr, const ArrayType::size_type d) {
    LeftRotateBlockSwapRecursive(arr.begin(), d, arr.size());
    return arr;
}

auto LeftRotateBlockSwapIterative(ArrayType arr, const ArrayType::size_type d) {
    if (d == 0 or arr.size() == d) {
        return arr;
    }

    auto i = d;
    auto j = arr.size() - d;
    const auto begin = arr.begin() + d;
    while (i != j) {
        if (i < j) {
            BlockSwap(begin - i, begin + j - i, i);
            j -= i;
        } else {
            BlockSwap(begin - i, begin, j);
            i -= j;
        }
    }
    BlockSwap(begin - i, begin, i);

    return arr;
}

/** Reversal algorithm for array rotation
 *
 * @reference   https://www.geeksforgeeks.org/program-for-array-rotation-continued-reversal-algorithm/
 */
auto LeftRotateReversal(ArrayType elements, const ArrayType::size_type d) {
    const auto mid = elements.begin() + d;
    std::reverse(elements.begin(), mid);
    std::reverse(mid, elements.end());
    std::reverse(elements.begin(), elements.end());

    return elements;
}


/** Reversal algorithm for right rotation of an array
 *
 * @reference   https://www.geeksforgeeks.org/reversal-algorithm-right-rotation-array/
 *
 * Given an array, right rotate it by k elements.
 */
auto RightRotateReversal(ArrayType elements, const ArrayType::size_type k) {
    const auto mid = elements.begin() + k;
    std::reverse(elements.begin(), elements.end());
    std::reverse(elements.begin(), mid);
    std::reverse(mid, elements.end());

    return elements;
}


/** Split the array and add the first part to the end
 *
 * @reference   https://www.geeksforgeeks.org/split-array-add-first-part-end/
 * @reference   Split the array and add the first part to the end | Set 2
 *              https://www.geeksforgeeks.org/split-the-array-and-add-the-first-part-to-the-end-set-2/
 *
 * Given an array and split it from a specified position, and move the first part of array add to the end.
 */


/** Program to cyclically rotate an array by one
 *
 * @reference   https://www.geeksforgeeks.org/c-program-cyclically-rotate-array-one/
 *
 * Given an array, cyclically rotate the array clockwise by one.
 */


const ArrayType SampleArray = {1, 2, 3, 4, 5, 6, 7};
const ArrayType ExpectedArray = {3, 4, 5, 6, 7, 1, 2};
const ArrayType SampleArray2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
const ArrayType ExpectedArray2 = {4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3};

SIMPLE_BENCHMARK(LeftRotateSimple, SampleArray, 2);

SIMPLE_TEST(LeftRotateSimple, TestSample, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotateSimple, TestSample2, ExpectedArray2, SampleArray2, 3);

SIMPLE_BENCHMARK(LeftRotateGCD, SampleArray2, 3);

SIMPLE_TEST(LeftRotateGCD, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotateGCD, TestSample2, ExpectedArray2, SampleArray2, 3);

SIMPLE_BENCHMARK(LeftRotateBlockSwapRecursive, SampleArray2, 3);

SIMPLE_TEST(LeftRotateBlockSwapRecursive, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotateBlockSwapRecursive, TestSample2, ExpectedArray2, SampleArray2, 3);

SIMPLE_BENCHMARK(LeftRotateBlockSwapIterative, SampleArray2, 3);

SIMPLE_TEST(LeftRotateBlockSwapIterative, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotateBlockSwapIterative, TestSample2, ExpectedArray2, SampleArray2, 3);

SIMPLE_BENCHMARK(LeftRotateReversal, SampleArray2, 3);

SIMPLE_TEST(LeftRotateReversal, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotateReversal, TestSample2, ExpectedArray2, SampleArray2, 3);


const ArrayType SampleArrayR1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const ArrayType ExpectedArrayR1 = {8, 9, 10, 1, 2, 3, 4, 5, 6, 7};
const ArrayType SampleArrayR2 = {121, 232, 33, 43, 5};
const ArrayType ExpectedArrayR2 = {43, 5, 121, 232, 33};

SIMPLE_BENCHMARK(RightRotateReversal, SampleArrayR1, 3);

SIMPLE_TEST(RightRotateReversal, TestSample, ExpectedArrayR1, SampleArrayR1, 3);
SIMPLE_TEST(RightRotateReversal, TestSample2, ExpectedArrayR2, SampleArrayR2, 2);
