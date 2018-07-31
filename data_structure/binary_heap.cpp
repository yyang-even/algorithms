#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "binary_heap.h"

auto testBinaryHeapPushAndPop(const MinHeap::ArrayType &array) {
    MinHeap heap;
    for (const auto elem : array) {
        heap.Push(elem);
    }

    MinHeap::ArrayType sorted_array;
    while (not heap.Empty()) {
        sorted_array.push_back(heap.Pop());
    }

    return sorted_array;
}


const MinHeap::ArrayType SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const MinHeap::ArrayType EXPECTED_ARRAY {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

SIMPLE_TEST(testBinaryHeapPushAndPop, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
