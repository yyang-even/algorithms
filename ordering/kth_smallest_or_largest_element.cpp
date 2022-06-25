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
 * @reference   Why is it faster to process sorted array than an unsorted array ?
 *              https://www.geeksforgeeks.org/faster-process-sorted-array-unsorted-array/
 * @reference   Tournament Tree (Winner Tree) and Binary Heap
 *              https://www.geeksforgeeks.org/tournament-tree-and-binary-heap/
 *
 * Given an array and a number k where k is smaller than size of array, we need to find the k'th
 * smallest element in the given array. It is given that all array elements are distinct.
 *
 * @reference   Kth Largest Element in an Array
 *              https://leetcode.com/problems/kth-largest-element-in-an-array/
 *
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 */
inline auto KthSmallest_Sort(ArrayType elements, const ArrayType::size_type K) {
    assert(K < elements.size());

    std::sort(elements.begin(), elements.end());
    return elements[K];
}


auto KthSmallest_MinHeap(ArrayType elements, ArrayType::size_type K) {
    assert(K < elements.size());

    static constexpr auto compare = std::greater<ArrayType::value_type> {};
    std::make_heap(elements.begin(), elements.end(), compare);

    auto end = elements.end();
    do {
        std::pop_heap(elements.begin(), end--, compare);
    } while (K--);

    return *end;
}


