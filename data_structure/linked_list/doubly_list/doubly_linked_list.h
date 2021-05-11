#pragma once

#include "common_header.h"


/** Doubly Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.2.
 *
 * @reference   Doubly Linked List | Set 1 (Introduction and Insertion)
 *              https://www.geeksforgeeks.org/doubly-linked-list/
 *
 * @reference   Program to find size of Doubly Linked List
 *              https://www.geeksforgeeks.org/program-find-size-doubly-linked-list/
 */
class DoublyLinkedList {
public:
    struct Node {
        using ValueType = int;
        using PointerType = std::shared_ptr<Node>;

        ValueType value;

        static inline std::size_t node_alive = 0;

        constexpr explicit Node(const ValueType v = 0): value(v) {
            ++node_alive;
        }

        ~Node() {
            --node_alive;
        }

        constexpr PointerType &Next() {
            return next;
        }

        constexpr const PointerType &Next() const {
            return next;
        }


        constexpr PointerType &Prev() {
            return prev;
        }

        constexpr const PointerType &Prev() const {
            return prev;
        }

    private:
        PointerType prev = nullptr;
        PointerType next = nullptr;
    };

protected:
    Node::PointerType head = nullptr;
    Node::PointerType tail = nullptr;
    std::size_t size = 0;

public:
    using ValueType = Node::ValueType;

    DoublyLinkedList() = default;
    explicit DoublyLinkedList(const std::vector<ValueType> &array) {
        for (const auto elem : array) {
            PushBack(elem);
        }
    }


    ~DoublyLinkedList() {
        for (; head; head = head->Next()) {
            head->Prev() = nullptr;
        }

        if (tail) {
            tail->Next() = nullptr;
            tail = nullptr;
        }
    }


    auto GetHead() const {
        return head;
    }


    constexpr auto Empty() const {
        return not size;
    }


    constexpr auto Size() const {
        return size;
    }


    void PushFront(const ValueType v) {
        const auto new_node = std::make_shared<Node>(v);
        new_node->Next() = head;

        if (head) {
            head->Prev() = new_node;
        }

        head = new_node;

        if (not tail) {
            tail = new_node;
        }

        ++size;
    }


    void InsertBefore(const Node::PointerType next, const ValueType v) {
        assert(next);

        const auto new_node = std::make_shared<Node>(v);
        new_node->Prev() = next->Prev();
        new_node->Next() = next;

        next->Prev() = new_node;

        if (new_node->Prev()) {
            new_node->Prev()->Next() = new_node;
        } else {
            head = new_node;
        }

        ++size;
    }


    void InsertAfter(const Node::PointerType prev, const ValueType v) {
        assert(prev);

        const auto new_node = std::make_shared<Node>(v);
        new_node->Prev() = prev;
        new_node->Next() = prev->Next();

        prev->Next() = new_node;

        if (new_node->Next()) {
            new_node->Next()->Prev() = new_node;
        } else {
            tail = new_node;
        }

        ++size;
    }


    /** Sorted insert in a doubly linked list with head and tail pointers
     *
     * @reference   https://www.geeksforgeeks.org/create-doubly-linked-list-using-double-pointer-inserting-nodes-list-remains-ascending-order/
     *
     * A Doubly linked list is a linked list that consists of a set of sequentially linked
     * records called nodes. Each node contains two fields that are references to the
     * previous and to the next node in the sequence of nodes. The task is to create a
     * doubly linked list by inserting nodes such that list remains in ascending order on
     * printing from left to right. Also, we need to maintain two pointers, head (points
     * to first node) and tail (points to last node).
     *
     * @reference   Insert value in sorted way in a sorted doubly linked list
     *              https://www.geeksforgeeks.org/insert-value-sorted-way-sorted-doubly-linked-list/
     *
     * Given a sorted doubly linked list and a value to insert, write a function to insert
     * the value in sorted way.
     */
    void SortedInsert(const ValueType v) {
        auto current = head;

        while (current and (current->value < v)) {
            current = current->Next();
        }

        if (current) {
            InsertBefore(current, v);
        } else {
            PushBack(v);
        }
    }


    void PushBack(const ValueType v) {
        const auto new_node = std::make_shared<Node>(v);
        new_node->Prev() = tail;

        if (tail) {
            tail->Next() = new_node;
        }

        tail = new_node;

        if (not head) {
            head = new_node;
        }

        ++size;
    }


    const auto Search(const ValueType v) const {
        auto iter = head;
        for (; iter and iter->value != v; iter = iter->Next());
        return iter;
    }


    const auto At(std::size_t index) const {
        assert(index < size);
        auto iter = head;
        for (; index--; iter = iter->Next());
        return iter;
    }


    const auto CopyToArray() const {
        std::vector<Node::ValueType> array;
        for (auto iter = head; iter; iter = iter->Next()) {
            array.push_back(iter->value);
        }

        return array;
    }


    /**
     * @reference   Print Doubly Linked list in Reverse Order
     *              https://www.geeksforgeeks.org/print-doubly-linked-list-in-reverse-order/
     */
    const auto CopyToArray_Reverse() const {
        std::vector<Node::ValueType> array;
        for (auto iter = tail; iter; iter = iter->Prev()) {
            array.push_back(iter->value);
        }

        return array;
    }


    /**
     * @reference   Delete a node in a Doubly Linked List
     *              https://www.geeksforgeeks.org/delete-a-node-in-a-doubly-linked-list/
     */
    void Delete(const Node::PointerType del) {
        assert(del);

        if (head == del) {
            head = del->Next();
        }
        if (tail == del) {
            tail = del->Prev();
        }

        if (del->Next()) {
            del->Next()->Prev() = del->Prev();
        }
        if (del->Prev()) {
            del->Prev()->Next() = del->Next();
        }

        --size;
    }


    /**
     * @reference   Delete a Doubly Linked List node at a given position
     *              https://www.geeksforgeeks.org/delete-doubly-linked-list-node-given-position/
     *
     * Given a doubly linked list and a position n. The task is to delete the node at the
     * given position n from the beginning.
     */
    void DeleteAt(const std::size_t index) {
        const auto del = At(index);
        Delete(del);
    }


    /**
     * @reference   Reverse a Doubly Linked List
     *              https://www.geeksforgeeks.org/reverse-a-doubly-linked-list/
     * @reference   Reverse a Doubly linked list using recursion
     *              https://www.geeksforgeeks.org/reverse-doubly-linked-list-using-recursion/
     * @reference   Reverse a Doubly Linked List | Set-2
     *              https://www.geeksforgeeks.org/reverse-doubly-linked-list-set-2/
     * @reference   Reverse a Doubly Linked List | Set 4 (Swapping Data)
     *              https://www.geeksforgeeks.org/reverse-doubly-linked-list-set-4-swapping-data/
     */
    void Reverse() {
        for (auto iter = head; iter; iter = iter->Prev()) {
            std::swap(iter->Next(), iter->Prev());
        }
        std::swap(head, tail);
    }


    void Reverse_Recursive() {
        Reverse_Recursive(head);
        std::swap(head, tail);
    }

    void Reverse_Recursive(const Node::PointerType current) {
        if (current) {
            std::swap(current->Next(), current->Prev());
            Reverse_Recursive(current->Prev());
        }
    }


    void Reverse_TwoPointers() {
        if (head) {
            auto left = head;
            auto right = tail;
            for (; left != right and left->Prev() != right;
                 left = left->Next(), right = right->Prev()) {
                std::swap(left->value, right->value);
            }
        }
    }
};
