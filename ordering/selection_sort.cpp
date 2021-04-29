#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Selection Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises Solutions 2.2-2.
 * @reference   https://mitpress.mit.edu/sites/default/files/titles/content/Intro_to_Algo_Selected_Solutions.pdf
 * @reference   https://www.geeksforgeeks.org/selection-sort/
 * @reference   Which sorting algorithm makes minimum number of memory writes?
 *              https://www.geeksforgeeks.org/which-sorting-algorithm-makes-minimum-number-of-writes/
 * @reference   Program to sort an array of strings using Selection Sort
 *              https://www.geeksforgeeks.org/program-to-sort-an-array-of-strings-using-selection-sort/
 * @reference   Recursive Selection Sort
 *              https://www.geeksforgeeks.org/recursive-selection-sort/
 * @reference   C Program for Selection Sort
 *              https://www.geeksforgeeks.org/c-program-for-selection-sort/
 * @reference   C++ program for Sorting Dates using Selection Sort
 *              https://www.geeksforgeeks.org/c-program-for-sorting-dates-using-selection-sort/
 * @reference   C program to sort an array using pointers
 *              https://www.geeksforgeeks.org/c-program-to-sort-an-array-using-pointers/
 * @reference   C program to sort an array in ascending order
 *              https://www.geeksforgeeks.org/c-program-to-sort-an-array-in-ascending-order/
 *
 * @complexity: O(n^2)
 */
template <typename T>
auto SelectionSort(std::vector<T> values) {
    for (typename std::vector<T>::iterator smallest_iter, iter_j, iter_i = values.begin();
         iter_i != values.end(); ++iter_i) {
        for (iter_j = iter_i + 1, smallest_iter = iter_i; iter_j != values.end(); ++iter_j) {
            if (*iter_j < *smallest_iter) {
                smallest_iter = iter_j;
            }
        }
        std::iter_swap(iter_i, smallest_iter);
    }

    return values;
}


/**
 * @reference   std::iter_swap
 *              https://en.cppreference.com/w/cpp/algorithm/iter_swap
 */
auto SelectionSort_Concise(ArrayType values) {
    for (auto i = values.begin(); i != values.end(); ++i) {
        std::iter_swap(i, std::min_element(i, values.end()));
    }

    return values;
}


/**
 * @reference   Stable Selection Sort
 *              https://www.geeksforgeeks.org/stable-selection-sort/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 8.
 */
auto SelectionSort_Stable(ArrayType values) {
    for (auto i = values.begin(); i != values.end(); ++i) {
        const auto min_iter = std::min_element(i, values.end());
        std::rotate(i, min_iter, std::next(min_iter));
    }

    return values;
}


void SelectionSort_Recursive(const ArrayType::iterator begin,
                             const ArrayType::iterator end) {
    if (begin != end) {
        std::iter_swap(begin, std::min_element(begin, end));
        SelectionSort_Recursive(std::next(begin), end);
    }
}
auto SelectionSort_Recursive(ArrayType values) {
    SelectionSort_Recursive(values.begin(), values.end());
    return values;
}


/** A sorting algorithm that slightly improves on selection sort
 *
 * @reference   https://www.geeksforgeeks.org/sorting-algorithm-slightly-improves-selection-sort/
 */
auto SelectionSort_MinMax(ArrayType values) {
    if (not values.empty()) {
        auto left = values.begin();
        auto right = values.end();
        for (; isThereMoreThanOneElements(left, right); ++left) {
            const auto [min, max] = std::minmax_element(left, right);
            std::iter_swap(min, left);
            std::iter_swap(max == left ? min : max, --right);
        }
    }

    return values;
}


/** Iterative selection sort for linked list
 *
 * @reference   https://www.geeksforgeeks.org/iterative-selection-sort-for-linked-list/
 */
