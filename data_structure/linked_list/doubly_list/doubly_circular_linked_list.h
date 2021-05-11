#pragma once

#include "common_header.h"

#include "doubly_linked_list.h"


/** Doubly Circular Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.2.
 * @reference   Doubly Circular Linked List | Set 1 (Introduction and Insertion)
 *              https://www.geeksforgeeks.org/doubly-circular-linked-list-set-1-introduction-and-insertion/
 *
 * Circular Doubly Linked List has properties of both doubly linked list and circular
 * linked list in which two consecutive elements are linked or connected by previous and
 * next pointer and the last node points to first node by next pointer and also the first
 * node points to last node by previous pointer.
 */
class DoublyCircularLinkedList {
public:
    using Node = DoublyLinkedList::Node;
    using ValueType = Node::ValueType;

protected:
    Node::PointerType head = nullptr;
    std::size_t size = 0;

public:
    /**
     * @reference   Convert an Array to a Circular Doubly Linked List
     *              https://www.geeksforgeeks.org/convert-array-to-circular-doubly-linked-list/
     */
    DoublyCircularLinkedList() = default;
    explicit DoublyCircularLinkedList(const std::vector<ValueType> &array) {
        for (const auto elem : array) {
            PushBack(elem);
        }
    }


    ~DoublyCircularLinkedList() {
        if (head) {
            head->Prev()->Next() = nullptr;
            for (; head; head = head->Next()) {
                head->Prev() = nullptr;
            }
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

        if (not head) {
            new_node->Next() = new_node->Prev() = new_node;

            ++size;
        } else {
            InsertBefore_Helper(head, new_node);
        }
        head = new_node;
    }


    void InsertBefore_Helper(const Node::PointerType next,
                             const Node::PointerType new_node) {
        assert(next);
        assert(new_node);

        new_node->Next() = next;
        new_node->Prev() = next->Prev();
        new_node->Prev()->Next() = next->Prev() = new_node;

        ++size;
    }

    void InsertBefore(const Node::PointerType next, const ValueType v) {
        assert(next);

        const auto new_node = std::make_shared<Node>(v);
        InsertBefore_Helper(next, new_node);
        if (next == head) {
            head = new_node;
        }
    }

    /**
     * @reference   Insertion at Specific Position in a Circular Doubly Linked List
     *              https://www.geeksforgeeks.org/insertion-at-specific-position-in-a-circular-doubly-linked-list/
     */
    void InsertAfter(const Node::PointerType prev, const ValueType v) {
        assert(prev);

        const auto new_node = std::make_shared<Node>(v);
        new_node->Prev() = prev;
        new_node->Next() = prev->Next();
        new_node->Next()->Prev() = prev->Next() = new_node;

        ++size;
    }


    void PushBack(const ValueType v) {
        const auto new_node = std::make_shared<Node>(v);

        if (not head) {
            new_node->Next() = new_node->Prev() = new_node;
            head = new_node;

            ++size;
        } else {
            InsertBefore_Helper(head, new_node);
        }
    }


    /**
     * @reference   Search an Element in Doubly Circular Linked List
     *              https://www.geeksforgeeks.org/search-an-element-in-doubly-circular-linked-list/
     */
    const auto Search(const ValueType v) const {
        if (head) {
            auto iter = head->Next();
            for (; iter != head and iter->value != v; iter = iter->Next());

            if (not(iter == head and iter->value != v)) {
                return iter;
            }
        }
        return Node::PointerType{nullptr};
    }


    const auto At(std::size_t index) const {
        assert(index < size);
        auto iter = head;
        for (; index--; iter = iter->Next());
        return iter;
    }


    const auto CopyToArray() const {
        std::vector<Node::ValueType> array;

        if (head) {
            auto iter = head;
            for (; iter->Next() != head; iter = iter->Next()) {
                array.push_back(iter->value);
            }
            array.push_back(iter->value);
        }

        return array;
    }


    const auto CopyToArray_Reverse() const {
        std::vector<Node::ValueType> array;

        if (head) {
            const auto tail = head->Prev();
            auto iter = tail;
            for (; iter->Prev() != tail; iter = iter->Prev()) {
                array.push_back(iter->value);
            }
            array.push_back(iter->value);
        }

        return array;
    }


    /**
     * @reference   Doubly Circular Linked List | Set 2 (Deletion)
     *              https://www.geeksforgeeks.org/doubly-circular-linked-list-set-2-deletion/
     */
    void Delete(const Node::PointerType del) {
        assert(del);

        if (size == 1) {
            head = nullptr;
        } else {
            del->Next()->Prev() = del->Prev();
            del->Prev()->Next() = del->Next();
            if (head == del) {
                head = del->Next();
            }
        }

        --size;
    }


    void DeleteAt(const std::size_t index) {
        const auto del = At(index);
        Delete(del);
    }


    /**
     * @reference   Reverse a doubly circular linked list
     *              https://www.geeksforgeeks.org/reverse-a-doubly-circular-linked-list/
     */
    void Reverse() {
        if (size > 1) {
            for (auto iter = head->Next(); iter != head; iter = iter->Prev()) {
                std::swap(iter->Next(), iter->Prev());
            }
            std::swap(head->Next(), head->Prev());
            head = head->Next();
        }
    }
};
