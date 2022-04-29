#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"

#include "mathematics/matrix/matrix.h"


using namespace graph;

using TableType = MatrixTypeTemplate<unsigned>;

namespace {

bool Relax(std::vector<int> &distances,
           const std::size_t from, const std::size_t to, const int weight,
           std::vector<int> *parents = nullptr) {
    if (distances[from] != std::numeric_limits<int>::max()) {
        const auto new_weight = distances[from] + weight;
        if (distances[to] > new_weight) {
            distances[to] = new_weight;
            if (parents) {
                (*parents)[to] = from;
            }

            return true;
        }
    }

    return false;
}

inline void Relax(std::vector<int> &distances,
                  std::vector<int> &parents,
                  const DirectedEdge &edge) {
    Relax(distances, edge.from, edge.to, edge.weight, &parents);
}

/** Single-source Shortest Paths
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 24.1.
 * @reference   Bellman–Ford Algorithm | DP-23
 *              https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
 * @reference   Bellman Ford Algorithm (Simple Implementation)
 *              https://www.geeksforgeeks.org/bellman-ford-algorithm-simple-implementation/
 *
 * Given a graph and a source vertex src in graph, find shortest paths from src to all
 * vertices in the given graph. The graph may contain negative weight edges.
 *
 * Dijkstra doesn't work for Graphs with negative weight edges, Bellman-Ford works for
 * such graphs. Bellman-Ford is also simpler than Dijkstra and suites well for
 * distributed systems. But time complexity of Bellman-Ford is O(VE), which is more than
 * Dijkstra.
 */
auto SingleSourceShortestPaths_BellmanFord(const std::size_t number_vertices,
                                           const DirectedEdgeArrayType &edges,
                                           const std::size_t source,
                                           std::pair<int, std::vector<int>> *negative_cycle_pair = nullptr) {
    assert(source < number_vertices);

    std::vector<int>
    distances_from_source(number_vertices, std::numeric_limits<int>::max());
    distances_from_source[source] = 0;
    std::vector<int> parents(number_vertices, -1);

    for (std::size_t i = 1; i < number_vertices; ++i) {
        for (const auto &one_edge : edges) {
            Relax(distances_from_source, parents, one_edge);
        }
    }

    for (const auto &one_edge : edges) {
        if (distances_from_source[one_edge.from] != std::numeric_limits<int>::max() and
            distances_from_source[one_edge.to] >
            (distances_from_source[one_edge.from] + one_edge.weight)) {
            if (negative_cycle_pair) {
                negative_cycle_pair->first = one_edge.to;
                negative_cycle_pair->second = parents;
            }
            return std::pair(false, distances_from_source);
        }
    }

    return std::pair(true, distances_from_source);
}


/**
 * @reference   Minimum Cost of Simple Path between two nodes in a Directed and Weighted Graph
 *              https://www.geeksforgeeks.org/minimum-cost-of-simple-path-between-two-nodes-in-a-directed-and-weighted-graph/
 *
 * @note    This is a brute force solution.
 */


/**
 * @reference   Detect a negative cycle in a Graph | (Bellman Ford)
 *              https://www.geeksforgeeks.org/detect-negative-cycle-graph-bellman-ford/
 */
auto hasNegativeCycle(const std::size_t number_vertices,
                      const DirectedEdgeArrayType &edges) {
    std::vector<bool> visited_vertices(number_vertices, false);

    for (std::size_t i = 0; i < number_vertices; ++i) {
        if (not visited_vertices[i]) {
            const auto &[no_negative_cycle, distances_from_source] =
                SingleSourceShortestPaths_BellmanFord(number_vertices, edges, i);
            if (not no_negative_cycle) {
                return true;
            }

            for (std::size_t i = 0; i < number_vertices; ++i) {
                if (distances_from_source[i] != std::numeric_limits<int>::max()) {
                    visited_vertices[i] = true;
                }
            }
        }
    }

    return false;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 24.1-6.
 * @reference   Print negative weight cycle in a Directed Graph
 *              https://www.geeksforgeeks.org/print-negative-weight-cycle-in-a-directed-graph/
 */
auto PrintNegativeWeightCycle(const std::size_t number_vertices,
                              const DirectedEdgeArrayType &edges,
                              const std::size_t source) {
    std::pair<int, std::vector<int>> negative_cycle_pair{};
    const auto result_pair =
        SingleSourceShortestPaths_BellmanFord(
            number_vertices, edges, source, &negative_cycle_pair);

    std::unordered_set<std::size_t> results;
    if (not result_pair.first) {
        auto cycle_start = negative_cycle_pair.first;
        const auto &parents = negative_cycle_pair.second;

        for (std::size_t i = 0; i < number_vertices; ++i) {
            cycle_start = parents[cycle_start];
        }

        auto vertex = cycle_start;
        do {
            results.insert(vertex);
            vertex = parents[vertex];
        } while (vertex != cycle_start);
    }

    return results;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 24.2.
 * @reference   Shortest Path in Directed Acyclic Graph
 *              https://www.geeksforgeeks.org/shortest-path-for-directed-acyclic-graphs/
 */
auto SingleSourceShortestPaths_DAG(const std::size_t number_vertices,
                                   const DirectedEdgeArrayType &edges,
                                   const std::size_t source) {
    assert(source < number_vertices);

    WeightedAdjacencyListGraph graph{number_vertices, edges};

    ArrayType topological_order;
    GraphTraverse(graph,
    [&topological_order](const auto & graph, const auto source, auto & visited_vertices) {
        TopologicalSort(graph, source, visited_vertices, topological_order);
        return true;
    });

    std::vector<int>
    distances_from_source(number_vertices, std::numeric_limits<int>::max());
    distances_from_source[source] = 0;

    for (auto iter = topological_order.crbegin();
         iter != topological_order.crend();
         ++iter) {
        const auto from = *iter;
        graph.Visit([from, &distances_from_source](const auto & graph) {
            for (const auto &node : graph[from]) {
                Relax(distances_from_source, from, node.destination, node.weight);
            }
        });
    }

    return distances_from_source;
}


/**
 * @reference   Shortest path in an unweighted graph
 *              https://www.geeksforgeeks.org/shortest-path-unweighted-graph/
 */
auto SingleSourceShortestPaths_Unweighted_Undirected_BFS(
    const AdjacencyListGraph::RepresentationType &graph,
    const std::size_t source,
    const std::size_t destination,
    std::vector<int> &distances_from_source,
    std::vector<int> &parents) {
    std::queue<std::size_t> gray_vertex_queue;
    gray_vertex_queue.push(source);

    std::vector<bool> visited_vertices(graph.size(), false);
    visited_vertices[source] = true;

    while (not gray_vertex_queue.empty()) {
        const auto vertex = gray_vertex_queue.front();
        gray_vertex_queue.pop();

        for (const auto adjacent_vertex : graph.at(vertex)) {
            if (not visited_vertices[adjacent_vertex]) {
                visited_vertices[adjacent_vertex] = true;
                distances_from_source[adjacent_vertex] = distances_from_source[vertex] + 1;
                parents[adjacent_vertex] = vertex;
                gray_vertex_queue.push(adjacent_vertex);

                if (adjacent_vertex == destination) {
                    return true;
                }
            }
        }
    }

    return false;
}

auto SingleSourceShortestPaths_Unweighted_Undirected_BFS(
    const std::size_t number_vertices,
    const UndirectedEdgeArrayType &edges,
    const std::size_t source,
    const std::size_t destination) {
    assert(source < number_vertices);
    assert(destination < number_vertices);

    AdjacencyListGraph graph{number_vertices, edges};

    std::vector<int>
    distances_from_source(number_vertices, std::numeric_limits<int>::max());
    distances_from_source[source] = 0;
    std::vector<int> parents(number_vertices, -1);

    const auto path_found = graph.Visit(
    [source, destination, &distances_from_source, &parents](const auto & graph) {
        return SingleSourceShortestPaths_Unweighted_Undirected_BFS(
                   graph, source, destination, distances_from_source, parents);
    });

    ArrayType path;
    if (path_found) {
        for (int i = destination; i != -1; i = parents[i]) {
            path.push_back(i);
        }
        std::reverse(path.begin(), path.end());
    }

    return path;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 24.3.
 * @reference   Dijkstra’s shortest path algorithm | Greedy Algo-7
 *              https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
 * @reference   C / C++ Program for Dijkstra’s shortest path algorithm | Greedy Algo-7
 *              https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/
 * @reference   Dijkstra’s Algorithm for Adjacency List Representation | Greedy Algo-8
 *              https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
 * @reference   Dijkstra’s shortest path algorithm using set in STL
 *              https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-set-in-stl/
 * @reference   Dijkstra’s Shortest Path Algorithm using priority_queue of STL
 *              https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
 * @reference   What are the differences between Bellman Ford’s and Dijkstra’s algorithms?
 *              https://www.geeksforgeeks.org/what-are-the-differences-between-bellman-fords-and-dijkstras-algorithms/
 */
using CostVertexPair = std::pair<int, std::size_t>;

auto SingleSourceShortestPaths_Dijkstra(
    const WeightedAdjacencyListGraph::RepresentationType &graph,
    const std::size_t source,
    std::vector<int> *parents = nullptr) {
    std::vector<int> distances_from_source(graph.size(), std::numeric_limits<int>::max());
    distances_from_source[source] = 0;

    if (parents) {
        (*parents)[source] = -1;
    }

    std::priority_queue<CostVertexPair, std::vector<CostVertexPair>, std::greater<CostVertexPair>>
            open_list;
    open_list.emplace(0, source);

    std::vector<bool> closed_vertices(graph.size(), false);

    while (not open_list.empty()) {
        const auto from_vertex = open_list.top().second;
        open_list.pop();

        if (not closed_vertices[from_vertex]) {
            for (const auto &node : graph[from_vertex]) {
                if (Relax(distances_from_source, from_vertex, node.destination, node.weight, parents)) {
                    open_list.emplace(distances_from_source[node.destination], node.destination);
                }
            }

            closed_vertices[from_vertex] = true;
        }
    }

    return distances_from_source;
}

/**
 * @reference   Shortest path in a directed graph by Dijkstra’s algorithm
 *              https://www.geeksforgeeks.org/shortest-path-in-a-directed-graph-by-dijkstras-algorithm/
 */
template <typename EdgeArrayType>
inline constexpr auto
SingleSourceShortestPaths_Dijkstra(const std::size_t number_vertices,
                                   const EdgeArrayType &edges,
                                   const std::size_t source) {
    return WeightedAdjacencyListGraph{number_vertices, edges}.Visit(
    [source](const auto & graph) {
        return SingleSourceShortestPaths_Dijkstra(graph, source);
    });
}


/**
 * @reference   Min Cost Path | DP-6
 *              https://www.geeksforgeeks.org/min-cost-path-dp-6/
 * @reference   C Program for Min Cost Path
 *              https://www.geeksforgeeks.org/c-program-for-min-cost-path/
 *
 * Given a cost matrix cost[][] and a position (m, n) in cost[][], write a function that
 * returns cost of minimum cost path to reach (m, n) from (0, 0). Each cell of the matrix
 * represents a cost to traverse through that cell. Total cost of a path to reach (m, n)
 * is sum of all the costs on that path (including both source and destination). You can
 * only traverse down, right and diagonally lower cells from a given cell, i.e., from a
 * given cell (i, j), cells (i+1, j), (i, j+1) and (i+1, j+1) can be traversed. You may
 * assume that all costs are positive integers.
 */
auto MinCostPath(TableType costs, const std::size_t m, const std::size_t n) {
    assert(m < costs.size());
    assert(n < costs.front().size());

    for (std::size_t i = 1 ; i <= m ; ++i) {
        costs[i][0] += costs[i - 1][0];
    }

    for (std::size_t j = 1 ; j <= n ; ++j) {
        costs[0][j] += costs[0][j - 1];
    }

    for (std::size_t i = 1 ; i <= m ; ++i) {
        for (std::size_t j = 1 ; j <= n ; ++j) {
            costs[i][j] += std::min({costs[i - 1][j - 1], costs[i - 1][j], costs[i][j - 1]});
        }
    }

    return costs[m][n];
}


/**
 * @reference   Printing Paths in Dijkstra’s Shortest Path Algorithm
 *              https://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/
 */
inline void PrintOneSingleSourceShortestPath_Dijkstra(const std::vector<int> &parents,
                                                      const int i, ArrayType &path) {
    if (i != -1) {
        PrintOneSingleSourceShortestPath_Dijkstra(parents, parents[i], path);
        path.push_back(i);
    }
}

auto PrintSingleSourceShortestPaths_Dijkstra(const std::size_t number_vertices,
                                             const UndirectedEdgeArrayType &edges,
                                             const std::size_t source) {
    std::vector<int> parents(number_vertices, -1);
    WeightedAdjacencyListGraph{number_vertices, edges}.Visit(
    [source, &parents](const auto & graph) {
        return SingleSourceShortestPaths_Dijkstra(graph, source, &parents);
    });

    std::vector<ArrayType> results;
    for (std::size_t i = 0; i < number_vertices; ++i) {
        results.emplace_back();
        PrintOneSingleSourceShortestPath_Dijkstra(parents, i, results.back());
    }

    return results;
}


/**
 * @reference   Shortest Path in a Grid with Obstacles Elimination
 *              https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
 * @reference   https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-1293-shortest-path-in-a-grid-with-obstacles-elimination/
 *
 * You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1
 * (obstacle). You can move up, down, left, or right from and to an empty cell in one
 * step. Return the minimum number of steps to walk from the upper left corner (0, 0) to
 * the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles.
 * If it is not possible to find such walk return -1.
 */
auto ShortestPathsWithObstaclesElimination(const MatrixType &grid, const int k) {
    assert(not grid.empty());

    const int M = grid.size();
    const int N = grid.front().size();

    std::vector seen(M, std::vector(N, INT_MAX));
    seen[0][0] = 0;
    std::queue<std::tuple<int, int, int>> q;
    q.emplace(0, 0, 0);
    int step = 0;

    while (not q.empty()) {
        for (int size = q.size(); size-- > 0;) {
            const auto [x, y, obstacle_eliminated] = q.front();
            q.pop();

            if (x + 1 == M and y + 1 == N) {
                return step;
            }

            ForEachDirection(M, N, x, y,
            [k, &grid, &seen, obstacle_eliminated, &q](const auto new_x, const auto new_y) {
                const auto new_obstacle = obstacle_eliminated + grid[new_x][new_y];
                if (new_obstacle < seen[new_x][new_y] and new_obstacle <= k) {
                    seen[new_x][new_y] = new_obstacle;
                    q.emplace(new_x, new_y, new_obstacle);
                }
            });
        }

        ++step;
    }

    return -1;
}


/**
 * @reference   Dungeon Game
 *              https://leetcode.com/problems/dungeon-game/
 *
 * The demons had captured the princess and imprisoned her in the bottom-right corner of
 * a dungeon. The dungeon consists of m x n rooms laid out in a 2D grid. Our valiant
 * knight was initially positioned in the top-left room and must fight his way through
 * dungeon to rescue the princess. The knight has an initial health point represented by
 * a positive integer. If at any point his health point drops to 0 or below, he dies
 * immediately. Some of the rooms are guarded by demons (represented by negative integers),
 * so the knight loses health upon entering these rooms; other rooms are either empty
 * (represented as 0) or contain magic orbs that increase the knight's health (represented
 * by positive integers). To reach the princess as quickly as possible, the knight decides
 * to move only rightward or downward in each step. Return the knight's minimum initial
 * health so that he can rescue the princess. Note that any room can contain threats or
 * power-ups, even the first room the knight enters and the bottom-right room where the
 * princess is imprisoned.
 */
auto DungeonGame_DP(const MatrixType &dungeon) {
    const int M = dungeon.size();
    const int N = dungeon.front().size();
    std::vector dp(M + 1, std::vector(N + 1, INT_MAX));

    dp[M - 1][N] = dp[M][N - 1] = 1;
    for (int i = M - 1; i >= 0; --i) {
        for (int j = N - 1; j >= 0; --j) {
            dp[i][j] = std::max(1, std::min(dp[i][j + 1], dp[i + 1][j]) - dungeon[i][j]);
        }
    }

    return dp[0][0];
}


auto DungeonGame_Dijkstra(const MatrixType &dungeon) {
    const int M = dungeon.size();
    const int N = dungeon.front().size();
    std::priority_queue<std::tuple<int, int, int>> q;
    q.emplace(dungeon[0][0], 0, 0);
    std::vector seen(M, std::vector(N, INT_MIN));
    seen[0][0] = dungeon[0][0];
    int result = 0;

    while (not q.empty()) {
        const auto [health, x, y] = q.top();
        q.pop();

        if (health < 0) {
            result = std::max(-health, result);
        }

        if (x + 1 == M and y + 1 == N) {
            break;
        }

        if (x + 1 < M) {
            const auto new_health = health + dungeon[x + 1][y];
            if (new_health > seen[x + 1][y]) {
                q.emplace(new_health, x + 1, y);
                seen[x + 1][y] = new_health;
            }
        }

        if (y + 1 < N) {
            const auto new_health = health + dungeon[x][y + 1];
            if (new_health > seen[x][y + 1]) {
                q.emplace(new_health, x, y + 1);
                seen[x][y + 1] = new_health;
            }
        }
    }

    return result + 1;
}


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


/**
 * @reference   Path With Minimum Effort
 *              https://leetcode.com/problems/path-with-minimum-effort/
 *
 * You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of
 * size rows x columns, where heights[row][col] represents the height of cell (row, col).
 * You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right
 * cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right,
 * and you wish to find a route that requires the minimum effort.
 * A route's effort is the maximum absolute difference in heights between two consecutive
 * cells of the route.
 * Return the minimum effort required to travel from the top-left cell to the bottom-right
 * cell.
 */
using NodeType = std::tuple<int, int, int>;

auto MinimumEffortPath_Dijkstra(const MatrixType &heights) {
    const int M = heights.size();
    const int N = heights.front().size();
    std::vector efforts(M, std::vector(N, INT_MAX));
    std::priority_queue<NodeType, std::vector<NodeType>, std::greater<NodeType>> q;
    q.emplace(0, 0, 0);

    while (not q.empty()) {
        const auto [e, x, y] = q.top();
        q.pop();

        if (e > efforts[x][y]) {
            continue;
        }

        if (x == M - 1 and y == N - 1) {
            return e;
        }

        const auto h = heights[x][y];
        if (x > 0) {
            const auto new_effort = std::max(e, std::abs(heights[x - 1][y] - h));
            if (efforts[x - 1][y] > new_effort) {
                efforts[x - 1][y] = new_effort;
                q.emplace(new_effort, x - 1, y);
            }
        }
        if (x < M - 1) {
            const auto new_effort = std::max(e, std::abs(heights[x + 1][y] - h));
            if (efforts[x + 1][y] > new_effort) {
                efforts[x + 1][y] = new_effort;
                q.emplace(new_effort, x + 1, y);
            }
        }
        if (y > 0) {
            const auto new_effort = std::max(e, std::abs(heights[x][y - 1] - h));
            if (efforts[x][y - 1] > new_effort) {
                efforts[x][y - 1] = new_effort;
                q.emplace(new_effort, x, y - 1);
            }
        }
        if (y < N - 1) {
            const auto new_effort = std::max(e, std::abs(heights[x][y + 1] - h));
            if (efforts[x][y + 1] > new_effort) {
                efforts[x][y + 1] = new_effort;
                q.emplace(new_effort, x, y + 1);
            }
        }
    }

    return 0;
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}};
const auto EXPECTED1 = std::pair(true,
std::vector {
    0, -1, 2, -2, 1
});


THE_BENCHMARK(SingleSourceShortestPaths_BellmanFord, 5, SAMPLE1, 0);

SIMPLE_TEST(SingleSourceShortestPaths_BellmanFord, TestSAMPLE1, EXPECTED1,
            5, SAMPLE1, 0);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1, 1}, {1, 2, -1}, {2, 3, -1}, {3, 0, -1}};
const std::unordered_set<std::size_t> EXPECTED2 = {0, 1, 2, 3};


THE_BENCHMARK(hasNegativeCycle, 5, SAMPLE1);

SIMPLE_TEST(hasNegativeCycle, TestSAMPLE1, false, 5, SAMPLE1);
SIMPLE_TEST(hasNegativeCycle, TestSAMPLE2, true, 4, SAMPLE2);


THE_BENCHMARK(PrintNegativeWeightCycle, 4, SAMPLE2, 0);

SIMPLE_TEST(PrintNegativeWeightCycle, TestSAMPLE2, EXPECTED2, 4, SAMPLE2, 0);


const DirectedEdgeArrayType SAMPLE3 = {{0, 1, 5}, {0, 2, 3}, {1, 3, 6}, {1, 2, 2}, {2, 4, 4}, {2, 5, 2}, {2, 3, 7}, {3, 4, -1}, {4, 5, -2}};
const std::vector<int> EXPECTED3 = {std::numeric_limits<int>::max(), 0, 2, 6, 5, 3};


THE_BENCHMARK(SingleSourceShortestPaths_DAG, 6, SAMPLE3, 1);

SIMPLE_TEST(SingleSourceShortestPaths_DAG, TestSAMPLE3, EXPECTED3, 6, SAMPLE3, 1);


const UndirectedEdgeArrayType SAMPLE4 = {{0, 1}, {0, 3}, {1, 2}, {3, 4}, {3, 7}, {4, 5}, {4, 6}, {4, 7}, {5, 6}, {6, 7}};
const ArrayType EXPECTED4 = {0, 3, 7};


THE_BENCHMARK(SingleSourceShortestPaths_Unweighted_Undirected_BFS, 8, SAMPLE4, 0, 7);

SIMPLE_TEST(SingleSourceShortestPaths_Unweighted_Undirected_BFS, TestSAMPLE4,
            EXPECTED4, 8, SAMPLE4, 0, 7);


const UndirectedEdgeArrayType SAMPLE5 = {{0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11}, {2, 3, 7}, {2, 8, 2}, {2, 5, 4}, {3, 4, 9}, {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1}, {6, 8, 6}, {7, 8, 7}};
const std::vector<int> EXPECTED5 = {0, 4, 12, 19, 21, 11, 9, 8, 14};
const std::vector<ArrayType> EXPECTED_PATHS5 = {{0}, {0, 1}, {0, 1, 2}, {0, 1, 2, 3}, {0, 7, 6, 5, 4}, {0, 7, 6, 5}, {0, 7, 6}, {0, 7}, {0, 1, 2, 8}};

const DirectedEdgeArrayType SAMPLE6 = {{0, 1, 1}, {0, 2, 4}, {1, 2, 2}, {1, 3, 6}, {2, 3, 3}};
const std::vector<int> EXPECTED6 = {0, 1, 3, 6};


THE_BENCHMARK(SingleSourceShortestPaths_Dijkstra, 9, SAMPLE5, 0);

SIMPLE_TEST(SingleSourceShortestPaths_Dijkstra, TestSAMPLE5, EXPECTED5, 9, SAMPLE5, 0);
SIMPLE_TEST(SingleSourceShortestPaths_Dijkstra, TestSAMPLE6, EXPECTED6, 4, SAMPLE6, 0);


THE_BENCHMARK(PrintSingleSourceShortestPaths_Dijkstra, 9, SAMPLE5, 0);

SIMPLE_TEST(PrintSingleSourceShortestPaths_Dijkstra, TestSAMPLE5, EXPECTED_PATHS5,
            9, SAMPLE5, 0);


const TableType COSTS1 = {
    {1, 2, 3},
    {4, 8, 2},
    {1, 5, 3}
};


THE_BENCHMARK(MinCostPath, COSTS1, 2, 2);

SIMPLE_TEST(MinCostPath, TestSAMPLE1, 8, COSTS1, 2, 2);


const MatrixType SAMPLE1M = {
    {0, 0, 0},
    {1, 1, 0},
    {0, 0, 0},
    {0, 1, 1},
    {0, 0, 0}
};

const MatrixType SAMPLE2M = {
    {0, 1, 1},
    {1, 1, 1},
    {1, 0, 0}
};


THE_BENCHMARK(ShortestPathsWithObstaclesElimination, SAMPLE1M, 1);

SIMPLE_TEST(ShortestPathsWithObstaclesElimination, TestSAMPLE1, 6, SAMPLE1M, 1);
SIMPLE_TEST(ShortestPathsWithObstaclesElimination, TestSAMPLE2, -1, SAMPLE2M, 1);


const MatrixType SAMPLE1D = {
    {-2, -3, 3},
    {-5, -10, 1},
    {10, 30, -5}
};

const MatrixType SAMPLE2D = {
    {0}
};


THE_BENCHMARK(DungeonGame_DP, SAMPLE1D);

SIMPLE_TEST(DungeonGame_DP, TestSAMPLE1, 7, SAMPLE1D);
SIMPLE_TEST(DungeonGame_DP, TestSAMPLE2, 1, SAMPLE2D);


THE_BENCHMARK(DungeonGame_Dijkstra, SAMPLE1D);

SIMPLE_TEST(DungeonGame_Dijkstra, TestSAMPLE1, 7, SAMPLE1D);
SIMPLE_TEST(DungeonGame_Dijkstra, TestSAMPLE2, 1, SAMPLE2D);


const MatrixType SAMPLE1S = {
    {0, 2},
    {1, 3}
};

const MatrixType SAMPLE2S = {
    {0, 1, 2, 3, 4},
    {24, 23, 22, 21, 5},
    {12, 13, 14, 15, 16},
    {11, 17, 18, 19, 20},
    {10, 9, 8, 7, 6}
};

const MatrixType SAMPLE3S = {
    {3, 2},
    {0, 1}
};


THE_BENCHMARK(SwimInRisingWater_Dijkstra, SAMPLE1S);

SIMPLE_TEST(SwimInRisingWater_Dijkstra, TestSAMPLE1, 3, SAMPLE1S);
SIMPLE_TEST(SwimInRisingWater_Dijkstra, TestSAMPLE2, 16, SAMPLE2S);
SIMPLE_TEST(SwimInRisingWater_Dijkstra, TestSAMPLE3, 3, SAMPLE3S);


const MatrixType SAMPLE1E = {
    {1, 2, 2},
    {3, 8, 2},
    {5, 3, 5}
};

const MatrixType SAMPLE2E = {
    {1, 2, 3},
    {3, 8, 4},
    {5, 3, 5}
};

const MatrixType SAMPLE3E = {
    {1, 2, 1, 1, 1},
    {1, 2, 1, 2, 1},
    {1, 2, 1, 2, 1},
    {1, 2, 1, 2, 1},
    {1, 1, 1, 2, 1}
};


THE_BENCHMARK(MinimumEffortPath_Dijkstra, SAMPLE1E);

SIMPLE_TEST(MinimumEffortPath_Dijkstra, TestSAMPLE1, 2, SAMPLE1E);
SIMPLE_TEST(MinimumEffortPath_Dijkstra, TestSAMPLE2, 1, SAMPLE2E);
SIMPLE_TEST(MinimumEffortPath_Dijkstra, TestSAMPLE3, 0, SAMPLE3E);
