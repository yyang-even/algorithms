#include "common_header.h"

#include "depth_first_search.h"
#include "graph.h"
#include "topological_sort.h"


using namespace graph;
using BombType = std::vector<int>;
using BombArray = std::vector<BombType>;

namespace {

/** Strongly Connected Components
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 22.5.
 * @reference   https://www.geeksforgeeks.org/strongly-connected-components/
 *
 * A directed graph is strongly connected if there is a path between all pairs of vertices. A strongly
 * connected component (SCC) of a directed graph is a maximal strongly connected subgraph.
 */
auto StronglyConnectedComponents_Kosaraju(const std::size_t number_vertices,
                                          const DirectedEdgeArrayType &edges) {
    const auto graph = AdjacencyListGraph {number_vertices, edges};

    ArrayType finish_times_stack;
    GraphTraverse(
        graph,
        [&finish_times_stack](const auto &graph, const auto source, auto &visited_vertices) {
            TopologicalSort(graph, source, visited_vertices, finish_times_stack);
            return true;
        });

    const auto transpose = graph.Visit(GraphTranspose);

    std::multiset<std::multiset<std::size_t>> strongly_connected_components;
    std::vector<bool> visited_vertices(number_vertices, false);
    while (not finish_times_stack.empty()) {
        const auto source = finish_times_stack.back();
        finish_times_stack.pop_back();

        if (not visited_vertices[source]) {
            ArrayType one_strongly_connected_component;
            transpose.Visit([source, &visited_vertices, &one_strongly_connected_component](
                                const auto &graph) {
                DepthFirstSearch_Recursive(
                    graph, source, visited_vertices, one_strongly_connected_component);
            });

            strongly_connected_components.emplace(one_strongly_connected_component.cbegin(),
                                                  one_strongly_connected_component.cend());
        }
    }

    return strongly_connected_components;
}


/**
 * @reference   Check if a graph is strongly connected | Set 1 (Kosaraju using DFS)
 *              https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
 *
 * @reference   Check if a given directed graph is strongly connected | Set 2 (Kosaraju using BFS)
 *              https://www.geeksforgeeks.org/check-given-directed-graph-strongly-connected-set-2-kosaraju-using-bfs/
 *
 * @note    Simply replace DepthFirstSearch_Recursive() with BreadthFirstSearchSingleSource().
 */
auto allVisited(const std::vector<bool> &visited_vertices) {
    for (const auto visited : visited_vertices) {
        if (not visited) {
            return false;
        }
    }

    return true;
}

auto isStronglyConnectedComponents_Kosaraju_DFS(const std::size_t number_vertices,
                                                const DirectedEdgeArrayType &edges) {
    const auto graph = AdjacencyListGraph {number_vertices, edges};

    ArrayType to_be_ignored;
    {
        std::vector<bool> visited_vertices(number_vertices, false);
        graph.Visit([&visited_vertices, &to_be_ignored](const auto &graph) {
            DepthFirstSearch_Recursive(graph, 0, visited_vertices, to_be_ignored);
        });

        if (not allVisited(visited_vertices)) {
            return false;
        }
    }

    const auto transpose = graph.Visit(GraphTranspose);

    {
        std::vector<bool> visited_vertices(number_vertices, false);
        transpose.Visit([&visited_vertices, &to_be_ignored](const auto &graph) {
            DepthFirstSearch_Recursive(graph, 0, visited_vertices, to_be_ignored);
        });

        if (not allVisited(visited_vertices)) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   TARJAN’S ALGORITHM FOR STRONGLY CONNECTED COMPONENTS
 *              https://www.topcoder.com/thrive/articles/tarjans-algorithm-for-strongly-connected-components
 * @reference   Tarjan’s Algorithm to find Strongly Connected Components
 *              https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
 */
void StronglyConnectedComponents_Tarjan(const AdjacencyListGraph::RepresentationType &graph,
                                        const std::size_t node,
                                        std::vector<int> &discover,
                                        std::vector<int> &low_link,
                                        std::stack<std::size_t> &s,
                                        std::vector<bool> &in_stack,
                                        std::multiset<std::multiset<std::size_t>> &results) {
    static int time = 0;
    discover[node] = low_link[node] = ++time;
    s.push(node);
    in_stack[node] = true;

    for (const auto neighbor : graph[node]) {
        if (discover[neighbor] == -1) {
            StronglyConnectedComponents_Tarjan(
                graph, neighbor, discover, low_link, s, in_stack, results);
            low_link[node] = std::min(low_link[neighbor], low_link[node]);
        } else if (in_stack[neighbor]) {
            low_link[node] = std::min(discover[neighbor], low_link[node]);
        }
    }

    if (low_link[node] == discover[node]) {
        std::multiset<std::size_t> one_component;
        while (s.top() != node) {
            const auto i = s.top();
            s.pop();
            in_stack[i] = false;
            one_component.insert(i);
        }

        s.pop();
        in_stack[node] = false;
        one_component.insert(node);

        results.insert(one_component);
    }
}

auto StronglyConnectedComponents_Tarjan(const std::size_t number_vertices,
                                        const DirectedEdgeArrayType &edges) {
    return AdjacencyListGraph {number_vertices, edges}.Visit([](const auto &graph) {
        std::vector<int> discover(graph.size(), -1);
        auto low_link = discover;
        std::stack<std::size_t> s;
        std::vector in_stack(graph.size(), false);
        std::multiset<std::multiset<std::size_t>> results;

        for (std::size_t i = 0; i < graph.size(); ++i) {
            if (discover[i] == -1) {
                StronglyConnectedComponents_Tarjan(
                    graph, i, discover, low_link, s, in_stack, results);
            }
        }

        return results;
    });
}


/**
 * @reference   Critical Connections in a Network
 *              https://leetcode.com/problems/critical-connections-in-a-network/
 *
 * There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections
 * forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi.
 * Any server can reach other servers directly or indirectly through the network.
 * A critical connection is a connection that, if removed, will make some servers unable to reach some
 * other server.
 * Return all critical connections in the network in any order.
 */
void CriticalConnections_Tarjan(const std::size_t node,
                                const AdjacencyListGraph::RepresentationType &graph,
                                const std::size_t parent,
                                std::vector<int> &discover,
                                std::vector<int> &low_link,
                                std::multiset<std::multiset<std::size_t>> &results) {
    static int time = 0;
    discover[node] = low_link[node] = ++time;

    for (const auto neighbor : graph[node]) {
        if (neighbor == parent) {
            continue;
        }

        if (discover[neighbor] == -1) {
            CriticalConnections_Tarjan(neighbor, graph, node, discover, low_link, results);
            low_link[node] = std::min(low_link[neighbor], low_link[node]);
            if (low_link[neighbor] > discover[node]) {
                std::multiset<std::size_t> one_connection = {node, neighbor};
                results.insert(one_connection);
            }
        } else {
            low_link[node] = std::min(discover[neighbor], low_link[node]);
        }
    }
}

auto CriticalConnections_Tarjan(const std::size_t number_vertices,
                                const UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph {number_vertices, edges}.Visit([](const auto &graph) {
        std::vector<int> discover(graph.size(), -1);
        auto low_link = discover;
        std::multiset<std::multiset<std::size_t>> results;

        for (std::size_t i = 0; i < graph.size(); ++i) {
            if (discover[i] == -1) {
                CriticalConnections_Tarjan(i, graph, i, discover, low_link, results);
            }
        }

        return results;
    });
}


/**
 * @reference   Check if a directed graph is connected or not
 *              https://www.geeksforgeeks.org/check-if-a-directed-graph-is-connected-or-not/
 */
auto isConnected(const std::size_t number_vertices, const DirectedEdgeArrayType &edges) {
    const auto graph = AdjacencyListGraph {number_vertices, edges};

    ArrayType to_be_ignored;
    std::vector<bool> visited_vertices_correct_direction(number_vertices, false);
    graph.Visit([&visited_vertices_correct_direction, &to_be_ignored](const auto &graph) {
        DepthFirstSearch_Recursive(graph, 0, visited_vertices_correct_direction, to_be_ignored);
    });

    const auto transpose = graph.Visit(GraphTranspose);

    std::vector<bool> visited_vertices_reverse_direction(number_vertices, false);
    transpose.Visit([&visited_vertices_reverse_direction, &to_be_ignored](const auto &graph) {
        DepthFirstSearch_Recursive(graph, 0, visited_vertices_reverse_direction, to_be_ignored);
    });

    for (std::size_t i = 0; i < number_vertices; ++i) {
        if (not visited_vertices_correct_direction[i] and
            not visited_vertices_reverse_direction[i]) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Detonate the Maximum Bombs
 *              https://leetcode.com/problems/detonate-the-maximum-bombs/
 *
 * You are given a list of bombs. The range of a bomb is defined as the area where its effect can be
 * felt. This area is in the shape of a circle with the center as the location of the bomb.
 * The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and
 * yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes the
 * radius of its range.
 * You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that
 * lie in its range. These bombs will further detonate the bombs that lie in their ranges.
 * Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed
 * to detonate only one bomb.
 */
int CountReachableNodes(const std::vector<std::vector<int>> &graph, const int i) {
    std::queue<int> q;
    q.push(i);
    std::unordered_set<int> visited;

    while (not q.empty()) {
        for (int size = q.size(); size-- > 0;) {
            const auto from = q.front();
            q.pop();
            for (const auto to : graph.at(from)) {
                if (visited.insert(to).second) {
                    q.push(to);
                }
            }
        }
    }

    return visited.size();
}

auto MaxDetonation(const BombArray &bombs) {
    std::vector graph(bombs.size(), std::vector<int> {});

    for (std::size_t i = 0; i < bombs.size(); ++i) {
        const long x_i = bombs[i][0];
        const long y_i = bombs[i][1];
        const long r_square = bombs[i][2] * bombs[i][2];

        for (std::size_t j = 0; j < bombs.size(); ++j) {
            const long x_j = bombs[j][0];
            const long y_j = bombs[j][1];

            const auto x_diff = x_i - x_j;
            const auto y_diff = y_i - y_j;

            if (x_diff * x_diff + y_diff * y_diff <= r_square) {
                graph[i].push_back(j);
            }
        }
    }

    int result = 0;
    for (std::size_t i = 0; i < bombs.size(); ++i) {
        result = std::max(result, CountReachableNodes(graph, i));
    }

    return result;
}

} //namespace


const DirectedEdgeArrayType SAMPLE1 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}};
const std::multiset<std::multiset<std::size_t>> EXPECTED1 = {{0, 1, 2}, {3}, {4}};


THE_BENCHMARK(StronglyConnectedComponents_Kosaraju, 5, SAMPLE1);

SIMPLE_TEST(StronglyConnectedComponents_Kosaraju, TestSAMPLE1, EXPECTED1, 5, SAMPLE1);


THE_BENCHMARK(StronglyConnectedComponents_Tarjan, 5, SAMPLE1);

SIMPLE_TEST(StronglyConnectedComponents_Tarjan, TestSAMPLE1, EXPECTED1, 5, SAMPLE1);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {2, 4}, {4, 2}};
const DirectedEdgeArrayType SAMPLE3 = {{0, 1}, {1, 2}, {2, 3}};


THE_BENCHMARK(isStronglyConnectedComponents_Kosaraju_DFS, 5, SAMPLE1);

SIMPLE_TEST(isStronglyConnectedComponents_Kosaraju_DFS, TestSAMPLE1, false, 5, SAMPLE1);
SIMPLE_TEST(isStronglyConnectedComponents_Kosaraju_DFS, TestSAMPLE2, true, 5, SAMPLE2);
SIMPLE_TEST(isStronglyConnectedComponents_Kosaraju_DFS, TestSAMPLE3, false, 4, SAMPLE3);


const DirectedEdgeArrayType SAMPLE4 = {{0, 1}, {0, 2}, {1, 2}};
const DirectedEdgeArrayType SAMPLE5 = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};


