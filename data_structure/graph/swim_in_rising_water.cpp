#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

struct Node {
    int cost;
    unsigned row;
    unsigned column;

    constexpr Node(const int c, const unsigned x, const unsigned y):
        cost(c), row(x), column(y) {
    }
};

inline constexpr auto
operator>(const Node &lhs, const Node &rhs) {
    return lhs.cost > rhs.cost;
}

/** Swim in Rising Water
 *
 * @reference   https://leetcode.com/problems/swim-in-rising-water/
 *
 * On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).
 * Now rain starts to fall. At time t, the depth of the water everywhere is t. You can
 * swim from a square to another 4-directionally adjacent square if and only if the
 * elevation of both squares individually are at most t. You can swim infinite distance
 * in zero time. Of course, you must stay within the boundaries of the grid during your
 * swim. You start at the top left square (0, 0). What is the least time until you can
 * reach the bottom right square (N-1, N-1)?
 * 2 <= N <= 50.
 * grid[i][j] is a permutation of [0, ..., N*N - 1].
 */
auto SwimInRisingWater_Dijkstra(MatrixType grid) {
    assert(grid.size() >= 2 and grid.size() <= 50);
    assert(grid.size() == grid.front().size());

    constexpr auto VISITED = std::numeric_limits<int>::max();

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_list;
    open_list.emplace(grid[0][0], 0, 0);
    grid[0][0] = VISITED;

    while (not open_list.empty()) {
        const auto node = std::move(open_list.top());
        open_list.pop();

        if (node.row + 1 != grid.size() and grid[node.row + 1][node.column] != VISITED) {
            if (node.row + 2 == grid.size() and node.column + 1 == grid.size()) {
                return std::max(grid[node.row + 1][node.column], node.cost);
            }
            open_list.emplace(std::max(grid[node.row + 1][node.column], node.cost),
                              node.row + 1, node.column);
            grid[node.row + 1][node.column] = VISITED;
        }

        if (node.column + 1 != grid.size() and grid[node.row][node.column + 1] != VISITED) {
            if (node.row + 1 == grid.size() and node.column + 2 == grid.size()) {
                return std::max(grid[node.row][node.column + 1], node.cost);
            }
            open_list.emplace(std::max(grid[node.row][node.column + 1], node.cost),
                              node.row, node.column + 1);
            grid[node.row][node.column + 1] = VISITED;
        }

        if (node.row != 0 and grid[node.row - 1][node.column] != VISITED) {
            open_list.emplace(std::max(grid[node.row - 1][node.column], node.cost),
                              node.row - 1, node.column);
            grid[node.row - 1][node.column] = VISITED;
        }

        if (node.column != 0 and grid[node.row][node.column - 1] != VISITED) {
            open_list.emplace(std::max(grid[node.row][node.column - 1], node.cost),
                              node.row, node.column - 1);
            grid[node.row][node.column - 1] = VISITED;
        }
    }

    return -1;
}

}//namespace


const MatrixType SAMPLE1 = {
    {0, 2},
    {1, 3}
};

const MatrixType SAMPLE2 = {
    {0, 1, 2, 3, 4},
    {24, 23, 22, 21, 5},
    {12, 13, 14, 15, 16},
    {11, 17, 18, 19, 20},
    {10, 9, 8, 7, 6}
};

const MatrixType SAMPLE3 = {
    {3, 2},
    {0, 1}
};


THE_BENCHMARK(SwimInRisingWater_Dijkstra, SAMPLE1);

SIMPLE_TEST(SwimInRisingWater_Dijkstra, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(SwimInRisingWater_Dijkstra, TestSAMPLE2, 16, SAMPLE2);
SIMPLE_TEST(SwimInRisingWater_Dijkstra, TestSAMPLE3, 3, SAMPLE3);
