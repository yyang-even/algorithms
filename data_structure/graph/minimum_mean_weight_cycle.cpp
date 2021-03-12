#include "common_header.h"

#include "graph.h"
#include "mathematics/matrix/matrix.h"


using namespace graph;

namespace {

/** Karp’s minimum mean (or average) weight cycle algorithm
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 24-5.
 * @reference   Karp’s minimum mean (or average) weight cycle algorithm
 *              https://www.geeksforgeeks.org/karps-minimum-mean-average-weight-cycle-algorithm/
 *
 * Given a directed and strongly connected graph with non negative edge weighs. We define
 * mean weight of a cycle as the summation of all the edge weights of the cycle divided
 * by the NO. of edges. Our task is to find the minimum mean weight among all the directed
 * cycles of the graph.
 */
auto ShortestPaths(const WeightedAdjacencyListInGraph::RepresentationType &graph) {
    MatrixType shortest_paths(graph.size() + 1, std::vector<int>(graph.size(), -1));
    shortest_paths[0][0] = 0;

    for (std::size_t i = 1; i <= graph.size(); ++i) {
        for (std::size_t j = 0; j < graph.size(); ++j) {
            for (const auto &node : graph[j]) {
                if (shortest_paths[i - 1][node.source] != -1) {
                    const auto current_weight = shortest_paths[i - 1][node.source] + node.weight;
                    if (shortest_paths[i][j] == -1) {
                        shortest_paths[i][j] = current_weight;
                    } else {
                        shortest_paths[i][j] = std::min(shortest_paths[i][j], current_weight);
                    }
                }
            }
        }
    }

    return shortest_paths;
}

auto MinMeanWeightCycle(const std::size_t number_vertices,
                        const DirectedEdgeArrayType &edges) {
    const auto shortest_paths =
        WeightedAdjacencyListInGraph{number_vertices, edges}.Visit(ShortestPaths);

    std::vector<double> means(number_vertices, -1);
    for (std::size_t i = 0; i < number_vertices; ++i) {
        if (shortest_paths[number_vertices][i] != -1) {
            for (std::size_t j = 0; j < number_vertices; ++j) {
                if (shortest_paths[j][i] != -1) {
                    means[i] = std::max(means[i],
                                        (shortest_paths[number_vertices][i] - shortest_paths[j][i]) /
                                        static_cast<double>(number_vertices - j));
                }
            }
        }
    }

    auto result = means[0];
    for (const auto average : means) {
        if (average != -1 and average < result) {
            result = average;
        }
    }

    return result;
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1, 1}, {0, 2, 10}, {1, 2, 3}, {2, 3, 2}, {3, 1, 0}, {3, 0, 8}};


THE_BENCHMARK(MinMeanWeightCycle, 4, SAMPLE1);

SIMPLE_DOUBLE_TEST(MinMeanWeightCycle, TestSAMPLE1, 1.66667, 4, SAMPLE1);
