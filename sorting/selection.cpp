#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

/** Selection Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises Solutions 2.2-2.
 *              https://mitpress.mit.edu/sites/default/files/titles/content/Intro_to_Algo_Selected_Solutions.pdf
 *
 *              http://www.geeksforgeeks.org/selection-sort/
 */
template<std::size_t N>
auto SelectionSort(std::array<int, N> values) {
    assert(values.size());

    const auto size = values.size();
    for (typename std::array<int, N>::size_type smallest_index, i, j = 0; j < (size - 1); ++j) {
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


constexpr std::array<int, 1> VALUES2 = {1};
constexpr std::array<int, 2> VALUES3 = {1, 2};
constexpr std::array<int, 3> VALUES4 = {2, 3, 1};
constexpr std::array<int, 3> EXPECTED4 = {1, 2, 3};
constexpr std::array<int, 4> VALUES5 = {4, 3, 2, 1};
constexpr std::array<int, 4> EXPECTED5 = {1, 2, 3, 4};

SIMPLE_TEST(SelectionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SelectionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SelectionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SelectionSort, TestSAMPLE5, EXPECTED5, VALUES5);
