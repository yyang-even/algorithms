#pragma once

#include "common_header.h"


/** Doubly Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.2.
 *
 * @reference   Doubly Linked List | Set 1 (Introduction and Insertion)
 *              https://www.geeksforgeeks.org/doubly-linked-list/
 */
class DoublyLinkedList {
public:
    struct DoublyListNode {
        using ValueType = int;
        using PointerType = std::shared_ptr<DoublyListNode>;

        ValueType value;

        static std::size_t node_alive;

        explicit DoublyListNode(const ValueType v = 0): value(v) {
            ++node_alive;
        }
        ~DoublyListNode() {
            --node_alive;
        }

        PointerType &Next() {
            return next;
        }
        const PointerType &Next() const {
            return next;
        }
        PointerType &Prev() {
            return prev;
        }
        const PointerType &Prev() const {
            return prev;
        }

    private:
        PointerType prev = nullptr;
        PointerType next = nullptr;
    };

protected:
    DoublyListNode::PointerType head = nullptr;
    DoublyListNode::PointerType tail = nullptr;
    std::size_t size = 0;

public:
    using ValueType = DoublyListNode::ValueType;

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

        tail = nullptr;
    }


    auto Empty() const {
        return not size;
    }


    auto Size() const {
        return size;
    }


    void PushFront(const ValueType v) {
        const auto new_node = std::make_shared<DoublyListNode>(v);
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


    void InsertBefore(const DoublyListNode::PointerType next, const ValueType v) {
        assert(next);

        const auto new_node = std::make_shared<DoublyListNode>(v);
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


    void InsertAfter(const DoublyListNode::PointerType prev, const ValueType v) {
        assert(prev);

        const auto new_node = std::make_shared<DoublyListNode>(v);
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


    void PushBack(const ValueType v) {
        const auto new_node = std::make_shared<DoublyListNode>(v);
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
        std::vector<DoublyListNode::ValueType> array;
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
        std::vector<DoublyListNode::ValueType> array;
        for (auto iter = tail; iter; iter = iter->Prev()) {
            array.push_back(iter->value);
        }

        return array;
    }


    /**
     * @reference   Delete a node in a Doubly Linked List
     *              https://www.geeksforgeeks.org/delete-a-node-in-a-doubly-linked-list/
     */
    void Delete(const DoublyListNode::PointerType del) {
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
     * Given a doubly linked list and a position n. The task is to delete the node at
     * the given position n from the beginning.
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
    void Reverse_Recursive(const DoublyListNode::PointerType current) {
        if (current) {
            std::swap(current->Next(), current->Prev());
            Reverse_Recursive(current->Prev());
        }
    }

    void Reverse_TwoPointers() {
        if (head) {
            auto left = head;
            auto right = tail;
            for (; left != right and left->Prev() != right; left = left->Next(), right = right->Prev()) {
                std::swap(left->value, right->value);
            }
        }
    }
};

std::size_t DoublyLinkedList::DoublyListNode::node_alive = 0;
