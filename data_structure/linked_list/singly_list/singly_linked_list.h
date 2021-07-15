#pragma once

#include "common_header.h"


template<typename Pointer>
static inline constexpr auto CopyToArray(const Pointer head) {
    std::vector<typename Pointer::element_type::ValueType> array;

    for (auto iter = head; iter; iter = iter->next) {
        array.push_back(iter->value);
    }

    return array;
}


template<typename Pointer>
static inline constexpr auto CountSize_Iterative(Pointer head) {
    std::size_t size = 0;
    for (; head; head = head->next) {
        ++size;
    }

    return size;
}


/** Singly Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.2.
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 4.
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
 * @reference   Difference between Singly linked list and Doubly linked list
 *              https://www.geeksforgeeks.org/difference-between-singly-linked-list-and-doubly-linked-list/
 * @reference   Search an element in a Linked List (Iterative and Recursive)
 *              https://www.geeksforgeeks.org/search-an-element-in-a-linked-list-iterative-and-recursive/
 * @reference   Find Length of a Linked List (Iterative and Recursive)
 *              https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/
 * @reference   Remove first node of the linked list
 *              https://www.geeksforgeeks.org/remove-first-node-of-the-linked-list/
 * @reference   Applications of linked list data structure
 *              https://www.geeksforgeeks.org/applications-of-linked-list-data-structure/
 * @reference   A Programmer’s approach of looking at Array vs. Linked List
 *              https://www.geeksforgeeks.org/programmers-approach-looking-array-vs-linked-list/
 */
class SinglyLinkedList {
public:
    struct Node {
        using ValueType = int;
        using PointerType = std::shared_ptr<Node>;

        ValueType value;
        PointerType next = nullptr;

        static inline std::size_t node_alive = 0;

        constexpr explicit Node(const ValueType v = 0): value(v) {
            ++node_alive;
        }

        ~Node() {
            --node_alive;
        }
    };

protected:
    Node::PointerType head = nullptr;
    Node::PointerType tail = nullptr;
    std::size_t size = 0;

