#include "common_header.h"

#include "data_structure/disjoint_set.h"
#include "matrix.h"


namespace {

using GridType = MatrixTypeTemplate<char>;
using ArrayType = std::vector<std::pair<int, int>>;
using RegionType = std::vector<std::string_view>;

/**
 * @reference   Number of Islands
 *              https://leetcode.com/problems/number-of-islands/
 *
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the
 * number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or
 * vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * @tags    #matrix #BFS #DFS #disjoint-set
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
 * A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand
 * operation which turns the water at position (row, col) into a land. Given a list of positions to
 * operate, count the number of islands after each addLand operation.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or
 * vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * @tags    #matrix #disjoint-set
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
 * @reference   Regions Cut By Slashes
 *              https://leetcode.com/problems/regions-cut-by-slashes/
 *
 * An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank
 * space ' '. These characters divide the square into contiguous regions.
 * Given the grid grid represented as a string array, return the number of regions.
 * Note that backslash characters are escaped, so a '\' is represented as '\\'.
 *
 * @tags    #matrix #BFS #DFS #disjoint-set
 */
auto RegionsBySlashes(const RegionType &grid) {
    const int N = grid.size();
    const int FACTOR = 3;
    const auto EXPANDED_N = N * FACTOR;

    std::vector visited(EXPANDED_N, std::vector(EXPANDED_N, false));
    for (int i = 0; i < N; ++i) {
        const auto base_row = i * FACTOR;
        for (int j = 0; j < N; ++j) {
            const auto base_column = j * FACTOR;

            if (grid[i][j] == '/') {
                visited[base_row][base_column + 2] = true;
                visited[base_row + 1][base_column + 1] = true;
                visited[base_row + 2][base_column] = true;
            } else if (grid[i][j] == '\\') {
                visited[base_row][base_column] = true;
                visited[base_row + 1][base_column + 1] = true;
                visited[base_row + 2][base_column + 2] = true;
            }
        }
    }

    int result = 0;
    for (int i = 0; i < EXPANDED_N; ++i) {
        for (int j = 0; j < EXPANDED_N; ++j) {
            if (not visited[i][j]) {
                ++result;

                std::queue<std::pair<int, int>> q;
                q.emplace(i, j);
                visited[i][j] = true;

                while (not q.empty()) {
                    const auto [r, c] = q.front();
                    q.pop();

                    for (const auto &[delta_r, delta_c] : DIRECTIONS) {
                        const auto x = r + delta_r;
                        const auto y = c + delta_c;

                        if (x >= 0 and x < EXPANDED_N and y >= 0 and y < EXPANDED_N) {
                            if (not visited[x][y]) {
                                visited[x][y] = true;
                                q.emplace(x, y);
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}


/**
 * @reference   Surrounded Regions
 *              https://leetcode.com/problems/surrounded-regions/
 *
 * Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally
 * surrounded by 'X'.
 * A region is captured by flipping all 'O's into 'X's in that surrounded region.
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


/**
 * @reference   Number of Closed Islands
 *              https://leetcode.com/problems/number-of-closed-islands/
 *
 * Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally
 * connected group of 0s and a closed island is an island totally (all left, top, right, bottom)
 * surrounded by 1s.
 * Return the number of closed islands.
 *
 * @reference   Number of Enclaves
 *              https://leetcode.com/problems/number-of-enclaves/
 *
 * You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land
 * cell.
 * A move consists of walking from one land cell to another adjacent (4-directionally) land cell or
 * walking off the boundary of the grid.
 * Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any
 * number of moves.
 */
auto NumClosedIslands(const GridType &grid,
                      const int start_i,
                      const int start_j,
                      std::vector<std::vector<bool>> &visited) {
    const int M = grid.size();
    const int N = grid.front().size();

    std::queue<std::pair<int, int>> q;
    q.emplace(start_i, start_j);
    visited[start_i][start_j] = true;

    bool is_closed = true;
    while (not q.empty()) {
        const auto [r, c] = q.front();
        q.pop();

        for (const auto &[delta_r, delta_c] : DIRECTIONS) {
            const auto new_r = r + delta_r;
            const auto new_c = c + delta_c;
            if (new_r < 0 or new_r >= M or new_c < 0 or new_c >= N) {
                is_closed = false;
            } else if (grid[new_r][new_c] == 0 and not visited[new_r][new_c]) {
                q.emplace(new_r, new_c);
                visited[new_r][new_c] = true;
            }
        }
    }

    return is_closed;
}

auto NumClosedIslands(const GridType &grid) {
    const int M = grid.size();
    const int N = grid.front().size();
    std::vector visited(M, std::vector(N, false));

    int result = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 0 and not visited[i][j] and NumClosedIslands(grid, i, j, visited)) {
                ++result;
            }
        }
    }

    return result;
}


/**
 * @reference   Most Stones Removed with Same Row or Column
 *              https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/
 *
 * On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at
 * most one stone.
 * A stone can be removed if it shares either the same row or the same column as another stone that has
 * not been removed.
 * Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith
 * stone, return the largest possible number of stones that can be removed.
 * 0 <= xi, yi <= 10^4
 */
int disjointSet_Find(std::unordered_map<int, int> &disjoint_set, const int x, int &island) {
    const auto [iter, inserted] = disjoint_set.emplace(x, x);
    if (inserted) {
        ++island;
    }

    if (x != iter->second) {
        disjoint_set[x] = disjointSet_Find(disjoint_set, iter->second, island);
    }

    return disjoint_set[x];
}

void disjointSet_Union(std::unordered_map<int, int> &disjoint_set, int x, int y, int &island) {
    x = disjointSet_Find(disjoint_set, x, island);
    y = disjointSet_Find(disjoint_set, y, island);

    if (x != y) {
        disjoint_set[x] = y;
        --island;
    }
}

int RemoveStones(const ArrayType stones) {
    std::unordered_map<int, int> disjoint_set;
    int island = 0;

    for (const auto &[x, y] : stones) {
        disjointSet_Union(disjoint_set, x, ~y, island);
    }

    return stones.size() - island;
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
const RegionType SAMPLE1RCS = {
    R"( /)",
    R"(/ )"
};

const RegionType SAMPLE2RCS = {
    R"( /)",
    R"(  )"
};

const RegionType SAMPLE3RCS = {
    R"(/\)",
    R"(\/)"
};

const RegionType SAMPLE4RCS = {
    R"(//)",
    R"(/ )"
};
// clang-format on


THE_BENCHMARK(RegionsBySlashes, SAMPLE4RCS);

SIMPLE_TEST(RegionsBySlashes, TestSAMPLE1, 2, SAMPLE1RCS);
SIMPLE_TEST(RegionsBySlashes, TestSAMPLE2, 1, SAMPLE2RCS);
SIMPLE_TEST(RegionsBySlashes, TestSAMPLE3, 5, SAMPLE3RCS);
SIMPLE_TEST(RegionsBySlashes, TestSAMPLE4, 3, SAMPLE4RCS);


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


const ArrayType SAMPLE1S = {{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}};
const ArrayType SAMPLE2S = {{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}};
const ArrayType SAMPLE3S = {{0, 0}};


THE_BENCHMARK(RemoveStones, SAMPLE1S);

SIMPLE_TEST(RemoveStones, TestSAMPLE1, 5, SAMPLE1S);
SIMPLE_TEST(RemoveStones, TestSAMPLE2, 3, SAMPLE2S);
SIMPLE_TEST(RemoveStones, TestSAMPLE3, 0, SAMPLE3S);


// clang-format off
const GridType SAMPLE1C = {
    {1, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 1, 1, 0},
    {1, 0, 1, 0, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0}
};

const GridType SAMPLE2C = {
    {0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0}
};

const GridType SAMPLE3C = {
    {1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1}
};
// clang-format on


THE_BENCHMARK(NumClosedIslands, SAMPLE1C);

SIMPLE_TEST(NumClosedIslands, TestSAMPLE1, 2, SAMPLE1C);
SIMPLE_TEST(NumClosedIslands, TestSAMPLE2, 1, SAMPLE2C);
SIMPLE_TEST(NumClosedIslands, TestSAMPLE3, 2, SAMPLE3C);
