#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

template <std::size_t N>
using ArrayType = std::array<int, N>;

/** Insertion Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 2.1.
 *
 *              http://www.geeksforgeeks.org/insertion-sort/
 */
template<std::size_t N>
auto InsertionSort(ArrayType<N> values) {
    for (int key_value, i, j = 1; j < values.size(); ++j) {
        key_value = values[j];
        i = j - 1;
        for (; (i >= 0) and (values[i] > key_value); --i) {
            values[i + 1] = values[i];
        }
        values[i + 1] = key_value;
    }
    return values;
}


/** Recursive Insertion Sort
 *
 * @reference   http://www.geeksforgeeks.org/recursive-insertion-sort/
 */
template<std::size_t N>
void InsertionSortRecursive(ArrayType<N> &values, int n) {
    if (n > 1) {
        auto key_index = n - 1;
        InsertionSortRecursive(values, key_index);
        const auto key_value = values[key_index];
        auto i = key_index - 1;
        for (; (i >= 0) and (values[i] > key_value); --i) {
            values[i + 1] = values[i];
        }
        values[i + 1] = key_value;
    }
}
template<std::size_t N>
auto InsertionSortRecursive(ArrayType<N> values) {
    InsertionSortRecursive(values, values.size());
    return values;
}


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<1> VALUES2 = {1};
constexpr ArrayType<2> VALUES3 = {1, 2};
constexpr ArrayType<3> VALUES4 = {2, 3, 1};
constexpr ArrayType<3> EXPECTED4 = {1, 2, 3};
constexpr ArrayType<4> VALUES5 = {4, 3, 2, 1};
constexpr ArrayType<4> EXPECTED5 = {1, 2, 3, 4};

SIMPLE_TEST(InsertionSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(InsertionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(InsertionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(InsertionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(InsertionSort, TestSAMPLE5, EXPECTED5, VALUES5);

SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE5, EXPECTED5, VALUES5);
