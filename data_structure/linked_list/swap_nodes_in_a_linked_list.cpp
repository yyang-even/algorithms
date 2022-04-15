#include "common_header.h"

#include "singly_list/singly_linked_list.h"


namespace {

const std::vector SAMPLE_ARRAY = {10, 15, 12, 13, 20, 14};


inline auto testSwapNodes(const int x, const int y) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.Swap(x, y);

    list.InsertFront(-1);
    list.PushBack(100);

    return list.CopyToArray();
}


inline auto testSwapNodes_Clever(const int x, const int y) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.Swap_Clever(x, y);

    list.InsertFront(-1);
    list.PushBack(100);

    return list.CopyToArray();
}


/**
 * @reference   Swapping Nodes in a Linked List
 *              https://leetcode.com/problems/swapping-nodes-in-a-linked-list/
 *
 * You are given the head of a linked list, and an integer k.
 * Return the head of the linked list after swapping the values of the kth node from
 * the beginning and the kth node from the end (the list is 1-indexed).
 * 1 <= k <= n <= 10^5
 */
inline auto SwapNodes_Value(const SinglyLinkedList::Node::PointerType head, int k) {
    auto one = head;
    while (k-- > 1) {
        one = one->next;
    }

    auto another = head;
    for (auto p = one->next; p; p = p->next) {
        another = another->next;
    }

    std::swap(one->value, another->value);

    return head;
}

}//namespace


const std::vector EXPECTED_ARRAY1 = {-1, 10, 15, 20, 13, 12, 14, 100};
const std::vector EXPECTED_ARRAY2 = {-1, 20, 15, 12, 13, 10, 14, 100};  //head
const std::vector EXPECTED_ARRAY3 = {-1, 10, 15, 13, 12, 20, 14, 100};  //adjacent
const std::vector EXPECTED_ARRAY4 = {-1, 10, 14, 12, 13, 20, 15, 100};  //tail


THE_BENCHMARK(testSwapNodes, 12, 20);

SIMPLE_TEST(testSwapNodes, TestSample1, EXPECTED_ARRAY1, 12, 20);
SIMPLE_TEST(testSwapNodes, TestSample2, EXPECTED_ARRAY2, 10, 20);
SIMPLE_TEST(testSwapNodes, TestSample3, EXPECTED_ARRAY3, 12, 13);
SIMPLE_TEST(testSwapNodes, TestSample4, EXPECTED_ARRAY4, 15, 14);


THE_BENCHMARK(testSwapNodes_Clever, 12, 20);

SIMPLE_TEST(testSwapNodes_Clever, TestSample1, EXPECTED_ARRAY1, 12, 20);
SIMPLE_TEST(testSwapNodes_Clever, TestSample2, EXPECTED_ARRAY2, 10, 20);
SIMPLE_TEST(testSwapNodes_Clever, TestSample3, EXPECTED_ARRAY3, 12, 13);
SIMPLE_TEST(testSwapNodes_Clever, TestSample4, EXPECTED_ARRAY4, 15, 14);


const std::vector SAMPLE1 = {1, 2, 3, 4, 5};
const std::vector EXPECTED1 = {1, 4, 3, 2, 5};

const std::vector SAMPLE2 = {7, 9, 6, 6, 7, 8, 3, 0, 9, 5};
const std::vector EXPECTED2 = {7, 9, 6, 6, 8, 7, 3, 0, 9, 5};

const std::vector EXPECTED3 = {5, 2, 3, 4, 1};


SIMPLE_TEST(TestHelper, TestSample1, EXPECTED1, SwapNodes_Value, SAMPLE1, 2);
SIMPLE_TEST(TestHelper, TestSample2, EXPECTED2, SwapNodes_Value, SAMPLE2, 5);
SIMPLE_TEST(TestHelper, TestSample3, EXPECTED3, SwapNodes_Value, SAMPLE1, 1);
