#include "common_header.h"

#include "data_structure/disjoint_set.h"
#include "matrix.h"


namespace {

using GridType = MatrixTypeTemplate<char>;
using ArrayType = std::vector<std::pair<int, int>>;

/** Number of Islands
 *
 * @reference   https://leetcode.com/problems/number-of-islands/
 *
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's
 * (water), return the number of islands. An island is surrounded by water and is
 * formed by connecting adjacent lands horizontally or vertically. You may assume all
 * four edges of the grid are all surrounded by water.
 */
auto NumberIslands_BFS(GridType grid) {
    const auto M = grid.size();
    const auto N = grid.front().size();

    int result = 0;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == '1') {
                ++result;

                grid[i][j] = '0';
                std::queue<std::pair<int, int>> q;
                q.emplace(i, j);

                while (not q.empty()) {
                    const auto [row, column] = q.front();
                    q.pop();
                    ForEachDirection(M, N, row, column, [&grid, &q](const auto x, const auto y) {
                        if (grid[x][y] == '1') {
                            grid[x][y] = '0';
                            q.emplace(x, y);
                        }
                    });
                }
            }
        }
    }

    return result;
}


auto eraseIslands(GridType &grid, const int i, const int j) {
    const int M = grid.size();
    const int N = grid.front().size();

    if (i < 0 or i == M or j < 0 or j == N or grid[i][j] == '0') {
        return;
    }

    grid[i][j] = '0';
    eraseIslands(grid, i - 1, j);
    eraseIslands(grid, i + 1, j);
    eraseIslands(grid, i, j - 1);
    eraseIslands(grid, i, j + 1);
}

auto NumberIslands_DFS(GridType grid) {
    const auto M = grid.size();
    const auto N = grid.front().size();

    int result = 0;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == '1') {
                ++result;
                eraseIslands(grid, i, j);
            }
        }
    }

    return result;
}


/**
 * @reference   Number of Islands II
 *              https://www.cnblogs.com/grandyang/p/5190419.html
 *
 * A 2d grid map of m rows and n columns is initially filled with water. We may perform
 * an addLand operation which turns the water at position (row, col) into a land. Given
 * a list of positions to operate, count the number of islands after each addLand
 * operation. An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically. You may assume all four edges of the grid are all surrounded
 * by water.
 */
inline int disjointSet_Find(std::vector<int> &disjoint_set, const int i) {
    auto &parent = disjoint_set[i];
    if (parent != -1 and parent != i) {
        parent = disjointSet_Find(disjoint_set, parent);
    }
    return parent;
}

inline bool disjointSet_Union(std::vector<int> &disjoint_set, const int x, const int y) {
    const auto x_parent = disjointSet_Find(disjoint_set, x);
    const auto y_parent = disjointSet_Find(disjoint_set, y);
    if (x_parent != y_parent) {
        disjoint_set[y] = x;
        return true;
    }

    return false;
}

auto NumberIslandsStream(const int m, const int n, const ArrayType &positions) {
    std::vector<int> disjoint_set(m * n, -1);
    std::vector<int> result;
    int count = 0;
    for (const auto &[x, y] : positions) {
        const auto index = n * x + y;
        auto parent = disjointSet_Find(disjoint_set, index);
        if (parent == -1) {

            disjoint_set[index] = index;
            ++count;

            ForEachDirection(
                m, n, x, y, [n, &disjoint_set, index, &count](const auto r, const auto c) {
                    const auto i = n * r + c;
                    const auto neighbor_parent = disjointSet_Find(disjoint_set, i);
                    if (neighbor_parent != -1) {
                        if (disjointSet_Union(disjoint_set, index, neighbor_parent)) {
                            --count;
                        }
                    }
                });
        }

        result.push_back(count);
    }

    return result;
}


/**
 * @reference   Surrounded Regions
 *              https://leetcode.com/problems/surrounded-regions/
 *
 * Given an m x n matrix board containing 'X' and 'O', capture all regions that are
 * 4-directionally surrounded by 'X'. A region is captured by flipping all 'O's into
 * 'X's in that surrounded region.
 */
inline void
onCell(GridType &board, std::queue<std::pair<int, int>> &q, const int i, const int j) {
    if (board[i][j] == 'O') {
        q.emplace(i, j);
        board[i][j] = 'B';
    }
}

