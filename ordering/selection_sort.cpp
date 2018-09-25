#include "common_header.h"


template <std::size_t N>
using ArrayType = std::array<int, N>;

/** Selection Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises Solutions 2.2-2.
 *              https://mitpress.mit.edu/sites/default/files/titles/content/Intro_to_Algo_Selected_Solutions.pdf
 *
 *              http://www.geeksforgeeks.org/selection-sort/
 *
 * @complexity: O(n^2)
 */
template <typename Container>
auto SelectionSort(Container values) {
    for (typename Container::iterator smallest_iter, iter_j, iter_i = values.begin();
         iter_i != values.end();
         ++iter_i) {
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
auto SelectionSortConcise(Container values) {
    for(auto i = values.begin(); i != values.end(); ++i){
        std::iter_swap(i, std::min_element(i, values.end()));
    }
    
    return values;
}


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<1> VALUES2 = {1};
constexpr ArrayType<2> VALUES3 = {1, 2};
constexpr ArrayType<3> VALUES4 = {2, 3, 1};
constexpr ArrayType<3> EXPECTED4 = {1, 2, 3};
constexpr ArrayType<4> VALUES5 = {4, 3, 2, 1};
constexpr ArrayType<4> EXPECTED5 = {1, 2, 3, 4};

SIMPLE_BENCHMARK(SelectionSort, VALUES5);

SIMPLE_TEST(SelectionSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort, TestSAMPLE5, EXPECTED5, VALUES5);

SIMPLE_BENCHMARK(SelectionSortConcise, VALUES5);

SIMPLE_TEST(SelectionSortConcise, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SelectionSortConcise, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSortConcise, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSortConcise, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSortConcise, TestSAMPLE5, EXPECTED5, VALUES5);

/** C program to sort an array of strings using Selection Sort
 *
 * @reference   http://www.geeksforgeeks.org/c-program-to-sort-an-array-of-strings-using-selection-sort-2/
 */
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
