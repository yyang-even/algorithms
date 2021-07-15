#include "common_header.h"

#include "singly_list/singly_linked_list.h"
#include "singly_list/singly_circular_linked_list.h"
#include "doubly_list/doubly_linked_list.h"
#include "doubly_list/doubly_circular_linked_list.h"


namespace {

const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


SinglyLinkedList::Node::PointerType
DetectLoop_Hash(const SinglyLinkedList::Node::PointerType head) {
    std::unordered_set<SinglyLinkedList::Node *> visited_nodes;

    for (auto current = head; current; current = current->next) {
        if (not visited_nodes.insert(current.get()).second) {
            return current;
        }
    }

    return nullptr;
}

inline auto testDetectLoop_Hash_SinglyList() {
    SinglyLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_Hash(list.GetHead()) == nullptr;
}

inline auto testDetectLoop_Hash_SinglyCircular() {
    SinglyCircularLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_Hash(list.GetHead()) == list.GetHead();
}

inline auto testDetectLoop_Hash_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    return DetectLoop_Hash(list.GetHead()) == list.At(index);
}


/**
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 4.
 * @reference   Detect loop in a linked list
 *              https://www.geeksforgeeks.org/detect-loop-in-a-linked-list/
 * @reference   How does Floyd’s slow and fast pointers approach work?
 *              https://www.geeksforgeeks.org/how-does-floyds-slow-and-fast-pointers-approach-work/
 * @reference   Finding a Loop in a Singly Linked List
 *              https://blog.ostermiller.org/find-loop-singly-linked-list
 * @reference   Linked List Cycle
 *              https://leetcode.com/problems/linked-list-cycle/
 *
 * This solution is "Floyd's Cycle-Finding Algorithm" as published in "Non-deterministic
 * Algorithms" by Robert W. Floyd in 1967. It is also called "The Tortoise and the Hare
 * Algorithm".
 *
 * @reference   Find first node of loop in a linked list
 *              https://www.geeksforgeeks.org/find-first-node-of-loop-in-a-linked-list/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 2.6.
 * @reference   Linked List Cycle II
 *              https://leetcode.com/problems/linked-list-cycle-ii/
 *
 * Write a function findFirstLoopNode() that checks whether a given Linked List contains
 * loop. If loop is present then it returns point to first node of loop. Else it returns
 * NULL.
 *
 * @reference   Detect and Remove Loop in a Linked List
 *              https://www.geeksforgeeks.org/detect-and-remove-loop-in-a-linked-list/
 *
 * Write a function detectAndRemoveLoop() that checks whether a given Linked List
 * contains loop and if loop is present then removes the loop and returns true. If the
 * list doesn't contain loop then it returns false.
 *
 * @reference   Find length of loop in linked list
 *              https://www.geeksforgeeks.org/find-length-of-loop-in-linked-list/
 *
 * Write a function detectAndCountLoop() that checks whether a given Linked List contains
 * loop and if loop is present then returns count of nodes in loop.
 */
auto DetectLoop_FloydsCycleFinding(const SinglyLinkedList::Node::PointerType head,
                                   std::size_t *loop_length = nullptr,
                                   SinglyLinkedList::Node::PointerType *first_node = nullptr,
                                   SinglyLinkedList::Node::PointerType *last_node = nullptr) {
    auto slow_ptr = head;
    auto fast_ptr = head;

    while (fast_ptr and fast_ptr->next) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;

        if (slow_ptr == fast_ptr) {
            if (loop_length) {
                *loop_length = 0;
                do {
                    ++(*loop_length);
                    slow_ptr = slow_ptr->next;
                } while (slow_ptr != fast_ptr);
            }
            if (first_node or last_node) {
                SinglyLinkedList::Node::PointerType prev = nullptr;
                for (slow_ptr = head;
                     slow_ptr != fast_ptr;
                     slow_ptr = slow_ptr->next, fast_ptr = fast_ptr->next) {
                    prev = slow_ptr;
                }
                if (first_node) {
                    *first_node = slow_ptr;
                }
                if (last_node) {
                    if (not prev) {
                        for (prev = head; prev->next != head; prev = prev->next);
                    }
                    *last_node = prev;
                }
            }
            return true;
        }
    }

    return false;
}

