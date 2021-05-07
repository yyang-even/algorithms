#include "common_header.h"


namespace {

#include "merge_k_sorted_array.h"

using ArrayType = std::vector<int>;

/** Merge k sorted arrays
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 6.5. Exercises 6.5-9.
 * @reference   Merge k sorted arrays | Set 1
 *              https://www.geeksforgeeks.org/merge-k-sorted-arrays/
 *
 * Given k sorted arrays of size n each, merge them and print the sorted output.
 *
 * @reference   Merge k sorted arrays | Set 2 (Different Sized Arrays)
 *              https://www.geeksforgeeks.org/merge-k-sorted-arrays-set-2-different-sized-arrays/
 *
 * Given k sorted arrays of possibly different sizes, merge them and print the sorted output.
 *
 * @reference   Merge 3 Sorted Arrays
 *              https://www.geeksforgeeks.org/merge-3-sorted-arrays/
 *
 * @complexity  O(nk*lgk)
 */
inline auto MergeKSortedArrays(const std::vector<ArrayType> &k_arrays) {
    ArrayType final_sorted_array;

    MergeKSortedArrays(k_arrays, std::back_insert_iterator(final_sorted_array));

    return final_sorted_array;
}


/** Merge K sorted arrays | Set 3 ( Using Divide and Conquer Approach )
 *
 * @reference   https://www.geeksforgeeks.org/merge-k-sorted-arrays-set-3-using-divide-and-conquer-approach/
 * @reference   Merge K sorted arrays of different sizes | ( Divide and Conquer Approach )
 *              https://www.geeksforgeeks.org/merge-k-sorted-arrays-of-different-sizes-divide-and-conquer-approach/
 */


/** Merge K sorted Doubly Linked List in Sorted Order
 *
 * @reference   https://www.geeksforgeeks.org/merge-k-sorted-doubly-linked-list-in-sorted-order/
 */

}//namespace


const std::vector<ArrayType> SAMPLE_ARRAYS = {{1, 3, 5, 7, 9},
    {2, 4, 6, 8, 10},
    {11, 12, 13, 19},
    {14, 15, 16, 20}
};
const ArrayType EXPECTED_ARRAY = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 19, 20};


SIMPLE_BENCHMARK(MergeKSortedArrays, Sample1, SAMPLE_ARRAYS);

SIMPLE_TEST(MergeKSortedArrays, TestSAMPLE, EXPECTED_ARRAY, SAMPLE_ARRAYS);


const std::vector<ArrayType> SAMPLE_DIFF_SIZE_ARRAYS = {{1, 3, 5, 7, 9},
    {2, 4, 6, 8},
    {11},
    {10, 12, 13, 14, 15, 16, 20}
};
const ArrayType EXPECTED_DIFF_SIZE_ARRAY = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20};


SIMPLE_BENCHMARK(MergeKSortedArrays, Sample2, SAMPLE_DIFF_SIZE_ARRAYS);

SIMPLE_TEST(MergeKSortedArrays, TestSampleDiffSize, EXPECTED_DIFF_SIZE_ARRAY,
            SAMPLE_DIFF_SIZE_ARRAYS);
