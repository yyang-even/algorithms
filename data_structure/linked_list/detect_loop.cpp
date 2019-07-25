#include "common_header.h"

#include "singly_list/singly_linked_list.h"
#include "singly_list/singly_circular_linked_list.h"
#include "doubly_list/doubly_linked_list.h"
#include "doubly_list/doubly_circular_linked_list.h"


namespace {

const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


/** Detect loop in a linked list
 *
 * @reference   https://www.geeksforgeeks.org/detect-loop-in-a-linked-list/
 */
SinglyLinkedList::Node::PointerType
DetectLoop_Hash(const SinglyLinkedList::Node::PointerType head) {
    std::unordered_set<SinglyLinkedList::Node *> visited_nodes;

    for (auto current = head; current; current = current->next) {
        if (visited_nodes.find(current.get()) != visited_nodes.cend()) {
            return current;
        } else {
            visited_nodes.insert(current.get());
        }
    }

    return nullptr;
}

auto testDetectLoop_Hash_SinglyList() {
    SinglyLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_Hash(list.GetHead()) == nullptr;
}

auto testDetectLoop_Hash_SinglyCircular() {
    SinglyCircularLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_Hash(list.GetHead()) == list.GetHead();
}

auto testDetectLoop_Hash_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    return DetectLoop_Hash(list.GetHead()) == list.At(index);
}


/**
 * @reference   Detect loop in a linked list
 *              https://www.geeksforgeeks.org/detect-loop-in-a-linked-list/
 * @reference   How does Floyd’s slow and fast pointers approach work?
 *              https://www.geeksforgeeks.org/how-does-floyds-slow-and-fast-pointers-approach-work/
 * @reference   Finding a Loop in a Singly Linked List
 *              https://blog.ostermiller.org/find-loop-singly-linked-list
 *
 * This solution is “Floyd’s Cycle-Finding Algorithm” as published in “Non-deterministic Algorithms”
 * by Robert W. Floyd in 1967. It is also called “The Tortoise and the Hare Algorithm”.
 *
 * @reference   Find first node of loop in a linked list
 *              https://www.geeksforgeeks.org/find-first-node-of-loop-in-a-linked-list/
 *
 * Write a function findFirstLoopNode() that checks whether a given Linked List contains loop.
 * If loop is present then it returns point to first node of loop. Else it returns NULL.
 *
 * @reference   Find length of loop in linked list
 *              https://www.geeksforgeeks.org/find-length-of-loop-in-linked-list/
 *
 * Write a function detectAndCountLoop() that checks whether a given Linked List contains loop and
 * if loop is present then returns count of nodes in loop.
 */
auto DetectLoop_FloydsCycleFinding(const SinglyLinkedList::Node::PointerType head,
                                   std::size_t *loop_length = nullptr,
                                   SinglyLinkedList::Node::PointerType *first_node = nullptr) {
    auto slow_ptr = head;
    auto fast_ptr = head;

    while (slow_ptr and fast_ptr and fast_ptr->next) {
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
            if (first_node) {
                for (slow_ptr = head; slow_ptr != fast_ptr; slow_ptr = slow_ptr->next, fast_ptr = fast_ptr->next);
                *first_node = slow_ptr;
            }
            return true;
        }
    }

    return false;
}

auto testDetectLoop_FloydsCycleFinding_SinglyList() {
    SinglyLinkedList list{SAMPLE_ARRAY};
    std::size_t loop_length = 0;
    SinglyLinkedList::Node::PointerType first_node = nullptr;
    return not(DetectLoop_FloydsCycleFinding(list.GetHead(), &loop_length, &first_node) or
               loop_length or first_node);
}

auto testDetectLoop_FloydsCycleFinding_SinglyCircular() {
    SinglyCircularLinkedList list{SAMPLE_ARRAY};
    std::size_t loop_length = 0;
    SinglyLinkedList::Node::PointerType first_node = nullptr;
    return DetectLoop_FloydsCycleFinding(list.GetHead(), &loop_length, &first_node) and
           loop_length == SAMPLE_ARRAY.size() and first_node == list.GetHead();
}

