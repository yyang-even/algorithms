#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

/** Insertion Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 2.1.
 *
 *              http://www.geeksforgeeks.org/insertion-sort/
 */
template<std::size_t N>
auto InsertionSort(std::array<int, N> values) {
    for (int key_value, i, j = 1; j < values.size(); ++j) {
        key_value = values[j];
        i = j - 1;
        while ((i >= 0) and (values[i] > key_value)) {
            values[i + 1] = values[i];
            --i;
        }
        values[i + 1] = key_value;
    }
    return values;
}


constexpr std::array<int, 0> VALUES1 = {};
constexpr std::array<int, 1> VALUES2 = {1};
constexpr std::array<int, 2> VALUES3 = {1, 2};
constexpr std::array<int, 3> VALUES4 = {2, 3, 1};
constexpr std::array<int, 3> EXPECTED4 = {1, 2, 3};
constexpr std::array<int, 4> VALUES5 = {4, 3, 2, 1};
constexpr std::array<int, 4> EXPECTED5 = {1, 2, 3, 4};

SIMPLE_TEST(InsertionSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(InsertionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(InsertionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(InsertionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(InsertionSort, TestSAMPLE5, EXPECTED5, VALUES5);
