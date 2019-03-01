#include "common_header.h"

#include <forward_list>
#include <stack>


namespace {
using ArrayType = std::vector<int>;

/** QuickSort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 7.
 * @reference   https://www.geeksforgeeks.org/quick-sort/
 * @reference   When does the worst case of Quicksort occur?
 *              https://www.geeksforgeeks.org/when-does-the-worst-case-of-quicksort-occur/
 * @reference   Generic Implementation of QuickSort Algorithm in C
 *              https://www.geeksforgeeks.org/generic-implementation-of-quicksort-algorithm-in-c/
 * @reference   C++ Program for QuickSort
 *              https://www.geeksforgeeks.org/cpp-program-for-quicksort/
 * @reference   Why quicksort is better than mergesort ?
 *              https://www.geeksforgeeks.org/quicksort-better-mergesort/
 * @reference   Why Quick Sort preferred for Arrays and Merge Sort for Linked Lists?
 *              https://www.geeksforgeeks.org/why-quick-sort-preferred-for-arrays-and-merge-sort-for-linked-lists/
 * @reference   Quick Sort vs Merge Sort
 *              https://www.geeksforgeeks.org/quick-sort-vs-merge-sort/
 * @reference   Iterative Quick Sort
 *              https://www.geeksforgeeks.org/iterative-quick-sort/
 * @reference   C Program for Iterative Quick Sort
 *              https://www.geeksforgeeks.org/c-program-for-iterative-quick-sort/
 * @reference   Tail Recursion
 *              https://www.geeksforgeeks.org/tail-recursion/
 * @reference   Tail Call Elimination
 *              https://www.geeksforgeeks.org/tail-call-elimination/
 * @reference   QuickSort Tail Call Optimization (Reducing worst case space to Log n )
 *              https://www.geeksforgeeks.org/quicksort-tail-call-optimization-reducing-worst-case-space-log-n/
 * @reference   Hoare’s vs Lomuto partition scheme in QuickSort
 *              https://www.geeksforgeeks.org/hoares-vs-lomuto-partition-scheme-quicksort/
 * Hoare’s scheme is more efficient than Lomuto’s partition scheme because it does three times fewer
 * swaps on average, and it creates efficient partitions even when all values are equal.
 * @reference   QuickSort using Random Pivoting
 *              https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
 * @reference   Stable QuickSort
 *              https://www.geeksforgeeks.org/stable-quicksort/
 * @reference   Stability in sorting algorithms
 *              https://www.geeksforgeeks.org/stability-in-sorting-algorithms/
 * @reference   Quick Sort
 *              http://users.monash.edu/~lloyd/tildeAlgDS/Sort/Quick/
 *
 * @complexity  T(n) = T(k) + T(n-k-1) + O(n)
 * @complexity  O(nLogn)
 */
auto partitionLomuto(const ArrayType::iterator begin, const ArrayType::size_type size) {
    const auto pivot = begin + (size - 1);
    ArrayType::size_type mid = 0;
    for (auto iter = begin; iter != pivot; ++iter) {
        if (*iter <= *pivot) {
            std::iter_swap(iter, (begin + mid++));
        }
    }
    std::iter_swap(pivot, begin + mid);

    return mid;
}

auto partitionHoare(const ArrayType::iterator begin, const ArrayType::size_type size) {
    const auto pivot = begin;
    auto left = begin;
    auto mid = size - 1;    //to avoid right - left, which is more expensive
    auto right = begin + mid;

    while (true) {
        for (; *left < *pivot; ++left);
        for (; *right > *pivot; --right, --mid);

        if (left >= right) {
            break;
        }
        std::iter_swap(left, right);
    }

    return mid;
}

auto partitionRandomizedHoare(const ArrayType::iterator begin, const ArrayType::size_type size) {
    const auto random_pivot_index = Random_Number<ArrayType::size_type>(0, size - 1);
    std::iter_swap(begin, begin + random_pivot_index);
    return partitionHoare(begin, size);
}

auto partitionStable(const ArrayType::iterator begin, const ArrayType::size_type size) {
    const auto pivot = begin + (size - 1);
    ArrayType::size_type mid = 0;
    ArrayType smaller, greater;

    for (auto iter = begin; iter != pivot; ++iter) {
        if (*iter <= *pivot) {
            smaller.push_back(std::move(*iter));
            ++mid;
        } else {
            greater.push_back(std::move(*iter));
        }
    }
    std::copy(std::make_move_iterator(smaller.begin()), std::make_move_iterator(smaller.end()), begin);
    const auto mid_iter = begin + mid;
    *mid_iter = std::move(*pivot);
    std::copy(std::make_move_iterator(greater.begin()), std::make_move_iterator(greater.end()),
              mid_iter + 1);

    return mid;
}


template <typename PartitionFunc>
void QuickSort(const ArrayType::iterator begin, const ArrayType::size_type size,
               const PartitionFunc partition) {
    if (size > 1) {
        const auto mid = partition(begin, size);
        QuickSort(begin, mid, partition);
        const auto mid_plus_one = mid + 1;
        QuickSort(begin + mid_plus_one, size - mid_plus_one, partition);
    }
}
auto QuickSortLomuto(ArrayType values) {
    QuickSort(values.begin(), values.size(), &partitionLomuto);
    return values;
}


auto QuickSortHoare(ArrayType values) {
    QuickSort(values.begin(), values.size(), &partitionHoare);
    return values;
}


auto QuickSortIterative(ArrayType values) {
    if (values.size() > 1) {
        std::stack<std::pair<const ArrayType::iterator, const ArrayType::size_type> > range_stack;
        range_stack.emplace(values.begin(), values.size());

        while (not range_stack.empty()) {
            const auto range = range_stack.top();
            range_stack.pop();
            const auto mid = partitionLomuto(range.first, range.second);
            if (mid > 1) {
                range_stack.emplace(range.first, mid);
            }
            const auto mid_plus_one = mid + 1;
            const auto right_size = range.second - mid_plus_one;
            if (right_size > 1) {
                range_stack.emplace(range.first + mid_plus_one, right_size);
            }
        }
    }

    return values;
}


auto QuickSortRandomizedHoare(ArrayType values) {
    QuickSort(values.begin(), values.size(), &partitionRandomizedHoare);
    return values;
}


auto QuickSortStable(ArrayType values) {
    QuickSort(values.begin(), values.size(), &partitionStable);
    return values;
}


/** QuickSort on Singly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
 */
auto GetLastNodeBeforeEnd(const std::forward_list<int> &values) {
    auto before_end = values.cbefore_begin();
    for (auto next = values.cbegin(); next != values.cend(); ++next, ++before_end);
    return before_end;
}
auto partitionSinglyLinkedList(std::forward_list<int> &values,
                               const std::forward_list<int>::const_iterator before_begin,
                               const std::forward_list<int>::const_iterator begin,
                               std::forward_list<int>::const_iterator &last) {
    const auto pivot = last;
    auto before_mid = before_begin;
    for (auto iter = begin; iter != pivot; ++iter) {
        if (*iter > *pivot) {
            values.splice_after(last, values, before_mid);
            ++last;
            iter = before_mid;
        } else {
            ++before_mid;
        }
    }

    return before_mid;
}
void QuickSortSinglyLinkedList(std::forward_list<int> &values,
                               const std::forward_list<int>::const_iterator before_begin,
                               std::forward_list<int>::const_iterator last) {
    const auto begin = std::next(before_begin);
    if (before_begin != last and begin != last) {
        const auto before_mid = partitionSinglyLinkedList(values, before_begin, begin, last);
        QuickSortSinglyLinkedList(values, before_begin, before_mid);
        QuickSortSinglyLinkedList(values, std::next(before_mid), last);
    }
}
auto QuickSortSinglyLinkedList(std::forward_list<int> values) {
    QuickSortSinglyLinkedList(values, values.cbefore_begin(), GetLastNodeBeforeEnd(values));
    return values;
}

auto TestQuickSortSinglyLinkedList(const ArrayType &values) {
    const auto sorted_values = QuickSortSinglyLinkedList({values.cbegin(), values.cend()});
    return ArrayType{sorted_values.cbegin(), sorted_values.cend()};
}


/** QuickSort on Doubly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/quicksort-for-linked-list/
 *
 * @highlight   The use of std::prev(std::list::end)
 */
auto partitionDoublyLinkedList(std::list<int> &values,
                               std::list<int>::const_iterator &begin,
                               const std::list<int>::const_iterator end) {
    const auto pivot = std::prev(end);
    for (auto iter = begin; iter != pivot;) {
        if (*iter > *pivot) {
            if (iter == begin) {
                ++begin;
            }
            values.splice(end, values, iter++);
        } else {
            ++iter;
        }
    }

    return pivot;
}
void QuickSortDoublyLinkedList(std::list<int> &values,
                               std::list<int>::const_iterator begin,
                               const std::list<int>::const_iterator end) {
    if (begin != end and std::next(begin) != end) {
        auto mid = partitionDoublyLinkedList(values, begin, end);
        QuickSortDoublyLinkedList(values, begin, mid);
        QuickSortDoublyLinkedList(values, ++mid, end);
    }
}
auto QuickSortDoublyLinkedList(std::list<int> values) {
    QuickSortDoublyLinkedList(values, values.cbegin(), values.cend());
    return values;
}

auto TestQuickSortDoublyLinkedList(const ArrayType &values) {
    const auto sorted_values = QuickSortDoublyLinkedList({values.cbegin(), values.cend()});
    return ArrayType{sorted_values.cbegin(), sorted_values.cend()};
}


/** 3-Way QuickSort (Dutch National Flag)
 *
 * @reference   https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/
 * @reference   Quick Sort 3 Way
 *              https://www.toptal.com/developers/sorting-algorithms/quick-sort-3-way
 * @reference   Dual pivot Quicksort
 *              https://www.geeksforgeeks.org/dual-pivot-quicksort/
 */
auto partition3Way(const ArrayType::iterator begin, const ArrayType::iterator end) {
    auto smallers_end = begin;
    auto greaters_begin = end;
    for (auto equals_end = std::next(smallers_end); equals_end != greaters_begin;) {
        if (*equals_end < *smallers_end) {
            std::iter_swap(smallers_end++, equals_end++);
        } else if (*equals_end == *smallers_end) {
            ++equals_end;
        } else {
            std::iter_swap(equals_end, --greaters_begin);
        }
    }

    return std::make_pair(smallers_end, greaters_begin);
}
void QuickSort3Way(const ArrayType::iterator begin, const ArrayType::iterator end) {
    if (begin != end and std::next(begin) != end) {
        const auto mid_pair = partition3Way(begin, end);
        QuickSort3Way(begin, mid_pair.first);
        QuickSort3Way(mid_pair.second, end);
    }
}
auto QuickSort3Way(ArrayType values) {
    QuickSort3Way(values.begin(), values.end());
    return values;
}


auto partitionDualPivots(const ArrayType::iterator begin, const ArrayType::iterator end) {
    const auto smaller_pivot = begin;
    auto smallers_end = std::next(begin);
    auto greaters_begin = std::prev(end);
    const auto greater_pivot = greaters_begin;

    if (*smaller_pivot > *greater_pivot) {
        std::iter_swap(smaller_pivot, greater_pivot);
    }

    for (auto equals_end = smallers_end; equals_end != greaters_begin;) {
        if (*equals_end < *smaller_pivot) {
            std::iter_swap(smallers_end++, equals_end++);
        } else if (*equals_end < *greater_pivot) {
            ++equals_end;
        } else {
            std::iter_swap(equals_end, --greaters_begin);
        }
    }

    std::iter_swap(smaller_pivot, std::prev(smallers_end));
    std::iter_swap(greater_pivot, greaters_begin);

    return std::make_pair(smallers_end, greaters_begin);
}
void QuickSortDualPivots(const ArrayType::iterator begin, const ArrayType::iterator end) {
    if (begin != end and std::next(begin) != end) {
        const auto mid_pair = partitionDualPivots(begin, end);
        QuickSortDualPivots(begin, mid_pair.first);
        QuickSortDualPivots(mid_pair.first, mid_pair.second);
        QuickSortDualPivots(mid_pair.second, end);
    }
}
auto QuickSortDualPivots(ArrayType values) {
    QuickSortDualPivots(values.begin(), values.end());
    return values;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};

SIMPLE_BENCHMARK(QuickSortLomuto, VALUES5);

SIMPLE_TEST(QuickSortLomuto, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortLomuto, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortLomuto, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortLomuto, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortLomuto, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(QuickSortIterative, VALUES5);

SIMPLE_TEST(QuickSortIterative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortIterative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortIterative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortIterative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortIterative, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(QuickSortHoare, VALUES5);

SIMPLE_TEST(QuickSortHoare, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortHoare, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortHoare, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortHoare, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortHoare, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(QuickSortRandomizedHoare, VALUES5);

SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortRandomizedHoare, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(QuickSortStable, VALUES5);

SIMPLE_TEST(QuickSortStable, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortStable, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortStable, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortStable, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortStable, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(TestQuickSortSinglyLinkedList, VALUES5);

SIMPLE_TEST(TestQuickSortSinglyLinkedList, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(TestQuickSortSinglyLinkedList, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(TestQuickSortSinglyLinkedList, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(TestQuickSortSinglyLinkedList, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(TestQuickSortSinglyLinkedList, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(TestQuickSortDoublyLinkedList, VALUES5);

SIMPLE_TEST(TestQuickSortDoublyLinkedList, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(TestQuickSortDoublyLinkedList, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(TestQuickSortDoublyLinkedList, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(TestQuickSortDoublyLinkedList, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(TestQuickSortDoublyLinkedList, TestSAMPLE5, EXPECTED5, VALUES5);


const ArrayType VALUES6 = {4, 9, 4, 4, 1, 9, 4, 4, 9, 4, 4, 1, 4};
const ArrayType EXPECTED6 = {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9};


SIMPLE_BENCHMARK(QuickSort3Way, VALUES5);

SIMPLE_TEST(QuickSort3Way, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSort3Way, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSort3Way, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSort3Way, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSort3Way, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(QuickSort3Way, TestSAMPLE6, EXPECTED6, VALUES6);


const ArrayType VALUES7 = {24, 8, 42, 75, 29, 77, 38, 57};
const ArrayType EXPECTED7 = {8, 24, 29, 38, 42, 57, 75, 77};


SIMPLE_BENCHMARK(QuickSortDualPivots, VALUES5);

SIMPLE_TEST(QuickSortDualPivots, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortDualPivots, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortDualPivots, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortDualPivots, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortDualPivots, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(QuickSortDualPivots, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(QuickSortDualPivots, TestSAMPLE7, EXPECTED7, VALUES7);
