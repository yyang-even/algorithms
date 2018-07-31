#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "data_structure/binary_heap.h"

/** Heap Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.4.
 *
 *              https://www.geeksforgeeks.org/heap-sort/
 *              Heap Sort for decreasing order using min heap
 *              https://www.geeksforgeeks.org/heap-sort-for-decreasing-order-using-min-heap/
 */
inline auto HeapSortRecursive(const MaxHeap::ArrayType &array) {
    return MaxHeap(array).ToSortedArray();
}
/** Iterative Heap Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.2. Exercises 6.2-5.
 *              
 *              https://www.geeksforgeeks.org/iterative-heap-sort/
 */
inline auto HeapSortIterative(const MaxHeap::ArrayType &array) {
    return MaxHeap(array, false).ToSortedArray();
}


const MaxHeap::ArrayType EMPTY_ARRAY {};
const MaxHeap::ArrayType SINGLE_ARRAY {
    1
};
const MaxHeap::ArrayType EVEN_ARRAY {
    1, 3
};
const MaxHeap::ArrayType ODD_ARRAY {
    1, 2, 3
};
const MaxHeap::ArrayType SAMPLE_ARRAY {
    1, 0, 8, 6, 2, 3, 7, 4, 5, 9
};
const MaxHeap::ArrayType EXPECTED_ARRAY {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

SIMPLE_BENCHMARK(HeapSortRecursive, {7, 8, 5, 6, 3, 7, 5, 1, 5, 6, 7, 6, 4, 6, 2, 1, 3, 4, 6, 5, 7, 8, 9});

SIMPLE_TEST(HeapSortRecursive, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(HeapSortRecursive, TestSingle, SINGLE_ARRAY, SINGLE_ARRAY);
SIMPLE_TEST(HeapSortRecursive, TestEven, EVEN_ARRAY, EVEN_ARRAY);
SIMPLE_TEST(HeapSortRecursive, TestOdd, ODD_ARRAY, ODD_ARRAY);
SIMPLE_TEST(HeapSortRecursive, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


SIMPLE_BENCHMARK(HeapSortIterative, {7, 8, 5, 6, 3, 7, 5, 1, 5, 6, 7, 6, 4, 6, 2, 1, 3, 4, 6, 5, 7, 8, 9});

SIMPLE_TEST(HeapSortIterative, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(HeapSortIterative, TestSingle, SINGLE_ARRAY, SINGLE_ARRAY);
SIMPLE_TEST(HeapSortIterative, TestEven, EVEN_ARRAY, EVEN_ARRAY);
SIMPLE_TEST(HeapSortIterative, TestOdd, ODD_ARRAY, ODD_ARRAY);
SIMPLE_TEST(HeapSortIterative, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
