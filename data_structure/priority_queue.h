#pragma once

#include "common_header.h"

#include "heap/binary_heap.h"

#include "data_structure/linked_list/singly_list/singly_linked_list.h"
#include "data_structure/linked_list/sorted_insert_linked_list.h"


/** Priority Queue
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 6.5. Exercises 6.5-3.
 *
 *              https://www.geeksforgeeks.org/priority-queue-set-1-introduction/
 *              Priority Queue in C++ Standard Template Library (STL)
 *              https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
 */
template <typename T>
using MaxPriorityQueue = MaxHeap<T>;
template <typename T>
using MinPriorityQueue = MinHeap<T>;


/** Priority Queue using Linked List
 *
 * @reference   https://www.geeksforgeeks.org/priority-queue-using-linked-list/
 *
 * Implement Priority Queue using Linked Lists.
 *
 * @reference   Priority Queue using doubly linked list
 *              https://www.geeksforgeeks.org/priority-queue-using-doubly-linked-list/
 *
 * @highlight   The use of std::make_move_iterator().
 */
class SinglyLinkedListMinPriorityQueue : protected SinglyLinkedList {
public:
    SinglyLinkedListMinPriorityQueue() = default;
    explicit
    SinglyLinkedListMinPriorityQueue(const std::vector<Node::ValueType> &array) {
        for (const auto elem : array) {
            SortedInsert(elem);
        }
    }

    void Push(const Node::ValueType v) {
        SortedInsert(v);
    }

    void Pop() {
        PopHead();
    }

    auto Peek() const {
        return head->value;
    }

    auto MoveToSortedArray() {
        const auto array = CopyToArray();
        DeleteAllOneByOne();
        return array;
    }
};


class SinglyLinkedListMinPriorityQueue_STL {
    using ListType = std::forward_list<int>;
    ListType sorted_list;

public:
    SinglyLinkedListMinPriorityQueue_STL() = default;
    explicit
    SinglyLinkedListMinPriorityQueue_STL(std::vector<ListType::value_type> array) {
        std::sort(array.begin(), array.end());
        sorted_list = ContainerCast<ListType>(std::move(array));
    }

    void Push(const ListType::value_type v) {
        SortedInsert_STL(sorted_list, v);
    }

    void Pop() {
        sorted_list.pop_front();
    }

    auto Peek() const {
        return sorted_list.front();
    }

    auto MoveToSortedArray() {
        auto array =
            ContainerCast<std::vector<ListType::value_type>>(std::move(sorted_list));
        sorted_list.clear();
        return array;
    }
};
