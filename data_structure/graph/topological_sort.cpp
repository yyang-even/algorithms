#include "common_header.h"

#include "graph.h"


namespace {

/** Topological Sorting
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 22.4.
 * @reference   Topological Sorting
 *              https://www.geeksforgeeks.org/topological-sorting/
 *
 * Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices
 * such that for every directed edge uv, vertex u comes before v in the ordering.
 * Topological Sorting for a graph is not possible if the graph is not a DAG.
 */
void TopologicalSort(const AdjacencyListGraph::RepresentationType &graph,
                     const std::size_t vertex,
                     std::vector<bool> &visited_vertices,
                     AdjacencyListGraph::ArrayType &results) {
    visited_vertices[vertex] = true;

    for (const auto adjacent_vertex : graph.at(vertex)) {
        if (not visited_vertices[adjacent_vertex]) {
            TopologicalSort(graph, adjacent_vertex, visited_vertices, results);
        }
    }

    results.push_back(vertex);
}

auto TopologicalSort(const std::size_t number_vertices,
                     const AdjacencyListGraph::EdgeArrayType &edges) {
    auto results = GraphTraverse(number_vertices, edges, ToLambda(TopologicalSort));

    std::reverse(results.begin(), results.end());
    return results;
}

}//namespace


const AdjacencyListGraph::EdgeArrayType SAMPLE1 = {{5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}};
const AdjacencyListGraph::ArrayType EXPECTED1 = {5, 4, 2, 3, 1, 0};


SIMPLE_BENCHMARK(TopologicalSort, 6, SAMPLE1);

SIMPLE_TEST(TopologicalSort, TestSAMPLE1, EXPECTED1, 6, SAMPLE1);
