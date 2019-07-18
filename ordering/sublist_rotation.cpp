#include "common_header.h"

#include "sublist_rotation.h"


namespace {

using ListType = std::forward_list<int>;

/** Rotate the sub-list of a linked list from position M to N to the right by K places
 *
 * @reference   https://www.geeksforgeeks.org/rotate-the-sub-list-of-a-linked-list-from-position-m-to-n-to-the-right-by-k-places/
 *
 * Given a linked list and two positions ‘m’ and ‘n’. The task is to rotate the sublist
 * from position m to n, to the right by k places.
 */
auto SublistRightRotate_SinglyList(ListType elements,
                                   const ListType::size_type m,
                                   const ListType::size_type n,
                                   const ListType::difference_type k) {
    assert(m and n and m < n);

    auto cbefore_begin = elements.cbefore_begin();
    std::advance(cbefore_begin, m - 1);
    auto cend = cbefore_begin;
    const auto length = n - m + 1;
    std::advance(cend, length + 1);

    return SublistLeftRotate_SinglyList(elements, cbefore_begin, cend, length - (k % (length)));
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


SIMPLE_BENCHMARK(SublistRightRotate_SinglyList, SampleArray, 2, 5, 2);

SIMPLE_TEST(SublistRightRotate_SinglyList, TestSample, ExpectedArray, SampleArray, 2, 5, 2);
SIMPLE_TEST(SublistRightRotate_SinglyList, TestSample1, ExpectedArray1, SampleArray1, 1, 6, 2);
SIMPLE_TEST(SublistRightRotate_SinglyList, TestSample2, ExpectedArray2, SampleArray2, 3, 6, 2);
SIMPLE_TEST(SublistRightRotate_SinglyList, TestSample3, ExpectedArray3, SampleArray3, 3, 6, 3);
