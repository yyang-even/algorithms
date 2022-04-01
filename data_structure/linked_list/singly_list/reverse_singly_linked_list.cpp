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
    return TestHelper(ReverseSublist, array, left, right);
}


/**
 * @reference   Reverse a Linked List in groups of given size | Set 1
 *              https://www.geeksforgeeks.org/reverse-a-list-in-groups-of-given-size/
 *
 * Given a linked list, write a function to reverse every k nodes (where k is an input
 * to the function).
 */
SinglyLinkedList::Node::PointerType
ReverseNodesInGroups_Recursive(const SinglyLinkedList::Node::PointerType head,
                               const int K) {
    if (not head)
        return {};

    auto current = head;
    SinglyLinkedList::Node::PointerType next;
    SinglyLinkedList::Node::PointerType prev;
    int count = 0;
    while (current and count++ < K) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head->next = ReverseNodesInGroups_Recursive(next, K);

    return prev;
}


/**
 * @reference   Reverse a Linked List in groups of given size | Set 2
 *              https://www.geeksforgeeks.org/reverse-linked-list-groups-given-size-set-2/
 */
inline auto
ReverseNodesInGroups_Stack(SinglyLinkedList::Node::PointerType head, const int K) {
    std::stack<SinglyLinkedList::Node::PointerType> node_stack;
    auto current = head;
    SinglyLinkedList::Node::PointerType prev;

    for (auto current = head; current;) {
        for (int count = 0; current and count++ < K;) {
            node_stack.push(current);
            current = current->next;
        }

        while (not node_stack.empty()) {
            if (not prev) {
                prev = node_stack.top();
                head = prev;
            } else {
                prev->next = node_stack.top();
                prev = prev->next;
            }
            node_stack.pop();
        }
    }

    prev->next = nullptr;

    return head;
}


/**
 * @reference   Reverse a singly Linked List in groups of given size | Set 3
 *              https://www.geeksforgeeks.org/reverse-a-singly-linked-list-in-groups-of-given-size-set-3/
 */
inline auto
ReverseNodesInGroups_Data(const SinglyLinkedList::Node::PointerType head, const int K) {
    if (not head) {
        return head;
    }

    std::deque<SinglyLinkedList::Node::PointerType> node_queue;
    for (auto current = head; current;) {
        for (int count = 0; current and count++ < K;) {
            node_queue.push_back(current);
            current = current->next;
        }

        while (not node_queue.empty()) {
            std::swap(node_queue.front()->value, node_queue.back()->value);

            if (not node_queue.empty()) {
                node_queue.pop_front();
            }
            if (not node_queue.empty()) {
                node_queue.pop_back();
            }
        }
    }

    return head;
}


/**
 * @reference   Reverse a Linked List in groups of given size (Iterative Approach)
 *              https://www.geeksforgeeks.org/reverse-a-linked-list-in-groups-of-given-size-iterative-approach/
 */
inline auto
ReverseNodesInGroups_Iterative(const SinglyLinkedList::Node::PointerType head,
                               const int K) {
    SinglyLinkedList::Node::PointerType new_head, tail;

    for (auto current = head; current;) {
        const auto joint = current;

        SinglyLinkedList::Node::PointerType prev;
        for (int count = 0; current and count++ < K;) {
            const auto next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        if (not new_head) {
            new_head = prev;
        }

        if (tail) {
            tail->next = prev;
        }

        tail = joint;
    }

    return new_head;
}


template <typename ReverseGroups>
inline constexpr auto
testReverseNodesInGroups(const ReverseGroups reverse_groups,
                         const ArrayType &array, const int K) {
    return TestHelper(reverse_groups, array, K);
}


/**
 * @reference   Reverse Nodes in k-Group
 *              https://leetcode.com/problems/reverse-nodes-in-k-group/
 *
 * Given a linked list, reverse the nodes of a linked list k at a time and return its
 * modified list. k is a positive integer and is less than or equal to the length of the
 * linked list. If the number of nodes is not a multiple of k then left-out nodes, in
 * the end, should remain as it is. You may not alter the values in the list's nodes,
 * only nodes themselves may be changed.
 * Follow-up: Can you solve the problem in O(1) extra memory space?
 */

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


const ArrayType EXPECTED1K = {2, 1, 4, 3, 5};

const ArrayType SAMPLE3 = {1, 2, 3, 4, 5, 6, 7, 8};
const ArrayType EXPECTED3K = {3, 2, 1, 6, 5, 4, 8, 7};

const ArrayType EXPECTED4K = {5, 4, 3, 2, 1, 8, 7, 6};


THE_BENCHMARK(testReverseNodesInGroups, ReverseNodesInGroups_Recursive, SAMPLE1, 2);

SIMPLE_TEST(testReverseNodesInGroups, TestSample1R, EXPECTED1K,
            ReverseNodesInGroups_Recursive, SAMPLE1, 2);
SIMPLE_TEST(testReverseNodesInGroups, TestSample2R, SAMPLE2,
            ReverseNodesInGroups_Recursive, SAMPLE2, 1);
SIMPLE_TEST(testReverseNodesInGroups, TestSample3R, EXPECTED3K,
            ReverseNodesInGroups_Recursive, SAMPLE3, 3);
SIMPLE_TEST(testReverseNodesInGroups, TestSample4R, EXPECTED4K,
            ReverseNodesInGroups_Recursive, SAMPLE3, 5);


SIMPLE_TEST(testReverseNodesInGroups, TestSample1S, EXPECTED1K,
            ReverseNodesInGroups_Stack, SAMPLE1, 2);
SIMPLE_TEST(testReverseNodesInGroups, TestSample2S, SAMPLE2,
            ReverseNodesInGroups_Stack, SAMPLE2, 1);
SIMPLE_TEST(testReverseNodesInGroups, TestSample3S, EXPECTED3K,
            ReverseNodesInGroups_Stack, SAMPLE3, 3);
SIMPLE_TEST(testReverseNodesInGroups, TestSample4S, EXPECTED4K,
            ReverseNodesInGroups_Stack, SAMPLE3, 5);


SIMPLE_TEST(testReverseNodesInGroups, TestSample1D, EXPECTED1K,
            ReverseNodesInGroups_Data, SAMPLE1, 2);
SIMPLE_TEST(testReverseNodesInGroups, TestSample2D, SAMPLE2,
            ReverseNodesInGroups_Data, SAMPLE2, 1);
SIMPLE_TEST(testReverseNodesInGroups, TestSample3D, EXPECTED3K,
            ReverseNodesInGroups_Data, SAMPLE3, 3);
SIMPLE_TEST(testReverseNodesInGroups, TestSample4D, EXPECTED4K,
            ReverseNodesInGroups_Data, SAMPLE3, 5);


SIMPLE_TEST(testReverseNodesInGroups, TestSample1I, EXPECTED1K,
            ReverseNodesInGroups_Iterative, SAMPLE1, 2);
SIMPLE_TEST(testReverseNodesInGroups, TestSample2I, SAMPLE2,
            ReverseNodesInGroups_Iterative, SAMPLE2, 1);
SIMPLE_TEST(testReverseNodesInGroups, TestSample3I, EXPECTED3K,
            ReverseNodesInGroups_Iterative, SAMPLE3, 3);
SIMPLE_TEST(testReverseNodesInGroups, TestSample4I, EXPECTED4K,
            ReverseNodesInGroups_Iterative, SAMPLE3, 5);
