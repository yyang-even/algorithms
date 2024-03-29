#include "common_header.h"

#include "binary_heap.h"


namespace {

inline auto testBinaryHeap(const MinHeap<int>::ArrayType &array) {
    MinHeap<int> heap;
    for (const auto elem : array) {
        heap.Push(elem);
    }

    heap.Delete(5); //Delete value 8

    MinHeap<int>::ArrayType sorted_array;
    while (not heap.Empty()) {
        sorted_array.push_back(heap.Pop());
    }

    return sorted_array;
}


/**
 * @reference   Last Stone Weight
 *              https://leetcode.com/problems/last-stone-weight/
 *
 * You are given an array of integers stones where stones[i] is the weight of the ith stone. We
 * are playing a game with the stones. On each turn, we choose the heaviest two stones and smash
 * them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of
 * this smash is:
 *  If x == y, both stones are destroyed, and
 *  If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
 * At the end of the game, there is at most one stone left. Return the smallest possible weight
 * of the left stone. If there are no stones left, return 0.
 */

} //namespace


const MinHeap<int>::ArrayType SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const MinHeap<int>::ArrayType EXPECTED_ARRAY = {0, 1, 2, 3, 4, 5, 6, 7, 9};


SIMPLE_TEST(testBinaryHeap, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
