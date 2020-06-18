#include "common_header.h"

#include "graph.h"


namespace {

using ArrayType = std::vector<std::size_t>;

/** Depth First Search or DFS for a Graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 22.3            .
 * @reference   Depth First Search or DFS for a Graph
 *              https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
 * @reference   Graph implementation using STL for competitive programming | Set 1 (DFS of Unweighted and Undirected)
 *              https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/
 */
void DepthFirstSearch(const AdjacencyListGraph::RepresentationType &graph, const std::size_t vertex,
                      std::vector<bool> &visited_vertices, ArrayType &results) {
    visited_vertices[vertex] = true;
    results.push_back(vertex);

    for (const auto adjacent_vertex : graph.at(vertex)) {
        if (not visited_vertices[adjacent_vertex]) {
            DepthFirstSearch(graph, adjacent_vertex, visited_vertices, results);
        }
    }
}

auto DepthFirstSearch(const AdjacencyListGraph::RepresentationType &graph) {
    ArrayType results;
    std::vector<bool> visited_vertices(graph.size(), false);
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (not visited_vertices[i]) {
            DepthFirstSearch(graph, i, visited_vertices, results);
        }
    }

    return results;
}

auto DepthFirstSearch(const std::size_t number_vertices,
                      const AdjacencyListGraph::EdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(DepthFirstSearch));
}

}//namespace


const AdjacencyListGraph::EdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const ArrayType EXPECTED1 = {0, 1, 2, 3};


SIMPLE_BENCHMARK(DepthFirstSearch, 4, SAMPLE1);

SIMPLE_TEST(DepthFirstSearch, TestSAMPLE1, EXPECTED1, 4, SAMPLE1);
