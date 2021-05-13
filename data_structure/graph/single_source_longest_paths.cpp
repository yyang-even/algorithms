#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"


using namespace graph;

namespace {

/** Longest Path in a Directed Acyclic Graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 15-1.
 * @reference   https://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/
 * @reference   Longest Path in a Directed Acyclic Graph | Set 2
 *              https://www.geeksforgeeks.org/longest-path-directed-acyclic-graph-set-2/
 */
auto SingleSourceLongestPaths_DAG(const std::size_t number_vertices,
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
    distances_from_source(number_vertices, std::numeric_limits<int>::min());
    distances_from_source[source] = 0;

    for (auto iter = topological_order.crbegin();
         iter != topological_order.crend();
         ++iter) {
        const auto from = *iter;
        graph.Visit([from, &distances_from_source](const auto & graph) {
            if (distances_from_source[from] != std::numeric_limits<int>::min()) {
                for (const auto &node : graph[from]) {
                    const auto new_weight = distances_from_source[from] + node.weight;
                    if (distances_from_source[node.destination] < new_weight) {
                        distances_from_source[node.destination] = new_weight;
                    }
                }
            }
        });
    }

    return distances_from_source;
}


/**
 * @reference   Longest path in a directed Acyclic graph | Dynamic Programming
 *              https://www.geeksforgeeks.org/longest-path-in-a-directed-acyclic-graph-dynamic-programming/
 *
 * Given a directed graph G with N vertices and M edges. The task is to find the length
 * of the longest directed path in Graph.
 * Note: Length of a directed path is the number of edges in it.
 */
void LengthOfTheLongestPath_Unweighted_DAG_DFS(
    const AdjacencyListGraph::RepresentationType &graph,
    const std::size_t source,
    std::vector<bool> &visited_vertices, ArrayType &longest_paths) {
    visited_vertices[source] = true;

    for (const auto adjacent_vertex : graph.at(source)) {
        if (not visited_vertices[adjacent_vertex]) {
            LengthOfTheLongestPath_Unweighted_DAG_DFS(
                graph, adjacent_vertex, visited_vertices, longest_paths);
        }

        longest_paths[source] =
            std::max(longest_paths[source], 1 + longest_paths[adjacent_vertex]);
    }
}

inline auto
LengthOfTheLongestPath_Unweighted_DAG_DFS(const std::size_t number_vertices,
                                          const DirectedEdgeArrayType &edges) {
    ArrayType longest_paths(number_vertices, 0);

    GraphTraverse(number_vertices, edges,
    [&longest_paths](const auto & graph, const auto source, auto & visited_vertices) {
        LengthOfTheLongestPath_Unweighted_DAG_DFS(
            graph, source, visited_vertices, longest_paths);
        return true;
    });

    return *std::max_element(longest_paths.cbegin(), longest_paths.cend());
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1, 5}, {0, 2, 3}, {1, 3, 6}, {1, 2, 2}, {2, 4, 4}, {2, 5, 2}, {2, 3, 7}, {3, 5, 1}, {3, 4, -1}, {4, 5, -2}};
const std::vector<int> EXPECTED1 = {std::numeric_limits<int>::min(), 0, 2, 9, 8, 10};


THE_BENCHMARK(SingleSourceLongestPaths_DAG, 6, SAMPLE1, 1);

SIMPLE_TEST(SingleSourceLongestPaths_DAG, TestSAMPLE1, EXPECTED1, 6, SAMPLE1, 1);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {2, 1}, {1, 3}, {2, 3}};
const DirectedEdgeArrayType SAMPLE3 = {{0, 2}, {0, 3}, {1, 2}, {1, 3}, {3, 2}, {4, 1}, {4, 2}, {4, 0}};


THE_BENCHMARK(LengthOfTheLongestPath_Unweighted_DAG_DFS, 4, SAMPLE2);

SIMPLE_TEST(LengthOfTheLongestPath_Unweighted_DAG_DFS, TestSAMPLE2, 3, 4, SAMPLE2);
SIMPLE_TEST(LengthOfTheLongestPath_Unweighted_DAG_DFS, TestSAMPLE3, 3, 5, SAMPLE3);
