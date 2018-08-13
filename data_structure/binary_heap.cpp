#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "binary_heap.h"

auto testBinaryHeap(const MinHeap<int>::ArrayType &array) {
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


const MinHeap<int>::ArrayType SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const MinHeap<int>::ArrayType EXPECTED_ARRAY {
    0, 1, 2, 3, 4, 5, 6, 7, 9
};

SIMPLE_TEST(testBinaryHeap, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