inline auto testDetectLoop_FloydsCycleFinding_SinglyList() {
    SinglyLinkedList list{SAMPLE_ARRAY};
    std::size_t loop_length = 0;
    SinglyLinkedList::Node::PointerType first_node = nullptr;
    SinglyLinkedList::Node::PointerType last_node = nullptr;
    return not(DetectLoop_FloydsCycleFinding(
                   list.GetHead(), &loop_length, &first_node, &last_node) or
               loop_length or first_node or last_node);
}

inline auto testDetectLoop_FloydsCycleFinding_SinglyCircular() {
    SinglyCircularLinkedList list{SAMPLE_ARRAY};
    std::size_t loop_length = 0;
    SinglyLinkedList::Node::PointerType first_node = nullptr;
    SinglyLinkedList::Node::PointerType last_node = nullptr;
    return DetectLoop_FloydsCycleFinding(
               list.GetHead(), &loop_length, &first_node, &last_node) and
           loop_length == SAMPLE_ARRAY.size() and
           first_node == list.GetHead() and
           last_node->next == first_node;
}

inline auto testDetectLoop_FloydsCycleFinding_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    std::size_t loop_length = 0;
    SinglyLinkedList::Node::PointerType first_node = nullptr;
    SinglyLinkedList::Node::PointerType last_node = nullptr;
    return DetectLoop_FloydsCycleFinding(
               list.GetHead(), &loop_length, &first_node, &last_node) and
           loop_length == (SAMPLE_ARRAY.size() - index) and
           first_node == list.At(index) and
           last_node->next == first_node;
}


SinglyLinkedList::Node::PointerType
DetectLoop_NextFlag(const SinglyLinkedList::Node::PointerType head) {
    const auto temp_node = std::make_shared<SinglyLinkedList::Node>();

    for (auto current = head; current;) {
        if (current->next == temp_node) {
            return current;
        } else {
            const auto next = current->next;
            current->next = temp_node;
            current = next;
        }
    }

    return nullptr;
}

inline auto testDetectLoop_NextFlag_SinglyList() {
    SinglyLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_NextFlag(list.GetHead()) == nullptr;
}

inline auto testDetectLoop_NextFlag_SinglyCircular() {
    SinglyCircularLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_NextFlag(list.GetHead()) == list.GetHead();
}

inline auto testDetectLoop_NextFlag_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    return DetectLoop_NextFlag(list.GetHead()) == list.At(index);
}


auto DetectLoop_DoublyList(const DoublyLinkedList::Node::PointerType head) {
    DoublyLinkedList::Node::PointerType prev = nullptr;

    for (auto current = head; current; current = current->Next()) {
        if (prev != current->Prev()) {
            return true;
        }
        prev = current;
    }

    return false;
}

inline auto testDetectLoop_DoublyList() {
    DoublyLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_DoublyList(list.GetHead());
}

inline auto testDetectLoop_DoublyCircular() {
    DoublyCircularLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_DoublyList(list.GetHead());
}


auto DetectLoop_Reverse(const SinglyLinkedList::Node::PointerType head) {
    auto current = head;
    SinglyLinkedList::Node::PointerType prev = nullptr;

    while (current) {
        const auto next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev == head;
}

inline auto testDetectLoop_Reverse_SinglyList() {
    SinglyLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_Reverse(list.GetHead());
}

inline auto testDetectLoop_Reverse_SinglyCircular() {
    SinglyCircularLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_Reverse(list.GetHead());
}

inline auto testDetectLoop_Reverse_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    return DetectLoop_Reverse(list.GetHead());
}


