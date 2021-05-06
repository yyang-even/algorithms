#include "common_header.h"

#include "sublist_rotation.h"


namespace {

using ListType = std::forward_list<int>;

/** Rotate the sub-list of a linked list from position M to N to the right by K places
 *
 * @reference   https://www.geeksforgeeks.org/rotate-the-sub-list-of-a-linked-list-from-position-m-to-n-to-the-right-by-k-places/
 *
 * Given a linked list and two positions 'm' and 'n'. The task is to rotate the sublist
 * from position m to n, to the right by k places.
 */
auto SublistRightRotate_SinglyList(ListType elements,
                                   const ListType::size_type m,
                                   const ListType::size_type n,
                                   const ListType::difference_type k) {
    assert(m and n and m < n);

    const auto cbefore_begin = std::next(elements.cbefore_begin(), m - 1);
    const auto length = n - m + 1;
    const auto cend = std::next(cbefore_begin, length + 1);

    return SublistLeftRotate_SinglyList(
               elements, cbefore_begin, cend, length - (k % (length)));
}


/** Rotate Linked List block wise
 *
 * @reference   https://www.geeksforgeeks.org/rotate-linked-list-block-wise/
 *
 * Given a Linked List of length n and block length k rotate in circular manner towards
 * right/left each block by a number d. If d is positive rotate towards right else rotate
 * towards left.
 */
auto BlockwiseRightRotate_SinglyList(std::forward_list<int> elements,
                                     const std::forward_list<int>::size_type k, const int d) {
    auto cbefore_begin = elements.cbefore_begin();
    for (auto iter = std::next(cbefore_begin); iter != elements.cend();) {
        std::forward_list<int>::size_type i = 0;
        for (; i < k and iter != elements.cend(); ++i, std::advance(iter, 1));
        SublistLeftRotate_SinglyList(elements, cbefore_begin, iter, -d);
        std::advance(cbefore_begin, i);
    }

    return elements;
}

}//namespace


const ListType SampleArray = {1, 2, 3, 4, 5, 6};
const ListType ExpectedArray = {1, 4, 5, 2, 3, 6};
const ListType SampleArray1 = {1, 2, 3, 4, 5, 6};
const ListType ExpectedArray1 = {5, 6, 1, 2, 3, 4};
const ListType SampleArray2 = {10, 20, 30, 40, 50, 60, 70};
const ListType ExpectedArray2 = {10, 20, 50, 60, 30, 40, 70};
const ListType SampleArray3 = {20, 45, 32, 34, 22, 28};
const ListType ExpectedArray3 = {20, 45, 34, 22, 28, 32};


THE_BENCHMARK(SublistRightRotate_SinglyList, SampleArray, 2, 5, 2);

SIMPLE_TEST(SublistRightRotate_SinglyList, TestSample, ExpectedArray,
            SampleArray, 2, 5, 2);
SIMPLE_TEST(SublistRightRotate_SinglyList, TestSample1, ExpectedArray1,
            SampleArray1, 1, 6, 2);
SIMPLE_TEST(SublistRightRotate_SinglyList, TestSample2, ExpectedArray2,
            SampleArray2, 3, 6, 2);
SIMPLE_TEST(SublistRightRotate_SinglyList, TestSample3, ExpectedArray3,
            SampleArray3, 3, 6, 3);


const ListType SampleArray4 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
const ListType ExpectedArray4 = {2, 3, 4, 1, 6, 7, 8, 5, 10, 11, 12, 9, 14, 15, 13};
const ListType ExpectedArray5 = {2, 3, 1, 5, 6, 4, 8, 9, 7, 11, 12, 10, 14, 15, 13};


THE_BENCHMARK(BlockwiseRightRotate_SinglyList, SampleArray4, 4, -1);

SIMPLE_TEST(BlockwiseRightRotate_SinglyList, TestSample4, ExpectedArray4,
            SampleArray4, 4, -1);
SIMPLE_TEST(BlockwiseRightRotate_SinglyList, TestSample5, ExpectedArray5,
            SampleArray4, 3, -1);
