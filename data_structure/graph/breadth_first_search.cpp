#include "common_header.h"

#include "graph.h"


namespace {

using ArrayType = std::vector<std::size_t>;

/** Breadth First Search or BFS for a Graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 22.2.
 * @reference   Breadth First Search or BFS for a Graph
 *              https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
 */
void BreadthFirstSearch(const AdjacencyListGraph::RepresentationType &graph,
                        const std::size_t source,
                        std::vector<bool> &visited_vertices, ArrayType &results) {
    std::queue<std::size_t> gray_vertex_queue;
    visited_vertices[source] = true;
    gray_vertex_queue.push(source);

    while (not gray_vertex_queue.empty()) {
        const auto vertex = gray_vertex_queue.front();
        results.push_back(vertex);
        gray_vertex_queue.pop();

        for (const auto adjacent_vertex : graph.at(vertex)) {
            if (not visited_vertices[adjacent_vertex]) {
                visited_vertices[adjacent_vertex] = true;
                gray_vertex_queue.push(adjacent_vertex);
            }
        }
    }
}

auto BreadthFirstSearch(const AdjacencyListGraph::RepresentationType &graph,
                        const std::size_t source) {
    ArrayType results;
    std::vector<bool> visited_vertices(graph.size(), false);
    BreadthFirstSearch(graph, source, visited_vertices, results);

    return results;
}

auto BreadthFirstSearch(const std::size_t number_vertices,
                        const AdjacencyListGraph::EdgeArrayType &edges,
                        const std::size_t source) {
    return AdjacencyListGraph(number_vertices, edges).Visit(
    [source](const AdjacencyListGraph::RepresentationType & graph) {
        return BreadthFirstSearch(graph, source);
    });
}

}//namespace


const AdjacencyListGraph::EdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const ArrayType EXPECTED1 = {2, 0, 3, 1};


SIMPLE_BENCHMARK(BreadthFirstSearch, 4, SAMPLE1, 2);

SIMPLE_TEST(BreadthFirstSearch, TestSAMPLE1, EXPECTED1, 4, SAMPLE1, 2);
