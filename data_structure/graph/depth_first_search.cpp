#include "common_header.h"

#include "graph.h"


namespace {

using ArrayType = std::vector<std::size_t>;

template <typename DFS>
auto DepthFirstSearch(const AdjacencyListGraph::RepresentationType &graph, const DFS dfs) {
    ArrayType results;
    std::vector<bool> visited_vertices(graph.size(), false);
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (not visited_vertices[i]) {
            dfs(graph, i, visited_vertices, results);
        }
    }

    return results;
}

/** Depth First Search or DFS for a Graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 22.3.
 * @reference   Depth First Search or DFS for a Graph
 *              https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
 * @reference   Graph implementation using STL for competitive programming | Set 1 (DFS of Unweighted and Undirected)
 *              https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/
 * @reference   Applications of Depth First Search
 *              https://www.geeksforgeeks.org/applications-of-depth-first-search/
 */
void DepthFirstSearch_Recursive(const AdjacencyListGraph::RepresentationType &graph,
                                const std::size_t vertex,
                                std::vector<bool> &visited_vertices, ArrayType &results) {
    visited_vertices[vertex] = true;
    results.push_back(vertex);

    for (const auto adjacent_vertex : graph.at(vertex)) {
        if (not visited_vertices[adjacent_vertex]) {
            DepthFirstSearch_Recursive(graph, adjacent_vertex, visited_vertices, results);
        }
    }
}

auto DepthFirstSearch_Recursive(const std::size_t number_vertices,
                                const AdjacencyListGraph::EdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(
    [](const AdjacencyListGraph::RepresentationType & graph) {
        return DepthFirstSearch(graph, ToLambda(DepthFirstSearch_Recursive));
    });
}


/**
 * @reference   Iterative Depth First Traversal of Graph
 *              https://www.geeksforgeeks.org/iterative-depth-first-traversal/
 */
void DepthFirstSearch_Iterative(const AdjacencyListGraph::RepresentationType &graph,
                                const std::size_t source,
                                std::vector<bool> &visited_vertices, ArrayType &results) {
    std::stack<std::size_t> gray_vertex_stack;
    gray_vertex_stack.push(source);

    while (not gray_vertex_stack.empty()) {
        const auto vertex = gray_vertex_stack.top();
        gray_vertex_stack.pop();

        visited_vertices[vertex] = true;
        results.push_back(vertex);

        for (const auto adjacent_vertex : graph.at(vertex)) {
            if (not visited_vertices[adjacent_vertex]) {
                gray_vertex_stack.push(adjacent_vertex);
            }
        }
    }
}

auto DepthFirstSearch_Iterative(const std::size_t number_vertices,
                                const AdjacencyListGraph::EdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(
    [](const AdjacencyListGraph::RepresentationType & graph) {
        return DepthFirstSearch(graph, ToLambda(DepthFirstSearch_Iterative));
    });
}


/**
 * @reference   Print the DFS traversal step-wise (Backtracking also)
 *              https://www.geeksforgeeks.org/print-the-dfs-traversal-step-wise-backtracking-also/
 */

}//namespace


const AdjacencyListGraph::EdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const ArrayType EXPECTED1 = {0, 1, 2, 3};


SIMPLE_BENCHMARK(DepthFirstSearch_Recursive, 4, SAMPLE1);

SIMPLE_TEST(DepthFirstSearch_Recursive, TestSAMPLE1, EXPECTED1, 4, SAMPLE1);


const AdjacencyListGraph::EdgeArrayType SAMPLE2 = {{1, 0}, {2, 1}, {3, 4}, {4, 0}};
const ArrayType EXPECTED2 = {0, 1, 2, 3, 4};


SIMPLE_BENCHMARK(DepthFirstSearch_Iterative, 5, SAMPLE2);

SIMPLE_TEST(DepthFirstSearch_Iterative, TestSAMPLE2, EXPECTED2, 5, SAMPLE2);
