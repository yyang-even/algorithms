#include "common_header.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Cells with Odd Values in a Matrix
 *
 * @reference   https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/
 *
 * There is an m x n matrix that is initialized to all 0's. There is also a 2D array
 * indices where each indices[i] = [ri, ci] represents a 0-indexed location to perform
 * some increment operations on the matrix. For each location indices[i], do both of the
 * following:
 *  Increment all the cells on row ri.
 *  Increment all the cells on column ci.
 * Given m, n, and indices, return the number of odd-valued cells in the matrix after
 * applying the increment to all locations in indices.
 * Follow up: Could you solve this in O(n + m + indices.length) time with only O(n + m)
 * extra space?
 */
auto CellsWithOddValues(const int m, const int n, const ArrayType &indices) {
    std::vector rows(m, false);
    std::vector columns(n, false);

    for (const auto &[i, j] : indices) {
        rows[i] = rows[i] ^ true;
        columns[j] = columns[j] ^ true;
    }

    int odd_row = 0;
    int odd_column = 0;
    for (const auto v : rows) {
        if (v) {
            ++odd_row;
        }
    }

    for (const auto v : columns) {
        if (v) {
            ++odd_column;
        }
    }

    // odd_row * (n - odd_column) + odd_column * (m - odd_row)
    return odd_row * n + odd_column * m - 2 * odd_row * odd_column;
}

} //namespace


const ArrayType SAMPLE1 = {{0, 1}, {1, 1}};
const ArrayType SAMPLE2 = {{1, 1}, {0, 0}};


THE_BENCHMARK(CellsWithOddValues, 2, 3, SAMPLE1);

SIMPLE_TEST(CellsWithOddValues, TestSAMPLE1, 6, 2, 3, SAMPLE1);
SIMPLE_TEST(CellsWithOddValues, TestSAMPLE2, 0, 2, 2, SAMPLE2);
