#pragma once

#include "common_header.h"

#include <stack>

/** Singly Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.2.
 *
 * @reference   Linked List | Set 1 (Introduction)
 *              https://www.geeksforgeeks.org/linked-list-set-1-introduction/
 * @reference   Linked List | Set 2 (Inserting a node)
 *              https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
 * @reference   How to write C functions that modify head pointer of a Linked List?
 *              https://www.geeksforgeeks.org/how-to-write-functions-that-modify-the-head-pointer-of-a-linked-list/
 * @reference   Linked List | Set 3 (Deleting a node)
 *              https://www.geeksforgeeks.org/linked-list-set-3-deleting-node/
 * @reference   Delete a Linked List node at a given position
 *              https://www.geeksforgeeks.org/delete-a-linked-list-node-at-a-given-position/
 * @reference   Linked List vs Array
 *              https://www.geeksforgeeks.org/linked-list-vs-array/
 * @reference   Search an element in a Linked List (Iterative and Recursive)
 *              https://www.geeksforgeeks.org/search-an-element-in-a-linked-list-iterative-and-recursive/
 * @reference   Find Length of a Linked List (Iterative and Recursive)
 *              https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/
 */
class SinglyLinkedList {
public:
    struct SinglyListNode {
        using ValueType = int;
        using PointerType = std::shared_ptr<SinglyListNode>;

        ValueType value;
        PointerType next;

        static std::size_t node_alive;

        SinglyListNode() {
            ++node_alive;
        }
        SinglyListNode(const ValueType v): value(v) {
            ++node_alive;
        }
        ~SinglyListNode() {
            --node_alive;
        }
    };

protected:
    SinglyListNode::PointerType head;
    SinglyListNode::PointerType tail;
    std::size_t size = 0;

    void delete_Nonhead(SinglyListNode::PointerType previous,
                        const std::function<bool(const SinglyListNode &)> is_same_node) {
        assert(previous);

        while (previous->next) {
            if (is_same_node(*(previous->next))) {
                previous->next = previous->next->next;
                if (not previous->next) {
                    tail = previous;
                }
                --size;
                break;
            }
            previous = previous->next;
        }
    }

    void deleteHelper(const std::function<bool(const SinglyListNode &)> is_same_node) {
        if (head) {
            if (is_same_node(*head)) {
                PopHead();
            } else {
                delete_Nonhead(head, is_same_node);
            }
        }
    }

    const SinglyListNode::PointerType search_RecursiveHelper(const SinglyListNode::PointerType node,
            const SinglyListNode::ValueType key) const {
        return (not node or node->value == key) ? node : search_RecursiveHelper(node->next, key);
    }

    std::size_t countSize_RecursiveHelper(const SinglyListNode::PointerType node) const {
        return node ? countSize_RecursiveHelper(node->next) + 1 : 0;
    }

    void reverse_RecursiveHelper(const SinglyListNode::PointerType current,
                                 const SinglyListNode::PointerType previous) {
        if (not current->next) {
            head = current;
            current->next = previous;
            return;
        }

        const auto next = current->next;
        current->next = previous;
        reverse_RecursiveHelper(next, current);
    }

    SinglyListNode::ValueType getN_RecursiveHelper(const SinglyListNode::PointerType node,
            const std::size_t index) const {
        return index == 0 ? node->value : getN_RecursiveHelper(node->next, index - 1);
    }

    void getReverseN_RecursiveHelper(const SinglyListNode::PointerType node, const std::size_t index,
                                     std::size_t &i, SinglyListNode::ValueType &output) const {
        if (node) {
            getReverseN_RecursiveHelper(node->next, index, i, output);

            if (i++ == index) {
                output = node->value;
            }
        }
    }

