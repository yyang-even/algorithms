#include "common_header.h"

#include "sublist_rotation.h"

#include "data_structure/linked_list/singly_list/singly_linked_list.h"


namespace {

using ArrayType = std::vector<int>;
using ShiftArrayType = std::vector<std::pair<int, int>>;

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
 * Given an array and split it from a specified position, and move the first part of
 * array add to the end.
 *
 * @reference   Program to cyclically rotate an array by one
 *              https://www.geeksforgeeks.org/c-program-cyclically-rotate-array-one/
 *
 * Given an array, cyclically rotate the array clockwise by one.
 *
 * @reference   C Program for Program for array rotation
 *              https://www.geeksforgeeks.org/c-program-for-program-for-array-rotation-2/
 *
 * @reference   Left rotation of an array using vectors in C++
 *              https://www.geeksforgeeks.org/left-rotation-of-an-array-using-vectors-in-c/
 */
inline auto LeftRotate_Simple(const ArrayType &arr, const ArrayType::size_type d) {
    assert(d < arr.size());

    auto output = arr;
    const auto mid = arr.cbegin() + d;
    const auto iter = std::copy(mid, arr.cend(), output.begin());
    std::copy(arr.cbegin(), mid, iter);

    return output;
}


auto LeftRotate_GCD(ArrayType arr, const ArrayType::size_type d) {
    const auto N = arr.size();
    assert(d < N);

    const auto step = std::gcd(N, d);

    for (ArrayType::size_type i = 0; i < step; ++i) {
        auto j = i;
        while (true) {
            auto k = j + d;
            if (k >= N) {
                k -= N;
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
inline constexpr void
BlockSwap(ArrayType::iterator begin1, ArrayType::iterator begin2, ArrayType::size_type n) {
    while (n--) {
        std::iter_swap(begin1++, begin2++);
    }
}

constexpr void LeftRotate_BlockSwap_Recursive(const ArrayType::iterator begin,
                                              const ArrayType::size_type d,
                                              const ArrayType::size_type n) {
    if (d == 0 or d == n) {
        return;
    }
    const auto right_size = n - d;
    if (right_size == d) {
        BlockSwap(begin, begin + d, d);
    } else if (d < right_size) {
        BlockSwap(begin, begin + n - d, d);
        LeftRotate_BlockSwap_Recursive(begin, d, right_size);
    } else {
        BlockSwap(begin, begin + d, right_size);
        LeftRotate_BlockSwap_Recursive(begin + right_size, 2 * d - n, d);
    }
}

inline auto LeftRotate_BlockSwap_Recursive(ArrayType arr, const ArrayType::size_type d) {
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
 * @reference   Left Rotation and Right Rotation of a String
 *              https://www.geeksforgeeks.org/left-rotation-right-rotation-string-2/
 * @reference   C Program for Reversal algorithm for array rotation
 *              https://www.geeksforgeeks.org/c-program-for-reversal-algorithm-for-array-rotation/
 */
inline auto LeftRotate_Reversal(ArrayType elements, const ArrayType::size_type d) {
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
 *
 * @reference   Rotate Array
 *              https://leetcode.com/problems/rotate-array/
 *
 * Given an array, rotate the array to the right by k steps, where k is non-negative.
 */
inline auto RightRotate_Reversal(ArrayType elements, const ArrayType::size_type k) {
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
 * Given a singly linked list, rotate the linked list counter-clockwise by k nodes. Where
 * k is a given positive integer. For example, if the given linked list is
 * 10->20->30->40->50->60 and k is 4, the list should be modified to
 * 50->60->10->20->30->40. Assume that k is smaller than the count of nodes
 * in linked list.
 *
 * @reference   Move first element to end of a given Linked List
 *              https://www.geeksforgeeks.org/move-first-element-to-end-of-a-given-linked-list/
 */
inline auto LeftRotate_SinglyList(std::forward_list<int> elements,
                                  const std::forward_list<int>::size_type k) {
    return SublistLeftRotate_SinglyList(elements, elements.cbefore_begin(), elements.cend(), k);
}


/** Move last element to front of a given Linked List
 *
 * @reference   https://www.geeksforgeeks.org/move-last-element-to-front-of-a-given-linked-list/
 */


/**
 * @reference   Rotate List
 *              https://leetcode.com/problems/rotate-list/
 *
 * Given the head of a linked list, rotate the list to the right by k places.
 */
inline auto RotateRight(const SinglyLinkedList::Node::PointerType head, int k) {
    if (not head) {
        return head;
    }

    int length = 1;
    auto tail = head;

    while (tail->next) {
        tail = tail->next;
        ++length;
    }
    tail->next = head;

    k = length - k % length;
    if (k != length) {
        for (int i = 0; i < k; ++i) {
            tail = tail->next;
        }
    }

    const auto new_head = tail->next;
    tail->next = nullptr;

    return new_head;
}


/** Rotate Doubly linked list by N nodes
 *
 * @reference   https://www.geeksforgeeks.org/rotate-doubly-linked-list-n-nodes/
 *
 * Given a doubly linked list, rotate the linked list counter-clockwise by N nodes. Here
 * N is a given positive integer and is smaller than the count of nodes in linked list.
 */
inline auto LeftRotate_DoublyList(std::list<int> elements, const std::list<int>::size_type k) {
    assert(k < elements.size());

    auto mid = std::next(elements.cbegin(), k);
    elements.splice(elements.cbegin(), elements, mid, elements.cend());
    return elements;
}


/** Quickly find multiple left rotations of an array | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/quickly-find-multiple-left-rotations-of-an-array/
 * @reference   Print left rotation of array in O(n) time and O(1) space
 *              https://www.geeksforgeeks.org/print-left-rotation-array/
 *
 * Given an array of size n and multiple values around which we need to left rotate the
 * array. How to quickly find multiple left rotations?
 */
auto MultipleLeftRotate_2n(const ArrayType &elements, const ArrayType &queries) {
    auto elements_after_elements = elements;
    for (const auto e : elements) {
        elements_after_elements.push_back(e);
    }

    std::vector<ArrayType> outputs;
    for (const auto k : queries) {
        const auto start_index = k % elements.size();
        const auto cbegin = std::next(elements_after_elements.cbegin(), start_index);
        const auto cend = std::next(cbegin, elements.size());
        outputs.emplace_back(cbegin, cend);
    }

    return outputs;
}


auto MultipleLeftRotate_n(const ArrayType &elements, const ArrayType &queries) {
    std::vector<ArrayType> outputs;
    for (const auto k : queries) {
        outputs.emplace_back();
        auto &out = outputs.back();
        for (ArrayType::size_type i = k; i < k + elements.size(); ++i) {
            out.emplace_back(elements[i % elements.size()]);
        }
    }

    return outputs;
}


/**
 * @reference   Perform String Shifts
 *              https://code.dennyzhang.com/perform-string-shifts
 *
 * You are given a string s containing lowercase English letters, and a matrix shift,
 * where shift[i] = [direction, amount]:
 *  direction can be 0 (for left shift) or 1 (for right shift).
 *  amount is the amount by which string s is to be shifted.
 *  A left shift by 1 means remove the first character of s and append it to the end.
 *  Similarly, a right shift by 1 means remove the last character of s and add it to the
 *  beginning.
 * Return the final string after all operations.
 */
auto StrShifts(std::string s, const ShiftArrayType &shifts) {
    int count = 0;
    for (const auto &[direction, amount] : shifts) {
        if (direction == 0) {
            count += amount;
        } else {
            count -= amount;
        }
    }

    const int N = s.size();
    count = ((count % N) + N) % N;
    std::rotate(s.begin(), s.begin() + count, s.end());
    return s;
}

} //namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;


constexpr InitializerType SampleArray = {1, 2, 3, 4, 5, 6, 7};
constexpr InitializerType ExpectedArray = {3, 4, 5, 6, 7, 1, 2};

constexpr InitializerType SampleArray2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
constexpr InitializerType ExpectedArray2 = {4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3};

constexpr InitializerType SampleArray7 = {1, 2, 3, 4, 5, 6, 7};
constexpr InitializerType ExpectedArray7 = {4, 5, 6, 7, 1, 2, 3};


THE_BENCHMARK(LeftRotate_Simple, SampleArray, 2);

SIMPLE_TEST(LeftRotate_Simple, TestSample, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_Simple, TestSample2, ExpectedArray2, SampleArray2, 3);
SIMPLE_TEST(LeftRotate_Simple, TestSample7, ExpectedArray7, SampleArray7, 3);


THE_BENCHMARK(LeftRotate_GCD, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_GCD, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_GCD, TestSample2, ExpectedArray2, SampleArray2, 3);
SIMPLE_TEST(LeftRotate_GCD, TestSample7, ExpectedArray7, SampleArray7, 3);


THE_BENCHMARK(LeftRotate_BlockSwap_Recursive, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_BlockSwap_Recursive, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_BlockSwap_Recursive, TestSample2, ExpectedArray2, SampleArray2, 3);


THE_BENCHMARK(LeftRotate_BlockSwap_Iterative, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_BlockSwap_Iterative, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_BlockSwap_Iterative, TestSample2, ExpectedArray2, SampleArray2, 3);


THE_BENCHMARK(LeftRotate_Reversal, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_Reversal, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_Reversal, TestSample2, ExpectedArray2, SampleArray2, 3);


constexpr InitializerType SampleArray3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
constexpr InitializerType ExpectedArrayR1 = {8, 9, 10, 1, 2, 3, 4, 5, 6, 7};
constexpr InitializerType SampleArray4 = {121, 232, 33, 43, 5};
constexpr InitializerType ExpectedArrayR2 = {43, 5, 121, 232, 33};


THE_BENCHMARK(RightRotate_Reversal, SampleArray3, 3);

SIMPLE_TEST(RightRotate_Reversal, TestSample, ExpectedArrayR1, SampleArray3, 3);
SIMPLE_TEST(RightRotate_Reversal, TestSample2, ExpectedArrayR2, SampleArray4, 2);


constexpr InitializerType ExpectedArray3 = {2, 3, 4, 5, 6, 7, 1};


THE_BENCHMARK(LeftRotate_SinglyList, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_SinglyList, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_SinglyList, TestSample2, ExpectedArray2, SampleArray2, 3);
SIMPLE_TEST(LeftRotate_SinglyList, TestSample3, ExpectedArray3, SampleArray, 1);


THE_BENCHMARK(LeftRotate_DoublyList, SampleArray2, 3);

SIMPLE_TEST(LeftRotate_DoublyList, TestSample1, ExpectedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotate_DoublyList, TestSample2, ExpectedArray2, SampleArray2, 3);


constexpr InitializerType SampleArray5 = {1, 3, 5, 7, 9};
constexpr InitializerType SampleQuery5 = {1, 3, 4, 6, 14};
// clang-format off
const std::vector<ArrayType> ExpectedMultiple5 = {
    {3, 5, 7, 9, 1},
    {7, 9, 1, 3, 5},
    {9, 1, 3, 5, 7},
    {3, 5, 7, 9, 1},
    {9, 1, 3, 5, 7}
};
// clang-format on


THE_BENCHMARK(MultipleLeftRotate_2n, SampleArray5, SampleQuery5);

SIMPLE_TEST(MultipleLeftRotate_2n, TestSample, ExpectedMultiple5, SampleArray5, SampleQuery5);


THE_BENCHMARK(MultipleLeftRotate_n, SampleArray5, SampleQuery5);

SIMPLE_TEST(MultipleLeftRotate_n, TestSample, ExpectedMultiple5, SampleArray5, SampleQuery5);


const ShiftArrayType SAMPLE1S = {{0, 1}, {1, 2}};
const ShiftArrayType SAMPLE2S = {{1, 1}, {0, 2}};
const ShiftArrayType SAMPLE3S = {{1, 1}, {1, 1}, {0, 2}, {1, 3}};


THE_BENCHMARK(StrShifts, "abcdefg", SAMPLE3S);

SIMPLE_TEST(StrShifts, TestSample1, "cab", "abc", SAMPLE1S);
SIMPLE_TEST(StrShifts, TestSample2, "bca", "abc", SAMPLE2S);
SIMPLE_TEST(StrShifts, TestSample3, "efgabcd", "abcdefg", SAMPLE3S);


SIMPLE_TEST(TestHelper, TestRightRotateSample1, ExpectedArrayR1, RotateRight, SampleArray3, 3);
SIMPLE_TEST(TestHelper, TestRightRotateSample2, ExpectedArrayR2, RotateRight, SampleArray4, 2);
