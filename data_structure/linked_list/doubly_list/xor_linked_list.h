#pragma once

#include "common_header.h"


/** XOR Linked List – A Memory Efficient Doubly Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.2-8.
 * @reference   XOR Linked List – A Memory Efficient Doubly Linked List | Set 1
 *              https://www.geeksforgeeks.org/xor-linked-list-a-memory-efficient-doubly-linked-list-set-1/
 * @reference   XOR Linked List – A Memory Efficient Doubly Linked List | Set 2
 *              https://www.geeksforgeeks.org/xor-linked-list-a-memory-efficient-doubly-linked-list-set-2/
 * @reference   A Memory-Efficient Doubly Linked List
 *              https://www.linuxjournal.com/article/6828
 * @reference   Memory efficient doubly linked list
 *              https://www.geeksforgeeks.org/memory-efficient-doubly-linked-list/
 */
class XorLinkedList {
public:
    struct Node {
        using ValueType = int;
        using PointerType = Node*;

        ValueType value;
        PointerType prev_xor_next = nullptr;

        static inline std::size_t node_alive = 0;

        explicit Node(const ValueType v = 0): value(v) {
            ++node_alive;
        }
        ~Node() {
            --node_alive;
        }

        static PointerType Xor(const PointerType lhs, const PointerType rhs) {
            return reinterpret_cast<PointerType>(reinterpret_cast<unsigned long>(lhs) ^
                                                 reinterpret_cast<unsigned long>(rhs));
        }

        PointerType Next(const PointerType prev) const {
            return Xor(prev_xor_next, prev);
        }
        PointerType Next(PointerType &prev) {
            const auto next = Xor(prev_xor_next, prev);
            prev = this;
            return next;
        }
        PointerType Prev(PointerType &next) {
            return Next(next);
        }
    };

protected:
    Node::PointerType head = nullptr;
    Node::PointerType tail = nullptr;
    std::size_t size = 0;

public:
    using ValueType = Node::ValueType;

    XorLinkedList() = default;
    /**
     * @reference   Convert Singly Linked List to XOR Linked List
     *              https://www.geeksforgeeks.org/convert-singly-linked-list-to-xor-linked-list/
     */
    explicit XorLinkedList(const std::vector<ValueType> &array) {
        for (const auto elem : array) {
            PushBack(elem);
        }
    }
    XorLinkedList(const XorLinkedList &) = delete;
    XorLinkedList(XorLinkedList &&) = default;


    ~XorLinkedList() {
        Node::PointerType prev = nullptr;
        for (auto iter = head; iter;) {
            const auto next = iter->Next(prev);
            delete iter;
            iter = next;
        }
    }


    auto Empty() const {
        return not size;
    }


    auto Size() const {
        return size;
    }


    void PushFront(const ValueType v) {
        const auto new_node = new Node(v);
        new_node->prev_xor_next = head;

        if (head) {
            head->prev_xor_next = Node::Xor(new_node, head->prev_xor_next);
        }

        head = new_node;

        if (not tail) {
            tail = new_node;
        }

        ++size;
    }


    void InsertAfter(
        const std::pair<Node::PointerType, Node::PointerType> &prev_prev_pair,
        const ValueType v) {
        const auto [prev, prev_prev] = prev_prev_pair;
        assert(prev);

        const auto new_node = new Node(v);
        const auto next = prev->Next(prev_prev);
        new_node->prev_xor_next = Node::Xor(prev, next);

        prev->prev_xor_next = Node::Xor(prev_prev, new_node);

        if (next) {
            next->prev_xor_next = Node::Xor(new_node, next->Next(prev));
        } else {
            tail = new_node;
        }

        ++size;
    }


    void PushBack(const ValueType v) {
        const auto new_node = new Node(v);
        new_node->prev_xor_next = tail;

        if (tail) {
            tail->prev_xor_next = Node::Xor(new_node, tail->prev_xor_next);
        }

        tail = new_node;

        if (not head) {
            head = new_node;
        }

        ++size;
    }


    const auto Search(const ValueType v) const {
        Node::PointerType prev = nullptr;
        auto iter = head;
        for (; iter and iter->value != v; iter = iter->Next(prev));
        return std::make_pair(iter, prev);
    }


    const auto CopyToArray() const {
        std::vector<Node::ValueType> array;
        Node::PointerType prev = nullptr;
        for (auto current = head; current; current = current->Next(prev)) {
            array.push_back(current->value);
        }

        return array;
    }

    const auto CopyToArray_Reverse() const {
        std::vector<Node::ValueType> array;
        Node::PointerType next = nullptr;
        for (auto current = tail; current; current = current->Prev(next)) {
            array.push_back(current->value);
        }

        return array;
    }
};