    void delete_Nonhead(Node::PointerType previous,
                        const std::function<bool(const Node &)> is_same_node) {
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

    void deleteHelper(const std::function<bool(const Node &)> is_same_node) {
        if (head) {
            if (is_same_node(*head)) {
                PopHead();
            } else {
                delete_Nonhead(head, is_same_node);
            }
        }
    }

    const Node::PointerType search_RecursiveHelper(const Node::PointerType node,
                                                   const Node::ValueType key) const {
        return (not node or node->value == key) ?
               node : search_RecursiveHelper(node->next, key);
    }

    std::size_t countSize_RecursiveHelper(const Node::PointerType node) const {
        return node ? countSize_RecursiveHelper(node->next) + 1 : 0;
    }

    void reverse_RecursiveHelper(const Node::PointerType current,
                                 const Node::PointerType previous) {
        if (not current->next) {
            head = current;
            current->next = previous;
            return;
        }

        const auto next = current->next;
        current->next = previous;
        reverse_RecursiveHelper(next, current);
    }

    Node::ValueType getN_RecursiveHelper(const Node::PointerType node,
                                         const std::size_t index) const {
        return index == 0 ? node->value : getN_RecursiveHelper(node->next, index - 1);
    }

    void getReverseN_RecursiveHelper(const Node::PointerType node, const std::size_t index,
                                     std::size_t &i, Node::ValueType &output) const {
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
     * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
     *              Questions 2.3.
     *
     * Given a pointer to a node to be deleted, delete the node.
     * Note: that we don’t have pointer to head node.
     *
     * @reference   Delete Node in a Linked List
     *              https://leetcode.com/problems/delete-node-in-a-linked-list/
     *
     * Write a function to delete a node in a singly-linked list. You will not be given
     * access to the head of the list, instead you will be given access to the node to
     * be deleted directly. It is guaranteed that the node to be deleted is not a tail
     * node in the list.
     */
    static void deleteNode_WithoutHead(Node &to_be_deleted, std::size_t &size) {
        assert(to_be_deleted.next);

        to_be_deleted = *(to_be_deleted.next);
        --size;
    }

public:
    using ValueType = Node::ValueType;
    friend class SinglyCircularLinkedList;

    SinglyLinkedList() = default;
    /**
     * @reference   Create linked list from a given array
     *              https://www.geeksforgeeks.org/create-linked-list-from-a-given-array/
     * @reference   Convert a String to a Singly Linked List
     *              https://www.geeksforgeeks.org/convert-a-string-to-a-singly-linked-list/
     */
    explicit SinglyLinkedList(const std::vector<Node::ValueType> &array) {
        for (const auto elem : array) {
            PushBack(elem);
        }
    }

    ~SinglyLinkedList() {
        if (tail) {
            tail->next = nullptr;
        }
    }


    auto GetHead() const {
        return head;
    }


    auto Empty() const {
        return not head;
    }


    constexpr auto Size() const {
        return size;
    }


    void PushBack(const Node::ValueType v) {
        const auto new_node = std::make_shared<Node>(v);
        if (tail) {
            tail->next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
        ++size;
    }

    void InsertFront(const Node::ValueType v) {
        const auto new_node = std::make_shared<Node>(v);
        if (head) {
            new_node->next = head;
            head = new_node;
        } else {
            head = tail = new_node;
        }
        ++size;
    }

    void InsertAfter(Node &node, const Node::ValueType v) {
        const auto new_node = std::make_shared<Node>(v);
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
     * Given a singly linked list, a position and an element, the task is to write a
     * program to insert that element in a linked list at a given position.
     */
    void InsertAt_Simple(std::size_t position, const Node::ValueType v) {
        assert(position and position <= size + 1);

        const auto new_node = std::make_shared<Node>(v);
        if (position == 1) {
            InsertFront(v);
        } else {
            const auto prev = At(position - 2);
            InsertAfter(*prev, v);
        }
    }

    void InsertAt_Clever(std::size_t position, const Node::ValueType v) {
        ++size;
        assert(position and position <= size);

        auto *current = &head;
        const auto new_node = std::make_shared<Node>(v);
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
     * Given a sorted linked list and a value to insert, write a function to insert the
     * value in sorted way.
     */
    void SortedInsert(const Node::ValueType v) {
        auto *current = &head;
        const auto new_node = std::make_shared<Node>(v);

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


    auto Search_Iterative(const Node::ValueType key,
                          Node::PointerType *prev = nullptr) const {
        auto iter = head;
        while (iter and iter->value != key) {
            if (prev) {
                *prev = iter;
            }
            iter = iter->next;
        }
        return iter;
    }

    auto Search_Recursive(const Node::ValueType key) const {
        return search_RecursiveHelper(head, key);
    }


    auto CopyToArray() const {
        return ::CopyToArray(head);
    }


    Node::ValueType PopHead() {
        assert(head);

        const auto v = head->value;
        head = head->next;
        --size;

        return v;
    }


    void Delete(const Node::ValueType key) {
        deleteHelper([key](const auto & node) {
            return node.value == key;
        });
    }

    void Delete(const Node &target_node) {
        deleteHelper([&target_node](const auto & node) {
            return &node == &target_node;
        });
    }

    /** Delete a given node in Linked List under given constraints
     *
     * @reference   https://www.geeksforgeeks.org/delete-a-given-node-in-linked-list-under-given-constraints/
     *
     * Given a Singly Linked List, write a function to delete a given node.
     * Your function must follow following constraints:
     *  1) It must accept pointer to the start node as first parameter and node to be
     *  deleted as second parameter i.e., pointer to head node is not global.
     *  2) It should not return pointer to the head node.
     *  3) It should not accept pointer to pointer to head node.
     *
     * You may assume that the Linked List never becomes empty.
     */
    void DeleteNode_Constrained(const Node &target_node) {
        if (head) {
            if (head.get() == &target_node) {
                deleteNode_WithoutHead(*head, size);
            } else {
                delete_Nonhead(head, [&target_node](const auto & node) {
                    return &node == &target_node;
                });
            }
        }
    }


    /** Write a function to delete a Linked List
     *
     * @reference   https://www.geeksforgeeks.org/write-a-function-to-delete-a-linked-list/
     *
     * Algorithm For C/C++: Iterate through the linked list and delete all the nodes one
     * by one. Main point here is not to access next of the current pointer if current
     * pointer is deleted.
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


    /** Delete last occurrence of an item from linked list
     *
     * @reference   https://www.geeksforgeeks.org/delete-last-occurrence-of-an-item-from-linked-list/
     *
     * Given a liked list and a key to be deleted. Delete last occurrence of key from
     * linked. The list may have duplicates.
     */
    void DeleteLastOfKey(const Node::ValueType key) {
        if (head) {
            Node::PointerType *pointer_to_last_of_key = nullptr;
            if (head->value == key) {
                pointer_to_last_of_key = &head;
                if (head == tail) {
                    tail = nullptr;
                }
            }

            for (auto iter = head; iter->next; iter = iter->next) {
                if (iter->next->value == key) {
                    pointer_to_last_of_key = &(iter->next);
                    if (not iter->next->next) {
                        tail = iter;
                    }
                }
            }

            if (pointer_to_last_of_key) {
                *pointer_to_last_of_key = (*pointer_to_last_of_key)->next;
                --size;
            }
        }
    }


    auto CountSize_Iterative() const {
        return ::CountSize_Iterative(head);
    }

    auto CountSize_Recursive() const {
        return countSize_RecursiveHelper(head);
    }


    /** Reverse a linked list
     *
     * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
     *              Introduction to Algorithms, Third Edition. Section 10.2. Exercises 10.2-7.
     * @reference   https://www.geeksforgeeks.org/reverse-a-linked-list/
     * @reference   Recursively Reversing a linked list (A simple implementation)
     *              https://www.geeksforgeeks.org/recursively-reversing-a-linked-list-a-simple-implementation/
     * @reference   Can we reverse a linked list in less than O(n)?
     *              https://www.geeksforgeeks.org/can-we-reverse-a-linked-list-in-less-than-on/
     * @reference   Print reverse of a Linked List without actually reversing
     *              https://www.geeksforgeeks.org/print-reverse-of-a-linked-list-without-actually-reversing/
     * @reference   C Program for Reverse a linked list
     *              https://www.geeksforgeeks.org/c-program-for-reverse-a-linked-list/
     * @reference   Reverse Linked List
     *              https://leetcode.com/problems/reverse-linked-list/
     *
     * Given pointer to the head node of a linked list, the task is to reverse the linked
     * list. We need to reverse the list by changing links between nodes.
     *
     * @complexity  O(n)
     */
    void Reverse_Iterative() {
        tail = head;
        auto current = head;
        Node::PointerType previous = nullptr;

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
        while (current->next) {
            const auto next = current->next;
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

        std::stack<Node::PointerType> node_stack;
        while (head->next) {
            node_stack.push(head);
            head = head->next;
        }

        while (not node_stack.empty()) {
            tail = tail->next = node_stack.top();
            node_stack.pop();
        }
        tail->next = nullptr;
    }

    /**
     * Print reverse of a Linked List without extra space and modifications
     * @reference   https://www.geeksforgeeks.org/print-reverse-linked-list-without-extra-space-modifications/
     *
     * For i = n to 1, do following.
     *     Print i-th node using get n-th node function
     */

    /**
     * An interesting method to print reverse of a linked list
     * @reference   https://www.geeksforgeeks.org/an-interesting-method-to-print-reverse-of-a-linked-list/
     *
     * Carriage return ("r"): It commands a printer (cursor or the display of a system
     * console), to move the position of the cursor to the first position on the same
     * line.
     */


    /** Write a function to get Nth node in a Linked List
     *
     * @reference   https://www.geeksforgeeks.org/write-a-function-to-get-nth-node-in-a-linked-list/
     *
     * Write a GetNth() function that takes a linked list and an integer index and
     * returns the data value stored in the node at that index position.
     */
    Node::PointerType At(std::size_t index) const {
        assert(index < size);

        auto target = head;
        while (index--) {
            target = target->next;
        }

        return target;
    }

    auto GetN_Iterative(const std::size_t index) const {
        return At(index)->value;
    }

    auto GetN_Recursive(const std::size_t index) const {
        assert(index < size);
        return getN_RecursiveHelper(head, index);
    }


    /**
     * @reference   Recursive function to delete k-th node from linked list
     *              https://www.geeksforgeeks.org/recursive-function-delete-k-th-node-linked-list/
     */


    /** Program for n'th node from the end of a Linked List
     *
     * @reference   https://www.geeksforgeeks.org/nth-node-from-the-end-of-a-linked-list/
     * @reference   Recursive Approach to find nth node from the end in the linked list
     *              https://www.geeksforgeeks.org/recursive-approach-to-find-nth-node-from-the-end-in-the-linked-list/
     * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
     *              Questions 2.2.
     *
     * Given a Linked List and a number n, write a function that returns the value at the
     * n'th node from end of the Linked List.
     */
    auto GetReverseN_Iterative(const std::size_t index) const {
        return GetN_Iterative(size - index - 1);
    }

    auto GetReverseN_Recursive(const std::size_t index) const {
        assert(index < size);

        std::size_t i = 0;
        Node::ValueType output{};
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

    /**
     * @reference   Find the sum of last n nodes of the given Linked List
     *              https://www.geeksforgeeks.org/find-sum-last-n-nodes-given-linked-list/
     */


    /**
     * @reference   Delete Nth node from the end of the given linked list
     *              https://www.geeksforgeeks.org/delete-nth-node-from-the-end-of-the-given-linked-list/
     */

    /**
     * @reference   Print the last k nodes of the linked list in reverse order | Recursive approach
     *              https://www.geeksforgeeks.org/print-the-last-k-nodes-of-the-linked-list-in-reverse-order/
     * @reference   Print the last k nodes of the linked list in reverse order | Iterative Approaches
     *              https://www.geeksforgeeks.org/print-the-last-k-nodes-of-the-linked-list-in-reverse-order-iterative-approaches/
     */


    /** Find the middle of a given linked list in C and Java
     *
     * @reference   https://www.geeksforgeeks.org/write-a-c-function-to-print-the-middle-of-the-linked-list/
     *
     * Given a singly linked list, find middle of the linked list. For example, if given
     * linked list is 1->2->3->4->5 then output should be 3. If there are even nodes,
     * then there would be two middle nodes, we need to print second middle element. For
     * example, if given linked list is 1->2->3->4->5->6 then output should be 4.
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


    /**
     * @reference   Swap nodes in a linked list without swapping data
     *              https://www.geeksforgeeks.org/swap-nodes-in-a-linked-list-without-swapping-data/
     *
     * Given a linked list and two keys in it, swap nodes for two given keys. Nodes
     * should be swapped by changing links. Swapping data of nodes may be expensive in
     * many situations when data contains many fields. It may be assumed that all keys
     * in linked list are distinct.
     */
    void Swap(const Node::ValueType x, const Node::ValueType y) {
        assert(x != y);
        assert(size > 1);

        Node::PointerType prev_x = nullptr;
        const auto current_x = Search_Iterative(x, &prev_x);

        Node::PointerType prev_y = nullptr;
        const auto current_y = Search_Iterative(y, &prev_y);

        assert(current_x and current_y);

        if (tail == current_x) {
            tail = current_y;
        } else if (tail == current_y) {
            tail = current_x;
        }

        if (prev_x == nullptr) {
            head = current_y;
        } else {
            prev_x->next = current_y;
        }

        if (prev_y == nullptr) {
            head = current_x;
        } else {
            prev_y->next = current_x;
        }

        std::swap(current_x->next, current_y->next);
    }

    void Swap_Clever(const Node::ValueType x, const Node::ValueType y) {
        assert(x != y);
        assert(size > 1);

        Node::PointerType *node_x = nullptr;
        Node::PointerType *node_y = nullptr;
        for (auto current = &head;
             *current and not(node_x and node_y);
             current = &((*current)->next)) {
            if ((*current)->value == x) {
                node_x = current;
            } else if ((*current)->value == y) {
                node_y = current;
            }
        }

        assert(*node_x and * node_y);

        if (tail == *node_x) {
            tail = *node_y;
        } else if (tail == *node_y) {
            tail = *node_x;
        }

        std::swap(*node_x, *node_y);
        std::swap((*node_x)->next, (*node_y)->next);
    }


    /**
     * @reference   Make a loop at k-th position in a linked list
     *              https://www.geeksforgeeks.org/make-loop-k-th-position-linked-list/
     */
    void MakeLoopAt(const std::size_t index) const {
        tail->next = At(index);
    }


    /**
     * @reference   Recursive insertion and traversal linked list
     *              https://www.geeksforgeeks.org/recursive-insertion-and-traversal-linked-list/
     */
};
