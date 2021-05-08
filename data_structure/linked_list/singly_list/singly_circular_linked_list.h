#pragma once

#include "common_header.h"

#include "singly_linked_list.h"


/** Circular Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.2. Exercises 10.2-5.
 * @reference   Circular Linked List | Set 1 (Introduction and Applications)
 *              https://www.geeksforgeeks.org/circular-linked-list/
 * @reference   Circular Linked List | Set 2 (Traversal)
 *              https://www.geeksforgeeks.org/circular-linked-list-set-2-traversal/
 * @reference   Circular Singly Linked List | Insertion
 *              https://www.geeksforgeeks.org/circular-singly-linked-list-insertion/
 *
 * Circular linked list is a linked list where all nodes are connected to form a circle.
 * There is no NULL at the end. A circular linked list can be a singly circular linked
 * list or doubly circular linked list.
 */
class SinglyCircularLinkedList {
public:
    using Node = SinglyLinkedList::Node;
    using ValueType = Node::ValueType;

protected:
    Node::PointerType tail = nullptr;
    std::size_t size = 0;

public:
    SinglyCircularLinkedList() = default;

    explicit SinglyCircularLinkedList(const std::vector<ValueType> &array) {
        for (const auto elem : array) {
            PushBack(elem);
        }
    }

    SinglyCircularLinkedList(SinglyCircularLinkedList &&list): tail(std::move(list.tail)),
        size(list.size) {
    }

    SinglyCircularLinkedList &operator=(SinglyCircularLinkedList &&list) {
        std::swap(tail, list.tail);
        std::swap(size, list.size);

        return *this;
    }

    /**
     * @reference   Convert singly linked list into circular linked list
     *              https://www.geeksforgeeks.org/convert-singly-linked-list-circular-linked-list/
     */
    explicit SinglyCircularLinkedList(SinglyLinkedList &&list): tail(std::move(list.tail)),
        size(std::move(list.size)) {
        if (tail) {
            tail->next = std::move(list.head);
        }
    }


    explicit operator SinglyLinkedList() {
        SinglyLinkedList list;
        list.tail = std::move(tail);
        list.size = std::move(size);
        if (list.tail) {
            list.head = std::move(list.tail->next);
        }

        return list;
    }


    ~SinglyCircularLinkedList() {
        if (tail) {
            tail->next = nullptr;
        }
    }


    Node::PointerType GetHead() const {
        return tail ? tail->next : nullptr;
    }


    constexpr auto Empty() const {
        return not size;
    }


    constexpr auto Size() const {
        return size;
    }

    /**
     * @reference   Count nodes in Circular linked list
     *              https://www.geeksforgeeks.org/count-nodes-circular-linked-list/
     */
    void OrderlessTraversal(const std::function<void(const Node::PointerType)> func) const {
        if (tail) {
            auto current = tail;
            do {
                current = current->next;
                func(current);
            } while (current != tail);
        }
    }

    auto CountSize() const {
        std::size_t count = 0;
        OrderlessTraversal([&count](const auto) {
            ++count;
        });
        return count;
    }


    void PushFront(const Node::PointerType new_node) {
        assert(new_node);

        if (not tail) {
            new_node->next = new_node;
            tail = new_node;

            ++size;
        } else {
            InsertAfterHelper(tail, new_node);
        }
    }

    void PushFront(const ValueType v) {
        const auto new_node = std::make_shared<Node>(v);
        PushFront(new_node);
    }


    void InsertAfterHelper(const Node::PointerType prev, const Node::PointerType new_node) {
        assert(prev);
        assert(new_node);

        new_node->next = prev->next;
        prev->next = new_node;

        ++size;
    }

    void InsertAfter(const Node::PointerType prev, const ValueType v) {
        const auto new_node = std::make_shared<Node>(v);
        InsertAfterHelper(prev, new_node);
        if (prev == tail) {
            tail = new_node;
        }
    }


    void PushBack(const ValueType v) {
        const auto new_node = std::make_shared<Node>(v);
        PushFront(new_node);
        tail = new_node;
    }


    /**
     * @reference   Sorted insert for circular linked list
     *              https://www.geeksforgeeks.org/sorted-insert-for-circular-linked-list/
     */
    void SortedInsert(const Node::ValueType v) {
        const auto new_node = std::make_shared<Node>(v);

        if (not tail) {
            PushFront(new_node);
        } else {
            auto *current = &tail;

            do {
                current = &(*current)->next;
            } while (*current != tail and (*current)->value < v);

            if (*current == tail and tail->value < v) {
                InsertAfterHelper(tail, new_node);
                tail = new_node;
            } else {
                new_node->next = *current;
                *current = new_node;

                ++size;
            }
        }
    }

    void SortedInsert_Convert(const Node::ValueType v) {
        auto list = static_cast<SinglyLinkedList>(*this);
        list.SortedInsert(v);
        *this = SinglyCircularLinkedList{std::move(list)};
    }


    const auto SearchPrev(const ValueType v) const {
        if (tail) {
            auto iter = tail;
            for (; iter->next != tail and iter->next->value != v; iter = iter->next);

            if (not(iter->next == tail and iter->next->value != v)) {
                return iter;
            }
        }
        return Node::PointerType{nullptr};
    }


    const auto PrevAt(std::size_t index) const {
        assert(index < size);
        auto iter = tail;
        for (; index--; iter = iter->next);
        return iter;
    }


    const auto CopyToArray() const {
        std::vector<Node::ValueType> array;

        OrderlessTraversal([&array](const auto node) {
            array.push_back(node->value);
        });

        return array;
    }


    /**
     * @reference   Deletion from a Circular Linked List
     *              https://www.geeksforgeeks.org/deletion-circular-linked-list/
     */
    void Delete(const Node::ValueType v) {
        const auto prev_del = SearchPrev(v);
        DeleteAfter(prev_del);
    }

    void DeleteAfter(const Node::PointerType prev_del) {
        assert(prev_del);

        if (size == 1) {
            tail = nullptr;
        } else {
            if (tail == prev_del->next) {
                tail = prev_del;
            }
            prev_del->next = prev_del->next->next;
        }

        --size;
    }


    auto PopHead() {
        assert(tail);

        const auto top = tail->next->value;
        DeleteAfter(tail);
        return top;
    }


    /**
     * @reference   Deletion at different positions in a Circular Linked List
     *              https://www.geeksforgeeks.org/deletion-at-different-positions-in-a-circular-linked-list/
     */
    void DeleteAt(const std::size_t index) {
        const auto prev_del = PrevAt(index);
        DeleteAfter(prev_del);
    }


    /**
     * @reference   Reverse a circular linked list
     *              https://www.geeksforgeeks.org/reverse-circular-linked-list/
     */
    void Reverse() {
        if (size > 1) {
            auto previous = tail;
            auto current = tail->next;

            do {
                const auto next = current->next;
                current->next = previous;
                previous = current;
                current = next;
            } while (current != tail);

            const auto new_tail = tail->next;
            tail->next = previous;
            tail = new_tail;
        }
    }


    /**
     * @reference   Check if a linked list is Circular Linked List
     *              https://www.geeksforgeeks.org/check-if-a-linked-list-is-circular-linked-list/
     */
    auto isCircular() const {
        if (not tail) {
            return true;
        }

        Node::PointerType iter = nullptr;
        OrderlessTraversal([&iter](const auto current) {
            iter = current;
        });
        return iter == tail;
    }
};
