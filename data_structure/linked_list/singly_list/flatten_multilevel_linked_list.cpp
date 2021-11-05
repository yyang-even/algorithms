#include "common_header.h"

#include "singly_linked_list.h"


namespace {

struct MultiLevelNode {
    using ValueType = int;
    using PointerType = std::shared_ptr<MultiLevelNode>;

    constexpr explicit MultiLevelNode(const ValueType v = 0): value(v) {
    }

    ValueType value;
    PointerType next;
    PointerType child;
};

using ArrayType = std::vector<MultiLevelNode::ValueType>;

/**
 * @reference   Doubly Linked List Flattening
 *              John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 4.
 *
 * @reference   Flatten a multilevel linked list
 *              https://www.geeksforgeeks.org/flatten-a-linked-list-with-next-and-child-pointers/
 *
 * Given a linked list where in addition to the next pointer, each node has a child
 * pointer, which may or may not point to a separate list. These child lists may have
 * one or more children of their own, and so on, to produce a multilevel data structure,
 * as shown in below figure.You are given the head of the first level of the list.
 * Flatten the list so that all the nodes appear in a single-level linked list. You need
 * to flatten the list in way that all nodes at first level should come first, then nodes
 * of second level, and so on.
 */
auto FlattenMultilevelLinkedList_Levelwise(const MultiLevelNode::PointerType head) {
    std::queue<MultiLevelNode::PointerType> children_queue;
    for (auto current = head; current; current = current->next) {
        if (current->child) {
            children_queue.push(current->child);
        }
        if (not children_queue.empty() and not current->next) {
            current->next = children_queue.front();
            children_queue.pop();
        }
    }

    return head;
}


/**
 * @reference   Flatten a multi-level linked list | Set 2 (Depth wise)
 *              https://www.geeksforgeeks.org/flatten-a-multi-level-linked-list-set-2-depth-wise/
 *
 * @reference   Flatten a Multilevel Doubly Linked List
 *              https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/
 */
MultiLevelNode::PointerType FlattenMultilevelLinkedList_Depthwise(
    const MultiLevelNode::PointerType head) {
    for (auto current = head; current; current = current->next) {
        if (current->child) {
            const auto next = current->next;
            current->next = FlattenMultilevelLinkedList_Depthwise(current->child);
            current->child.reset();
            for (; current->next; current = current->next);
            current->next = next;
        }
    }

    return head;
}


/** List Unflattening
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 4.
 *
 * Unflatten the list created by the previous problem and restore the data structure to
 * its original condition.
 */


auto ToList(const ArrayType &an_array) {
    MultiLevelNode::PointerType head, current;
    for (const auto value : an_array) {
        if (not head) {
            head = current = std::make_shared<MultiLevelNode>(value);
        } else {
            current->next = std::make_shared<MultiLevelNode>(value);
            current = current->next;
        }
    }

    return head;
}

auto GetTheSampleList() {
    const auto head1 = ToList({10, 5, 12, 7, 11});
    const auto head2 = ToList({4, 20, 13});
    const auto head3 = ToList({17, 6});
    const auto head4 = ToList({9, 8});
    const auto head5 = ToList({19, 15});
    const auto head6 = ToList({2});
    const auto head7 = ToList({16});
    const auto head8 = ToList({3});

    head1->child = head2;
    head1->next->next->next->child = head3;
    head3->child = head4;
    head4->child = head5;
    head2->next->child = head6;
    head2->next->next->child = head7;
    head7->child = head8;

    return head1;
}

inline auto TestFlattenMultilevelLinkedList(
    const MultiLevelNode::PointerType head,
    const std::function<MultiLevelNode::PointerType(MultiLevelNode::PointerType)> flatter) {
    flatter(head);
    return CopyToArray(head);
}

}//namespace


const auto SAMPLE1 = GetTheSampleList();
const ArrayType EXPECTED1 = {10, 5, 12, 7, 11, 4, 20, 13, 17, 6, 2, 16, 9, 8, 3, 19, 15};


THE_BENCHMARK(FlattenMultilevelLinkedList_Levelwise, SAMPLE1);

SIMPLE_TEST(TestFlattenMultilevelLinkedList, TestSAMPLE1, EXPECTED1,
            SAMPLE1, FlattenMultilevelLinkedList_Levelwise);


const auto SAMPLE2 = GetTheSampleList();
const ArrayType EXPECTED2 = {10, 4, 20, 2, 13, 16, 3, 5, 12, 7, 17, 9, 19, 15, 8, 6, 11};


THE_BENCHMARK(FlattenMultilevelLinkedList_Depthwise, SAMPLE1);

SIMPLE_TEST(TestFlattenMultilevelLinkedList, TestSAMPLE2, EXPECTED2,
            SAMPLE2, FlattenMultilevelLinkedList_Depthwise);
