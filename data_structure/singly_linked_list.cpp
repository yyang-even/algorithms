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
 *              Search an element in a Linked List (Iterative and Recursive)
 *              https://www.geeksforgeeks.org/search-an-element-in-a-linked-list-iterative-and-recursive/
 *              Find Length of a Linked List (Iterative and Recursive)
 *              https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/
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

    void deleteNonhead(SinglyListNode::PointerType previous,
                       const std::function<bool(const SinglyListNode &)> is_same_node) {
        assert(previous);

        while (previous->next) {
            if (is_same_node(*(previous->next))) {
                previous->next = previous->next->next;
                if (not previous->next) {
                    tail = previous;
                }
                break;
            }
            previous = previous->next;
        }
    }

    void deleteHelper(const std::function<bool(const SinglyListNode &)> is_same_node) {
        if (head) {
            if (is_same_node(*head)) {
                head = head->next;
            } else {
                deleteNonhead(head, is_same_node);
            }
        }
    }

    const SinglyListNode::PointerType searchRecursiveHelper(const SinglyListNode::PointerType node,
            const SinglyListNode::ValueType key) const {
        return (not node or node->value == key) ? node : searchRecursiveHelper(node->next, key);
    }

    std::size_t countSizeRecursiveHelper(const SinglyListNode::PointerType node) const {
        return node ? countSizeRecursiveHelper(node->next) + 1 : 0;
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

    void InsertAfter(SinglyListNode &node, const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (not node.next) {
            tail = new_node;
        } else {
            new_node->next = node.next;
        }
        node.next = new_node;
    }

    auto SearchIterative(const SinglyListNode::ValueType key) const {
        auto iter = head;
        while (iter and iter->value != key) {
            iter = iter->next;
        }
        return iter;
    }

    auto SearchRecursive(const SinglyListNode::ValueType key) const {
        return searchRecursiveHelper(head, key);
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
        deleteHelper([key](const SinglyListNode & node) {
            return node.value == key;
        });
    }

    void Delete(const SinglyListNode &target_node) {
        deleteHelper([&target_node](const SinglyListNode & node) {
            return &node == &target_node;
        });
    }

    /** Delete a given node in Linked List under given constraints
     *
     * @reference   https://www.geeksforgeeks.org/delete-a-given-node-in-linked-list-under-given-constraints/
     *
     * Given a Singly Linked List, write a function to delete a given node.
     * Your function must follow following constraints:
     * 1) It must accept pointer to the start node as first parameter and
     * node to be deleted as second parameter i.e., pointer to head node is not global.
     * 2) It should not return pointer to the head node.
     * 3) It should not accept pointer to pointer to head node.
     *
     * You may assume that the Linked List never becomes empty.
     */
    void DeleteNodeConstrained(const SinglyListNode &target_node) {
        if (head) {
            if (head.get() == &target_node) {
                assert(head->next);

                *head = *(head->next);
            } else {
                deleteNonhead(head, [&target_node](const SinglyListNode & node) {
                    return &node == &target_node;
                });
            }
        }
    }

    auto CountSizeIterative() const {
        std::size_t size = 0;
        auto iter = head;
        while (iter) {
            ++size;
            iter = iter->next;
        }

        return size;
    }

    auto CountSizeRecursive() const {
        return countSizeRecursiveHelper(head);
    }
};


auto testLinkedListInsert(const std::vector<int> &array) {
    SinglyLinkedList list{array};
    list.InsertFront(-1);
    list.PushBack(10);
    list.SearchIterative(255);  //non-exist
    list.SearchRecursive(255);  //non-exist
    const auto node = list.SearchIterative(5);
    list.InsertAfter(*node, 23);
    list.InsertFront(-2);
    list.PushBack(12);
    list.Delete(255);   //non-exist
    list.Delete(0);
    list.Delete(-2);    //head
    list.Delete(12);    //tail
    list.InsertFront(-3);
    list.PushBack(13);
    list.Delete(*node);
    list.Delete(*list.SearchRecursive(-3)); //head
    list.Delete(*list.SearchIterative(13)); //tail
    list.InsertFront(-4);
    list.PushBack(14);
    list.Delete(*list.SearchRecursive(-4)); //head
    list.Delete(*list.SearchIterative(14)); //tail
    list.InsertFront(-5);
    list.PushBack(15);

    return list.CopyToArray();
}


auto testCountSizeIterative(const std::vector<int> &array) {
    SinglyLinkedList list{array};
    return list.CountSizeIterative();
}

auto testCountSizeRecursive(const std::vector<int> &array) {
    SinglyLinkedList list{array};
    return list.CountSizeRecursive();
}


const std::vector<int> EMPTY_ARRAY {};
const std::vector<int> SINGLE_ARRAY {
    1
};
const std::vector<int> EVEN_ARRAY {
    1, 3
};
const std::vector<int> ODD_ARRAY {
    1, 2, 3
};
const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_ARRAY {
    -5, -1, 1, 8, 6, 2, 3, 7, 4, 23, 9, 10, 15
};
const auto EXPECTED_SIZE = SAMPLE_ARRAY.size();


SIMPLE_TEST(testLinkedListInsert, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


SIMPLE_TEST(testCountSizeIterative, TestEmpty, 0, EMPTY_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestSingle, 1, SINGLE_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestEven, 2, EVEN_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestOdd, 3, ODD_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestSample, EXPECTED_SIZE, SAMPLE_ARRAY);


SIMPLE_TEST(testCountSizeRecursive, TestEmpty, 0, EMPTY_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestSingle, 1, SINGLE_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestEven, 2, EVEN_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestOdd, 3, ODD_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestSample, EXPECTED_SIZE, SAMPLE_ARRAY);
