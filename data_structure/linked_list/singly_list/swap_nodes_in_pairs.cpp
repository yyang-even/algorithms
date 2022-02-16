#include "common_header.h"

#include "singly_linked_list.h"


namespace {

using ArrayType = std::vector<int>;

/** Swap Nodes in Pairs
 *
 * @reference   https://leetcode.com/problems/swap-nodes-in-pairs/
 *
 * Given a linked list, swap every two adjacent nodes and return its head. You must solve
 * the problem without modifying the values in the list's nodes (i.e., only nodes
 * themselves may be changed.)
 */
auto SwapPairs(const SinglyLinkedList::Node::PointerType head) {
    SinglyLinkedList::Node dummy;
    dummy.next = head;

    for (auto *prev = &dummy; prev->next and prev->next->next;) {
        auto next = prev->next->next;
        prev->next->next = next->next;
        next->next = prev->next;
        prev->next = next;
        prev = next->next.get();
    }

    return dummy.next;
}

inline auto testSwapPairs(const ArrayType &array) {
    return TestHelper(array, SwapPairs);
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4};
const ArrayType EXPECTED1 = {2, 1, 4, 3};

const ArrayType SAMPLE2 = {1};

const ArrayType SAMPLE3 = {};


THE_BENCHMARK(testSwapPairs, SAMPLE1);

SIMPLE_TEST(testSwapPairs, TestSample1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(testSwapPairs, TestSample2, SAMPLE2, SAMPLE2);
SIMPLE_TEST(testSwapPairs, TestSample3, SAMPLE3, SAMPLE3);
