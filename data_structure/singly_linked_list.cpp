#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

/** Singly Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.2.
 *
 *              Linked List | Set 1 (Introduction)
 *              https://www.geeksforgeeks.org/linked-list-set-1-introduction/
 */
class SinglyLinkedList {
    struct SinglyListNode {
        using ValueType = int;
        using PointerType = std::shared_ptr<SinglyListNode>;

        ValueType value;
        PointerType next;

        SinglyListNode() = default;
        SinglyListNode(const ValueType v): value(v) {}
    };

    SinglyListNode::PointerType head;
    SinglyListNode::PointerType tail;

public:
    SinglyLinkedList() = default;
    SinglyLinkedList(const std::vector<SinglyListNode::ValueType> &array) {
        for (const auto elem : array) {
            PushBack(elem);
        }
    }

    bool Empty() const {
        return not head;
    }

    void PushBack(const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (tail) {
            tail->next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
    }

    void InsertFront(const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (head) {
            new_node->next = head;
            head = new_node;
        } else {
            head = tail = new_node;
        }
    }

    auto Search(const SinglyListNode::ValueType k) const {
        auto iter = head;
        while (iter and iter->value != k) {
            iter = iter->next;
        }
        return iter;
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
};


auto testLinkedListInsert(const std::vector<int> &array) {
    SinglyLinkedList list{array};
    list.InsertFront(-1);
    list.PushBack(10);

    return list.CopyToArray();
}


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_ARRAY {
    -1, 1, 0, 8, 6, 2, 3, 7, 4, 5, 9, 10
};

SIMPLE_TEST(testLinkedListInsert, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
