#include "common_header.h"

#include "data_structure/linked_list/sorted_insert_linked_list.h"

#include "sorted_insert.h"


namespace {

#include "insertion_sort.h"

using ArrayType = std::vector<int>;

/** Insertion Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 2.1.
 *
 * @reference   https://www.geeksforgeeks.org/insertion-sort/
 * @reference   An Insertion Sort time complexity question
 *              https://www.geeksforgeeks.org/insertion-sort-time-complexity-question/
 * @reference   Time complexity of insertion sort when there are O(n) inversions?
 *              https://www.geeksforgeeks.org/time-complexity-insertion-sort-inversions/
 * @reference   Insertion sort using C++ STL
 *              https://www.geeksforgeeks.org/insertion-sort-using-c-stl/
 * @reference   C Program for Insertion Sort
 *              https://www.geeksforgeeks.org/c-program-for-insertion-sort/
 * @reference   Comparison among Bubble Sort, Selection Sort and Insertion Sort
 *              https://www.geeksforgeeks.org/comparison-among-bubble-sort-selection-sort-and-insertion-sort/
 *
 * @complexity: O(n^2)
 */
inline auto InsertionSort_STL(ArrayType values) {
    for (auto iter = values.begin(); iter != values.end(); ++iter) {
        SortedInsert(values.begin(), iter);
    }

    return values;
}


/** Sort 3 numbers
 *
 * @reference   https://www.geeksforgeeks.org/sort-3-numbers/
 *
 * Given three numbers, how to sort them?
 * How to write our own sort function that does minimum comparison and does not use extra
 * variables?
 * The idea is to use insertion sort as insertion sort works best for small arrays.
 */
inline auto InsertionSort(ArrayType values) {
    return InsertionSort(std::move(values), std::greater<ArrayType::value_type> {});
}


/** Recursive Insertion Sort
 *
 * @reference   https://www.geeksforgeeks.org/recursive-insertion-sort/
 * @reference   C Program for Recursive Insertion Sort
 *              https://www.geeksforgeeks.org/c-program-for-recursive-insertion-sort/
 *
 * @complexity: O(n^2)
 */
void InsertionSort_Recursive(ArrayType &values, const int n) {
    if (n > 1) {
        const auto key_index = n - 1;
        InsertionSort_Recursive(values, key_index);
        auto key_value = std::move(values[key_index]);
        auto i = key_index - 1;
        for (; (i >= 0) and (values[i] > key_value); --i) {
            values[i + 1] = std::move(values[i]);
        }
        values[i + 1] = std::move(key_value);
    }
}

inline auto InsertionSort_Recursive(ArrayType values) {
    InsertionSort_Recursive(values, values.size());
    return values;
}


/** Binary Insertion Sort
 *
 * @reference   https://www.geeksforgeeks.org/binary-insertion-sort/
 * @reference   C Program for Binary Insertion Sort
 *              https://www.geeksforgeeks.org/c-program-for-binary-insertion-sort/
 *
 * @complexity: O(n^2)
 */
auto UpperBound(const int target, const ArrayType::const_iterator begin,
                const ArrayType::size_type n) {
    if (n > 1) {
        const auto middle = n >> 1;
        const auto middle_value = *(begin + middle);

        if (target == middle_value) {
            return begin + middle + 1;
        } else if (target < middle_value) {
            return UpperBound(target, begin, middle);
        } else {
            return UpperBound(target, begin + middle, n - middle);
        }
    } else {
        return (target > *begin) ? begin + 1 : begin;
    }
}

auto BinaryInsertionSort(ArrayType values) {
    const auto N = values.size();
    for (ArrayType::size_type j = 1; j < N; ++j) {
        auto key_value = std::move(values[j]);
        ArrayType::difference_type i = j - 1;

        const auto location = UpperBound(key_value, values.cbegin(), j) - values.cbegin();
        while (i >= location) {
            values[i + 1] = std::move(values[i]);
            --i;
        }
        values[i + 1] = std::move(key_value);
    }

    return values;
}


/** Insertion Sort by Swapping Elements
 *
 * @reference   https://www.geeksforgeeks.org/insertion-sort-swapping-elements/
 */


/** Insertion Sort for Singly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/
 *
 * @reference   Insertion Sort List
 *              https://leetcode.com/problems/insertion-sort-list/
 *
 * Given the head of a singly linked list, sort the list using insertion sort, and return
 * the sorted list's head. The steps of the insertion sort algorithm:
 *  1. Insertion sort iterates, consuming one input element each repetition and growing a
 *  sorted output list.
 *  2. At each iteration, insertion sort removes one element from the input data, finds
 *  the location it belongs within the sorted list and inserts it there.
 *  3. It repeats until no input elements remain.
 */
inline auto InsertionSort_SinglyList(std::forward_list<ArrayType::value_type> values) {
    std::forward_list<ArrayType::value_type> sorted_list;
    while (not values.empty()) {
        SortedInsert_STL(sorted_list, values, values.cbefore_begin(), values.cbegin());
    }

    return sorted_list;
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
constexpr InitializerType VALUES6 = {1, 2, 3, 1, 2, 2};
constexpr InitializerType EXPECTED6 = {1, 1, 2, 2, 2, 3};


THE_BENCHMARK(InsertionSort, VALUES6);

SIMPLE_TEST(InsertionSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(InsertionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(InsertionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(InsertionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(InsertionSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(InsertionSort, TestSAMPLE6, EXPECTED6, VALUES6);


THE_BENCHMARK(InsertionSort_Recursive, VALUES6);

SIMPLE_TEST(InsertionSort_Recursive, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(InsertionSort_Recursive, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(InsertionSort_Recursive, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(InsertionSort_Recursive, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(InsertionSort_Recursive, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(InsertionSort_Recursive, TestSAMPLE6, EXPECTED6, VALUES6);


THE_BENCHMARK(BinaryInsertionSort, VALUES6);

SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE6, EXPECTED6, VALUES6);


THE_BENCHMARK(InsertionSort_STL, VALUES6);

SIMPLE_TEST(InsertionSort_STL, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(InsertionSort_STL, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(InsertionSort_STL, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(InsertionSort_STL, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(InsertionSort_STL, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(InsertionSort_STL, TestSAMPLE6, EXPECTED6, VALUES6);


THE_BENCHMARK(InsertionSort_SinglyList, VALUES6);

SIMPLE_TEST(InsertionSort_SinglyList, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(InsertionSort_SinglyList, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(InsertionSort_SinglyList, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(InsertionSort_SinglyList, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(InsertionSort_SinglyList, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(InsertionSort_SinglyList, TestSAMPLE6, EXPECTED6, VALUES6);
