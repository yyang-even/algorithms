#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using MatrixType = MatrixTypeTemplate<int>;
using ResultType = std::pair<int, int>;

const ResultType NOT_FOUND = {-1, -1};

/** Search in a row wise and column wise sorted matrix
 *
 * @reference   https://www.geeksforgeeks.org/search-in-row-wise-and-column-wise-sorted-matrix/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.6.
 *
 * Given an n x n matrix and a number x, find the position of x in the matrix if it is
 * present in it. Otherwise, print "Not Found". In the given matrix, every row and column
 * is sorted in increasing order. The designed algorithm should have linear time
 * complexity.
 */
ResultType SearchMatrix(const MatrixType &a_matrix, const int key) {
    assert(not a_matrix.empty());
    assert(not a_matrix.front().empty());

    const auto smallest = a_matrix[0][0];
    const auto largest = a_matrix.back().back();
    if (key < smallest or key > largest) {
        return NOT_FOUND;
    }

    MatrixType::size_type i = 0;
    int j = a_matrix.front().size() - 1;
    while (i < a_matrix.size() and j >= 0) {
        if (a_matrix[i][j] == key)
            return {i, j};

        if (a_matrix[i][j] > key) {
            --j;
        } else {
            ++i;
        }
    }

    return NOT_FOUND;
}


/**
 * @reference   Search in a Row-wise and Column-wise Sorted 2D Array using Divide and Conquer algorithm
 *              https://www.geeksforgeeks.org/search-in-a-row-wise-and-column-wise-sorted-2d-array-using-divide-and-conquer-algorithm/
 */
ResultType SearchMatrix_BinarySearch(const MatrixType &a_matrix, const int key,
                                     const int from_row, const int to_row,
                                     const int from_column, const int to_column) {
    if (from_row > to_row or from_column > to_column) {
        return NOT_FOUND;
    }

    const auto mid_row = (from_row + to_row) / 2;
    const auto mid_column = (from_column + to_column) / 2;

    if (a_matrix[mid_row][mid_column] == key)
        return {mid_row, mid_column};

    if (mid_row != to_row or mid_column != from_column) {
        const auto result = SearchMatrix_BinarySearch(a_matrix, key, from_row, mid_row,
                                                      mid_column, to_column);
        if (result != NOT_FOUND) {
            return result;
        }
    }

    if (from_row == to_row and from_column + 1 == to_column) {
        if (a_matrix[from_row][to_column] == key)
            return {from_row, to_column};
    }

    if (a_matrix[mid_row][mid_column] < key) {
        return SearchMatrix_BinarySearch(a_matrix, key, mid_row + 1, to_row,
                                         from_column, to_column);
    } else {
        return SearchMatrix_BinarySearch(a_matrix, key, from_row, to_row,
                                         from_column, mid_column - 1);
    }
}

inline ResultType
SearchMatrix_BinarySearch(const MatrixType &a_matrix, const int key) {
    assert(not a_matrix.empty());
    assert(not a_matrix.front().empty());

    return SearchMatrix_BinarySearch(a_matrix, key, 0, a_matrix.size() - 1,
                                     0, a_matrix.front().size() - 1);
}

}//namespace


const MatrixType SAMPLE1 = {
    {10, 20, 30, 40},
    {15, 25, 35, 45},
    {27, 29, 37, 48},
    {32, 33, 39, 50}
};

constexpr ResultType EXPECTED1 = {2, 1};
constexpr ResultType EXPECTED2 = {0, 0};
constexpr ResultType EXPECTED3 = {1, 2};
constexpr ResultType EXPECTED4 = {3, 3};


THE_BENCHMARK(SearchMatrix, SAMPLE1, 29);

SIMPLE_TEST(SearchMatrix, TestSAMPLE1, EXPECTED1, SAMPLE1, 29);
SIMPLE_TEST(SearchMatrix, TestSAMPLE2, EXPECTED2, SAMPLE1, 10);
SIMPLE_TEST(SearchMatrix, TestSAMPLE3, EXPECTED3, SAMPLE1, 35);
SIMPLE_TEST(SearchMatrix, TestSAMPLE4, EXPECTED4, SAMPLE1, 50);
SIMPLE_TEST(SearchMatrix, TestSAMPLE5, NOT_FOUND, SAMPLE1, 100);


THE_BENCHMARK(SearchMatrix_BinarySearch, SAMPLE1, 29);

SIMPLE_TEST(SearchMatrix_BinarySearch, TestSAMPLE1, EXPECTED1, SAMPLE1, 29);
SIMPLE_TEST(SearchMatrix_BinarySearch, TestSAMPLE2, EXPECTED2, SAMPLE1, 10);
SIMPLE_TEST(SearchMatrix_BinarySearch, TestSAMPLE3, EXPECTED3, SAMPLE1, 35);
SIMPLE_TEST(SearchMatrix_BinarySearch, TestSAMPLE4, EXPECTED4, SAMPLE1, 50);
SIMPLE_TEST(SearchMatrix_BinarySearch, TestSAMPLE5, NOT_FOUND, SAMPLE1, 100);
