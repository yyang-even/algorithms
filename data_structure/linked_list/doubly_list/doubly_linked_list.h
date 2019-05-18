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
        PointerType prev;
        PointerType next;

        static std::size_t node_alive;

        explicit DoublyListNode(const ValueType v = 0): value(v) {
            ++node_alive;
        }
        ~DoublyListNode() {
            --node_alive;
        }
    };

protected:
    DoublyListNode::PointerType head;
    DoublyListNode::PointerType tail;
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
        for (; head; head = head->next) {
            head->prev = nullptr;
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
        new_node->next = head;

        if (head) {
            head->prev = new_node;
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
        new_node->prev = next->prev;
        new_node->next = next;

        next->prev = new_node;

        if (new_node->prev) {
            new_node->prev->next = new_node;
        } else {
            head = new_node;
        }

        ++size;
    }


    void InsertAfter(const DoublyListNode::PointerType prev, const ValueType v) {
        assert(prev);

        const auto new_node = std::make_shared<DoublyListNode>(v);
        new_node->prev = prev;
        new_node->next = prev->next;

        prev->next = new_node;

        if (new_node->next) {
            new_node->next->prev = new_node;
        } else {
            tail = new_node;
        }

        ++size;
    }


    void PushBack(const ValueType v) {
        const auto new_node = std::make_shared<DoublyListNode>(v);
        new_node->prev = tail;

        if (tail) {
            tail->next = new_node;
        }

        tail = new_node;

        if (not head) {
            head = new_node;
        }

        ++size;
    }


    const auto Search(const ValueType v) const {
        DoublyListNode::PointerType iter;
        for (iter = head; iter and iter->value != v; iter = iter->next);
        return iter;
    }


    const auto At(std::size_t index) const {
        assert(index < size);
        auto iter = head;
        for (; index--; iter = iter->next);
        return iter;
    }


    const auto CopyToArray() const {
        std::vector<DoublyListNode::ValueType> array;
        for (auto iter = head; iter; iter = iter->next) {
            array.push_back(iter->value);
        }

        return array;
    }

    const auto CopyToArray_Reverse() const {
        std::vector<DoublyListNode::ValueType> array;
        for (auto iter = tail; iter; iter = iter->prev) {
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
            head = del->next;
        }
        if (tail == del) {
            tail = del->prev;
        }

        if (del->next) {
            del->next->prev = del->prev;
        }
        if (del->prev) {
            del->prev->next = del->next;
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
     */
    void Reverse() {
        for (auto iter = head; iter; iter = iter->prev) {
            std::swap(iter->next, iter->prev);
        }
        std::swap(head, tail);
    }
};

std::size_t DoublyLinkedList::DoublyListNode::node_alive = 0;
