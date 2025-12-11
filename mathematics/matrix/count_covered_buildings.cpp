#include "common_header.h"


namespace {

using ArrayType = std::vector<std::vector<int>>;

/**
 * @reference   Count Covered Buildings
 *              https://leetcode.com/problems/count-covered-buildings/
 *
 * You are given a positive integer n, representing an n x n city. You are also given a 2D grid
 * buildings, where buildings[i] = [x, y] denotes a unique building located at coordinates [x, y].
 * A building is covered if there is at least one building in all four directions: left, right, above,
 * and below.
 * Return the number of covered buildings.
 *
 * @tags    #matrix #hash-table #min-max-element
 */
auto CountCoveredBuildings(const int n, const ArrayType &buildings) {
    std::vector rows(n + 1, std::pair(n + 1, 0));
    std::vector columns(n + 1, std::pair(n + 1, 0));
    for (const auto &b : buildings) {
        auto &[column_min, column_max] = rows[b[0]];
        column_min = std::min(column_min, b[1]);
        column_max = std::max(column_max, b[1]);
        auto &[row_min, row_max] = columns[b[1]];
        row_min = std::min(row_min, b[0]);
        row_max = std::max(row_max, b[0]);
    }

    int result = 0;
    for (const auto &b : buildings) {
        const auto &[column_min, column_max] = rows[b[0]];
        const auto &[row_min, row_max] = columns[b[1]];
        result += column_min < b[1] and b[1] < column_max and row_min < b[0] and b[0] < row_max;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {{1, 2}, {2, 2}, {3, 2}, {2, 1}, {2, 3}};
const ArrayType SAMPLE2 = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
const ArrayType SAMPLE3 = {{1, 3}, {3, 2}, {3, 3}, {3, 5}, {5, 3}};


THE_BENCHMARK(CountCoveredBuildings, 3, SAMPLE1);

SIMPLE_TEST(CountCoveredBuildings, TestSAMPLE1, 1, 3, SAMPLE1);
SIMPLE_TEST(CountCoveredBuildings, TestSAMPLE2, 0, 3, SAMPLE2);
SIMPLE_TEST(CountCoveredBuildings, TestSAMPLE3, 1, 5, SAMPLE3);