    /** Given only a pointer/reference to a node to be deleted in a singly linked list, how do you delete it?
     *
     * @reference   https://www.geeksforgeeks.org/given-only-a-pointer-to-a-node-to-be-deleted-in-a-singly-linked-list-how-do-you-delete-it/
     * @reference   https://www.geeksforgeeks.org/in-a-linked-list-given-only-a-pointer-to-a-node-to-be-deleted-in-a-singly-linked-list-how-do-you-delete-it/
     * @reference   Delete a Node from linked list without head pointer
     *              https://www.geeksforgeeks.org/delete-a-node-from-linked-list-without-head-pointer/
     *
     * Given a pointer to a node to be deleted, delete the node.
     * Note that we don’t have pointer to head node.
     */
    static void deleteNode_WithoutHead(SinglyListNode &to_be_deleted, std::size_t &size) {
        assert(to_be_deleted.next);

        to_be_deleted = *(to_be_deleted.next);
        --size;
    }
public:
    using ValueType = SinglyListNode::ValueType;

    SinglyLinkedList() = default;
    SinglyLinkedList(const std::vector<SinglyListNode::ValueType> &array) {
        for (const auto elem : array) {
            PushBack(elem);
        }
    }

    auto Empty() const {
        return not head;
    }

    auto Size() const {
        return size;
    }

