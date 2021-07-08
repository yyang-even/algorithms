#include "common_header.h"

#include "singly_list/singly_linked_list.h"


namespace {

using ArrayType = std::vector<int>;

/** Intersection of Two Linked Lists
 *
 * @reference   https://leetcode.com/problems/intersection-of-two-linked-lists/
 *
 * Given the heads of two singly linked-lists headA and headB, return the node at which
 * the two lists intersect. If the two linked lists have no intersection at all, return
 * null. It is guaranteed that there are no cycles anywhere in the entire linked
 * structure. Note that the linked lists must retain their original structure after the
 * function returns. Follow up: Could you write a solution that runs in O(n) time and
 * use only O(1) memory?
 *  1 <= Node.val <= 105
 *
 * @reference   Write a function to get the intersection point of two Linked Lists
 *              https://www.geeksforgeeks.org/write-a-function-to-get-the-intersection-point-of-two-linked-lists/
 */
auto IntersectionPoint_Length(const SinglyLinkedList::Node::PointerType one_head,
                              const SinglyLinkedList::Node::PointerType another_head) {
    const int one_size = CountSize_Iterative(one_head);
    const int another_size = CountSize_Iterative(another_head);

    const auto diff = std::abs(one_size - another_size);
    auto shorter = one_head;
    auto longer = another_head;
    if (one_size > another_size) {
        std::swap(shorter, longer);
    }

    for (int i = 0; i < diff; ++i) {
        longer = longer->next;
    }

    while (longer and shorter) {
        if (longer == shorter) {
            return longer;
        }

        longer = longer->next;
        shorter = shorter->next;
    }

    return SinglyLinkedList::Node::PointerType{};
}


/**
 * @reference   Write a function to get the intersection point of two Linked Lists | Set 2
 *              https://www.geeksforgeeks.org/write-a-function-to-get-the-intersection-point-of-two-linked-lists-set-2/
 * @reference   Find intersection point of two Linked Lists without finding the length
 *              https://www.geeksforgeeks.org/find-intersection-point-of-two-linked-lists-without-finding-the-length/
 */
inline auto
IntersectionPoint_TwoPointers(const SinglyLinkedList::Node::PointerType one_head,
                              const SinglyLinkedList::Node::PointerType another_head) {
    auto one_ptr = one_head;
    auto another_ptr = another_head;

    while (one_ptr != another_ptr) {
        if (not one_ptr) {
            one_ptr = another_head;
        } else {
            one_ptr = one_ptr->next;
        }

        if (not another_ptr) {
            another_ptr = one_head;
        } else {
            another_ptr = another_ptr->next;
        }
    }

    return one_ptr;
}


/**
 * @reference   Intersection point of two Linked Lists | Set 3
 *              https://www.geeksforgeeks.org/intersection-point-of-two-linked-lists-set-3/
 *
 * Given two linked lists of size N and M consisting of positive value nodes, having a
 * common intersection point, the task is to find the intersection point of the two
 * linked lists where they merge.
 */
inline auto
IntersectionPoint_Flag(SinglyLinkedList::Node::PointerType one_head,
                       SinglyLinkedList::Node::PointerType another_head) {
    for (; one_head; one_head = one_head->next) {
        one_head->value *= -1;
    }

    for (; another_head; another_head = another_head->next) {
        if (another_head->value < 0) {
            another_head->value *= -1;
            return another_head;
        }
    }

    return SinglyLinkedList::Node::PointerType{};
}


template <typename Function>
constexpr auto
testIntersectionPoint(const ArrayType &one, const ArrayType &another,
                      const int intersection_rindex, const Function intersection_point) {
    const auto one_head = SinglyLinkedList{one}.GetHead();
    const auto another_head = SinglyLinkedList{another}.GetHead();

    if (intersection_rindex == -1) {
        return nullptr == intersection_point(one_head, another_head);
    } else {
        const auto expected = *(one.crbegin() + intersection_rindex);
        assert(another.size() >= one.size());
        const int diff = another.size() - one.size();
        auto one_iter = one_head;
        auto another_iter = another_head;
        for (int i = 0; i < diff; ++i) {
            another_iter = another_iter->next;
        }

        for (std::size_t i = 1; i < one.size() - intersection_rindex - 1; ++i) {
            one_iter = one_iter->next;
            another_iter = another_iter->next;
        }

        another_iter->next = one_iter->next;

        return expected == intersection_point(one_head, another_head)->value;
    }
}

}//namespace


const ArrayType SAMPLE1_L = {4, 1, 8, 4, 5};
const ArrayType SAMPLE1_R = {5, 6, 1, 8, 4, 5};

const ArrayType SAMPLE2_L = {3, 2, 4};
const ArrayType SAMPLE2_R = {1, 9, 1, 2, 4};


THE_BENCHMARK(testIntersectionPoint, SAMPLE1_L, SAMPLE1_R, 2, IntersectionPoint_Length);

SIMPLE_TEST(testIntersectionPoint, TestSAMPLE1L, true,
            SAMPLE1_L, SAMPLE1_R, 2, IntersectionPoint_Length);
SIMPLE_TEST(testIntersectionPoint, TestSAMPLE2L, true,
            SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_Length);
SIMPLE_TEST(testIntersectionPoint, TestSAMPLE3L, true,
            SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_Length);


SIMPLE_TEST(testIntersectionPoint, TestSAMPLE1T, true,
            SAMPLE1_L, SAMPLE1_R, 2, IntersectionPoint_TwoPointers);
SIMPLE_TEST(testIntersectionPoint, TestSAMPLE2T, true,
            SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_TwoPointers);
SIMPLE_TEST(testIntersectionPoint, TestSAMPLE3T, true,
            SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_TwoPointers);


SIMPLE_TEST(testIntersectionPoint, TestSAMPLE1F, true,
            SAMPLE1_L, SAMPLE1_R, 2, IntersectionPoint_Flag);
SIMPLE_TEST(testIntersectionPoint, TestSAMPLE2F, true,
            SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_Flag);
SIMPLE_TEST(testIntersectionPoint, TestSAMPLE3F, true,
            SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_Flag);
