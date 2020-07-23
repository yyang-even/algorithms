#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"


using namespace graph;

namespace {

/** Longest Path in a Directed Acyclic Graph
 *
 * @reference   https://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/
 */
auto SingleSourceLongestPaths_DAG(const std::size_t number_vertices,
                                  const DirectedEdgeArrayType &edges,
                                  const std::size_t source) {
    assert(source < number_vertices);

    WeightedAdjacencyListGraph graph{number_vertices, edges};

    ArrayType topological_order;
    graph.Visit([&topological_order](const auto & graph) {
        GraphTraverse(graph,
        [&topological_order](const auto & graph, const auto source, auto & visited_vertices) {
            TopologicalSort(graph, source, visited_vertices, topological_order);
            return true;
        });
    });

    std::vector<int> distances_from_source(number_vertices, std::numeric_limits<int>::min());
    distances_from_source[source] = 0;

    for (auto iter = topological_order.crbegin(); iter != topological_order.crend(); ++iter) {
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

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1,  5}, {0, 2, 3}, {1, 3, 6}, {1, 2, 2}, {2, 4, 4}, {2, 5, 2}, {2, 3, 7}, {3, 5,  1}, {3, 4, -1}, {4, 5, -2}};
const std::vector<int> EXPECTED1 = {std::numeric_limits<int>::min(), 0, 2, 9, 8, 10};


SIMPLE_BENCHMARK(SingleSourceLongestPaths_DAG, 6, SAMPLE1, 1);

SIMPLE_TEST(SingleSourceLongestPaths_DAG, TestSAMPLE1, EXPECTED1, 6, SAMPLE1, 1);
