#pragma once

#include "common_header.h"


/** Implement Linked List using Array
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.3.
 * @reference   https://comtechstash.wordpress.com/2013/12/03/implement-linked-list-using-array/
 * @reference   A Programmer’s approach of looking at Array vs. Linked List
 *              https://www.geeksforgeeks.org/programmers-approach-looking-array-vs-linked-list/
 */
class ArrayLinkedList {
public:
    struct Node {
        using ValueType = int;
        using PointerType = int;

        static constexpr PointerType NULL_PTR = -1;

        ValueType value;
        PointerType next = NULL_PTR;

        constexpr explicit Node(const ValueType v = 0): value(v) {
        }
    };

    using ValueType = Node::ValueType;

protected:
    static constexpr int CAPACITY = 64;

    std::vector<Node> nodes = std::vector<Node>(CAPACITY, Node{});
    Node::PointerType free_list = 0;
    Node::PointerType head = Node::NULL_PTR;
    Node::PointerType tail = Node::NULL_PTR;
    std::size_t size = 0;

    Node::PointerType newNode(const ValueType v) {
        assert(size < CAPACITY);

        const auto new_node = free_list;
        free_list = nodes[free_list].next;
        nodes[new_node] = Node{v};
        ++size;

        return new_node;
    }

    void freeNode(const Node::PointerType node) {
        nodes[node].next = free_list;
        free_list = node;
        --size;
    }

public:
    ArrayLinkedList() {
        Node::PointerType index = 1;

        for (auto &node : nodes) {
            node.next = index++;
        }
        nodes.back().next = Node::NULL_PTR;
    }

    explicit ArrayLinkedList(const std::vector<ValueType> &array): ArrayLinkedList() {
        assert(array.size() <= CAPACITY);

        for (const auto elem : array) {
            PushBack(elem);
        }
    }


    constexpr auto Empty() const {
        return not size;
    }


    constexpr auto Size() const {
        return size;
    }


    void PushFront(const ValueType v) {
        const auto new_node = newNode(v);

        nodes[new_node].next = head;
        head = new_node;

        if (tail == Node::NULL_PTR) {
            tail = new_node;
        }
    }


    void PushBack(const ValueType v) {
        const auto new_node = newNode(v);
        if (tail != Node::NULL_PTR) {
            nodes[tail].next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
    }


    auto PopHead() {
        assert(size);

        const auto v = nodes[head].value;
        const auto next = nodes[head].next;
        freeNode(head);
        head = next;

        return v;
    }


    void InsertAfter(const Node::PointerType prev, const Node::ValueType v) {
        assert(prev != Node::NULL_PTR);

        if (tail == prev) {
            PushBack(v);
        } else {
            const auto new_node = newNode(v);
            nodes[new_node].next = nodes[prev].next;
            nodes[prev].next = new_node;
        }
    }


    auto Search(const Node::ValueType key, Node::PointerType *prev = nullptr) const {
        auto iter = head;
        while (iter != Node::NULL_PTR and nodes[iter].value != key) {
            if (prev) {
                *prev = iter;
            }
            iter = nodes[iter].next;
        }
        return iter;
    }


    void DeleteAfter(const Node::PointerType prev_del) {
        assert(prev_del != Node::NULL_PTR);

        if (tail == nodes[prev_del].next) {
            tail = prev_del;
        }
        const auto next = nodes[nodes[prev_del].next].next;
        freeNode(nodes[prev_del].next);
        nodes[prev_del].next = next;
    }

    void Delete(const ValueType v) {
        auto prev_del = Node::NULL_PTR;
        const auto key = Search(v, &prev_del);
        if (key != Node::NULL_PTR) {
            if (key == head) {
                PopHead();
            } else {
                DeleteAfter(prev_del);
            }
        }
    }


    auto CopyToArray() const {
        std::vector<Node::ValueType> array;

        for (auto iter = head; iter != Node::NULL_PTR; iter = nodes[iter].next) {
            array.push_back(nodes[iter].value);
        }

        return array;
    }
};