auto SurroundedRegions(GridType board) {
    const auto M = board.size();
    const auto N = board.front().size();
    if (M <= 2 or N <= 2) {
        return board;
    }

    std::queue<std::pair<int, int>> q;
    for (std::size_t i = 0; i < M; ++i) {
        onCell(board, q, i, 0);
        onCell(board, q, i, N - 1);
    }

    for (std::size_t j = 0; j < N; ++j) {
        onCell(board, q, 0, j);
        onCell(board, q, M - 1, j);
    }

    while (not q.empty()) {
        const auto [i, j] = q.front();
        q.pop();

        ForEachDirection(M, N, i, j, [&board, &q](const auto r, const auto c) {
            onCell(board, q, r, c);
        });
    }

    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (board[i][j] != 'X') {
                board[i][j] = (board[i][j] == 'O' ? 'X' : 'O');
            }
        }
    }

    return board;
}


auto SurroundedRegions_UF(GridType board) {
    const auto M = board.size();
    const auto N = board.front().size();
    if (M <= 2 or N <= 2) {
        return board;
    }

    DisjointSet_Array disjoint_set(M * N + 1);
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (board[i][j] == 'O') {
                if (i == 0 or i == M - 1 or j == 0 or j == N - 1) {
                    disjoint_set.Union(i * N + j, M * N);
                } else {
                    if (board[i - 1][j] == 'O') {
                        disjoint_set.Union(i * N + j, (i - 1) * N + j);
                    }
                    if (board[i][j - 1] == 'O') {
                        disjoint_set.Union(i * N + j, i * N + j - 1);
                    }
                }
            }
        }
    }

    const auto dummy_parent = disjoint_set.Find(M * N);
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (dummy_parent != disjoint_set.Find(i * N + j)) {
                board[i][j] = 'X';
            }
        }
    }

    return board;
}

} //namespace


// clang-format off
const GridType SAMPLE1 = {
    {'1', '1', '1', '1', '0'},
    {'1', '1', '0', '1', '0'},
    {'1', '1', '0', '0', '0'},
    {'0', '0', '0', '0', '0'}
};

const GridType SAMPLE2 = {
    {'1', '1', '0', '0', '0'},
    {'1', '1', '0', '0', '0'},
    {'0', '0', '1', '0', '0'},
    {'0', '0', '0', '1', '1'}
};
// clang-format on


THE_BENCHMARK(NumberIslands_BFS, SAMPLE1);

SIMPLE_TEST(NumberIslands_BFS, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(NumberIslands_BFS, TestSAMPLE2, 3, SAMPLE2);


THE_BENCHMARK(NumberIslands_DFS, SAMPLE1);

SIMPLE_TEST(NumberIslands_DFS, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(NumberIslands_DFS, TestSAMPLE2, 3, SAMPLE2);


const ArrayType SAMPLE1P = {{0, 0}, {0, 1}, {1, 2}, {2, 1}};
const std::vector EXPECTED1 = {1, 1, 2, 3};


THE_BENCHMARK(NumberIslandsStream, 3, 3, SAMPLE1P);

SIMPLE_TEST(NumberIslandsStream, TestSAMPLE1, EXPECTED1, 3, 3, SAMPLE1P);


// clang-format off
const GridType SAMPLE1R = {
    {'X', 'X', 'X', 'X'},
    {'X', 'O', 'O', 'X'},
    {'X', 'X', 'O', 'X'},
    {'X', 'O', 'X', 'X'}
};

const GridType EXPECTED1R = {
    {'X', 'X', 'X', 'X'},
    {'X', 'X', 'X', 'X'},
    {'X', 'X', 'X', 'X'},
    {'X', 'O', 'X', 'X'}
};
// clang-format on

const GridType SAMPLE2R = {{'X'}};


THE_BENCHMARK(SurroundedRegions, SAMPLE1R);

SIMPLE_TEST(SurroundedRegions, TestSAMPLE1, EXPECTED1R, SAMPLE1R);
SIMPLE_TEST(SurroundedRegions, TestSAMPLE2, SAMPLE2R, SAMPLE2R);


THE_BENCHMARK(SurroundedRegions_UF, SAMPLE1R);

SIMPLE_TEST(SurroundedRegions_UF, TestSAMPLE1, EXPECTED1R, SAMPLE1R);
SIMPLE_TEST(SurroundedRegions_UF, TestSAMPLE2, SAMPLE2R, SAMPLE2R);
