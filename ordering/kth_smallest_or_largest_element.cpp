#include "common_header.h"

#include <queue>

namespace {
using ArrayType = std::vector<int>;

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
 * @reference   Why is it faster to process sorted array than an unsorted array ?
 *              https://www.geeksforgeeks.org/faster-process-sorted-array-unsorted-array/
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


auto KthSmallest_QuickSelect(const ArrayType::iterator begin, const ArrayType::iterator end,
                             const ArrayType::const_iterator target) {
    const auto pivot = std::prev(end);
    const auto partition_point = std::partition(begin, pivot, [pivot](const auto v) {
        return v <= *pivot;
    });
    std::iter_swap(pivot, partition_point);

    if (target == partition_point) {
        return partition_point;
    } else if (partition_point > target) {
        return KthSmallest_QuickSelect(begin, partition_point, target);
    } else {
        return KthSmallest_QuickSelect(std::next(partition_point), end, target);
    }
}
auto KthSmallest_QuickSelect(ArrayType elements, const ArrayType::size_type K) {
    assert(K < elements.size());

    return *KthSmallest_QuickSelect(elements.begin(), elements.end(), elements.cbegin() + K);
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