    void PushBack(const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (tail) {
            tail->next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
        ++size;
    }

    void InsertFront(const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (head) {
            new_node->next = head;
            head = new_node;
        } else {
            head = tail = new_node;
        }
        ++size;
    }

    void InsertAfter(SinglyListNode &node, const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (not node.next) {
            tail = new_node;
        } else {
            new_node->next = node.next;
        }
        node.next = new_node;
        ++size;
    }

    /** Insert a node at a specific position in a linked list
     *
     * @reference   https://www.geeksforgeeks.org/insert-a-node-at-a-specific-position-in-a-linked-list/
     *
     * Given a singly linked list, a position and an element, the task is to write
     * a program to insert that element in a linked list at a given position.
     */
    void InsertAt_Simple(std::size_t position, const SinglyListNode::ValueType v) {
        ++size;
        assert(position and position <= size);

        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (position == 1) {
            new_node->next = head;
            head = new_node;
        } else {
            auto current = head;
            while (--position > 1) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
            if (not new_node->next) {
                tail = new_node;
            }
        }
    }

    void InsertAt_Clever(std::size_t position, const SinglyListNode::ValueType v) {
        ++size;
        assert(position and position <= size);

        auto *current = &head;
        const auto new_node = std::make_shared<SinglyListNode>(v);
        while (position--) {
            if (not position) {
                new_node->next = *current;
                *current = new_node;
            } else {
                current = &(*current)->next;
            }
        }
        if (not new_node->next) {
            tail = new_node;
        }
    }


    /** Given a linked list which is sorted, how will you insert in sorted way
     *
     * @reference   https://www.geeksforgeeks.org/given-a-linked-list-which-is-sorted-how-will-you-insert-in-sorted-way/
     *
     * Given a sorted linked list and a value to insert, write a function to insert the value in sorted way.
     */
    void SortedInsert(const SinglyListNode::ValueType v) {
        auto *current = &head;
        const auto new_node = std::make_shared<SinglyListNode>(v);

        while (*current and (*current)->value < v) {
            current = &(*current)->next;
        }

        new_node->next = *current;
        *current = new_node;

        if (not new_node->next) {
            tail = new_node;
        }
        ++size;
    }


    auto Search_Iterative(const SinglyListNode::ValueType key) const {
        auto iter = head;
        while (iter and iter->value != key) {
            iter = iter->next;
        }
        return iter;
    }

    auto Search_Recursive(const SinglyListNode::ValueType key) const {
        return search_RecursiveHelper(head, key);
    }

    auto CopyToArray() const {
        std::vector<SinglyListNode::ValueType> array;
        auto iter = head;

        while (iter) {
            array.push_back(iter->value);
            iter = iter->next;
        }

        return array;
    }

    SinglyListNode::ValueType PopHead() {
        assert(head);

        const auto v = head->value;
        head = head->next;
        --size;

        return v;
    }

    void Delete(const SinglyListNode::ValueType key) {
        deleteHelper([key](const SinglyListNode & node) {
            return node.value == key;
        });
    }

    void Delete(const SinglyListNode &target_node) {
        deleteHelper([&target_node](const SinglyListNode & node) {
            return &node == &target_node;
        });
    }

    /** Delete a given node in Linked List under given constraints
     *
     * @reference   https://www.geeksforgeeks.org/delete-a-given-node-in-linked-list-under-given-constraints/
     *
     * Given a Singly Linked List, write a function to delete a given node.
     * Your function must follow following constraints:
     * 1) It must accept pointer to the start node as first parameter and
     * node to be deleted as second parameter i.e., pointer to head node is not global.
     * 2) It should not return pointer to the head node.
     * 3) It should not accept pointer to pointer to head node.
     *
     * You may assume that the Linked List never becomes empty.
     */
    void DeleteNode_Constrained(const SinglyListNode &target_node) {
        if (head) {
            if (head.get() == &target_node) {
                deleteNode_WithoutHead(*head, size);
            } else {
                delete_Nonhead(head, [&target_node](const SinglyListNode & node) {
                    return &node == &target_node;
                });
            }
        }
    }


    /** Write a function to delete a Linked List
     *
     * @reference   https://www.geeksforgeeks.org/write-a-function-to-delete-a-linked-list/
     *
     * Algorithm For C/C++: Iterate through the linked list and delete all the nodes one by one.
     * Main point here is not to access next of the current pointer if current pointer is deleted.
     *
     * @reference   Delete a linked list using recursion
     *              https://www.geeksforgeeks.org/delete-linked-list-using-recursion/
     */
    void DeleteAllOneByOne() {
        head = tail = nullptr;
        size = 0;
    }
    void DeleteAllOneByOne_Recursive() {
        if (head != tail) {
            head = head->next;
            DeleteAllOneByOne_Recursive();
        } else {
            head = tail = nullptr;
            size = 0;
        }
    }


    auto CountSize_Iterative() const {
        std::size_t size = 0;
        auto iter = head;
        while (iter) {
            ++size;
            iter = iter->next;
        }

        return size;
    }

    auto CountSize_Recursive() const {
        return countSize_RecursiveHelper(head);
    }


    /** Reverse a linked list
     *
     * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
     *              Introduction to Algorithms, Third Edition. Chapter 10.2. Exercises 10.2-7.
     * @reference   https://www.geeksforgeeks.org/reverse-a-linked-list/
     * @reference   Recursively Reversing a linked list (A simple implementation)
     *              https://www.geeksforgeeks.org/recursively-reversing-a-linked-list-a-simple-implementation/
     * @reference   Can we reverse a linked list in less than O(n)?
     *              https://www.geeksforgeeks.org/can-we-reverse-a-linked-list-in-less-than-on/
     * @reference   Print reverse of a Linked List without actually reversing
     *              https://www.geeksforgeeks.org/print-reverse-of-a-linked-list-without-actually-reversing/
     *
     * Given pointer to the head node of a linked list, the task is to reverse
     * the linked list. We need to reverse the list by changing links between nodes.
     *
     * @complexity  O(n)
     */
    void Reverse_Iterative() {
        tail = head;
        auto current = head;
        SinglyListNode::PointerType previous = nullptr;

        while (current) {
            const auto next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }

    void Reverse_Recursive() {
        if (not head) {
            return;
        }
        tail = head;

        reverse_RecursiveHelper(head, nullptr);
    }

    /** Iteratively Reverse a linked list using only 2 pointers (An Interesting Method)
     *
     * @reference   https://www.geeksforgeeks.org/iteratively-reverse-a-linked-list-using-only-2-pointers/
     *
     * Method 1: The idea is to use XOR to swap pointers.
     *
     * @comment     This method doesn't work with shared_ptr.
     *
     * Method 2: Implemented as below.
     */
    void Reverse_TwoPointers() {
        if (not head) {
            return;
        }
        tail = head;

        auto current = head;
        while (current->next != nullptr) {
            auto next = current->next;
            current->next = next->next;
            next->next = head;
            head = next;
        }
    }

    /** Program to reverse a linked list using Stack
     *
     * @reference   https://www.geeksforgeeks.org/program-to-reverse-a-linked-list-using-stack/
     * @reference   Print Reverse a linked list using Stack
     *              https://www.geeksforgeeks.org/print-reverse-linked-list-using-stack/
     */
    void Reverse_Stack() {
        if (not head) {
            return;
        }
        tail = head;

        std::stack<SinglyListNode::PointerType> node_stack;
        while (head->next) {
            node_stack.push(head);
            head = head->next;
        }

        auto prev = head;
        while (not node_stack.empty()) {
            prev = prev->next = node_stack.top();
            node_stack.pop();
        }
        prev->next = nullptr;
    }

    /** Write a function to get Nth node in a Linked List
     *
     * @reference   https://www.geeksforgeeks.org/write-a-function-to-get-nth-node-in-a-linked-list/
     *
     * Write a GetNth() function that takes a linked list and an integer index
     * and returns the data value stored in the node at that index position.
     */
    auto GetN_Iterative(std::size_t index) const {
        assert(index < size);

        auto target = head;
        while (index--) {
            target = target->next;
        }

        return target->value;
    }

    auto GetN_Recursive(const std::size_t index) const {
        assert(index < size);
        return getN_RecursiveHelper(head, index);
    }

    /** Program for n’th node from the end of a Linked List
     *
     * @reference   https://www.geeksforgeeks.org/nth-node-from-the-end-of-a-linked-list/
     *
     * Given a Linked List and a number n, write a function that returns the value
     * at the n’th node from end of the Linked List.
     */
    auto GetReverseN_Iterative(const std::size_t index) const {
        return GetN_Iterative(size - index - 1);
    }

    auto GetReverseN_Recursive(const std::size_t index) const {
        assert(index < size);

        std::size_t i = 0;
        SinglyListNode::ValueType output{};
        getReverseN_RecursiveHelper(head, index, i, output);
        return output;
    }

    auto GetReverseN_TwoPointers(std::size_t index) const {
        assert(index < size);

        auto target = head;
        auto helper = head;

        while (index--) {
            helper = helper->next;
        }

        while (helper->next) {
            helper = helper->next;
            target = target->next;
        }

        return target->value;
    }


    /** Find the middle of a given linked list in C and Java
     *
     * @reference   https://www.geeksforgeeks.org/write-a-c-function-to-print-the-middle-of-the-linked-list/
     *
     * Given a singly linked list, find middle of the linked list. For example,
     * if given linked list is 1->2->3->4->5 then output should be 3.
     * If there are even nodes, then there would be two middle nodes, we need
     * to print second middle element. For example, if given linked list is
     * 1->2->3->4->5->6 then output should be 4.
     */
    auto GetMid_Size() const {
        return GetN_Iterative(size / 2);
    }

    auto GetMid_TwoPointers() const {
        assert(head);

        auto fast_ptr = head;
        auto slow_ptr = head;

        while (fast_ptr and fast_ptr->next) {
            fast_ptr = fast_ptr->next->next;
            slow_ptr = slow_ptr->next;
        }

        return slow_ptr->value;
    }

    auto GetMid_Odd() const {
        assert(head);

        auto count = 0;
        auto mid = head;
        auto current = head;

        while (current) {
            if (count++ & 1) {
                mid = mid->next;
            }

            current = current->next;
        }

        return mid->value;
    }
};

std::size_t SinglyLinkedList::SinglyListNode::node_alive = 0;