void SelectionSort_SinglyList_Helper(std::forward_list<ArrayType::value_type> &l,
                                     const std::forward_list<ArrayType::value_type>::const_iterator cbefore_begin,
                                     const std::forward_list<ArrayType::value_type>::const_iterator cbegin) {
    assert(cbegin != l.cend());

    auto min_iter = cbegin;
    auto cbefore_min = cbefore_begin;
    auto cbefore_iter = min_iter;
    for (auto iter = std::next(min_iter); iter != l.cend(); ++iter, ++cbefore_iter) {
        if (*iter < *min_iter) {
            min_iter = iter;
            cbefore_min = cbefore_iter;
        }
    }

    l.splice_after(cbefore_begin, l, cbefore_min);
}

auto SelectionSort_SinglyList_Iterative(
    std::forward_list<ArrayType::value_type> values) {
    auto iter = values.cbegin();
    for (auto cbefore_iter = values.cbefore_begin(); iter != values.cend();
         iter = std::next(cbefore_iter)) {
        SelectionSort_SinglyList_Helper(values, cbefore_iter, iter);
        std::advance(cbefore_iter, 1);
    }

    return values;
}


/**
 * @reference   Recursive selection sort for singly linked list | Swapping node links
 *              https://www.geeksforgeeks.org/recursive-selection-sort-singly-linked-list-swapping-node-links/
 */
void SelectionSort_SinglyList_Recursive(std::forward_list<ArrayType::value_type> &l,
                                        const std::forward_list<ArrayType::value_type>::const_iterator cbefore_begin) {
    const auto cbegin = std::next(cbefore_begin);
    if (cbegin != l.cend()) {
        SelectionSort_SinglyList_Helper(l, cbefore_begin, cbegin);
        SelectionSort_SinglyList_Recursive(l, std::next(cbefore_begin));
    }
}

auto SelectionSort_SinglyList_Recursive(
    std::forward_list<ArrayType::value_type> values) {
    SelectionSort_SinglyList_Recursive(values, values.cbefore_begin());
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


const auto SelectionSort_Int = SelectionSort<ArrayType::value_type>;

SIMPLE_BENCHMARK(SelectionSort_Int, Sample1, VALUES5);

SIMPLE_TEST(SelectionSort_Int, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_Int, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_Int, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_Int, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_Int, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(SelectionSort_Concise, Sample1, VALUES5);

SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(SelectionSort_Stable, Sample1, VALUES5);

SIMPLE_TEST(SelectionSort_Stable, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_Stable, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_Stable, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_Stable, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_Stable, TestSAMPLE5, EXPECTED5, VALUES5);


const std::vector<std::string> VALUES21 = {};
const std::vector<std::string> VALUES22 = {"a"};
const std::vector<std::string> VALUES23 = {"paper", "true", "soap", "floppy", "flower"};
const std::vector<std::string> EXPECTED23 = {"floppy", "flower", "paper", "soap", "true"};
const std::vector<std::string> VALUES24 = {"paper", "soap", "floppy", "flower"};
const std::vector<std::string> EXPECTED24 = {"floppy", "flower", "paper", "soap"};


SIMPLE_BENCHMARK(SelectionSort, Sample1, VALUES24);

SIMPLE_TEST(SelectionSort, TestSAMPLE21, VALUES21, VALUES21);
SIMPLE_TEST(SelectionSort, TestSAMPLE22, VALUES22, VALUES22);
SIMPLE_TEST(SelectionSort, TestSAMPLE23, EXPECTED23, VALUES23);
SIMPLE_TEST(SelectionSort, TestSAMPLE24, EXPECTED24, VALUES24);


SIMPLE_BENCHMARK(SelectionSort_Recursive, Sample1, VALUES5);

SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(SelectionSort_MinMax, Sample1, VALUES5);

SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(SelectionSort_SinglyList_Iterative, Sample1, VALUES5);

SIMPLE_TEST(SelectionSort_SinglyList_Iterative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_SinglyList_Iterative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_SinglyList_Iterative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_SinglyList_Iterative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_SinglyList_Iterative, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(SelectionSort_SinglyList_Recursive, Sample1, VALUES5);

SIMPLE_TEST(SelectionSort_SinglyList_Recursive, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_SinglyList_Recursive, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_SinglyList_Recursive, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_SinglyList_Recursive, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_SinglyList_Recursive, TestSAMPLE5, EXPECTED5, VALUES5);
