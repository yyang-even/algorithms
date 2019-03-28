#include "common_header.h"


namespace {

template <std::size_t N>
using ArrayType = std::array<int, N>;


/** Bubble Sort
 *
 * @reference   http://www.geeksforgeeks.org/bubble-sort/
 * @reference   Sorting Strings using Bubble Sort
 *              https://www.geeksforgeeks.org/sorting-strings-using-bubble-sort-2/
 * @reference   C Program for Bubble Sort
 *              https://www.geeksforgeeks.org/c-program-for-bubble-sort/
 * @reference   C++ Program for Bubble Sort
 *              https://www.geeksforgeeks.org/cpp-program-for-bubble-sort/
 *
 * @complexity: O(n^2)
 */
template <std::size_t N>
auto BubbleSort(ArrayType<N> values) {
    const int last_i = static_cast<int>(values.size()) - 1;
    for (int i = 0, j, last_j; i < last_i; ++i) {
        for (j = 1, last_j = values.size() - i; j < last_j; ++j) {
            if (values[j - 1] > values[j]) {
                std::swap(values[j - 1], values[j]);
            }
        }
    }

    return values;
}

/** Bubble Sort Optimized
 *
 * @reference   http://www.geeksforgeeks.org/bubble-sort/
 *
 * @complexity: O(n^2) worst case; O(n) if the array is already sorted.
 */
template <std::size_t N>
auto BubbleSort_Optimized(ArrayType<N> values) {
    const int last_i = static_cast<int>(values.size()) - 1;
    bool swapped;

    for (int i = 0, j, last_j; i < last_i; ++i) {
        for (j = 1, last_j = values.size() - i, swapped = false; j < last_j; ++j) {
            if (values[j - 1] > values[j]) {
                std::swap(values[j - 1], values[j]);
                swapped = true;
            }
        }

        if (not swapped) {
            break;
        }
    }

    return values;
}


/** Recursive Bubble Sort
 *
 * @reference   http://www.geeksforgeeks.org/recursive-bubble-sort/
 * @reference   C++ Program for Recursive Bubble Sort
 *              https://www.geeksforgeeks.org/cpp-program-for-recursive-bubble-sort/
 *
 * @complexity: O(n^2)
 */
template <std::size_t N>
void BubbleSort_Recursive(ArrayType<N> &values, const typename ArrayType<N>::size_type n) {
    if (n > 1) {
        for (typename ArrayType<N>::size_type i = 1; i < n; ++i) {
            if (values[i - 1] > values[i]) {
                std::swap(values[i - 1], values[i]);
            }
        }

        BubbleSort_Recursive(values, n - 1);
    }
}
template <std::size_t N>
auto BubbleSort_Recursive(ArrayType<N> values) {
    BubbleSort_Recursive(values, values.size());
    return values;
}

}//namespace


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<1> VALUES2 = {1};
constexpr ArrayType<2> VALUES3 = {1, 2};
constexpr ArrayType<3> VALUES4 = {2, 3, 1};
constexpr ArrayType<3> EXPECTED4 = {1, 2, 3};
constexpr ArrayType<4> VALUES5 = {2, 3, 4, 1};
constexpr ArrayType<4> EXPECTED5 = {1, 2, 3, 4};
constexpr ArrayType<6> VALUES6 = {1, 2, 3, 1, 2, 2};
constexpr ArrayType<6> EXPECTED6 = {1, 1, 2, 2, 2, 3};

SIMPLE_TEST(BubbleSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSort, TestSAMPLE6, EXPECTED6, VALUES6);

SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE6, EXPECTED6, VALUES6);

SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE6, EXPECTED6, VALUES6);
