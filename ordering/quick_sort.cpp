#include "common_header.h"

#include <future>

#include "partition.h"


namespace {

using ArrayType = std::vector<int>;

/** QuickSort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 7.
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
 *
 * Hoare's scheme is more efficient than Lomuto's partition scheme because it does three
 * times fewer swaps on average, and it creates efficient partitions even when all values
 * are equal.
 *
 * @reference   QuickSort using Random Pivoting
 *              https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
 * @reference   Stable QuickSort
 *              https://www.geeksforgeeks.org/stable-quicksort/
 * @reference   Stability in sorting algorithms
 *              https://www.geeksforgeeks.org/stability-in-sorting-algorithms/
 * @reference   Quick Sort
 *              http://users.monash.edu/~lloyd/tildeAlgDS/Sort/Quick/
 * @reference   Can QuickSort be implemented in O(nLogn) worst case time complexity?
 *              https://www.geeksforgeeks.org/can-quicksort-implemented-onlogn-worst-case-time-complexity/
 * @reference   C Program to Sort an array of names or strings
 *              https://www.geeksforgeeks.org/c-program-sort-array-names-strings/
 * @reference   Print array of strings in sorted order without copying one string into another
 *              https://www.geeksforgeeks.org/print-array-strings-sorted-order-without-copying-one-string-another/
 *
 * @reference   Lower bound for comparison based sorting algorithms
 *              https://www.geeksforgeeks.org/lower-bound-on-comparison-based-sorting-algorithms/
 * @reference   Time Complexities of all Sorting Algorithms
 *              https://www.geeksforgeeks.org/time-complexities-of-all-sorting-algorithms/
 * @reference   Asymptotic Analysis and comparison of sorting algorithms
 *              https://www.geeksforgeeks.org/asymptotic-analysis-comparison-sorting-algorithms/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 8.
 *
 * @complexity  T(n) = T(k) + T(n-k-1) + O(n)
 * @complexity  O(nLogn)
 */
auto partition_Lomuto(const ArrayType::iterator begin, const ArrayType::iterator end) {
    const auto pivot = std::prev(end);
    const auto mid = Partition<ArrayType>(begin, pivot, [pivot](const auto v) {
        return v <= *pivot;
    });
    std::iter_swap(pivot, mid);

    return mid;
}

auto partition_Hoare(const ArrayType::iterator begin, const ArrayType::iterator end) {
    const auto pivot = begin;
    auto left = begin;
    auto right = std::prev(end);

    while (true) {
        for (; *left < *pivot; ++left);
        for (; *right > *pivot; --right);

        if (left >= right) {
            break;
        }
        std::iter_swap(left, right);
    }

    return right;
}

auto partition_RandomizedHoare(const ArrayType::iterator begin,
                               const ArrayType::iterator end) {
    const auto random_pivot_index = Random_Number(0, end - begin - 1);
    std::iter_swap(begin, begin + random_pivot_index);
    return partition_Hoare(begin, end);
}

auto partitionStable(const ArrayType::iterator begin, const ArrayType::iterator end) {
    const auto pivot = std::prev(end);
    auto mid = begin;
    ArrayType smaller, greater;

    for (auto iter = begin; iter != pivot; ++iter) {
        if (*iter <= *pivot) {
            smaller.push_back(std::move(*iter));
            ++mid;
        } else {
            greater.push_back(std::move(*iter));
        }
    }
    std::copy(std::make_move_iterator(smaller.begin()),
              std::make_move_iterator(smaller.end()), begin);
    *mid = std::move(*pivot);
    std::copy(std::make_move_iterator(greater.begin()),
              std::make_move_iterator(greater.end()),
              std::next(mid));

    return mid;
}


template <typename PartitionFunc>
void QuickSort(const ArrayType::iterator begin, const ArrayType::iterator end,
               const PartitionFunc partition) {
    if (isThereMoreThanOneElements(begin, end)) {
        const auto mid = partition(begin, end);
        QuickSort(begin, mid, partition);
        QuickSort(std::next(mid), end, partition);
    }
}
auto QuickSort_Lomuto(ArrayType values) {
    QuickSort(values.begin(), values.end(), &partition_Lomuto);
    return values;
}


auto QuickSort_Hoare(ArrayType values) {
    QuickSort(values.begin(), values.end(), &partition_Hoare);
    return values;
}


auto QuickSort_Iterative(ArrayType values) {
    if (values.size() > 1) {
        std::stack<std::pair<const ArrayType::iterator, const ArrayType::iterator>> range_stack;
        range_stack.emplace(values.begin(), values.end());

        while (not range_stack.empty()) {
            const auto [lower, upper] = range_stack.top();
            range_stack.pop();
            const auto mid = partition_Lomuto(lower, upper);
            if (isThereMoreThanOneElements(lower, mid)) {
                range_stack.emplace(lower, mid);
            }
            const auto mid_plus_one = mid + 1;
            if (isThereMoreThanOneElements(mid_plus_one, upper)) {
                range_stack.emplace(mid_plus_one, upper);
            }
        }
    }

    return values;
}


auto QuickSort_RandomizedHoare(ArrayType values) {
    QuickSort(values.begin(), values.end(), &partition_RandomizedHoare);
    return values;
}


auto QuickSortStable(ArrayType values) {
    QuickSort(values.begin(), values.end(), &partitionStable);
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
void quickSortSinglyLinkedList(std::forward_list<int> &values,
                               const std::forward_list<int>::const_iterator before_begin,
                               std::forward_list<int>::const_iterator last) {
    const auto begin = std::next(before_begin);
    if (before_begin != last and begin != last) {
        const auto before_mid = Partition_SinglyList(values, before_begin, begin, last);
        quickSortSinglyLinkedList(values, before_begin, before_mid);
        quickSortSinglyLinkedList(values, std::next(before_mid), last);
    }
}
auto QuickSortSinglyLinkedList(std::forward_list<int> values) {
    quickSortSinglyLinkedList(values, values.cbefore_begin(), GetLastNodeBeforeEnd(values));
    return values;
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
void quickSortDoublyLinkedList(std::list<int> &values,
                               std::list<int>::const_iterator begin,
                               const std::list<int>::const_iterator end) {
    if (isThereMoreThanOneElements(begin, end)) {
        auto mid = partitionDoublyLinkedList(values, begin, end);
        quickSortDoublyLinkedList(values, begin, mid);
        quickSortDoublyLinkedList(values, ++mid, end);
    }
}
auto QuickSortDoublyLinkedList(std::list<int> values) {
    quickSortDoublyLinkedList(values, values.cbegin(), values.cend());
    return values;
}


/**
 * @reference   Anthony Williams. C++ Concurrency in Action: Practical Multithreading, 1st Edition.
 *              Section 4.4.1.
 */
auto QuickSortDoublyLinkedList_Sequential(std::list<int> values) {
    if (values.size() < 2) {
        return values;
    }

    std::list<int> result;
    result.splice(result.cbegin(), values, values.cbegin());
    const auto &pivot = *result.cbegin();

    const auto divide_point = std::partition(values.begin(), values.end(),
    [&pivot](const auto & t) {
        return t < pivot;
    });

    std::list<int> lower_part;
    lower_part.splice(lower_part.cend(), values, values.cbegin(), divide_point);

    auto new_lowers = QuickSortDoublyLinkedList_Sequential(std::move(lower_part));
    auto new_highers = QuickSortDoublyLinkedList_Sequential(std::move(values));

    result.splice(result.cend(), new_highers);
    result.splice(result.cbegin(), new_lowers);

    return result;
}


auto QuickSortDoublyLinkedList_NaiveAsync(std::list<int> values) {
    if (values.size() < 2) {
        return values;
    }

    std::list<int> result;
    result.splice(result.cbegin(), values, values.cbegin());
    const auto &pivot = *result.cbegin();

    const auto divide_point = std::partition(values.begin(), values.end(),
    [&pivot](const auto & t) {
        return t < pivot;
    });

    std::list<int> lower_part;
    lower_part.splice(lower_part.cend(), values, values.cbegin(), divide_point);

    auto new_lowers =
        std::async(QuickSortDoublyLinkedList_NaiveAsync, std::move(lower_part));
    auto new_highers = QuickSortDoublyLinkedList_NaiveAsync(std::move(values));

    result.splice(result.cend(), new_highers);
    result.splice(result.cbegin(), new_lowers.get());

    return result;
}


/** 3-Way QuickSort (Dutch National Flag)
 *
 * @reference   https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/
 * @reference   Quick Sort 3 Way
 *              https://www.toptal.com/developers/sorting-algorithms/quick-sort-3-way
 * @reference   Dual pivot Quicksort
 *              https://www.geeksforgeeks.org/dual-pivot-quicksort/
 */
auto partition_3Way(const ArrayType::iterator begin, const ArrayType::iterator end) {
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

    return std::pair(smallers_end, greaters_begin);
}
void QuickSort_3Way(const ArrayType::iterator begin, const ArrayType::iterator end) {
    if (isThereMoreThanOneElements(begin, end)) {
        const auto mid_pair = partition_3Way(begin, end);
        QuickSort_3Way(begin, mid_pair.first);
        QuickSort_3Way(mid_pair.second, end);
    }
}
auto QuickSort_3Way(ArrayType values) {
    QuickSort_3Way(values.begin(), values.end());
    return values;
}


auto partition_DualPivots(const ArrayType::iterator begin,
                          const ArrayType::iterator end) {
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

    return std::pair(smallers_end, greaters_begin);
}
void QuickSort_DualPivots(const ArrayType::iterator begin,
                          const ArrayType::iterator end) {
    if (isThereMoreThanOneElements(begin, end)) {
        const auto mid_pair = partition_DualPivots(begin, end);
        QuickSort_DualPivots(begin, mid_pair.first);
        QuickSort_DualPivots(mid_pair.first, mid_pair.second);
        QuickSort_DualPivots(mid_pair.second, end);
    }
}
auto QuickSort_DualPivots(ArrayType values) {
    QuickSort_DualPivots(values.begin(), values.end());
    return values;
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

constexpr InitializerType VALUES1 = {};
constexpr InitializerType VALUES2 = {1};
constexpr InitializerType VALUES3 = {1, 2};
constexpr InitializerType VALUES4 = {2, 3, 1};
constexpr InitializerType EXPECTED4 = {1, 2, 3};
constexpr InitializerType VALUES5 = {4, 3, 2, 1};
constexpr InitializerType EXPECTED5 = {1, 2, 3, 4};


THE_BENCHMARK(QuickSort_Lomuto, VALUES5);

SIMPLE_TEST(QuickSort_Lomuto, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSort_Lomuto, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSort_Lomuto, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSort_Lomuto, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSort_Lomuto, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(QuickSort_Iterative, VALUES5);

SIMPLE_TEST(QuickSort_Iterative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSort_Iterative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSort_Iterative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSort_Iterative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSort_Iterative, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(QuickSort_Hoare, VALUES5);

SIMPLE_TEST(QuickSort_Hoare, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSort_Hoare, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSort_Hoare, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSort_Hoare, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSort_Hoare, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(QuickSort_RandomizedHoare, VALUES5);

SIMPLE_TEST(QuickSort_RandomizedHoare, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSort_RandomizedHoare, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSort_RandomizedHoare, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSort_RandomizedHoare, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSort_RandomizedHoare, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(QuickSortStable, VALUES5);

SIMPLE_TEST(QuickSortStable, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortStable, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortStable, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortStable, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortStable, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(QuickSortSinglyLinkedList, VALUES5);

SIMPLE_TEST(QuickSortSinglyLinkedList, TestSample1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortSinglyLinkedList, TestSample2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortSinglyLinkedList, TestSample3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortSinglyLinkedList, TestSample4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortSinglyLinkedList, TestSample5, EXPECTED5, VALUES5);


THE_BENCHMARK(QuickSortDoublyLinkedList, VALUES5);

SIMPLE_TEST(QuickSortDoublyLinkedList, TestSample1, VALUES1,
            VALUES1);
SIMPLE_TEST(QuickSortDoublyLinkedList, TestSample2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortDoublyLinkedList, TestSample3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortDoublyLinkedList, TestSample4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortDoublyLinkedList, TestSample5, EXPECTED5, VALUES5);


THE_BENCHMARK(QuickSortDoublyLinkedList_Sequential, VALUES5);

SIMPLE_TEST(QuickSortDoublyLinkedList_Sequential, TestSample1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortDoublyLinkedList_Sequential, TestSample2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortDoublyLinkedList_Sequential, TestSample3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortDoublyLinkedList_Sequential, TestSample4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortDoublyLinkedList_Sequential, TestSample5, EXPECTED5, VALUES5);


THE_BENCHMARK(QuickSortDoublyLinkedList_NaiveAsync, VALUES5);

SIMPLE_TEST(QuickSortDoublyLinkedList_NaiveAsync, TestSample1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSortDoublyLinkedList_NaiveAsync, TestSample2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSortDoublyLinkedList_NaiveAsync, TestSample3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSortDoublyLinkedList_NaiveAsync, TestSample4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSortDoublyLinkedList_NaiveAsync, TestSample5, EXPECTED5, VALUES5);


constexpr InitializerType VALUES6 = {4, 9, 4, 4, 1, 9, 4, 4, 9, 4, 4, 1, 4};
constexpr InitializerType EXPECTED6 = {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9};


THE_BENCHMARK(QuickSort_3Way, VALUES5);

SIMPLE_TEST(QuickSort_3Way, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSort_3Way, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSort_3Way, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSort_3Way, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSort_3Way, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(QuickSort_3Way, TestSAMPLE6, EXPECTED6, VALUES6);


constexpr InitializerType VALUES7 = {24, 8, 42, 75, 29, 77, 38, 57};
constexpr InitializerType EXPECTED7 = {8, 24, 29, 38, 42, 57, 75, 77};


THE_BENCHMARK(QuickSort_DualPivots, VALUES5);

SIMPLE_TEST(QuickSort_DualPivots, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(QuickSort_DualPivots, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(QuickSort_DualPivots, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(QuickSort_DualPivots, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(QuickSort_DualPivots, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(QuickSort_DualPivots, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(QuickSort_DualPivots, TestSAMPLE7, EXPECTED7, VALUES7);