/** Find duplicate in an array in O(n) and by using O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/duplicates-array-using-o1-extra-space-set-3/
 *
 * Given an array arr[] containing n + 1 integers where each integer is between 1 and n
 * (inclusive). There is only one duplicate element, find the duplicate element in O(n)
 * time complexity and O(1) space.
 *
 * @reference   Find duplicates in constant array with elements 0 to N-1 in O(1) space
 *              https://www.geeksforgeeks.org/find-duplicates-constant-array-elements-0-n-1-o1-space/
 *
 * Given a constant array of n elements which contains elements from 0 to n-1, with any
 * of these numbers appearing any number of times. Find any one of these repeating
 * numbers in O(n) and using only constant memory space.
 */
auto FindTheDuplicate_FloydsCycleFinding(const std::vector<unsigned> &values) {
    auto slow_ptr = values.front();
    auto fast_ptr = values.front();

    do {
        slow_ptr = values[slow_ptr];
        fast_ptr = values[values[fast_ptr]];
    } while (slow_ptr != fast_ptr);

    slow_ptr = values.front();
    while (slow_ptr != fast_ptr) {
        slow_ptr = values[slow_ptr];
        fast_ptr = values[fast_ptr];
    }

    return slow_ptr;
}

}//namespace


SIMPLE_BENCHMARK0(testDetectLoop_Hash_SinglyList);
SIMPLE_BENCHMARK0(testDetectLoop_Hash_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_Hash_SinglyMakeLoop, Sample1, 3);

SIMPLE_TEST0(testDetectLoop_Hash_SinglyList, TestSample, true);
SIMPLE_TEST0(testDetectLoop_Hash_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_Hash_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_Hash_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_Hash_SinglyMakeLoop, TestSample3, true,
            SAMPLE_ARRAY.size() - 1);


SIMPLE_BENCHMARK0(testDetectLoop_FloydsCycleFinding_SinglyList);
SIMPLE_BENCHMARK0(testDetectLoop_FloydsCycleFinding_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, Sample1, 3);

SIMPLE_TEST0(testDetectLoop_FloydsCycleFinding_SinglyList, TestSample, true);
SIMPLE_TEST0(testDetectLoop_FloydsCycleFinding_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, TestSample3, true,
            SAMPLE_ARRAY.size() - 1);


SIMPLE_BENCHMARK0(testDetectLoop_NextFlag_SinglyList);
SIMPLE_BENCHMARK0(testDetectLoop_NextFlag_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_NextFlag_SinglyMakeLoop, Sample1, 3);

SIMPLE_TEST0(testDetectLoop_NextFlag_SinglyList, TestSample, true);
SIMPLE_TEST0(testDetectLoop_NextFlag_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_NextFlag_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_NextFlag_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_NextFlag_SinglyMakeLoop, TestSample3, true,
            SAMPLE_ARRAY.size() - 1);


SIMPLE_BENCHMARK0(testDetectLoop_DoublyList);
SIMPLE_BENCHMARK0(testDetectLoop_DoublyCircular);

SIMPLE_TEST0(testDetectLoop_DoublyList, TestSample, false);
SIMPLE_TEST0(testDetectLoop_DoublyCircular, TestSample, true);


SIMPLE_BENCHMARK0(testDetectLoop_Reverse_SinglyList);
SIMPLE_BENCHMARK0(testDetectLoop_Reverse_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_Reverse_SinglyMakeLoop, Sample1, 3);

SIMPLE_TEST0(testDetectLoop_Reverse_SinglyList, TestSample, false);
SIMPLE_TEST0(testDetectLoop_Reverse_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_Reverse_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_Reverse_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_Reverse_SinglyMakeLoop, TestSample3, true,
            SAMPLE_ARRAY.size() - 1);


const std::vector<unsigned> SAMPLE1 = {1, 4, 3, 4, 2};
const std::vector<unsigned> SAMPLE2 = {1, 3, 2, 1};


THE_BENCHMARK(FindTheDuplicate_FloydsCycleFinding, SAMPLE1);

SIMPLE_TEST(FindTheDuplicate_FloydsCycleFinding, TestSample1, 4, SAMPLE1);
SIMPLE_TEST(FindTheDuplicate_FloydsCycleFinding, TestSample2, 1, SAMPLE2);
