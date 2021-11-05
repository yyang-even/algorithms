#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/**
 * @reference   Matrix Cells in Distance Order
 *              https://leetcode.com/problems/matrix-cells-in-distance-order/
 *
 * You are given four integers row, cols, rCenter, and cCenter. There is a rows x cols
 * matrix and you are on the cell with the coordinates (rCenter, cCenter). Return the
 * coordinates of all cells in the matrix, sorted by their distance from (rCenter, cCenter)
 * from the smallest distance to the largest distance. You may return the answer in any
 * order that satisfies this condition. The distance between two cells (r1, c1) and
 * (r2, c2) is |r1 - r2| + |c1 - c2|.
 */
auto OrderByDistance_CountingSort(const int rows, const int cols,
                                  const int r_center, const int c_center) {
    const auto length = std::max(r_center, rows - 1 - r_center) +
                        std::max(c_center, cols - 1 - c_center) + 1;
    int count[length] = {};
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            ++count[std::abs(r_center - i) + std::abs(c_center - j)];
        }
    }

    for (int i = 1; i < length; ++i) {
        count[i] += count[i - 1];
    }

    ArrayType result(count[length - 1]);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            const auto index = --count[std::abs(r_center - i) + std::abs(c_center - j)];
            result[index] = {i, j};
        }
    }

    return result;
}


auto OrderByDistance_Graph(const int rows, const int cols,
                           const int r_center, const int c_center) {
    std::vector visited(rows, std::vector(cols, false));
    visited[r_center][c_center] = true;
    std::queue<std::pair<int, int>> q;
    q.emplace(r_center, c_center);

    ArrayType result;
    while (not q.empty()) {
        const auto [i, j] = q.front();
        q.pop();

        result.emplace_back(i, j);

        ForEachDirection(rows, cols, i, j,
        [&visited, &q](const auto r, const auto c) {
            if (not visited[r][c]) {
                visited[r][c] = true;
                q.emplace(r, c);
            }
        });
    }

    return result;
}

}//namespace


const ArrayType EXPECTED1 = {{0, 0}, {0, 1}};
const ArrayType EXPECTED2 = {{0, 1}, {1, 1}, {0, 0}, {1, 0}};
const ArrayType EXPECTED3 = {{1, 2}, {1, 1}, {0, 2}, {1, 0}, {0, 1}, {0, 0}};


THE_BENCHMARK(OrderByDistance_CountingSort, 2, 3, 1, 2);

SIMPLE_TEST(OrderByDistance_CountingSort, TestSAMPLE1, EXPECTED1, 1, 2, 0, 0);
SIMPLE_TEST(OrderByDistance_CountingSort, TestSAMPLE2, EXPECTED2, 2, 2, 0, 1);
SIMPLE_TEST(OrderByDistance_CountingSort, TestSAMPLE3, EXPECTED3, 2, 3, 1, 2);


const ArrayType EXPECTED2G = {{0, 1}, {0, 0}, {1, 1}, {1, 0}};


THE_BENCHMARK(OrderByDistance_Graph, 2, 3, 1, 2);

SIMPLE_TEST(OrderByDistance_Graph, TestSAMPLE1, EXPECTED1, 1, 2, 0, 0);
SIMPLE_TEST(OrderByDistance_Graph, TestSAMPLE2, EXPECTED2G, 2, 2, 0, 1);
SIMPLE_TEST(OrderByDistance_Graph, TestSAMPLE3, EXPECTED3, 2, 3, 1, 2);
