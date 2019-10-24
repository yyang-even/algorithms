#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

#include "kth_smallest_or_largest_element.h"

/** K’th Smallest/Largest Element in Unsorted Array
 *
 * @reference   K’th Smallest/Largest Element in Unsorted Array | Set 1
 *              https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/
 * @reference   K’th Smallest/Largest Element in Unsorted Array | Set 2 (Expected Linear Time)
 *              https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array-set-2-expected-linear-time-2/
 *              https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array-set-2-expected-linear-time/
 * @reference   K’th Smallest/Largest Element in Unsorted Array | Set 3 (Worst Case Linear Time)
 *              https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array-set-3-worst-case-linear-time/
 * @reference   K’th Smallest/Largest Element using STL
 *              https://www.geeksforgeeks.org/kth-smallestlargest-element-using-stl/
 * @reference   Third largest element in an array of distinct elements
 *              https://www.geeksforgeeks.org/third-largest-element-array-distinct-elements/
 * @reference   Find Second largest element in an array
 *              https://www.geeksforgeeks.org/find-second-largest-element-array/
 * @reference   Find the Second Largest Element in a Linked List
 *              https://www.geeksforgeeks.org/find-the-second-largest-element-in-a-linked-list/
 * @reference   Second Smallest Element in a Linked List
 *              https://www.geeksforgeeks.org/second-smallest-element-in-a-linked-list/
 * @reference   Why is it faster to process sorted array than an unsorted array ?
 *              https://www.geeksforgeeks.org/faster-process-sorted-array-unsorted-array/
 * @reference   Tournament Tree (Winner Tree) and Binary Heap
 *              https://www.geeksforgeeks.org/tournament-tree-and-binary-heap/
 *
 * Given an array and a number k where k is smaller than size of array,
 * we need to find the k’th smallest element in the given array.
 * It is given that all array elements are distinct.
 */
auto KthSmallest_Sort(ArrayType elements, const ArrayType::size_type K) {
    assert(K < elements.size());

    std::sort(elements.begin(), elements.end());
    return elements[K];
}


auto KthSmallest_MinHeap(ArrayType elements, ArrayType::size_type K) {
    assert(K < elements.size());

    const auto compare = std::greater<ArrayType::value_type> {};
    std::make_heap(elements.begin(), elements.end(), compare);

    auto end = elements.end();
    do {
        std::pop_heap(elements.begin(), end, compare);
        --end;
    } while (K--);

    return *end;
}


auto KthSmallest_MaxHeap(const ArrayType &elements, const ArrayType::size_type K) {
    assert(K < elements.size());

    auto iter = elements.cbegin() + K + 1;
    std::priority_queue<ArrayType::value_type> heap{elements.cbegin(), iter};
    for (; iter != elements.cend(); ++iter) {
        if (*iter < heap.top()) {
            heap.pop();
            heap.push(*iter);
        }
    }

    return heap.top();
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 9.2.
 */
auto KthSmallest_QuickSelect(ArrayType elements, const ArrayType::size_type K) {
    assert(K < elements.size());

    return *KthSmallest_QuickSelect(elements.begin(), elements.end(), elements.cbegin() + K);
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 9.2-3.
 */
auto KthSmallest_QuickSelect_Iterative(ArrayType elements, const ArrayType::size_type K) {
    assert(K < elements.size());

    auto begin = elements.begin();
    auto end = elements.end();
    const auto target = elements.cbegin() + K;
    while (begin != end) {
        const auto pivot = std::prev(end);
        const auto partition_point = std::partition(begin, pivot, [pivot](const auto v) {
            return v <= *pivot;
        });
        std::iter_swap(pivot, partition_point);

        if (target == partition_point) {
            break;
        } else if (partition_point > target) {
            end = partition_point;
        } else {
            begin = std::next(partition_point);
        }
    }

    return *target;
}


/**
 * @reference   Kth smallest element in the array using constant space when array can’t be modified
 *              https://www.geeksforgeeks.org/kth-smallest-element-in-the-array-using-constant-space-when-array-cant-be-modified/
 */
ArrayType::value_type KthSmallest_BinarySearch(const ArrayType::value_type min,
        const ArrayType::value_type max, const ArrayType &elements, const ArrayType::size_type K) {
    assert(K <= elements.size());

    const auto mid = (min + max) / 2;

    ArrayType::size_type less_than_mid = 0;
    auto equal_to_mid = 0;
    for (const auto elem : elements) {
        if (elem < mid) {
            ++less_than_mid;
        } else if (elem == mid) {
            ++equal_to_mid;
        }
    }

    if (less_than_mid >= K) {
        return KthSmallest_BinarySearch(min, mid - 1, elements, K);
    } else if (less_than_mid + equal_to_mid < K) {
        return KthSmallest_BinarySearch(mid + 1, max, elements, K);
    }
    return mid;
}

auto KthSmallest_BinarySearch(const ArrayType &elements, const ArrayType::size_type K) {
    const auto min_max = std::minmax_element(elements.cbegin(), elements.cend());
    return KthSmallest_BinarySearch(*(min_max.first), *(min_max.second), elements, K + 1);
}

}//namespace


const ArrayType VALUES1 = {12, 3, 5, 7, 19};
const ArrayType VALUES2 = {19, -10, 20, 14, 2, 16, 10};


SIMPLE_BENCHMARK(KthSmallest_Sort, VALUES1, 1);

SIMPLE_TEST(KthSmallest_Sort, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_Sort, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_Sort, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_Sort, TestSAMPLE3, 14, VALUES2, 3);


SIMPLE_BENCHMARK(KthSmallest_MinHeap, VALUES1, 1);

SIMPLE_TEST(KthSmallest_MinHeap, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_MinHeap, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_MinHeap, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_MinHeap, TestSAMPLE3, 14, VALUES2, 3);


SIMPLE_BENCHMARK(KthSmallest_MaxHeap, VALUES1, 1);

SIMPLE_TEST(KthSmallest_MaxHeap, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_MaxHeap, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_MaxHeap, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_MaxHeap, TestSAMPLE3, 14, VALUES2, 3);


SIMPLE_BENCHMARK(KthSmallest_QuickSelect, VALUES1, 1);

SIMPLE_TEST(KthSmallest_QuickSelect, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_QuickSelect, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_QuickSelect, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_QuickSelect, TestSAMPLE3, 14, VALUES2, 3);


SIMPLE_BENCHMARK(KthSmallest_QuickSelect_Iterative, VALUES1, 1);

SIMPLE_TEST(KthSmallest_QuickSelect_Iterative, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_QuickSelect_Iterative, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_QuickSelect_Iterative, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_QuickSelect_Iterative, TestSAMPLE3, 14, VALUES2, 3);


const ArrayType VALUES3 = {7, 10, 4, 3, 20, 15};
const ArrayType VALUES4 = {12, 3, 5, 7, 19};


SIMPLE_BENCHMARK(KthSmallest_BinarySearch, VALUES1, 1);

SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE3, 14, VALUES2, 3);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE4, 7, VALUES3, 2);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE5, 5, VALUES4, 1);