THE_BENCHMARK(isConnected, 5, SAMPLE1);

SIMPLE_TEST(isConnected, TestSAMPLE1, true, 5, SAMPLE1);
SIMPLE_TEST(isConnected, TestSAMPLE2, true, 5, SAMPLE2);
SIMPLE_TEST(isConnected, TestSAMPLE3, true, 4, SAMPLE3);
SIMPLE_TEST(isConnected, TestSAMPLE4, false, 4, SAMPLE4);
SIMPLE_TEST(isConnected, TestSAMPLE5, true, 4, SAMPLE5);


const UndirectedEdgeArrayType SAMPLE1C = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
const std::multiset<std::multiset<std::size_t>> EXPECTED1C = {{1, 3}};

const UndirectedEdgeArrayType SAMPLE2C = {{0, 1}};
const std::multiset<std::multiset<std::size_t>> EXPECTED2C = {{0, 1}};


THE_BENCHMARK(CriticalConnections_Tarjan, 4, SAMPLE1C);

SIMPLE_TEST(CriticalConnections_Tarjan, TestSAMPLE1, EXPECTED1C, 4, SAMPLE1C);
SIMPLE_TEST(CriticalConnections_Tarjan, TestSAMPLE2, EXPECTED2C, 2, SAMPLE2C);


const BombArray SAMPLE1B = {{2, 1, 3}, {6, 1, 4}};
const BombArray SAMPLE2B = {{1, 1, 5}, {10, 10, 5}};
const BombArray SAMPLE3B = {{1, 2, 3}, {2, 3, 1}, {3, 4, 2}, {4, 5, 3}, {5, 6, 4}};


THE_BENCHMARK(MaxDetonation, SAMPLE1B);

SIMPLE_TEST(MaxDetonation, TestSAMPLE1, 2, SAMPLE1B);
SIMPLE_TEST(MaxDetonation, TestSAMPLE2, 1, SAMPLE2B);
SIMPLE_TEST(MaxDetonation, TestSAMPLE3, 5, SAMPLE3B);
