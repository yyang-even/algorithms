#pragma once


static inline auto GetBeforeMiddle_TwoPointersSTL(
    const std::forward_list<int>::const_iterator cbefore_begin,
    const std::forward_list<int>::const_iterator cend) {
    auto slow_ptr = cbefore_begin;
    auto fast_ptr = std::next(cbefore_begin);

    assert(fast_ptr != cend);

    for (; fast_ptr != cend and ++fast_ptr != cend; ++fast_ptr, ++slow_ptr);
    return slow_ptr;
}


/**
 * @reference   Middle of the Linked List
 *              https://leetcode.com/problems/middle-of-the-linked-list/
 *
 * Given the head of a singly linked list, return the middle node of the linked list. If
 * there are two middle nodes, return the second middle node.
 */
static inline auto
GetMiddle_TwoPointers_STL(const std::forward_list<int>::const_iterator cbegin,
                          const std::forward_list<int>::const_iterator cend) {
    auto slow_ptr = cbegin;
    auto fast_ptr = cbegin;

    for (; fast_ptr != cend and ++fast_ptr != cend; ++fast_ptr, ++slow_ptr);
    return slow_ptr;
}
