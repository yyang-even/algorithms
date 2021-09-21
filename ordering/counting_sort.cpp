#include "common_header.h"


namespace {

#include "counting_sort.h"

using ArrayType = std::vector<int>;

/** Counting Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 8.2.
 * @reference   https://www.geeksforgeeks.org/counting-sort/
 * @reference   C Program for Counting Sort
 *              https://www.geeksforgeeks.org/c-program-for-counting-sort-2/
 *
 * Counting sort is efficient if the range of input data is not significantly greater
 * than the number of objects to be sorted.
 *
 * @reference   Sort string of characters
 *              https://www.geeksforgeeks.org/sort-string-characters/
 * @reference   Program to sort string in descending order
 *              https://www.geeksforgeeks.org/program-sort-string-descending-order/
 * @reference   How to sort an Array in descending order using STL in C++?
 *              https://www.geeksforgeeks.org/how-to-sort-an-array-in-descending-order-using-stl-in-c/
 * @reference   How to sort a Vector in descending order using STL in C++?
 *              https://www.geeksforgeeks.org/how-to-sort-a-vector-in-descending-order-using-stl-in-c/
 * @reference   Sorting of Vector of Tuple in C++ (Ascending Order)
 *              https://www.geeksforgeeks.org/sorting-vector-tuple-c-ascending-order/
 * @reference   Sorting of Vector of Tuple in C++ (Descending Order)
 *              https://www.geeksforgeeks.org/sorting-vector-tuple-c-descending-order/
 * @reference   Sorting Vector of Pairs in C++ | Set 1 (Sort by first and second)
 *              https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/
 * @reference   Sorting Vector of Pairs in C++ | Set 2 (Sort in descending order by first and second)
 *              https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-2-sort-in-descending-order-by-first-and-second/
 * @reference   Keep track of previous indexes after sorting a vector in C++ STL
 *              https://www.geeksforgeeks.org/keep-track-of-previous-indexes-after-sorting-a-vector-in-c-stl/
 * @reference   Sorting a vector in C++
 *              https://www.geeksforgeeks.org/sorting-a-vector-in-c/
 * @reference   Sorting without comparison of elements
 *              https://www.geeksforgeeks.org/sorting-without-comparison-of-elements/
 */
inline auto CountingSort_NoNegative(ArrayType values) {
    static constexpr ArrayType::value_type MAXIMUM = 1 << 8;

    assert(std::all_of(values.cbegin(), values.cend(), [](const auto v) {
        return v >= 0 and v < MAXIMUM;
    }));

    return CountingSort(std::move(values), MAXIMUM, Copy);
}


/**
 * @reference   C++14 Language Extensions: Generalized lambda captures
 *              https://isocpp.org/wiki/faq/cpp14-language#lambda-captures
 */
inline auto CountingSort(ArrayType values) {
    if (values.empty()) {
        return values;
    }

    const auto [min_iter, max_iter] = std::minmax_element(values.cbegin(), values.cend());
    const auto RANGE = *max_iter - *min_iter + 1;

    return CountingSort(std::move(values), RANGE, [min = *min_iter](const auto v) {
        return v - min;
    });
}


inline auto CountingSort_STL(ArrayType values) {
    return CountingSort_STL(std::move(values), Copy);
}


/**
 * @reference   Actors and Directors Who Cooperated At Least Three Times
 *              https://leetcode.com/problems/height-checker/
 *
 * A school is trying to take an annual photo of all the students. The students are asked
 * to stand in a single file line in non-decreasing order by height. Let this ordering be
 * represented by the integer array expected where expected[i] is the expected height of
 * the ith student in line. You are given an integer array heights representing the
 * current order that the students are standing in. Each heights[i] is the height of the
 * ith student in line (0-indexed). Return the number of indices where
 * heights[i] != expected[i].
 * 1 <= heights[i] <= 100
 */

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


THE_BENCHMARK(CountingSort_NoNegative, VALUES6);

SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE6, EXPECTED6, VALUES6);


constexpr InitializerType VALUES7 = {-5, -10, 0, -3, 8, 5, -1, 10};
constexpr InitializerType EXPECTED7 = {-10, -5, -3, -1, 0, 5, 8, 10};


THE_BENCHMARK(CountingSort, VALUES6);

SIMPLE_TEST(CountingSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(CountingSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(CountingSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(CountingSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(CountingSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(CountingSort, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(CountingSort, TestSAMPLE7, EXPECTED7, VALUES7);


THE_BENCHMARK(CountingSort_STL, VALUES6);

SIMPLE_TEST(CountingSort_STL, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(CountingSort_STL, TestSAMPLE7, EXPECTED7, VALUES7);
