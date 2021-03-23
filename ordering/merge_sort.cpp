#include "common_header.h"


#include "merge_two_sorted_arrays.h"
#include "merge_k_sorted_array.h"

#include "data_structure/linked_list/middle_of_singly_linked_list.h"


namespace {

#include "merge_sort.h"

using ArrayType = std::vector<int>;


/** Merge Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 2.3.
 * @reference   https://www.geeksforgeeks.org/merge-sort/
 * @reference   C Program for Merge Sort
 *              https://www.geeksforgeeks.org/c-program-for-merge-sort/
 * @reference   In-Place Merge Sort
 *              https://www.geeksforgeeks.org/in-place-merge-sort/
 *
 * @reference   Sort an array when two halves are sorted
 *              https://www.geeksforgeeks.org/sort-array-two-halves-sorted/
 *
 * Given an integer array of which both first half and second half are sorted. Task is to
 * merge two sorted halves of array into single sorted array.
 *
 * @complexity: O(n*lgn)
 */
void Merge(const ArrayType::iterator begin, const ArrayType::iterator middle,
           const ArrayType::iterator end) {
    const auto L = ArrayType(begin, middle);
    const auto R = ArrayType(middle, end);

    MergeTwoSortedArrays(L, R, begin);
}
auto MergeSort(ArrayType values) {
    MergeSort<ArrayType>(values.begin(), values.size(), Merge);
    return values;
}


/** Iterative Merge Sort
 *
 * @reference   https://www.geeksforgeeks.org/iterative-merge-sort/
 * @reference   C Program for Iterative Merge Sort
 *              https://www.geeksforgeeks.org/c-program-for-iterative-merge-sort/
 *
 * Merge subarrays in bottom up manner. First merge subarrays of size 1 to create sorted
 * subarrays of size 2, then merge subarrays of size 2 to create sorted subarrays of size
 * 4, and so on.
 */
auto MergeSort_Iterative(ArrayType values) {
    for (ArrayType::size_type current_size = 1;
         current_size < values.size();
         current_size *= 2) {
        for (ArrayType::size_type i = 0ul; i < (values.size() - 1);) {
            const auto begin = values.begin() + i;
            const auto mid = begin + current_size;
            i += current_size * 2;
            const auto end = values.begin() + std::min(i, values.size());
            Merge(begin, mid, end);
        }
    }
    return values;
}


/** Merge Sort with O(1) extra space merge and O(n lg n) time
 *
 * @reference   https://www.geeksforgeeks.org/merge-sort-with-o1-extra-space-merge-and-on-lg-n-time/
 *
 * How to modify the algorithm so that merge works in O(1) extra space and algorithm still
 * works in O(n Log n) time.
 */
void Merge_O1(const ArrayType::iterator begin, const ArrayType::iterator middle,
              const ArrayType::iterator end, const ArrayType::value_type max) {
    auto L_iter = begin;
    auto R_iter = middle;
    auto iter = begin;
    for (; (L_iter != middle) and (R_iter != end); ++iter) {
        if (*L_iter % max <= *R_iter) {
            *iter = *iter + (*L_iter++ % max) * max;
        } else {
            *iter = *iter + (*R_iter++) * max;
        }
    }

    std::transform(L_iter, middle, iter, iter,
    [max](const ArrayType::value_type v1, const ArrayType::value_type v2) {
        return v2 + (v1 % max) * max;
    });

    // Restore to original values
    std::transform(begin, R_iter, begin, [max](const ArrayType::value_type v) {
        return v / max;
    });
}
auto MergeSort_O1(ArrayType values) {
    if (not values.empty()) {
        const auto max_element = *std::max_element(values.cbegin(), values.cend()) + 1;
        MergeSort<ArrayType>(values.begin(), values.size(),
                             [max_element](const ArrayType::iterator begin,
                                           const ArrayType::iterator middle,
        const ArrayType::iterator end) {
            Merge_O1(begin, middle, end, max_element);
        });
    }
    return values;
}


/** The external merge sort algorithm
 *
 * @reference   External Sorting
 *              https://www.geeksforgeeks.org/external-sorting/
 *
 * External sorting is a term for a class of sorting algorithms that can handle massive
 * amounts of data. External sorting is required when the data being sorted do not fit
 * into the main memory of a computing device (usually RAM) and instead they must reside
 * in the slower external memory (usually a hard drive). External sorting typically uses
 * a hybrid sort-merge strategy. In the sorting phase, chunks of data small enough to fit
 * in main memory are read, sorted, and written out to a temporary file. In the merge
 * phase, the sorted sub-files are combined into a single larger file.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.4.
 */


/** Merge Sort for Linked Lists
 *
 * @reference   https://www.geeksforgeeks.org/merge-sort-for-linked-list/
 * @reference   C Program for Merge Sort for Linked Lists
 *              https://www.geeksforgeeks.org/c-program-for-merge-sort-for-linked-lists/
 */
void MergeSort_SinglyListHelper(std::forward_list<int> &l) {
    if (not l.empty() and std::next(l.cbegin()) != l.cend()) {
        const auto before_mid = GetBeforeMiddle_TwoPointersSTL(l.cbefore_begin(), l.cend());
        std::forward_list<int> right;
        right.splice_after(right.cbefore_begin(), l, before_mid, l.cend());
        MergeSort_SinglyListHelper(l);
        MergeSort_SinglyListHelper(right);
        l.merge(std::move(right));
    }
}
auto MergeSort_SinglyList(std::forward_list<int> values) {
    MergeSort_SinglyListHelper(values);
    return values;
}


/** Iterative Merge Sort for Linked List
 *
 * @reference   https://www.geeksforgeeks.org/iterative-merge-sort-for-linked-list/
 */
auto MergeSort_SinglyList_Iterative(std::forward_list<int> values) {
    if (not values.empty()) {
        std::vector<std::forward_list<int>> lists;
        while (not values.empty()) {
            lists.emplace_back();
            lists.back().splice_after(lists.back().cbefore_begin(), values, values.cbefore_begin());
        }
        for (std::size_t gap = 1; gap <= lists.size();) {
            const auto step = gap * 2;
            std::size_t left_index = 0;
            for (auto right_index = left_index + gap;
                 right_index < lists.size() and left_index < lists.size();
                 left_index += step, right_index += step) {
                auto &left_list = lists[left_index];
                auto &right_list = lists[right_index];
                left_list.merge(std::move(right_list));
            }
            gap = step;
        }
        values = std::move(lists.front());
    }

    return values;
}


/** Merge Sort for Doubly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
 */
void MergeSort_DoublyListHelper(std::list<int> &l) {
    if (l.size() > 1) {
        auto mid = std::next(l.cbegin(), l.size() / 2);
        std::list<int> right;
        right.splice(right.cend(), l, mid, l.cend());
        MergeSort_DoublyListHelper(l);
        MergeSort_DoublyListHelper(right);
        l.merge(std::move(right));
    }
}
auto MergeSort_DoublyList(std::list<int> values) {
    MergeSort_DoublyListHelper(values);
    return values;
}


/** 3-way Merge Sort
 *
 * @reference   https://www.geeksforgeeks.org/3-way-merge-sort/
 */
void Merge_3Way(const ArrayType::iterator begin, const ArrayType::iterator middle1,
                const ArrayType::iterator middle2, const ArrayType::iterator end) {
    MergeKSortedArrays({ArrayType(begin, middle1), ArrayType(middle1, middle2), ArrayType(middle2, end)},
                       begin);
}

void MergeSort_3Way(const ArrayType::iterator begin, const ArrayType::size_type n) {
    if (n > 1) {
        const auto mid = n / 3;
        const auto mid_begin1 = begin + mid;
        const auto mid_begin2 = mid_begin1 + mid + 1;

        MergeSort_3Way(begin, mid);
        MergeSort_3Way(mid_begin1, mid + 1);
        MergeSort_3Way(mid_begin2, n - 2 * mid - 1);

        Merge_3Way(begin, mid_begin1, mid_begin2, begin + n);
    }
}

auto MergeSort_3Way(ArrayType values) {
    MergeSort_3Way(values.begin(), values.size());
    return values;
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

const InitializerType VALUES1 = {};
const InitializerType VALUES2 = {1};
const InitializerType VALUES3 = {1, 2};
const InitializerType VALUES4 = {2, 3, 1};
const InitializerType EXPECTED4 = {1, 2, 3};
const InitializerType VALUES5 = {4, 3, 2, 1};
const InitializerType EXPECTED5 = {1, 2, 3, 4};

THE_BENCHMARK(MergeSort, VALUES5);

SIMPLE_TEST(MergeSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(MergeSort_O1, VALUES5);

SIMPLE_TEST(MergeSort_O1, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort_O1, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort_O1, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort_O1, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort_O1, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(MergeSort_Iterative, VALUES5);

SIMPLE_TEST(MergeSort_Iterative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort_Iterative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort_Iterative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort_Iterative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort_Iterative, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(MergeSort_SinglyList, VALUES5);

SIMPLE_TEST(MergeSort_SinglyList, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort_SinglyList, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort_SinglyList, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort_SinglyList, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort_SinglyList, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(MergeSort_SinglyList_Iterative, VALUES5);

SIMPLE_TEST(MergeSort_SinglyList_Iterative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort_SinglyList_Iterative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort_SinglyList_Iterative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort_SinglyList_Iterative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort_SinglyList_Iterative, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(MergeSort_DoublyList, VALUES5);

SIMPLE_TEST(MergeSort_DoublyList, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort_DoublyList, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort_DoublyList, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort_DoublyList, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort_DoublyList, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(MergeSort_3Way, VALUES5);

SIMPLE_TEST(MergeSort_3Way, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort_3Way, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort_3Way, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort_3Way, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort_3Way, TestSAMPLE5, EXPECTED5, VALUES5);
