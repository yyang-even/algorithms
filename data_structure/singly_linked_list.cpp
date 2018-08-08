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
    std::size_t size = 0;

    void deleteNonhead(SinglyListNode::PointerType previous,
                       const std::function<bool(const SinglyListNode &)> is_same_node) {
        assert(previous);

        while (previous->next) {
            if (is_same_node(*(previous->next))) {
                previous->next = previous->next->next;
                if (not previous->next) {
                    tail = previous;
                }
                --size;
                break;
            }
            previous = previous->next;
        }
    }

    void deleteHelper(const std::function<bool(const SinglyListNode &)> is_same_node) {
        if (head) {
            if (is_same_node(*head)) {
                head = head->next;
                --size;
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

    void reverseRecursiveHelper(const SinglyListNode::PointerType current,
                                const SinglyListNode::PointerType previous) {
        if (not current->next) {
            head = current;
            current->next = previous;
            return;
        }

        const auto next = current->next;
        current->next = previous;
        reverseRecursiveHelper(next, current);
    }

    SinglyListNode::ValueType getNRecursiveHelper(const SinglyListNode::PointerType node,
            const std::size_t index) const {
        return index == 0 ? node->value : getNRecursiveHelper(node->next, index - 1);
    }

    void getReverseNRecursiveHelper(const SinglyListNode::PointerType node, const std::size_t index,
                                    std::size_t &i, SinglyListNode::ValueType &output) const {
        if (node) {
            getReverseNRecursiveHelper(node->next, index, i, output);

            if (i++ == index) {
                output = node->value;
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

    auto Empty() const {
        return not head;
    }

    auto Size() const {
        return size;
    }

    void PushBack(const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (tail) {
            tail->next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
        ++size;
    }

    void InsertFront(const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (head) {
            new_node->next = head;
            head = new_node;
        } else {
            head = tail = new_node;
        }
        ++size;
    }

    void InsertAfter(SinglyListNode &node, const SinglyListNode::ValueType v) {
        const auto new_node = std::make_shared<SinglyListNode>(v);
        if (not node.next) {
            tail = new_node;
        } else {
            new_node->next = node.next;
        }
        node.next = new_node;
        ++size;
    }

    /** Insert a node at a specific position in a linked list
     *
     * @reference   https://www.geeksforgeeks.org/insert-a-node-at-a-specific-position-in-a-linked-list/
     *
     * Given a singly linked list, a position and an element, the task is to write
     * a program to insert that element in a linked list at a given position.
     */
    void InsertAtSimple(std::size_t position, const SinglyListNode::ValueType v) {
        assert(position and position <= size);

        const auto new_node = std::make_shared<SinglyListNode>(v);
        if(position == 1) {
            new_node->next = head;
            head = new_node;
        } else {
            auto current = head;
            while(++position < size) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
            if(not new_node->next) {
                tail = new_node;
            }
        }
        ++size;
    }

    void InsertAtClever(int position, const SinglyListNode::ValueType v) {
        assert(position and position <= size);

        SinglyListNode::PointerType *current = &head;
        const auto new_node = std::make_shared<SinglyListNode>(v);
        while(position--) {
            if (not position) {
                new_node->next = *current;
                *current = new_node;
            } else {
                current = &(*current)->next;
            }
        }
            if(not new_node->next) {
                tail = new_node;
            }
        ++size;
    }


    /** Given a linked list which is sorted, how will you insert in sorted way
     *
     * @reference   https://www.geeksforgeeks.org/given-a-linked-list-which-is-sorted-how-will-you-insert-in-sorted-way/
     *
     * Given a sorted linked list and a value to insert, write a function to insert the value in sorted way.
     */
    void SortedInsert(const SinglyListNode::ValueType v) {
        SinglyListNode::PointerType *current = &head;
        const auto new_node = std::make_shared<SinglyListNode>(v);

        while(*current and (*current)->value < v) {
                current = &(*current)->next;
        }

        new_node->next = *current;
        *current = new_node;

            if(not new_node->next) {
                tail = new_node;
            }
        ++size;
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

    /** Given only a pointer/reference to a node to be deleted in a singly linked list, how do you delete it?
     *
     * @reference   https://www.geeksforgeeks.org/given-only-a-pointer-to-a-node-to-be-deleted-in-a-singly-linked-list-how-do-you-delete-it/
     *
     * Given a pointer to a node to be deleted, delete the node.
     * Note that we don’t have pointer to head node.
     */
    static void DeleteNodeWithoutHead(SinglyListNode &to_be_deleted, std::size_t &size) {
        assert(to_be_deleted.next);

        to_be_deleted = *(to_be_deleted.next);
        --size;
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
                DeleteNodeWithoutHead(*head, size);
            } else {
                deleteNonhead(head, [&target_node](const SinglyListNode & node) {
                    return &node == &target_node;
                });
            }
        }
    }


    /** Write a function to delete a Linked List
     *
     * @reference   https://www.geeksforgeeks.org/write-a-function-to-delete-a-linked-list/
     *
     * Algorithm For C/C++: Iterate through the linked list and delete all the nodes one by one.
     * Main point here is not to access next of the current pointer if current pointer is deleted.
     */
    void DeleteAllOneByOne() {
        head = nullptr;
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


    /** Iteratively Reverse a linked list using only 2 pointers (An Interesting Method)
     *
     * @reference   https://www.geeksforgeeks.org/iteratively-reverse-a-linked-list-using-only-2-pointers/
     *
     * Given pointer to the head node of a linked list, the task is to reverse the linked list.
     */
    /** Reverse a linked list
     *
     * @reference   https://www.geeksforgeeks.org/reverse-a-linked-list/
     *
     * Given pointer to the head node of a linked list, the task is to reverse
     * the linked list. We need to reverse the list by changing links between nodes.
     *
     * @complexity  O(n)
     */
    void ReverseIterative() {
        auto current = head;
        SinglyListNode::PointerType previous = nullptr;

        while (current) {
            const auto next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }

    void ReverseRecursive() {
        if (not head) {
            return;
        }

        reverseRecursiveHelper(head, nullptr);
    }

    /** Write a function to get Nth node in a Linked List
     *
     * @reference   https://www.geeksforgeeks.org/write-a-function-to-get-nth-node-in-a-linked-list/
     *
     * Write a GetNth() function that takes a linked list and an integer index
     * and returns the data value stored in the node at that index position.
     */
    auto GetNIterative(std::size_t index) const {
        assert(index < size);

        auto target = head;
        while (index--) {
            target = target->next;
        }

        return target->value;
    }

    auto GetNRecursive(const std::size_t index) const {
        assert(index < size);
        return getNRecursiveHelper(head, index);
    }

    /** Program for n’th node from the end of a Linked List
     *
     * @reference   https://www.geeksforgeeks.org/nth-node-from-the-end-of-a-linked-list/
     *
     * Given a Linked List and a number n, write a function that returns the value
     * at the n’th node from end of the Linked List.
     */
    auto GetReverseNIterative(const std::size_t index) const {
        return GetNIterative(size - index - 1);
    }

    auto GetReverseNRecursive(const std::size_t index) const {
        assert(index < size);

        std::size_t i = 0;
        SinglyListNode::ValueType output{};
        getReverseNRecursiveHelper(head, index, i, output);
        return output;
    }

    auto GetReverseNTwoPointers(std::size_t index) const {
        assert(index < size);

        auto target = head;
        auto helper = head;

        while (index--) {
            helper = helper->next;
        }

        while (helper->next) {
            helper = helper->next;
            target = target->next;
        }

        return target->value;
    }


    /** Find the middle of a given linked list in C and Java
     *
     * @reference   https://www.geeksforgeeks.org/write-a-c-function-to-print-the-middle-of-the-linked-list/
     *
     * Given a singly linked list, find middle of the linked list. For example,
     * if given linked list is 1->2->3->4->5 then output should be 3.
     * If there are even nodes, then there would be two middle nodes, we need
     * to print second middle element. For example, if given linked list is
     * 1->2->3->4->5->6 then output should be 4.
     */
    auto GetMidSize() const {
        return GetNIterative(size / 2);
    }

    auto GetMidTwoPointers() const {
        assert(head);

        auto fast_ptr = head;
        auto slow_ptr = head;

        while (fast_ptr and fast_ptr->next) {
            fast_ptr = fast_ptr->next->next;
            slow_ptr = slow_ptr->next;
        }

        return slow_ptr->value;
    }

    auto GetMidOdd() const {
        assert(head);

        auto count = 0;
        auto mid = head;
        auto current = head;

        while (current) {
            if (count++ & 1) {
                mid = mid->next;
            }

            current = current->next;
        }

        return mid->value;
    }
};


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
    -7, 111, -6, 11, -5, 44, -1, 33, 1, 8, 6, 2, 3, 7, 4, 23, 9, 10, 15, 77, 16, 777, 17
};
const auto EXPECTED_SIZE = SAMPLE_ARRAY.size();
const std::vector<int> EXPECTED_REVERSE_ARRAY {9, 5, 4, 7, 3, 2, 6, 8, 0, 1};


auto testLinkedListInsert(const std::vector<int> &array) {
    SinglyLinkedList list {array};
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
    list.InsertAtSimple(3, 33);
    list.InsertAtSimple(1, 11);   //head
    list.InsertAtSimple(list.size(), 77);   //tail
    list.InsertFront(-6);
    list.PushBack(16);
    list.InsertAtClever(4, 44);
    list.InsertAtClever(1, 111);   //head
    list.InsertAtClever(list.size(), 777);   //tail
    list.InsertFront(-7);
    list.PushBack(17);

    return list.CopyToArray();
}

SIMPLE_TEST(testLinkedListInsert, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


auto testCountSizeIterative(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSizeIterative();
}

SIMPLE_TEST(testCountSizeIterative, TestEmpty, 0, EMPTY_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestSingle, 1, SINGLE_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestEven, 2, EVEN_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestOdd, 3, ODD_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestSample, EXPECTED_SIZE, SAMPLE_ARRAY);


auto testCountSizeRecursive(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSizeRecursive();
}

SIMPLE_TEST(testCountSizeRecursive, TestEmpty, 0, EMPTY_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestSingle, 1, SINGLE_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestEven, 2, EVEN_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestOdd, 3, ODD_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestSample, EXPECTED_SIZE, SAMPLE_ARRAY);


auto testReverseIterative(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.ReverseIterative();
    return list.CopyToArray();
}

auto testReverseRecursive(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.ReverseRecursive();
    return list.CopyToArray();
}

SIMPLE_TEST(testReverseIterative, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverseIterative, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);

SIMPLE_TEST(testReverseRecursive, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverseRecursive, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


auto testGetNIterative(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetNIterative(index);
}

auto testGetNRecursive(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetNRecursive(index);
}

SIMPLE_TEST(testGetNIterative, TestSampleHead, SAMPLE_ARRAY[0], SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetNIterative, TestSampleTail, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetNIterative, TestSample, SAMPLE_ARRAY[5], SAMPLE_ARRAY, 5);

SIMPLE_TEST(testGetNRecursive, TestSampleHead, SAMPLE_ARRAY[0], SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetNRecursive, TestSampleTail, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetNRecursive, TestSample, SAMPLE_ARRAY[5], SAMPLE_ARRAY, 5);


auto testGetReverseNIterative(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetReverseNIterative(index);
}

auto testGetReverseNRecursive(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetReverseNRecursive(index);
}

auto testGetReverseNTwoPointers(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetReverseNTwoPointers(index);
}

SIMPLE_TEST(testGetReverseNIterative, TestSampleHead, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetReverseNIterative, TestSampleTail, SAMPLE_ARRAY[0], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetReverseNIterative, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 5 - 1],
            SAMPLE_ARRAY, 5);

SIMPLE_TEST(testGetReverseNRecursive, TestSampleHead, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetReverseNRecursive, TestSampleTail, SAMPLE_ARRAY[0], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetReverseNRecursive, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 5 - 1],
            SAMPLE_ARRAY, 5);

SIMPLE_TEST(testGetReverseNTwoPointers, TestSampleHead, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetReverseNTwoPointers, TestSampleTail, SAMPLE_ARRAY[0], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetReverseNTwoPointers, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 5 - 1],
            SAMPLE_ARRAY, 5);


auto testGetMidSize(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMidSize();
}

auto testGetMidTwoPointers(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMidTwoPointers();
}

auto testGetMidOdd(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMidOdd();
}

SIMPLE_TEST(testGetMidSize, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2], SINGLE_ARRAY);
SIMPLE_TEST(testGetMidSize, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMidSize, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMidSize, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2], SAMPLE_ARRAY);

SIMPLE_TEST(testGetMidTwoPointers, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2], SINGLE_ARRAY);
SIMPLE_TEST(testGetMidTwoPointers, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMidTwoPointers, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMidTwoPointers, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2], SAMPLE_ARRAY);

SIMPLE_TEST(testGetMidOdd, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2], SINGLE_ARRAY);
SIMPLE_TEST(testGetMidOdd, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMidOdd, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMidOdd, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2], SAMPLE_ARRAY);


auto testSortedInsert(std::vector<int> array) {
    std::sort(array.begin(), array.end());
    SinglyLinkedList list {array};

    list.SortedInsert(-1);
    list.SortedInsert(15);
    list.SortedInsert(11);
    list.InsertFront(-8);
    list.PushBack(18);

    return list.CopyToArray();
}

const std::vector<int> EXPECTED_SORTED_INSERT_ARRAY {-8, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 15, 18};

SIMPLE_TEST(testSortedInsert, TestSample, EXPECTED_SORTED_INSERT_ARRAY, SAMPLE_ARRAY);
