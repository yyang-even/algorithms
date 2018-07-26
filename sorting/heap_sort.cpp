#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "data_structure/binary_heap.h"

/** Heap Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.4.
 *
 *              https://www.geeksforgeeks.org/heap-sort/
 */
inline auto HeapSort(const MaxHeap::ArrayType &array) {
    return MaxHeap(array).ToSortedArray();
}


const MaxHeap::ArrayType EMPTY_ARRAY {};
const MaxHeap::ArrayType SINGLE_ARRAY {1};
const MaxHeap::ArrayType EVEN_ARRAY {1, 3};
const MaxHeap::ArrayType ODD_ARRAY {1, 2, 3};
const MaxHeap::ArrayType SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const MaxHeap::ArrayType EXPECTED_ARRAY {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
SIMPLE_BENCHMARK(HeapSort, {7, 8, 5, 6, 3, 7, 5, 1, 5, 6, 7, 6, 4, 6, 2, 1, 3, 4, 6, 5, 7, 8, 9});

SIMPLE_TEST(HeapSort, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(HeapSort, TestSingle, SINGLE_ARRAY, SINGLE_ARRAY);
SIMPLE_TEST(HeapSort, TestEven, EVEN_ARRAY, EVEN_ARRAY);
SIMPLE_TEST(HeapSort, TestOdd, ODD_ARRAY, ODD_ARRAY);
SIMPLE_TEST(HeapSort, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
