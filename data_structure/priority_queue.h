#include "common_header.h"

#include "binary_heap.h"

#include "singly_linked_list.h"

/** Priority Queue
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.5. Exercises 6.5-3.
 *
 *              https://www.geeksforgeeks.org/priority-queue-set-1-introduction/
 *              Priority Queue in C++ Standard Template Library (STL)
 *              https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
 */
using MaxPriorityQueue = MaxHeap;
using MinPriorityQueue = MinHeap;


/** Priority Queue using Linked List
 *
 * @reference   https://www.geeksforgeeks.org/priority-queue-using-linked-list/
 *
 * Implement Priority Queue using Linked Lists.
 */
class SinglyLinkedListMinPriorityQueue : protected SinglyLinkedList {
public:
    SinglyLinkedListMinPriorityQueue() = default;
    SinglyLinkedListMinPriorityQueue(const std::vector<SinglyListNode::ValueType> &array) {
        for (const auto elem : array) {
            SortedInsert(elem);
        }
    }

    void Push(const SinglyListNode::ValueType v) {
        SortedInsert(v);
    }

    void Pop() {
        Delete(*head);
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
