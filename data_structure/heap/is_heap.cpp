#include "common_header.h"

#include "binary_heap.h"


namespace {

auto isMaxHeap_Recursive(const MaxHeap<int>::ArrayType &values) {
    return MaxHeap<int>::isHeap_Recursive(values);
}


auto isMaxHeap_Iterative(const MaxHeap<int>::ArrayType &values) {
    return MaxHeap<int>::isHeap_Iterative(values);
}


auto isMinHeap_Iterative(const MinHeap<int>::ArrayType &values) {
    return MinHeap<int>::isHeap_Iterative(values);
}

}//namespace


const MaxHeap<int>::ArrayType SAMPLE_ARRAY1 = {90, 15, 10, 7, 12, 2};
const MaxHeap<int>::ArrayType SAMPLE_ARRAY2 = {9, 15, 10, 7, 12, 11};
const MaxHeap<int>::ArrayType SAMPLE_ARRAY3 = {9};
const MaxHeap<int>::ArrayType SAMPLE_ARRAY4 = {90, 15, 10, 7, 12, 2, 7, 3};


SIMPLE_BENCHMARK(isMaxHeap_Recursive, SAMPLE_ARRAY1);

SIMPLE_TEST(isMaxHeap_Recursive, TestSample1, true, SAMPLE_ARRAY1);
SIMPLE_TEST(isMaxHeap_Recursive, TestSample2, false, SAMPLE_ARRAY2);
SIMPLE_TEST(isMaxHeap_Recursive, TestSample3, true, SAMPLE_ARRAY3);
SIMPLE_TEST(isMaxHeap_Recursive, TestSample4, true, SAMPLE_ARRAY4);


SIMPLE_BENCHMARK(isMaxHeap_Iterative, SAMPLE_ARRAY1);

SIMPLE_TEST(isMaxHeap_Iterative, TestSample1, true, SAMPLE_ARRAY1);
SIMPLE_TEST(isMaxHeap_Iterative, TestSample2, false, SAMPLE_ARRAY2);
SIMPLE_TEST(isMaxHeap_Iterative, TestSample3, true, SAMPLE_ARRAY3);
SIMPLE_TEST(isMaxHeap_Iterative, TestSample4, true, SAMPLE_ARRAY4);


const MinHeap<int>::ArrayType SAMPLE_ARRAY5 = {10, 15, 14, 25, 30};
const MinHeap<int>::ArrayType SAMPLE_ARRAY6 = {30, 56, 22, 49, 30, 51, 2, 67};


SIMPLE_BENCHMARK(isMinHeap_Iterative, SAMPLE_ARRAY5);

SIMPLE_TEST(isMinHeap_Iterative, TestSample1, true, SAMPLE_ARRAY5);
SIMPLE_TEST(isMinHeap_Iterative, TestSample2, false, SAMPLE_ARRAY6);