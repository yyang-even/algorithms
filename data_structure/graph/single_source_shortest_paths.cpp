#include "common_header.h"

#include "graph.h"


namespace {

void Relax(std::vector<int> &distances, std::vector<int> &parents, const DirectedEdge &edge) {
    if (distances[edge.from] != std::numeric_limits<int>::max()) {
        const auto new_weight = distances[edge.from] + edge.weight;
        if (distances[edge.to] > new_weight) {
            distances[edge.to] = new_weight;
            parents[edge.to] = edge.from;
        }
    }
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
