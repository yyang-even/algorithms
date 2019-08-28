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
 *
 * @complexity: O(n^2)
 */
template <typename Container>
auto SelectionSort(Container values) {
    for (typename Container::iterator smallest_iter, iter_j, iter_i = values.begin();
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
template <typename Container>
auto SelectionSort_Concise(Container values) {
    for (auto i = values.begin(); i != values.end(); ++i) {
        std::iter_swap(i, std::min_element(i, values.end()));
    }

    return values;
}


void SelectionSort_Recursive(const ArrayType::iterator begin, const ArrayType::iterator end) {
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
            const auto min_max_pair = std::minmax_element(left, right);
            std::iter_swap(min_max_pair.first, left);
            std::iter_swap(min_max_pair.second == left ? min_max_pair.first : min_max_pair.second, --right);
        }
    }

    return values;
}


/** Iterative selection sort for linked list
 *
 * @reference   https://www.geeksforgeeks.org/iterative-selection-sort-for-linked-list/
 */
/*auto SelectionSort_SinglyList(std::forward_list<int> values) {
    for () {

    }
}*/

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};


SIMPLE_BENCHMARK(SelectionSort, VALUES5);

SIMPLE_TEST(SelectionSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(SelectionSort_Concise, VALUES5);

SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_Concise, TestSAMPLE5, EXPECTED5, VALUES5);


const std::vector<std::string> VALUES21 = {};
const std::vector<std::string> VALUES22 = {"a"};
const std::vector<std::string> VALUES23 = {"paper", "true", "soap", "floppy", "flower"};
const std::vector<std::string> EXPECTED23 = {"floppy", "flower", "paper", "soap", "true"};
const std::vector<std::string> VALUES24 = {"paper", "soap", "floppy", "flower"};
const std::vector<std::string> EXPECTED24 = {"floppy", "flower", "paper", "soap"};

SIMPLE_BENCHMARK(SelectionSort, VALUES24);

SIMPLE_TEST(SelectionSort, TestSAMPLE21, VALUES21, VALUES21);
SIMPLE_TEST(SelectionSort, TestSAMPLE22, VALUES22, VALUES22);
SIMPLE_TEST(SelectionSort, TestSAMPLE23, EXPECTED23, VALUES23);
SIMPLE_TEST(SelectionSort, TestSAMPLE24, EXPECTED24, VALUES24);


SIMPLE_BENCHMARK(SelectionSort_Recursive, VALUES5);

SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_Recursive, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(SelectionSort_MinMax, VALUES5);

SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort_MinMax, TestSAMPLE5, EXPECTED5, VALUES5);
