#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

/** Singly Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.2.
 *
 *              Linked List | Set 1 (Introduction)
 *              https://www.geeksforgeeks.org/linked-list-set-1-introduction/
 *              Linked List | Set 2 (Inserting a node)
 *              https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
 *              How to write C functions that modify head pointer of a Linked List?
 *              https://www.geeksforgeeks.org/how-to-write-functions-that-modify-the-head-pointer-of-a-linked-list/
 *              Linked List | Set 3 (Deleting a node)
 *              https://www.geeksforgeeks.org/linked-list-set-3-deleting-node/
 *              Delete a Linked List node at a given position
 *              https://www.geeksforgeeks.org/delete-a-linked-list-node-at-a-given-position/
 *              Linked List vs Array
 *              https://www.geeksforgeeks.org/linked-list-vs-array/
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

    void deleteHelper(const std::function<bool(const SinglyListNode&)> is_same_node) {
        if (head){
            if(is_same_node(*head))
                head = head->next;
            else {
                auto iter = head;
                while(iter->next) {
                    if(is_same_node(*(iter->next))) {
                        iter->next = iter->next->next;
                        if(not iter->next){
                            tail = iter;
                        }
                        break;
                    }
                }
            }
        }
    }

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

    void InsertAfter(const SinglyListNode &node, const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if(not node.next)
            tail = new_node;
        else
            new_node->next = node.next;
        node.next = new_node;
    }

    auto Search(const SinglyListNode::ValueType key) const {
        auto iter = head;
        while (iter and iter->value != key) {
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

    void Delete(const SinglyListNode::ValueType key) {
        deleteHelper([key](const SinglyListNode &node) {
                return node.value == key;
                });
    }

    void Delete(const SinglyListNode &target_node) {
        deleteHelper([&target_node](const SinglyListNode &node) {
                return &node == &target_node;
                });
    }
};


auto testLinkedListInsert(const std::vector<int> &array) {
    SinglyLinkedList list{array};
    list.InsertFront(-1);
    list.PushBack(10);
    const auto node = list.Search(5);
    list.InsertAfter(*node, 23);
    list.InsertFront(-2);
    list.PushBack(12);
    list.Delete(0);
    list.Delete(-2);
    list.Delete(12);
    list.InsertFront(-3);
    list.PushBack(13);
    list.Delete(node);
    list.Delete(list.Search(-3));
    list.Delete(list.Search(13));
    list.InsertFront(-4);
    list.PushBack(14);

    return list.CopyToArray();
}


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_ARRAY {
    -4, -1, 1, 8, 6, 2, 3, 7, 4, 23, 9, 10, 14
};

SIMPLE_TEST(testLinkedListInsert, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