auto testDetectLoop_FloydsCycleFinding_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    std::size_t loop_length = 0;
    SinglyLinkedList::Node::PointerType first_node = nullptr;
    return DetectLoop_FloydsCycleFinding(list.GetHead(), &loop_length, &first_node) and
           loop_length == (SAMPLE_ARRAY.size() - index) and first_node == list.At(index);
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

auto testDetectLoop_NextFlag_SinglyList() {
    SinglyLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_NextFlag(list.GetHead()) == nullptr;
}

auto testDetectLoop_NextFlag_SinglyCircular() {
    SinglyCircularLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_NextFlag(list.GetHead()) == list.GetHead();
}

auto testDetectLoop_NextFlag_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    return DetectLoop_NextFlag(list.GetHead()) == list.At(index);
}


/**
 * @reference   Finding a Loop in a Singly Linked List
 *              https://blog.ostermiller.org/find-loop-singly-linked-list
 */
auto DetectLoop_DoublyList(const DoublyLinkedList::Node::PointerType head) {
    auto current = head;
    DoublyLinkedList::Node::PointerType prev = nullptr;

    for (; current; current = current->Next()) {
        if (prev != current->Prev()) {
            return true;
        }
        prev = current;
    }

    return false;
}

auto testDetectLoop_DoublyList() {
    DoublyLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_DoublyList(list.GetHead());
}

auto testDetectLoop_DoublyCircular() {
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

auto testDetectLoop_Reverse_SinglyList() {
    SinglyLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_Reverse(list.GetHead());
}

auto testDetectLoop_Reverse_SinglyCircular() {
    SinglyCircularLinkedList list{SAMPLE_ARRAY};
    return DetectLoop_Reverse(list.GetHead());
}

auto testDetectLoop_Reverse_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    return DetectLoop_Reverse(list.GetHead());
}

}//namespace


SIMPLE_BENCHMARK(testDetectLoop_Hash_SinglyList);
SIMPLE_BENCHMARK(testDetectLoop_Hash_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_Hash_SinglyMakeLoop, 3);

SIMPLE_TEST0(testDetectLoop_Hash_SinglyList, TestSample, true);
SIMPLE_TEST0(testDetectLoop_Hash_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_Hash_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_Hash_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_Hash_SinglyMakeLoop, TestSample3, true, SAMPLE_ARRAY.size() - 1);


SIMPLE_BENCHMARK(testDetectLoop_FloydsCycleFinding_SinglyList);
SIMPLE_BENCHMARK(testDetectLoop_FloydsCycleFinding_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, 3);

SIMPLE_TEST0(testDetectLoop_FloydsCycleFinding_SinglyList, TestSample, true);
SIMPLE_TEST0(testDetectLoop_FloydsCycleFinding_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, TestSample3, true,
            SAMPLE_ARRAY.size() - 1);


SIMPLE_BENCHMARK(testDetectLoop_NextFlag_SinglyList);
SIMPLE_BENCHMARK(testDetectLoop_NextFlag_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_NextFlag_SinglyMakeLoop, 3);

SIMPLE_TEST0(testDetectLoop_NextFlag_SinglyList, TestSample, true);
SIMPLE_TEST0(testDetectLoop_NextFlag_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_NextFlag_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_NextFlag_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_NextFlag_SinglyMakeLoop, TestSample3, true, SAMPLE_ARRAY.size() - 1);


SIMPLE_BENCHMARK(testDetectLoop_DoublyList);
SIMPLE_BENCHMARK(testDetectLoop_DoublyCircular);

SIMPLE_TEST0(testDetectLoop_DoublyList, TestSample, false);
SIMPLE_TEST0(testDetectLoop_DoublyCircular, TestSample, true);


SIMPLE_BENCHMARK(testDetectLoop_Reverse_SinglyList);
SIMPLE_BENCHMARK(testDetectLoop_Reverse_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_Reverse_SinglyMakeLoop, 3);

SIMPLE_TEST0(testDetectLoop_Reverse_SinglyList, TestSample, false);
SIMPLE_TEST0(testDetectLoop_Reverse_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_Reverse_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_Reverse_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_Reverse_SinglyMakeLoop, TestSample3, true, SAMPLE_ARRAY.size() - 1);
