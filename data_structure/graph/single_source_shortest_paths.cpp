#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"

#include "mathematics/matrix/matrix.h"


using namespace graph;

using TableType = MatrixTypeTemplate<unsigned>;

namespace {

bool Relax(std::vector<int> &distances,
           const std::size_t from,
           const std::size_t to,
           const int weight,
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

inline void
Relax(std::vector<int> &distances, std::vector<int> &parents, const DirectedEdge &edge) {
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
 * Given a graph and a source vertex src in graph, find shortest paths from src to all vertices in the
 * given graph. The graph may contain negative weight edges.
 *
 * Dijkstra doesn't work for Graphs with negative weight edges, Bellman-Ford works for such graphs.
 * Bellman-Ford is also simpler than Dijkstra and suites well for distributed systems.  But time
 * complexity of Bellman-Ford is O(VE), which is more than Dijkstra.
 */
auto SingleSourceShortestPaths_BellmanFord(
    const std::size_t number_vertices,
    const DirectedEdgeArrayType &edges,
    const std::size_t source,
    std::pair<int, std::vector<int>> *negative_cycle_pair = nullptr) {
    assert(source < number_vertices);

    std::vector<int> distances_from_source(number_vertices, std::numeric_limits<int>::max());
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
auto hasNegativeCycle(const std::size_t number_vertices, const DirectedEdgeArrayType &edges) {
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
    std::pair<int, std::vector<int>> negative_cycle_pair {};
    const auto result_pair = SingleSourceShortestPaths_BellmanFord(
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

    WeightedAdjacencyListGraph graph {number_vertices, edges};

    ArrayType topological_order;
    GraphTraverse(
        graph,
        [&topological_order](const auto &graph, const auto source, auto &visited_vertices) {
            TopologicalSort(graph, source, visited_vertices, topological_order);
            return true;
        });

    std::vector<int> distances_from_source(number_vertices, std::numeric_limits<int>::max());
    distances_from_source[source] = 0;

    for (auto iter = topological_order.crbegin(); iter != topological_order.crend(); ++iter) {
        const auto from = *iter;
        graph.Visit([from, &distances_from_source](const auto &graph) {
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

auto SingleSourceShortestPaths_Unweighted_Undirected_BFS(const std::size_t number_vertices,
                                                         const UndirectedEdgeArrayType &edges,
                                                         const std::size_t source,
                                                         const std::size_t destination) {
    assert(source < number_vertices);
    assert(destination < number_vertices);

    AdjacencyListGraph graph {number_vertices, edges};

    std::vector<int> distances_from_source(number_vertices, std::numeric_limits<int>::max());
    distances_from_source[source] = 0;
    std::vector<int> parents(number_vertices, -1);

    const auto path_found =
        graph.Visit([source, destination, &distances_from_source, &parents](const auto &graph) {
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
                if (Relax(distances_from_source,
                          from_vertex,
                          node.destination,
                          node.weight,
                          parents)) {
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
template<typename EdgeArrayType>
inline constexpr auto SingleSourceShortestPaths_Dijkstra(const std::size_t number_vertices,
                                                         const EdgeArrayType &edges,
                                                         const std::size_t source) {
    return WeightedAdjacencyListGraph {number_vertices, edges}.Visit([source](const auto &graph) {
        return SingleSourceShortestPaths_Dijkstra(graph, source);
    });
}


/**
 * @reference   Path with Maximum Probability
 *              https://leetcode.com/problems/path-with-maximum-probability/
 *
 * You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where
 * edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of
 * traversing that edge succProb[i].
 * Given two nodes start and end, find the path with the maximum probability of success to go from start
 * to end and return its success probability.
 * If there is no path from start to end, return 0. Your answer will be accepted if it differs from the
 * correct answer by at most 1e-5.
 */


/**
 * @reference   Network Delay Time
 *              https://leetcode.com/problems/network-delay-time/
 *
 * You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel
 * times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node,
 * and wi is the time it takes for a signal to travel from source to target.
 * We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to
 * receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.
 */


/**
 * @reference   Min Cost Path | DP-6
 *              https://www.geeksforgeeks.org/min-cost-path-dp-6/
 * @reference   C Program for Min Cost Path
 *              https://www.geeksforgeeks.org/c-program-for-min-cost-path/
 *
 * Given a cost matrix cost[][] and a position (m, n) in cost[][], write a function that returns cost of
 * minimum cost path to reach (m, n) from (0, 0). Each cell of the matrix represents a cost to traverse
 * through that cell. Total cost of a path to reach (m, n) is sum of all the costs on that path
 * (including both source and destination). You can only traverse down, right and diagonally lower cells
 * from a given cell, i.e., from a given cell (i, j), cells (i+1, j), (i, j+1) and (i+1, j+1) can be
 * traversed. You may assume that all costs are positive integers.
 */
auto MinCostPath(TableType costs, const std::size_t m, const std::size_t n) {
    assert(m < costs.size());
    assert(n < costs.front().size());

    for (std::size_t i = 1; i <= m; ++i) {
        costs[i][0] += costs[i - 1][0];
    }

    for (std::size_t j = 1; j <= n; ++j) {
        costs[0][j] += costs[0][j - 1];
    }

    for (std::size_t i = 1; i <= m; ++i) {
        for (std::size_t j = 1; j <= n; ++j) {
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
                                                      const int i,
                                                      ArrayType &path) {
    if (i != -1) {
        PrintOneSingleSourceShortestPath_Dijkstra(parents, parents[i], path);
        path.push_back(i);
    }
}

auto PrintSingleSourceShortestPaths_Dijkstra(const std::size_t number_vertices,
                                             const UndirectedEdgeArrayType &edges,
                                             const std::size_t source) {
    std::vector<int> parents(number_vertices, -1);
    WeightedAdjacencyListGraph {number_vertices, edges}.Visit(
        [source, &parents](const auto &graph) {
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
 * You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle).  You
 * can move up, down, left, or right from and to an empty cell in one step.
 * Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right
 * corner (m - 1, n - 1) given that you can eliminate at most k obstacles. If it is not possible to find
 * such walk return -1.
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

            ForEachDirection(
                M,
                N,
                x,
                y,
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
 * The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. The
 * dungeon consists of m x n rooms laid out in a 2D grid. Our valiant knight was initially positioned in
 * the top-left room and must fight his way through dungeon to rescue the princess.
 * The knight has an initial health point represented by a positive integer. If at any point his health
 * point drops to 0 or below, he dies immediately.
 * Some of the rooms are guarded by demons (represented by negative integers), so the knight loses
 * health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic
 * orbs that increase the knight's health (represented by positive integers).
 * To reach the princess as quickly as possible, the knight decides to move only rightward or downward
 * in each step.
 * Return the knight's minimum initial health so that he can rescue the princess.
 * Note that any room can contain threats or power-ups, even the first room the knight enters and the
 * bottom-right room where the princess is imprisoned.
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

    constexpr Node(const int c, const unsigned x, const unsigned y) : cost(c), row(x), column(y) {
    }
};

inline constexpr auto operator>(const Node &lhs, const Node &rhs) {
    return lhs.cost > rhs.cost;
}

/** Swim in Rising Water
 *
 * @reference   https://leetcode.com/problems/swim-in-rising-water/
 *
 * You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at
 * that point (i, j).
 * The rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a
 * square to another 4-directionally adjacent square if and only if the elevation of both squares
 * individually are at most t. You can swim infinite distances in zero time. Of course, you must stay
 * within the boundaries of the grid during your swim.
 * Return the least time until you can reach the bottom right square (n - 1, n - 1) if you start at the
 * top left square (0, 0).
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
            open_list.emplace(
                std::max(grid[node.row + 1][node.column], node.cost), node.row + 1, node.column);
            grid[node.row + 1][node.column] = VISITED;
        }

        if (node.column + 1 != grid.size() and grid[node.row][node.column + 1] != VISITED) {
            if (node.row + 1 == grid.size() and node.column + 2 == grid.size()) {
                return std::max(grid[node.row][node.column + 1], node.cost);
            }
            open_list.emplace(
                std::max(grid[node.row][node.column + 1], node.cost), node.row, node.column + 1);
            grid[node.row][node.column + 1] = VISITED;
        }

        if (node.row != 0 and grid[node.row - 1][node.column] != VISITED) {
            open_list.emplace(
                std::max(grid[node.row - 1][node.column], node.cost), node.row - 1, node.column);
            grid[node.row - 1][node.column] = VISITED;
        }

        if (node.column != 0 and grid[node.row][node.column - 1] != VISITED) {
            open_list.emplace(
                std::max(grid[node.row][node.column - 1], node.cost), node.row, node.column - 1);
            grid[node.row][node.column - 1] = VISITED;
        }
    }

    return -1;
}


/**
 * @reference   Path With Minimum Effort
 *              https://leetcode.com/problems/path-with-minimum-effort/
 *
 * You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x
 * columns, where heights[row][col] represents the height of cell (row, col). You are situated in the
 * top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e.,
 * 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the
 * minimum effort.
 * A route's effort is the maximum absolute difference in heights between two consecutive cells of the
 * route.
 * Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
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


/**
 * @reference   Shortest Path in Binary Matrix
 *              https://leetcode.com/problems/shortest-path-in-binary-matrix/
 *
 * Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix.  If
 * there is no clear path, return -1.
 * A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right
 * cell (i.e., (n - 1, n - 1)) such that:
 *  All the visited cells of the path are 0.
 *  All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they
 *      share an edge or a corner).
 * The length of a clear path is the number of visited cells of this path.
 */
auto ShortestPathBinaryMatrix(MatrixType grid) {
    if (grid[0][0]) {
        return -1;
    }

    const int N = grid.size();
    std::queue<std::pair<int, int>> q;
    q.emplace(0, 0);
    grid[0][0] = 1;

    int result = 0;
    while (not q.empty()) {
        ++result;
        for (int i = q.size(); i-- > 0;) {
            const auto [x, y] = q.front();
            q.pop();

            if (x == N - 1 and y == N - 1) {
                return result;
            }

            for (int new_x = x - 1; new_x <= x + 1; ++new_x) {
                for (int new_y = y - 1; new_y <= y + 1; ++new_y) {
                    if (new_x != x or new_y != y) {
                        if (new_x >= 0 and new_x < N and new_y >= 0 and new_y < N and
                            grid[new_x][new_y] == 0) {
                            grid[new_x][new_y] = 1;
                            q.emplace(new_x, new_y);
                        }
                    }
                }
            }
        }
    }

    return -1;
}


/**
 * @reference   Nearest Exit from Entrance in Maze
 *              https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/
 *
 * You are given an m x n matrix maze (0-indexed) with empty cells (represented as '.') and walls
 * (represented as '+'). You are also given the entrance of the maze, where entrance = [entrancerow,
 * entrancecol] denotes the row and column of the cell you are initially standing at.
 * In one step, you can move one cell up, down, left, or right. You cannot step into a cell with a wall,
 * and you cannot step outside the maze. Your goal is to find the nearest exit from the entrance. An
 * exit is defined as an empty cell that is at the border of the maze. The entrance does not count as an
 * exit.
 * Return the number of steps in the shortest path from the entrance to the nearest exit, or -1 if no
 * such path exists.
 */
auto NearestExit(MatrixType maze, const std::pair<int, int> &entrance) {
    std::queue<std::pair<int, int>> q;
    q.emplace(entrance.first, entrance.second);
    maze[entrance.first][entrance.second] = '+';

    int moves = 1;
    const int M = maze.size();
    const int N = maze.front().size();

    while (not q.empty()) {
        for (int i = q.size(); i > 0; --i) {
            const auto &[x, y] = q.front();
            q.pop();

            for (const auto &[delta_x, delta_y] : DIRECTIONS) {
                const auto new_x = x + delta_x;
                const auto new_y = y + delta_y;

                if (new_x < 0 or new_y < 0 or new_x >= M or new_y >= N or
                    maze[new_x][new_y] == '+') {
                    continue;
                }

                if (new_x == 0 or new_y == 0 or new_x == M - 1 or new_y == N - 1) {
                    return moves;
                }

                maze[new_x][new_y] = '+';
                q.emplace(new_x, new_y);
            }
        }

        ++moves;
    }

    return -1;
}


/**
 * @reference   Shortest Bridge
 *              https://leetcode.com/problems/shortest-bridge/
 *
 * You are given an n x n binary matrix grid where 1 represents land and 0 represents water.
 * An island is a 4-directionally connected group of 1's not connected to any other 1's. There are
 * exactly two islands in grid.
 * You may change 0's to 1's to connect the two islands to form one island.
 * Return the smallest number of 0's you must flip to connect the two islands.
 */


/**
 * @reference   Snakes and Ladders
 *              https://leetcode.com/problems/snakes-and-ladders/
 *
 * You are given an n x n integer matrix board where the cells are labeled from 1 to n2 in a
 * Boustrophedon style starting from the bottom left of the board (i.e. board[n - 1][0]) and alternating
 * direction each row.
 * You start on square 1 of the board. In each move, starting from square curr, do the following:
 *  Choose a destination square next with a label in the range [curr + 1, min(curr + 6, n2)].
 *      This choice simulates the result of a standard 6-sided die roll: i.e., there are always at most
 *      6 destinations, regardless of the size of the board.
 *  If next has a snake or ladder, you must move to the destination of that snake or ladder. Otherwise,
 *  you move to next.
 *  The game ends when you reach the square n2.
 * A board square on row r and column c has a snake or ladder if board[r][c] != -1.  The destination of
 * that snake or ladder is board[r][c]. Squares 1 and n2 do not have a snake or ladder.
 * Note that you only take a snake or ladder at most once per move. If the destination to a snake or
 * ladder is the start of another snake or ladder, you do not follow the subsequent snake or ladder.
 *  For example, suppose the board is [[-1,4],[-1,3]], and on the first move, your destination square is
 *  2. You follow the ladder to square 3, but do not follow the subsequent ladder to 4.
 * Return the least number of moves required to reach the square n2. If it is not possible to reach the
 * square, return -1.
 */
constexpr auto toCell(const int i, const int n) {
    const auto x = (i - 1) / n;
    const auto y = (i - 1) % n;

    const auto row = n - x - 1;
    const auto column = (x % 2 == 0) ? y : (n - y - 1);

    return std::pair(row, column);
}

auto SnakesAndLadders(const MatrixType &board) {
    const int N = board.size();
    const auto destination = N * N;

    std::unordered_map<int, int> costs {{1, 0}};
    std::queue<int> q;
    q.push(1);

    while (not q.empty()) {
        const auto current = q.front();
        q.pop();
        const auto curr_cost = costs[current];

        for (auto j = current + 1; j <= current + 6; ++j) {
            const auto [row, column] = toCell(j, N);
            const auto next = (board[row][column] != -1) ? board[row][column] : j;
            const auto next_cost = curr_cost + 1;

            if (next == destination) {
                return next_cost;
            }

            if (costs.emplace(next, next_cost).second) {
                q.push(next);
            }
        }
    }

    return -1;
}


/**
 * @reference   Cheapest Flights Within K Stops
 *              https://leetcode.com/problems/cheapest-flights-within-k-stops/
 *
 * There are n cities connected by some number of flights. You are given an array flights where
 * flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with
 * cost pricei.
 * You are also given three integers src, dst, and k, return the cheapest price from src to dst with at
 * most k stops. If there is no such route, return -1.
 */
struct Trip {
    int cost = 0;
    int k = 0;
    std::size_t at = 0;

    Trip(const int c, const int stop, const int a) : cost(c), k(stop), at(a) {
    }
};

auto FindCheapestPrice(const WeightedAdjacencyListGraph::RepresentationType &graph,
                       const int src,
                       const std::size_t dst,
                       const int k) {
    constexpr auto Compare = [](const auto &left, const auto &right) {
        return left.cost > right.cost;
    };
    std::priority_queue<Trip, std::vector<Trip>, decltype(Compare)> min_heap(Compare);
    min_heap.emplace(0, k, src);

    std::vector visited(graph.size(), INT_MIN);
    while (not min_heap.empty()) {
        const auto t = min_heap.top();
        min_heap.pop();

        if (t.at == dst) {
            return t.cost;
        }

        if (visited[t.at] > t.k) {
            continue;
        }
        visited[t.at] = t.k;

        for (const auto &[neighbor, price] : graph[t.at]) {
            const auto new_cost = t.cost + price;
            if ((t.k > 0 or (t.k == 0 and dst == neighbor))) {
                min_heap.emplace(new_cost, t.k - 1, neighbor);
            }
        }
    }

    return -1;
}

inline auto FindCheapestPrice(const std::size_t n,
                              const DirectedEdgeArrayType &flights,
                              const int src,
                              const int dst,
                              const int k) {
    return WeightedAdjacencyListGraph {n, flights}.Visit([src, dst, k](const auto &graph) {
        return FindCheapestPrice(graph, src, dst, k);
    });
}


/**
 * @reference   Shortest Path with Alternating Colors
 *              https://leetcode.com/problems/shortest-path-with-alternating-colors/
 *
 * You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from
 * 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
 * You are given two arrays redEdges and blueEdges where:
 *  redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the
 *  graph, and
 *  blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the
 *  graph.
 * Return an array answer of length n, where each answer[x] is the length of the shortest path from node
 * 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
 */
void ShortestAlternatingPaths(const AdjacencyListGraph::RepresentationType &red_graph,
                              const AdjacencyListGraph::RepresentationType &blue_graph,
                              bool is_red,
                              std::vector<int> &red_result,
                              std::vector<int> &blue_result) {
    std::queue<int> q;
    q.emplace(0);

    int distance = 0;
    while (not q.empty()) {
        ++distance;

        for (int size = q.size(); size-- > 0;) {
            const auto i = q.front();
            q.pop();

            if (is_red) {
                for (const auto neighbor : blue_graph[i]) {
                    if (blue_result[neighbor] > distance) {
                        blue_result[neighbor] = distance;
                        q.emplace(neighbor);
                    }
                }
            } else {
                for (const auto neighbor : red_graph[i]) {
                    if (red_result[neighbor] > distance) {
                        red_result[neighbor] = distance;
                        q.emplace(neighbor);
                    }
                }
            }
        }

        is_red = not is_red;
    }
}

auto ShortestAlternatingPaths(const std::size_t n,
                              const DirectedEdgeArrayType &red_edges,
                              const DirectedEdgeArrayType &blue_edges) {
    AdjacencyListGraph::RepresentationType red_graph(n);
    for (const auto &e : red_edges) {
        red_graph[e.from].push_back(e.to);
    }

    AdjacencyListGraph::RepresentationType blue_graph(n);
    for (const auto &e : blue_edges) {
        blue_graph[e.from].push_back(e.to);
    }

    std::vector red_result(n, INT_MAX);
    red_result[0] = 0;
    std::vector blue_result(n, INT_MAX);
    blue_result[0] = 0;

    ShortestAlternatingPaths(red_graph, blue_graph, true, red_result, blue_result);
    ShortestAlternatingPaths(red_graph, blue_graph, false, red_result, blue_result);

    std::vector<int> result;
    for (std::size_t i = 0; i < n; ++i) {
        result.push_back(std::min(red_result[i], blue_result[i]));
        if (result.back() == INT_MAX)
            result.back() = -1;
    }

    return result;
}

} //namespace


const DirectedEdgeArrayType SAMPLE1 = {
    {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}};
const auto EXPECTED1 = std::pair(true, std::vector {0, -1, 2, -2, 1});


THE_BENCHMARK(SingleSourceShortestPaths_BellmanFord, 5, SAMPLE1, 0);

SIMPLE_TEST(SingleSourceShortestPaths_BellmanFord, TestSAMPLE1, EXPECTED1, 5, SAMPLE1, 0);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1, 1}, {1, 2, -1}, {2, 3, -1}, {3, 0, -1}};
const std::unordered_set<std::size_t> EXPECTED2 = {0, 1, 2, 3};


THE_BENCHMARK(hasNegativeCycle, 5, SAMPLE1);

SIMPLE_TEST(hasNegativeCycle, TestSAMPLE1, false, 5, SAMPLE1);
SIMPLE_TEST(hasNegativeCycle, TestSAMPLE2, true, 4, SAMPLE2);


THE_BENCHMARK(PrintNegativeWeightCycle, 4, SAMPLE2, 0);

SIMPLE_TEST(PrintNegativeWeightCycle, TestSAMPLE2, EXPECTED2, 4, SAMPLE2, 0);


const DirectedEdgeArrayType SAMPLE3 = {{0, 1, 5},
                                       {0, 2, 3},
                                       {1, 3, 6},
                                       {1, 2, 2},
                                       {2, 4, 4},
                                       {2, 5, 2},
                                       {2, 3, 7},
                                       {3, 4, -1},
                                       {4, 5, -2}};
const std::vector<int> EXPECTED3 = {std::numeric_limits<int>::max(), 0, 2, 6, 5, 3};


THE_BENCHMARK(SingleSourceShortestPaths_DAG, 6, SAMPLE3, 1);

SIMPLE_TEST(SingleSourceShortestPaths_DAG, TestSAMPLE3, EXPECTED3, 6, SAMPLE3, 1);


const UndirectedEdgeArrayType SAMPLE4 = {
    {0, 1}, {0, 3}, {1, 2}, {3, 4}, {3, 7}, {4, 5}, {4, 6}, {4, 7}, {5, 6}, {6, 7}};
const ArrayType EXPECTED4 = {0, 3, 7};


THE_BENCHMARK(SingleSourceShortestPaths_Unweighted_Undirected_BFS, 8, SAMPLE4, 0, 7);

SIMPLE_TEST(SingleSourceShortestPaths_Unweighted_Undirected_BFS,
            TestSAMPLE4,
            EXPECTED4,
            8,
            SAMPLE4,
            0,
            7);


const UndirectedEdgeArrayType SAMPLE5 = {{0, 1, 4},
                                         {0, 7, 8},
                                         {1, 2, 8},
                                         {1, 7, 11},
                                         {2, 3, 7},
                                         {2, 8, 2},
                                         {2, 5, 4},
                                         {3, 4, 9},
                                         {3, 5, 14},
                                         {4, 5, 10},
                                         {5, 6, 2},
                                         {6, 7, 1},
                                         {6, 8, 6},
                                         {7, 8, 7}};
const std::vector<int> EXPECTED5 = {0, 4, 12, 19, 21, 11, 9, 8, 14};
const std::vector<ArrayType> EXPECTED_PATHS5 = {{0},
                                                {0, 1},
                                                {0, 1, 2},
                                                {0, 1, 2, 3},
                                                {0, 7, 6, 5, 4},
                                                {0, 7, 6, 5},
                                                {0, 7, 6},
                                                {0, 7},
                                                {0, 1, 2, 8}};

const DirectedEdgeArrayType SAMPLE6 = {{0, 1, 1}, {0, 2, 4}, {1, 2, 2}, {1, 3, 6}, {2, 3, 3}};
const std::vector<int> EXPECTED6 = {0, 1, 3, 6};


THE_BENCHMARK(SingleSourceShortestPaths_Dijkstra, 9, SAMPLE5, 0);

SIMPLE_TEST(SingleSourceShortestPaths_Dijkstra, TestSAMPLE5, EXPECTED5, 9, SAMPLE5, 0);
SIMPLE_TEST(SingleSourceShortestPaths_Dijkstra, TestSAMPLE6, EXPECTED6, 4, SAMPLE6, 0);


THE_BENCHMARK(PrintSingleSourceShortestPaths_Dijkstra, 9, SAMPLE5, 0);

SIMPLE_TEST(PrintSingleSourceShortestPaths_Dijkstra, TestSAMPLE5, EXPECTED_PATHS5, 9, SAMPLE5, 0);


// clang-format off
const TableType COSTS1 = {
    {1, 2, 3},
    {4, 8, 2},
    {1, 5, 3}
};
// clang-format on


THE_BENCHMARK(MinCostPath, COSTS1, 2, 2);

SIMPLE_TEST(MinCostPath, TestSAMPLE1, 8, COSTS1, 2, 2);


// clang-format off
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
// clang-format on


THE_BENCHMARK(ShortestPathsWithObstaclesElimination, SAMPLE1M, 1);

SIMPLE_TEST(ShortestPathsWithObstaclesElimination, TestSAMPLE1, 6, SAMPLE1M, 1);
SIMPLE_TEST(ShortestPathsWithObstaclesElimination, TestSAMPLE2, -1, SAMPLE2M, 1);


// clang-format off
const MatrixType SAMPLE1D = {
    {-2, -3, 3},
    {-5, -10, 1},
    {10, 30, -5}
};

const MatrixType SAMPLE2D = {
    {0}
};
// clang-format on


THE_BENCHMARK(DungeonGame_DP, SAMPLE1D);

SIMPLE_TEST(DungeonGame_DP, TestSAMPLE1, 7, SAMPLE1D);
SIMPLE_TEST(DungeonGame_DP, TestSAMPLE2, 1, SAMPLE2D);


THE_BENCHMARK(DungeonGame_Dijkstra, SAMPLE1D);

SIMPLE_TEST(DungeonGame_Dijkstra, TestSAMPLE1, 7, SAMPLE1D);
SIMPLE_TEST(DungeonGame_Dijkstra, TestSAMPLE2, 1, SAMPLE2D);


// clang-format off
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
// clang-format on


THE_BENCHMARK(SwimInRisingWater_Dijkstra, SAMPLE1S);

SIMPLE_TEST(SwimInRisingWater_Dijkstra, TestSAMPLE1, 3, SAMPLE1S);
SIMPLE_TEST(SwimInRisingWater_Dijkstra, TestSAMPLE2, 16, SAMPLE2S);
SIMPLE_TEST(SwimInRisingWater_Dijkstra, TestSAMPLE3, 3, SAMPLE3S);


// clang-format off
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
// clang-format on


THE_BENCHMARK(MinimumEffortPath_Dijkstra, SAMPLE1E);

SIMPLE_TEST(MinimumEffortPath_Dijkstra, TestSAMPLE1, 2, SAMPLE1E);
SIMPLE_TEST(MinimumEffortPath_Dijkstra, TestSAMPLE2, 1, SAMPLE2E);
SIMPLE_TEST(MinimumEffortPath_Dijkstra, TestSAMPLE3, 0, SAMPLE3E);


// clang-format off
const MatrixType SAMPLE1B = {
    {0,1},
    {1,0}
};

const MatrixType SAMPLE2B = {
    {0,0,0},
    {1,1,0},
    {1,1,0}
};

const MatrixType SAMPLE3B = {
    {1,0,0},
    {1,1,0},
    {1,1,0}
};
// clang-format on


THE_BENCHMARK(ShortestPathBinaryMatrix, SAMPLE1B);

SIMPLE_TEST(ShortestPathBinaryMatrix, TestSAMPLE1, 2, SAMPLE1B);
SIMPLE_TEST(ShortestPathBinaryMatrix, TestSAMPLE2, 4, SAMPLE2B);
SIMPLE_TEST(ShortestPathBinaryMatrix, TestSAMPLE3, -1, SAMPLE3B);


// clang-format off
const MatrixType SAMPLE1NM = {
    {'+', '+', '.', '+'},
    {'.', '.', '.', '+'},
    {'+', '+', '+', '.'}
};
const auto SAMPLE1NE = std::pair(1, 2);

const MatrixType SAMPLE2NM = {
    {'+', '+', '+'},
    {'.', '.', '.'},
    {'+', '+', '+'}
};
const auto SAMPLE2NE = std::pair(1, 0);

const MatrixType SAMPLE3NM = {
    {'.', '+'}
};
const auto SAMPLE3NE = std::pair(0, 0);
// clang-format on


THE_BENCHMARK(NearestExit, SAMPLE1NM, SAMPLE1NE);

SIMPLE_TEST(NearestExit, TestSAMPLE1, 1, SAMPLE1NM, SAMPLE1NE);
SIMPLE_TEST(NearestExit, TestSAMPLE2, 2, SAMPLE2NM, SAMPLE2NE);
SIMPLE_TEST(NearestExit, TestSAMPLE3, -1, SAMPLE3NM, SAMPLE3NE);


// clang-format off
const MatrixType SAMPLE1SL = {
    {-1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1},
    {-1, 35, -1, -1, 13, -1},
    {-1, -1, -1, -1, -1, -1},
    {-1, 15, -1, -1, -1, -1}
};

const MatrixType SAMPLE2SL = {
    {-1, -1},
    {-1, 3}
};

const MatrixType SAMPLE3SL = {
    {-1, 4, -1},
    {6, 2, 6},
    {-1, 3, -1}
};

const MatrixType SAMPLE4SL = {
    {-1, -1, -1, -1, 48, 5, -1},
    {12, 29, 13, 9, -1, 2, 32},
    {-1, -1, 21, 7, -1, 12, 49},
    {42, 37, 21, 40, -1, 22, 12},
    {42, -1, 2, -1, -1, -1, 6},
    {39, -1, 35, -1, -1, 39, -1},
    {-1, 36, -1, -1, -1, -1, 5}
};
// clang-format on


THE_BENCHMARK(SnakesAndLadders, SAMPLE1SL);

SIMPLE_TEST(SnakesAndLadders, TestSAMPLE1, 4, SAMPLE1SL);
SIMPLE_TEST(SnakesAndLadders, TestSAMPLE2, 1, SAMPLE2SL);
SIMPLE_TEST(SnakesAndLadders, TestSAMPLE3, 2, SAMPLE3SL);
SIMPLE_TEST(SnakesAndLadders, TestSAMPLE4, 3, SAMPLE4SL);


const DirectedEdgeArrayType SAMPLE1F = {
    {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
const DirectedEdgeArrayType SAMPLE2F = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
const DirectedEdgeArrayType SAMPLE4F = {{0, 3, 3},
                                        {3, 4, 3},
                                        {4, 1, 3},
                                        {0, 5, 1},
                                        {5, 1, 100},
                                        {0, 6, 2},
                                        {6, 1, 100},
                                        {0, 7, 1},
                                        {7, 8, 1},
                                        {8, 9, 1},
                                        {9, 1, 1},
                                        {1, 10, 1},
                                        {10, 2, 1},
                                        {1, 2, 100}};


THE_BENCHMARK(FindCheapestPrice, 4, SAMPLE1F, 0, 3, 1);

SIMPLE_TEST(FindCheapestPrice, TestSAMPLE1, 700, 4, SAMPLE1F, 0, 3, 1);
SIMPLE_TEST(FindCheapestPrice, TestSAMPLE2, 200, 3, SAMPLE2F, 0, 2, 1);
SIMPLE_TEST(FindCheapestPrice, TestSAMPLE3, 500, 3, SAMPLE2F, 0, 2, 0);
SIMPLE_TEST(FindCheapestPrice, TestSAMPLE4, 11, 11, SAMPLE4F, 0, 2, 4);


const DirectedEdgeArrayType SAMPLE1AR = {{0, 1}, {1, 2}};
const DirectedEdgeArrayType SAMPLE1AB = {};
const std::vector EXPECTED1A = {0, 1, -1};

const DirectedEdgeArrayType SAMPLE2AR = {{0, 1}};
const DirectedEdgeArrayType SAMPLE2AB = {{2, 1}};

const DirectedEdgeArrayType SAMPLE3AB = {{1, 2}};
const std::vector EXPECTED3A = {0, 1, 2};


THE_BENCHMARK(ShortestAlternatingPaths, 3, SAMPLE1AR, SAMPLE1AB);

SIMPLE_TEST(ShortestAlternatingPaths, TestSAMPLE1, EXPECTED1A, 3, SAMPLE1AR, SAMPLE1AB);
SIMPLE_TEST(ShortestAlternatingPaths, TestSAMPLE2, EXPECTED1A, 3, SAMPLE2AR, SAMPLE2AB);
SIMPLE_TEST(ShortestAlternatingPaths, TestSAMPLE3, EXPECTED3A, 3, SAMPLE2AR, SAMPLE3AB);
