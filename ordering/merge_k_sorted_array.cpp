#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Merge k sorted arrays
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.5. Exercises 6.5-9.
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
using Node = std::pair<const ArrayType *, ArrayType::const_iterator>;

auto MergeKSortedArrays(const std::vector<ArrayType> &k_arrays) {
    ArrayType final_sorted_array;

    std::vector<Node> first_elements;
    for (const auto &a : k_arrays) {
        if (not a.empty()) {
            first_elements.emplace_back(&a, a.cbegin());
        }
    }

    const auto compare = [](const Node & lhs, const Node & rhs) {
        return  *lhs.second > *rhs.second;
    };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> heap(compare,
            std::move(first_elements));

    while (not heap.empty()) {
        const auto elem = heap.top();
        heap.pop();
        final_sorted_array.push_back(*elem.second);

        const auto next = std::next(elem.second);
        if (next != elem.first->cend()) {
            heap.emplace(elem.first, next);
        }
    }

    return final_sorted_array;
}

}//namespace


const std::vector<ArrayType> SAMPLE_ARRAYS = {{1, 3, 5, 7, 9},
    {2, 4, 6, 8, 10},
    {11, 12, 13, 19},
    {14, 15, 16, 20}
};
const ArrayType EXPECTED_ARRAY = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 19, 20};


SIMPLE_BENCHMARK(MergeKSortedArrays, SAMPLE_ARRAYS);

SIMPLE_TEST(MergeKSortedArrays, TestSAMPLE, EXPECTED_ARRAY, SAMPLE_ARRAYS);


const std::vector<ArrayType> SAMPLE_DIFF_SIZE_ARRAYS = {{1, 3, 5, 7, 9},
    {2, 4, 6, 8},
    {11},
    {10, 12, 13, 14, 15, 16, 20}
};
const ArrayType EXPECTED_DIFF_SIZE_ARRAY = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20};


SIMPLE_BENCHMARK(MergeKSortedArrays, SAMPLE_DIFF_SIZE_ARRAYS);

SIMPLE_TEST(MergeKSortedArrays, TestSampleDiffSize, EXPECTED_DIFF_SIZE_ARRAY,
            SAMPLE_DIFF_SIZE_ARRAYS);
