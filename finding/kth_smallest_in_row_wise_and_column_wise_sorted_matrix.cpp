#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** Kth Smallest Element in a Sorted Matrix
 *
 * @reference   https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
 *
 * Given an n x n matrix where each of the rows and columns are sorted in ascending
 * order, return the kth smallest element in the matrix. Note that it is the kth
 * smallest element in the sorted order, not the kth distinct element.
 *
 * @reference   Kth smallest element in a row-wise and column-wise sorted 2D array | Set 1
 *              https://www.geeksforgeeks.org/kth-smallest-element-in-a-row-wise-and-column-wise-sorted-2d-array-set-1/
 */
auto KthSmallestInSortedMatrix_Heap(const MatrixType &a_matrix, const int K) {
    assert(not a_matrix.empty() and a_matrix.size() == a_matrix.front().size());

    const auto compare = [&a_matrix](const auto lhs, const auto rhs) {
        return a_matrix[lhs.first][lhs.second] > a_matrix[rhs.first][rhs.second];
    };

    using RowColumnPair = std::pair<std::size_t, std::size_t>;
    std::priority_queue<RowColumnPair, std::vector<RowColumnPair>, decltype(compare)>
    min_heap(compare);
    for (std::size_t i = 0; i < a_matrix.size(); ++i) {
        min_heap.emplace(i, 0);
    }

    for (int i = 1; i < K; ++i) {
        const auto [row, column] = min_heap.top();
        min_heap.pop();

        if (column + 1 < a_matrix.size()) {
            min_heap.emplace(row, column + 1);
        }
    }

    const auto [row, column] = min_heap.top();
    return a_matrix[row][column];
}


auto countNoGreaterThan(const MatrixType &a_matrix, const int num) {
    int result = 0;

    for (std::size_t i = 0; i < a_matrix.size() and a_matrix[i][0] <= num; ++i) {
        if (a_matrix[i][a_matrix.size() - 1] <= num) {
            result += a_matrix.size();
            continue;
        }

        std::size_t no_greater_than = 0;
        for (std::size_t jump = a_matrix.size() / 2; jump >= 1; jump /= 2) {
            while (no_greater_than + jump < a_matrix.size() and
                   a_matrix[i][no_greater_than + jump] <= num) {
                no_greater_than += jump;
            }
        }

        result += no_greater_than + 1;
    }

    return result;
}

auto KthSmallestInSortedMatrix_BinarySearch(const MatrixType &a_matrix, const int K) {
    assert(not a_matrix.empty() and a_matrix.size() == a_matrix.front().size());

    int left = a_matrix[0][0];
    int right = a_matrix[a_matrix.size() - 1][a_matrix.size() - 1];
    while (left <= right) {
        const auto mid = (left + right) / 2;
        const auto number_no_greater_than = countNoGreaterThan(a_matrix, mid);

        if (number_no_greater_than >= K) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return left;
}


/**
 * @reference   Kth Smallest Number in Multiplication Table
 *              https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
 *
 * Nearly everyone has used the Multiplication Table. The multiplication table of size
 * m x n is an integer matrix mat where mat[i][j] == i * j (1-indexed). Given three
 * integers m, n, and k, return the kth smallest element in the m x n multiplication
 * table.
 */
constexpr auto
count(const int m, const int n, const int x) {
    int result = 0;
    for (int i = 1; i <= m; ++i) {
        result += std::min(x / i, n);
    }
    return result;
}

constexpr auto
KthNumberInMultiplicationTable(const int m, const int n, const int k) {
    int left = 1;
    int right = m * n;
    int result = 0;
    while (left <= right) {
        const auto mid = (left + right) / 2;
        if (count(m, n, mid) < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
            result = mid;
        }
    }

    return result;
}

}//namespace


const MatrixType SAMPLE1 = {
    {1, 5, 9},
    {10, 11, 13},
    {12, 13, 15},
};

const MatrixType SAMPLE2 = {
    {-5}
};

const MatrixType SAMPLE3 = {
    {10, 20, 30, 40},
    {15, 25, 35, 45},
    {24, 29, 37, 48},
    {32, 33, 39, 50}
};


THE_BENCHMARK(KthSmallestInSortedMatrix_Heap, SAMPLE1, 8);

SIMPLE_TEST(KthSmallestInSortedMatrix_Heap, TestSAMPLE1, 13, SAMPLE1, 8);
SIMPLE_TEST(KthSmallestInSortedMatrix_Heap, TestSAMPLE2, -5, SAMPLE2, 1);
SIMPLE_TEST(KthSmallestInSortedMatrix_Heap, TestSAMPLE3, 20, SAMPLE3, 3);
SIMPLE_TEST(KthSmallestInSortedMatrix_Heap, TestSAMPLE4, 30, SAMPLE3, 7);


THE_BENCHMARK(KthSmallestInSortedMatrix_BinarySearch, SAMPLE1, 8);

SIMPLE_TEST(KthSmallestInSortedMatrix_BinarySearch, TestSAMPLE1, 13, SAMPLE1, 8);
SIMPLE_TEST(KthSmallestInSortedMatrix_BinarySearch, TestSAMPLE2, -5, SAMPLE2, 1);
SIMPLE_TEST(KthSmallestInSortedMatrix_BinarySearch, TestSAMPLE3, 20, SAMPLE3, 3);
SIMPLE_TEST(KthSmallestInSortedMatrix_BinarySearch, TestSAMPLE4, 30, SAMPLE3, 7);


THE_BENCHMARK(KthNumberInMultiplicationTable, 3, 3, 5);

SIMPLE_TEST(KthNumberInMultiplicationTable, TestSAMPLE1, 3, 3, 3, 5);
SIMPLE_TEST(KthNumberInMultiplicationTable, TestSAMPLE2, 6, 2, 3, 6);
