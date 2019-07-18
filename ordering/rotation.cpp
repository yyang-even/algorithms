#include "common_header.h"

#include "sublist_rotation.h"


namespace {


using ArrayType = std::vector<int>;

/** Program for array rotation
 *
 * @reference   https://www.geeksforgeeks.org/array-rotation/
 *
 * Write a function rotate(ar[], d, n) that rotates arr[] of size n by d elements.
 *
 * @reference   Split the array and add the first part to the end
 *              https://www.geeksforgeeks.org/split-array-add-first-part-end/
 * @reference   Split the array and add the first part to the end | Set 2
 *              https://www.geeksforgeeks.org/split-the-array-and-add-the-first-part-to-the-end-set-2/
 *
 * Given an array and split it from a specified position, and move the first part of array add to the end.
 *
 * @reference   Program to cyclically rotate an array by one
 *              https://www.geeksforgeeks.org/c-program-cyclically-rotate-array-one/
 *
 * Given an array, cyclically rotate the array clockwise by one.
 */
auto LeftRotate_Simple(const ArrayType &arr, const ArrayType::size_type d) {
    assert(d < arr.size());

    auto output = arr;
    const auto mid = arr.cbegin() + d;
    const auto iter = std::copy(mid, arr.cend(), output.begin());
    std::copy(arr.cbegin(), mid, iter);
    return output;
}

auto LeftRotate_GCD(ArrayType arr, const ArrayType::size_type d) {
    assert(d < arr.size());

    const auto step = std::gcd(arr.size(), d);

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

/**
 * @reference   Block swap algorithm for array rotation
 *              https://www.geeksforgeeks.org/block-swap-algorithm-for-array-rotation/
 */
void BlockSwap(ArrayType::iterator begin1, ArrayType::iterator begin2, ArrayType::size_type n) {
    while (n--) {
        std::iter_swap(begin1++, begin2++);
    }
}
void LeftRotate_BlockSwap_Recursive(const ArrayType::iterator begin, const ArrayType::size_type d,
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
        LeftRotate_BlockSwap_Recursive(begin, d, right_size);
    } else {
        BlockSwap(begin, begin + d, right_size);
        LeftRotate_BlockSwap_Recursive(begin + right_size, 2 * d - n, d);
    }
}
auto LeftRotate_BlockSwap_Recursive(ArrayType arr, const ArrayType::size_type d) {
    assert(d < arr.size());

    LeftRotate_BlockSwap_Recursive(arr.begin(), d, arr.size());
    return arr;
}

auto LeftRotate_BlockSwap_Iterative(ArrayType arr, const ArrayType::size_type d) {
    assert(d < arr.size());

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

/**
 * @reference   Reversal algorithm for array rotation
 *              https://www.geeksforgeeks.org/program-for-array-rotation-continued-reversal-algorithm/
 */
auto LeftRotate_Reversal(ArrayType elements, const ArrayType::size_type d) {
    assert(d < elements.size());

    const auto mid = elements.begin() + d;
    std::reverse(elements.begin(), mid);
    std::reverse(mid, elements.end());
    std::reverse(elements.begin(), elements.end());

    return elements;
}


/**
 * @reference   Reversal algorithm for right rotation of an array
 *              https://www.geeksforgeeks.org/reversal-algorithm-right-rotation-array/
 *
 * Given an array, right rotate it by k elements.
 */
auto RightRotate_Reversal(ArrayType elements, const ArrayType::size_type k) {
    assert(k < elements.size());

    const auto mid = elements.begin() + k;
    std::reverse(elements.begin(), elements.end());
    std::reverse(elements.begin(), mid);
    std::reverse(mid, elements.end());

    return elements;
}


/** Rotate a Linked List
 *
 * @reference   https://www.geeksforgeeks.org/rotate-a-linked-list/
 *
 * Given a singly linked list, rotate the linked list counter-clockwise by k nodes. Where k is a given
 * positive integer. For example, if the given linked list is 10->20->30->40->50->60 and k is 4, the
 * list should be modified to 50->60->10->20->30->40. Assume that k is smaller than the count of nodes
 * in linked list.
 */
auto LeftRotate_SinglyList(std::forward_list<int> elements,
                           const std::forward_list<int>::size_type k) {
    return SublistLeftRotate_SinglyList(elements, elements.cbefore_begin(), elements.cend(), k);
}
auto TestLeftRotate_SinglyList(const ArrayType &elements,
                               const std::forward_list<int>::size_type k) {
    const auto rotated_list = LeftRotate_SinglyList({elements.cbegin(), elements.cend()}, k);
    return ArrayType{rotated_list.cbegin(), rotated_list.cend()};
}


/** Rotate Doubly linked list by N nodes
 *
 * @reference   https://www.geeksforgeeks.org/rotate-doubly-linked-list-n-nodes/
 *
 * Given a doubly linked list, rotate the linked list counter-clockwise by N nodes. Here N is a given
 * positive integer and is smaller than the count of nodes in linked list.
 */
auto LeftRotate_DoublyList(std::list<int> elements, const std::list<int>::size_type k) {
    auto mid = elements.cbegin();
    std::advance(mid, k);
    elements.splice(elements.cbegin(), elements, mid, elements.cend());
    return elements;
}
auto TestLeftRotate_DoublyList(const ArrayType &elements, const std::list<int>::size_type k) {
    const auto rotated_list = LeftRotate_DoublyList({elements.cbegin(), elements.cend()}, k);
    return ArrayType{rotated_list.cbegin(), rotated_list.cend()};
}

}//namespace


const ArrayType SampleArray = {1, 2, 3, 4, 5, 6, 7};
const ArrayType ExpectedArray = {3, 4, 5, 6, 7, 1, 2};
const ArrayType SampleArray2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
const ArrayType ExpectedArray2 = {4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3};


SIMPLE_BENCHMARK(LeftRotate_Simple, SampleArray, 2);

SIMPLE_TEST(LeftRotate_Simple, TestSample, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_Simple, TestSample2, ExpectedArray2, SampleArray2, 3);


SIMPLE_BENCHMARK(LeftRotate_GCD, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_GCD, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_GCD, TestSample2, ExpectedArray2, SampleArray2, 3);


SIMPLE_BENCHMARK(LeftRotate_BlockSwap_Recursive, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_BlockSwap_Recursive, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_BlockSwap_Recursive, TestSample2, ExpectedArray2, SampleArray2, 3);


SIMPLE_BENCHMARK(LeftRotate_BlockSwap_Iterative, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_BlockSwap_Iterative, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_BlockSwap_Iterative, TestSample2, ExpectedArray2, SampleArray2, 3);


SIMPLE_BENCHMARK(LeftRotate_Reversal, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_Reversal, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_Reversal, TestSample2, ExpectedArray2, SampleArray2, 3);


const ArrayType SampleArrayR1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const ArrayType ExpectedArrayR1 = {8, 9, 10, 1, 2, 3, 4, 5, 6, 7};
const ArrayType SampleArrayR2 = {121, 232, 33, 43, 5};
const ArrayType ExpectedArrayR2 = {43, 5, 121, 232, 33};


SIMPLE_BENCHMARK(RightRotate_Reversal, SampleArrayR1, 3);

SIMPLE_TEST(RightRotate_Reversal, TestSample, ExpectedArrayR1, SampleArrayR1, 3);
SIMPLE_TEST(RightRotate_Reversal, TestSample2, ExpectedArrayR2, SampleArrayR2, 2);


SIMPLE_BENCHMARK(TestLeftRotate_SinglyList, SampleArray2, 3);

SIMPLE_TEST(TestLeftRotate_SinglyList, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(TestLeftRotate_SinglyList, TestSample2, ExpectedArray2, SampleArray2, 3);


SIMPLE_BENCHMARK(TestLeftRotate_DoublyList, SampleArray2, 3);

SIMPLE_TEST(TestLeftRotate_DoublyList, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(TestLeftRotate_DoublyList, TestSample2, ExpectedArray2, SampleArray2, 3);
