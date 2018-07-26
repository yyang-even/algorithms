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
using MaxHeap = BinaryHeap< std::greater<int> > ;

inline auto HeapSort(const MaxHeap::ArrayType &array) {
    return MaxHeap(array).ToSortedArray();
}


const MaxHeap::ArrayType EMPTY_ARRAY {};
SIMPLE_BENCHMARK(HeapSort, {7, 8, 5, 6, 3, 7, 5, 1, 5, 6, 7, 6, 4, 6, 2, 1, 3, 4, 6, 5, 7, 8, 9});

SIMPLE_TEST(HeapSort, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
