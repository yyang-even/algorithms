#include "singly_linked_list.h"
#include "singly_circular_linked_list.h"


namespace {

using ArrayType = std::vector<int>;

inline auto testReverse_Iterative(const ArrayType &array) {
    SinglyLinkedList list {array};
    list.Reverse_Iterative();
    return list.CopyToArray();
}


inline auto testReverse_Recursive(const ArrayType &array) {
    SinglyLinkedList list {array};
    list.Reverse_Recursive();
    return list.CopyToArray();
}


inline auto testReverse_TwoPointers(const ArrayType &array) {
    SinglyLinkedList list {array};
    list.Reverse_TwoPointers();
    return list.CopyToArray();
}


inline auto testReverse_Stack(const ArrayType &array) {
    SinglyLinkedList list {array};
    list.Reverse_Stack();
    return list.CopyToArray();
}


inline auto testReverse_Circular(const ArrayType &array) {
    SinglyCircularLinkedList list {array};
    list.Reverse();
    return list.CopyToArray();
}


/**
 * @reference   Reverse a sublist of linked list
 *              https://www.geeksforgeeks.org/reverse-sublist-linked-list/
 * @reference   Reverse Linked List II
 *              https://leetcode.com/problems/reverse-linked-list-ii/
 *
 * Given the head of a singly linked list and two integers left and right where
 * left <= right, reverse the nodes of the list from position left to position right,
 * and return the reversed list.
 */
auto ReverseSublist(const SinglyLinkedList::Node::PointerType head,
                    int left, const int right) {
    if (not head) {
        return head;
    }

    const auto dummy = std::make_shared<SinglyLinkedList::Node>();
    dummy->next = head;

    auto before_begin = dummy;
    for (int i = 1; i < left; ++i) {
        before_begin = before_begin->next;
    }

    const auto new_sub_tail = before_begin->next;
    auto prev = new_sub_tail;
    auto current = prev->next;
    for (; current and left < right; ++left) {
        const auto next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    before_begin->next = prev;
    new_sub_tail->next = current;

    return dummy->next;
}

inline auto
testReverseSublist(const ArrayType &array, const int left, const int right) {
    const auto head = SinglyLinkedList{array}.GetHead();
    return CopyToArray(ReverseSublist(head, left, right));
}

}//namespace


const ArrayType EMPTY_ARRAY {};
const ArrayType SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const ArrayType EXPECTED_REVERSE_ARRAY {9, 5, 4, 7, 3, 2, 6, 8, 0, 1};


THE_BENCHMARK(testReverse_Iterative, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Iterative, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Iterative, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testReverse_Recursive, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Recursive, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Recursive, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testReverse_TwoPointers, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_TwoPointers, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_TwoPointers, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testReverse_Stack, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Stack, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Stack, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testReverse_Circular, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Circular, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Circular, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5};
const ArrayType EXPECTED1 = {1, 4, 3, 2, 5};

const ArrayType SAMPLE2 = {5};


THE_BENCHMARK(testReverseSublist, SAMPLE1, 2, 4);

SIMPLE_TEST(testReverseSublist, TestSample1, EXPECTED1, SAMPLE1, 2, 4);
SIMPLE_TEST(testReverseSublist, TestSample2, SAMPLE2, SAMPLE2, 1, 1);
SIMPLE_TEST(testReverseSublist, TestSample3, EXPECTED_REVERSE_ARRAY,
            SAMPLE_ARRAY, 1, SAMPLE_ARRAY.size());