auto KthSmallest_MaxHeap(const ArrayType &elements, const ArrayType::size_type K) {
    assert(K < elements.size());

    auto iter = elements.cbegin() + K + 1;
    std::priority_queue heap {elements.cbegin(), iter};
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
 *              Introduction to Algorithms, Third Edition. Section 9.2.
 * @reference   Quickselect Algorithm
 *              https://www.geeksforgeeks.org/quickselect-algorithm/
 */
inline auto KthSmallest_QuickSelect(ArrayType elements, const ArrayType::size_type K) {
    assert(K < elements.size());

    return *KthSmallest_QuickSelect(elements.begin(), elements.end(), elements.cbegin() + K);
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 9.2-3.
 * @reference   QuickSelect (A Simple Iterative Implementation)
 *              https://www.geeksforgeeks.org/quickselect-a-simple-iterative-implementation/
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
                                               const ArrayType::value_type max,
                                               const ArrayType &elements,
                                               const ArrayType::size_type K) {
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

inline auto KthSmallest_BinarySearch(const ArrayType &elements, const ArrayType::size_type K) {
    assert(not elements.empty());

    const auto [min, max] = std::minmax_element(elements.cbegin(), elements.cend());
    return KthSmallest_BinarySearch(*min, *max, elements, K + 1);
}


/**
 * @reference   Third Maximum Number
 *              https://leetcode.com/problems/third-maximum-number/
 *
 * Given integer array nums, return the third maximum number in this array. If the third maximum
 * does not exist, return the maximum number.
 * Follow up: Can you find an O(n) solution?
 */
auto ThirdMax(const ArrayType &nums) {
    auto largest = LONG_MIN;
    auto second_max = LONG_MIN;
    auto third_max = LONG_MIN;

    for (const auto i : nums) {
        if (i <= third_max or i == second_max or i == largest) {
            continue;
        }

        third_max = i;
        if (third_max > second_max) {
            std::swap(third_max, second_max);
        }
        if (second_max > largest) {
            std::swap(second_max, largest);
        }
    }

    return third_max > LONG_MIN ? third_max : largest;
}


/**
 * @reference   Second Largest Digit in a String
 *              https://leetcode.com/problems/second-largest-digit-in-a-string/
 *
 * Given an alphanumeric string s, return the second largest numerical digit that appears in s,
 * or -1 if it does not exist.
 * An alphanumeric string is a string consisting of lowercase English letters and digits.
 *
 * @reference   Find Second largest element in an array
 *              https://www.geeksforgeeks.org/find-second-largest-element-array/
 * @reference   Find the Second Largest Element in a Linked List
 *              https://www.geeksforgeeks.org/find-the-second-largest-element-in-a-linked-list/
 * @reference   Second Smallest Element in a Linked List
 *              https://www.geeksforgeeks.org/second-smallest-element-in-a-linked-list/
 */
constexpr auto SecondHighest(const std::string_view s) {
    int first = -1;
    int second = -1;
    for (const auto c : s) {
        if (std::isdigit(c)) {
            const auto digit = c - '0';
            if (digit > first) {
                second = std::exchange(first, digit);
            } else if (digit != first and digit > second) {
                second = digit;
            }
        }
    }

    return second;
}


constexpr auto SecondHighest_CountingSort(const std::string_view s) {
    int counts[10] = {};
    for (const auto c : s) {
        if (std::isdigit(c)) {
            ++counts[c - '0'];
        }
    }

    int digit_seen = 0;
    for (int i = 9; i >= 0; --i) {
        if (counts[i]) {
            if (digit_seen++) {
                return i;
            }
        }
    }

    return -1;
}

} //namespace


const ArrayType VALUES1 = {12, 3, 5, 7, 19};
const ArrayType VALUES2 = {19, -10, 20, 14, 2, 16, 10};


THE_BENCHMARK(KthSmallest_Sort, VALUES1, 1);

SIMPLE_TEST(KthSmallest_Sort, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_Sort, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_Sort, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_Sort, TestSAMPLE3, 14, VALUES2, 3);


THE_BENCHMARK(KthSmallest_MinHeap, VALUES1, 1);

SIMPLE_TEST(KthSmallest_MinHeap, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_MinHeap, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_MinHeap, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_MinHeap, TestSAMPLE3, 14, VALUES2, 3);


THE_BENCHMARK(KthSmallest_MaxHeap, VALUES1, 1);

SIMPLE_TEST(KthSmallest_MaxHeap, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_MaxHeap, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_MaxHeap, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_MaxHeap, TestSAMPLE3, 14, VALUES2, 3);


THE_BENCHMARK(KthSmallest_QuickSelect, VALUES1, 1);

SIMPLE_TEST(KthSmallest_QuickSelect, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_QuickSelect, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_QuickSelect, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_QuickSelect, TestSAMPLE3, 14, VALUES2, 3);


THE_BENCHMARK(KthSmallest_QuickSelect_Iterative, VALUES1, 1);

SIMPLE_TEST(KthSmallest_QuickSelect_Iterative, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_QuickSelect_Iterative, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_QuickSelect_Iterative, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_QuickSelect_Iterative, TestSAMPLE3, 14, VALUES2, 3);


const ArrayType VALUES3 = {7, 10, 4, 3, 20, 15};
const ArrayType VALUES4 = {12, 3, 5, 7, 19};


THE_BENCHMARK(KthSmallest_BinarySearch, VALUES1, 1);

SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE0, 3, VALUES1, 0);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE1, 5, VALUES1, 1);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE2, 19, VALUES1, VALUES1.size() - 1);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE3, 14, VALUES2, 3);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE4, 7, VALUES3, 2);
SIMPLE_TEST(KthSmallest_BinarySearch, TestSAMPLE5, 5, VALUES4, 1);


const ArrayType SAMPLE1 = {1, 2};
const ArrayType SAMPLE2 = {3, 2, 1};
const ArrayType SAMPLE3 = {2, 2, 3, 1};


THE_BENCHMARK(ThirdMax, VALUES1);

SIMPLE_TEST(ThirdMax, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(ThirdMax, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(ThirdMax, TestSAMPLE3, 1, SAMPLE3);


THE_BENCHMARK(SecondHighest, "dfa12321afd");

SIMPLE_TEST(SecondHighest, TestSAMPLE1, 2, "dfa12321afd");
SIMPLE_TEST(SecondHighest, TestSAMPLE2, -1, "abc1111");


THE_BENCHMARK(SecondHighest_CountingSort, "dfa12321afd");

SIMPLE_TEST(SecondHighest_CountingSort, TestSAMPLE1, 2, "dfa12321afd");
SIMPLE_TEST(SecondHighest_CountingSort, TestSAMPLE2, -1, "abc1111");
