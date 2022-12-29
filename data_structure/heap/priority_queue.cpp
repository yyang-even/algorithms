#include "common_header.h"

#include "priority_queue.h"


namespace {

using ArrayType = MinPriorityQueue<int>::ArrayType;

inline auto testPriorityQueue(const ArrayType &array) {
    MinPriorityQueue<int> priority_queue {array};

    //No-op
    priority_queue.Prioritize(2, 8);

    priority_queue.Prioritize(9, -1);

    return priority_queue.ToSortedArray();
}


inline auto testListPriorityQueue(const ArrayType &array) {
    SinglyLinkedListMinPriorityQueue priority_queue {array};
    priority_queue.Pop();

    return priority_queue.MoveToSortedArray();
}


inline auto testListPriorityQueue_STL(const ArrayType &array) {
    SinglyLinkedListMinPriorityQueue_STL priority_queue {array};
    priority_queue.Pop();

    return priority_queue.MoveToSortedArray();
}


/**
 * @reference   Remove Stones to Minimize the Total
 *              https://leetcode.com/problems/remove-stones-to-minimize-the-total/
 *
 * You are given a 0-indexed integer array piles, where piles[i] represents the number of stones in the
 * ith pile, and an integer k. You should apply the following operation exactly k times:
 *  Choose any piles[i] and remove floor(piles[i] / 2) stones from it.
 * Notice that you can apply the operation on the same pile more than once.
 * Return the minimum possible total number of stones remaining after applying the k operations.
 * floor(x) is the greatest integer that is smaller than or equal to x (i.e., rounds x down).
 */
auto MinStoneSum(ArrayType piles, int k) {
    std::make_heap(piles.begin(), piles.end());
    while (k-- > 0) {
        std::pop_heap(piles.begin(), piles.end());
        piles.back() = piles.back() - (piles.back() / 2);
        std::push_heap(piles.begin(), piles.end());
    }

    return std::accumulate(piles.cbegin(), piles.cend(), 0);
}

} //namespace


const ArrayType SAMPLE_ARRAY = {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const ArrayType EXPECTED_ARRAY = {8, 7, 6, 5, 4, 3, 2, 1, 0, -1};


SIMPLE_TEST(testPriorityQueue, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


const ArrayType EXPECTED_LIST_ARRAY = {1, 2, 3, 4, 5, 6, 7, 8, 9};


SIMPLE_TEST(testListPriorityQueue, TestSample, EXPECTED_LIST_ARRAY, SAMPLE_ARRAY);


SIMPLE_TEST(testListPriorityQueue_STL, TestSample, EXPECTED_LIST_ARRAY, SAMPLE_ARRAY);


const ArrayType SAMPLE1 = {5, 4, 9};
const ArrayType SAMPLE2 = {4, 3, 6, 7};


THE_BENCHMARK(MinStoneSum, SAMPLE1, 2);

SIMPLE_TEST(MinStoneSum, TestSAMPLE1, 12, SAMPLE1, 2);
SIMPLE_TEST(MinStoneSum, TestSAMPLE2, 12, SAMPLE2, 3);
