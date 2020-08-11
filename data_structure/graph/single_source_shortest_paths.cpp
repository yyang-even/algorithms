#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"


using namespace graph;

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

void Relax(std::vector<int> &distances, std::vector<int> &parents, const DirectedEdge &edge) {
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
 * Dijkstra doesn’t work for Graphs with negative weight edges, Bellman-Ford works for
 * such graphs. Bellman-Ford is also simpler than Dijkstra and suites well for
 * distributed systems. But time complexity of Bellman-Ford is O(VE), which is more
 * than Dijkstra.
 */
auto SingleSourceShortestPaths_BellmanFord(const std::size_t number_vertices,
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
            distances_from_source[one_edge.to] > distances_from_source[one_edge.from] + one_edge.weight) {
            if (negative_cycle_pair) {
                negative_cycle_pair->first = one_edge.to;
                negative_cycle_pair->second = parents;
            }
            return std::make_pair(false, distances_from_source);
        }
    }

    return std::make_pair(true, distances_from_source);
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
            const auto result_pair = SingleSourceShortestPaths_BellmanFord(number_vertices, edges, i);
            if (not result_pair.first) {
                return true;
            }

            for (std::size_t i = 0; i < number_vertices; ++i) {
                if (result_pair.second[i] != std::numeric_limits<int>::max()) {
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
auto PrintNegativeWeightCycle(const std::size_t number_vertices, const DirectedEdgeArrayType &edges,
                              const std::size_t source) {
    std::pair<int, std::vector<int>> negative_cycle_pair{};
    const auto result_pair = SingleSourceShortestPaths_BellmanFord(number_vertices, edges, source,
                             &negative_cycle_pair);

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

    std::vector<int> distances_from_source(number_vertices, std::numeric_limits<int>::max());
    distances_from_source[source] = 0;

    for (auto iter = topological_order.crbegin(); iter != topological_order.crend(); ++iter) {
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

auto SingleSourceShortestPaths_Unweighted_Undirected_BFS(const std::size_t number_vertices,
        const UndirectedEdgeArrayType &edges,
        const std::size_t source,
        const std::size_t destination) {
    assert(source < number_vertices);
    assert(destination < number_vertices);

    AdjacencyListGraph graph{number_vertices, edges};

    std::vector<int> distances_from_source(number_vertices, std::numeric_limits<int>::max());
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
 */
using CostVertexPair = std::pair<int, std::size_t>;

auto SingleSourceShortestPaths_Dijkstra(const WeightedAdjacencyListGraph::RepresentationType &graph,
                                        const std::size_t source) {
    std::vector<int> distances_from_source(graph.size(), std::numeric_limits<int>::max());
    distances_from_source[source] = 0;

    std::vector<int> parents(graph.size(), -1);

    std::priority_queue<CostVertexPair, std::vector<CostVertexPair>, std::greater<CostVertexPair>>
            open_list;
    open_list.emplace(0, source);

    std::vector<bool> closed_vertices(graph.size(), false);

    while (not open_list.empty()) {
        const auto from_vertex = open_list.top().second;
        open_list.pop();

        if (not closed_vertices[from_vertex]) {
            for (const auto &node : graph[from_vertex]) {
                if (Relax(distances_from_source, from_vertex, node.destination, node.weight, &parents)) {
                    open_list.emplace(distances_from_source[node.destination], node.destination);
                }
            }
        }
        std::cout << distances_from_source << std::endl;

        closed_vertices[from_vertex] = true;
    }

    return distances_from_source;
}

/**
 * @reference   Shortest path in a directed graph by Dijkstra’s algorithm
 *              https://www.geeksforgeeks.org/shortest-path-in-a-directed-graph-by-dijkstras-algorithm/
 */
template <typename EdgeArrayType>
inline auto SingleSourceShortestPaths_Dijkstra(const std::size_t number_vertices,
        const EdgeArrayType &edges,
        const std::size_t source) {
    return WeightedAdjacencyListGraph{number_vertices, edges}.Visit([source](const auto & graph) {
        return SingleSourceShortestPaths_Dijkstra(graph, source);
    });
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}};
const auto EXPECTED1 = std::make_pair(true,
std::vector<int> {
    0, -1, 2, -2, 1
});


SIMPLE_BENCHMARK(SingleSourceShortestPaths_BellmanFord, 5, SAMPLE1, 0);

SIMPLE_TEST(SingleSourceShortestPaths_BellmanFord, TestSAMPLE1, EXPECTED1, 5, SAMPLE1, 0);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1, 1}, {1, 2, -1}, {2, 3, -1}, {3, 0, -1}};
const std::unordered_set<std::size_t> EXPECTED2 = {0, 1, 2, 3};


SIMPLE_BENCHMARK(hasNegativeCycle, 5, SAMPLE1);

SIMPLE_TEST(hasNegativeCycle, TestSAMPLE1, false, 5, SAMPLE1);
SIMPLE_TEST(hasNegativeCycle, TestSAMPLE2, true, 4, SAMPLE2);


SIMPLE_BENCHMARK(PrintNegativeWeightCycle, 4, SAMPLE2, 0);

SIMPLE_TEST(PrintNegativeWeightCycle, TestSAMPLE2, EXPECTED2, 4, SAMPLE2, 0);


const DirectedEdgeArrayType SAMPLE3 = {{0, 1, 5}, {0, 2, 3}, {1, 3, 6}, {1, 2, 2}, {2, 4, 4}, {2, 5, 2}, {2, 3, 7}, {3, 4, -1}, {4, 5, -2}};
const std::vector<int> EXPECTED3 = {std::numeric_limits<int>::max(), 0, 2, 6, 5, 3};


SIMPLE_BENCHMARK(SingleSourceShortestPaths_DAG, 6, SAMPLE3, 1);

SIMPLE_TEST(SingleSourceShortestPaths_DAG, TestSAMPLE3, EXPECTED3, 6, SAMPLE3, 1);


const UndirectedEdgeArrayType SAMPLE4 = {{0, 1}, {0, 3}, {1, 2}, {3, 4}, {3, 7}, {4, 5}, {4, 6}, {4, 7}, {5, 6}, {6, 7}};
const ArrayType EXPECTED4 = {0, 3, 7};


SIMPLE_BENCHMARK(SingleSourceShortestPaths_Unweighted_Undirected_BFS, 8, SAMPLE4, 0, 7);

SIMPLE_TEST(SingleSourceShortestPaths_Unweighted_Undirected_BFS, TestSAMPLE4,
            EXPECTED4, 8, SAMPLE4, 0, 7);


const UndirectedEdgeArrayType SAMPLE5 = {{0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11}, {2, 3, 7}, {2, 8, 2}, {2, 5, 4}, {3, 4, 9}, {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1}, {6, 8, 6}, {7, 8, 7}};
const std::vector<int> EXPECTED5 = {0, 4, 12, 19, 21, 11, 9, 8, 14};

const DirectedEdgeArrayType SAMPLE6 = {{0, 1, 1}, {0, 2, 4}, {1, 2, 2}, {1, 3, 6}, {2, 3, 3}};
const std::vector<int> EXPECTED6 = {0, 1, 3, 6};


SIMPLE_BENCHMARK(SingleSourceShortestPaths_Dijkstra, 9, SAMPLE5, 0);

SIMPLE_TEST(SingleSourceShortestPaths_Dijkstra, TestSAMPLE5, EXPECTED5, 9, SAMPLE5, 0);
SIMPLE_TEST(SingleSourceShortestPaths_Dijkstra, TestSAMPLE6, EXPECTED6, 4, SAMPLE6, 0);
