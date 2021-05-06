#include "common_header.h"

#include "data_structure/heap/binary_heap.h"


namespace {

/** Heap Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 6.4.
 *
 * @reference   https://www.geeksforgeeks.org/heap-sort/
 * @reference   Heap Sort for decreasing order using min heap
 *              https://www.geeksforgeeks.org/heap-sort-for-decreasing-order-using-min-heap/
 * @reference   C++ Program for Heap Sort
 *              https://www.geeksforgeeks.org/cpp-program-for-heap-sort/
 * @reference   Where is Heap Sort used practically?
 *              https://www.geeksforgeeks.org/where-is-heap-sort-used-practically/
 */
inline auto HeapSort_Recursive(const MaxHeap<int>::ArrayType &array) {
    return MaxHeap<int>(array).ToSortedArray();
}


/** Iterative Heap Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 6.2. Exercises 6.2-5.
 *
 * @reference   https://www.geeksforgeeks.org/iterative-heap-sort/
 */
inline auto HeapSort_Iterative(const MaxHeap<int>::ArrayType &array) {
    return MaxHeap<int>(array, false).ToSortedArray();
}

}//namespace


const MaxHeap<int>::ArrayType EMPTY_ARRAY = {};
const MaxHeap<int>::ArrayType SINGLE_ARRAY = {1};
const MaxHeap<int>::ArrayType EVEN_ARRAY = {1, 3};
const MaxHeap<int>::ArrayType ODD_ARRAY = {1, 2, 3};
const MaxHeap<int>::ArrayType SAMPLE_ARRAY = {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const MaxHeap<int>::ArrayType EXPECTED_ARRAY = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


THE_BENCHMARK(HeapSort_Recursive, {7, 8, 5, 6, 3, 7, 5, 1, 5, 6, 7, 6, 4, 6, 2, 1, 3, 4, 6, 5, 7, 8, 9});

SIMPLE_TEST(HeapSort_Recursive, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(HeapSort_Recursive, TestSingle, SINGLE_ARRAY, SINGLE_ARRAY);
SIMPLE_TEST(HeapSort_Recursive, TestEven, EVEN_ARRAY, EVEN_ARRAY);
SIMPLE_TEST(HeapSort_Recursive, TestOdd, ODD_ARRAY, ODD_ARRAY);
SIMPLE_TEST(HeapSort_Recursive, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(HeapSort_Iterative, {7, 8, 5, 6, 3, 7, 5, 1, 5, 6, 7, 6, 4, 6, 2, 1, 3, 4, 6, 5, 7, 8, 9});

SIMPLE_TEST(HeapSort_Iterative, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(HeapSort_Iterative, TestSingle, SINGLE_ARRAY, SINGLE_ARRAY);
SIMPLE_TEST(HeapSort_Iterative, TestEven, EVEN_ARRAY, EVEN_ARRAY);
SIMPLE_TEST(HeapSort_Iterative, TestOdd, ODD_ARRAY, ODD_ARRAY);
SIMPLE_TEST(HeapSort_Iterative, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
