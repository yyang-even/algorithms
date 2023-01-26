#include "common_header.h"

#include "singly_linked_list.h"


namespace {

using ArrayType = std::vector<int>;

/** Intersection of Two Linked Lists
 *
 * @reference   https://leetcode.com/problems/intersection-of-two-linked-lists/
 *
 * Given the heads of two singly linked-lists headA and headB, return the node at which the two lists
 * intersect. If the two linked lists have no intersection at all, return null.
 * It is guaranteed that there are no cycles anywhere in the entire linked structure.
 * Note that the linked lists must retain their original structure after the function returns.
 * Follow up: Could you write a solution that runs in O(n) time and use only O(1) memory?
 * 1 <= Node.val <= 10^5
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

    return SinglyLinkedList::Node::PointerType {};
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
 * Given two linked lists of size N and M consisting of positive value nodes, having a common
 * intersection point, the task is to find the intersection point of the two linked lists where they
 * merge.
 */
inline auto IntersectionPoint_Flag(SinglyLinkedList::Node::PointerType one_head,
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

    return SinglyLinkedList::Node::PointerType {};
}


template<typename Function>
constexpr auto testIntersectionPoint(const ArrayType &one,
                                     const ArrayType &another,
                                     const int intersection_rindex,
                                     const Function intersection_point) {
    const auto one_head = SinglyLinkedList {one}.GetHead();
    const auto another_head = SinglyLinkedList {another}.GetHead();

    if (intersection_rindex == -1) {
        return nullptr == intersection_point(one_head, another_head);
    }

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


/**
 * @reference   Find Closest Node to Given Two Nodes
 *              https://leetcode.com/problems/find-closest-node-to-given-two-nodes/
 *
 * You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one
 * outgoing edge.
 * The graph is represented with a given 0-indexed array edges of size n, indicating that there is a
 * directed edge from node i to node edges[i]. If there is no outgoing edge from i, then edges[i] == -1.
 * You are also given two integers node1 and node2.
 * Return the index of the node that can be reached from both node1 and node2, such that the maximum
 * between the distance from node1 to that node, and from node2 to that node is minimized. If there are
 * multiple answers, return the node with the smallest index, and if no possible answer exists, return 1.
 * Note that edges may contain cycles.
 */
void ClosestMeetingNode(const ArrayType &edges,
                        const int i,
                        std::unordered_map<int, int> &distances,
                        const int current) {
    if (not distances.emplace(i, current).second) {
        return;
    }

    if (edges[i] != -1) {
        ClosestMeetingNode(edges, edges[i], distances, current + 1);
    }
}

int ClosestMeetingNode(const ArrayType &edges, const int node1, const int node2) {
    std::unordered_map<int, int> distances_to_one;
    ClosestMeetingNode(edges, node1, distances_to_one, 0);

    std::unordered_map<int, int> distances_to_two;
    ClosestMeetingNode(edges, node2, distances_to_two, 0);

    std::size_t result = INT_MAX;
    int min_distance = INT_MAX;
    for (std::size_t i = 0; i < edges.size(); ++i) {
        const auto one_iter = distances_to_one.find(i);
        if (one_iter == distances_to_one.cend())
            continue;

        const auto two_iter = distances_to_two.find(i);
        if (two_iter == distances_to_two.cend())
            continue;

        const auto distance = std::max(one_iter->second, two_iter->second);
        if (min_distance > distance) {
            result = i;
            min_distance = distance;
        } else if (min_distance == distance) {
            result = std::min(result, i);
        }
    }

    return min_distance == INT_MAX ? -1 : result;
}

} //namespace


const ArrayType SAMPLE1_L = {4, 1, 8, 4, 5};
const ArrayType SAMPLE1_R = {5, 6, 1, 8, 4, 5};

const ArrayType SAMPLE2_L = {3, 2, 4};
const ArrayType SAMPLE2_R = {1, 9, 1, 2, 4};


THE_BENCHMARK(testIntersectionPoint, SAMPLE1_L, SAMPLE1_R, 2, IntersectionPoint_Length);

SIMPLE_TEST(
    testIntersectionPoint, TestSAMPLE1L, true, SAMPLE1_L, SAMPLE1_R, 2, IntersectionPoint_Length);
SIMPLE_TEST(
    testIntersectionPoint, TestSAMPLE2L, true, SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_Length);
SIMPLE_TEST(
    testIntersectionPoint, TestSAMPLE3L, true, SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_Length);


SIMPLE_TEST(testIntersectionPoint,
            TestSAMPLE1T,
            true,
            SAMPLE1_L,
            SAMPLE1_R,
            2,
            IntersectionPoint_TwoPointers);
SIMPLE_TEST(testIntersectionPoint,
            TestSAMPLE2T,
            true,
            SAMPLE2_L,
            SAMPLE2_R,
            1,
            IntersectionPoint_TwoPointers);
SIMPLE_TEST(testIntersectionPoint,
            TestSAMPLE3T,
            true,
            SAMPLE2_L,
            SAMPLE2_R,
            1,
            IntersectionPoint_TwoPointers);


SIMPLE_TEST(
    testIntersectionPoint, TestSAMPLE1F, true, SAMPLE1_L, SAMPLE1_R, 2, IntersectionPoint_Flag);
SIMPLE_TEST(
    testIntersectionPoint, TestSAMPLE2F, true, SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_Flag);
SIMPLE_TEST(
    testIntersectionPoint, TestSAMPLE3F, true, SAMPLE2_L, SAMPLE2_R, 1, IntersectionPoint_Flag);


const ArrayType SAMPLE1E = {2, 2, 3, -1};
const ArrayType SAMPLE2E = {1, 2, -1};
const ArrayType SAMPLE3E = {4, 4, 4, 5, 1, 2, 2};
const ArrayType SAMPLE4E = {5, 3, 1, 0, 2, 4, 5};


THE_BENCHMARK(ClosestMeetingNode, SAMPLE1E, 0, 1);

SIMPLE_TEST(ClosestMeetingNode, TestSAMPLE1, 2, SAMPLE1E, 0, 1);
SIMPLE_TEST(ClosestMeetingNode, TestSAMPLE2, 2, SAMPLE2E, 0, 2);
SIMPLE_TEST(ClosestMeetingNode, TestSAMPLE3, 1, SAMPLE3E, 1, 1);
SIMPLE_TEST(ClosestMeetingNode, TestSAMPLE4, 3, SAMPLE4E, 3, 2);
