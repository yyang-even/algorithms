#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

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
template<std::size_t N>
auto SelectionSort(ArrayType<N> values) {
    assert(values.size());

    const auto size = values.size();
    for (typename ArrayType<N>::size_type smallest_index, i, j = 0; j < (size - 1); ++j) {
        smallest_index = j;
        for (i = j + 1; i < size; ++i) {
            if (values[i] < values[smallest_index]) {
                smallest_index = i;
            }
        }
        std::swap(values[j], values[smallest_index]);
    }

    return values;
}


constexpr ArrayType<1> VALUES2 = {1};
constexpr ArrayType<2> VALUES3 = {1, 2};
constexpr ArrayType<3> VALUES4 = {2, 3, 1};
constexpr ArrayType<3> EXPECTED4 = {1, 2, 3};
constexpr ArrayType<4> VALUES5 = {4, 3, 2, 1};
constexpr ArrayType<4> EXPECTED5 = {1, 2, 3, 4};

SIMPLE_TEST(SelectionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort, TestSAMPLE5, EXPECTED5, VALUES5);
